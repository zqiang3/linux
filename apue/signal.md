信号是软件中断。

<signal.h>

信号被定义为整数，不存在值为0的信号，0在kill()中在特殊的含义。

**信号的产生**

1. 按下某些终端键时，会产生信号。如Ctrl+C产生SIGINT信号
2. 硬件异常产生信号。如除数为0。这些条件通常由硬件检测到，并通知给内核，内核给相应的进程产生适当的信号。
3. 可以用kill命令发送信号。
4. 某些软件条件也可产生信号。如SIGPIPE（管道的读进程终止后，一个进程往管道写数据时产生），SIGALRM

信号是异步事件。

信号可在任意时刻出现，因此应告诉内核，在信号发生时，执行某些操作。

**信号的处理**

1. 忽略此信号。但SIGSTOP和SIGKILL不能被忽略。

2. 执行默认动作。

3. 捕捉信号，执行特定的信号处理函数。


常用的信号

SIGABRT, SIGALRM, SIGCANCEL, SIGCHLD, SIGINT, SIGKILL, SIGPIPE, SIGQUIT, SIGSTOP, SIGTERM, SIGUSR1, SIGUSR2

SIGINT: 当用户按中断键时（一般采用DELETE或Ctrl+C时，终端驱动程序产生此信号并送至前台进程组中的每一个进程。当一个进程在运行时失控，特别是它在屏幕上产生大量不必要的输出时，常用此信号终止它。

SIGQUIT: 在终端上按退出键（Ctrl+\）时，产生此信号。此信号不仅会终止前台进程组，同时会产生一个core文件

SIGTSTP: 交互式停止信号，在终端上按挂起键（Ctrl+Z）时，终端驱动程序产生此信号，该信号发送至前台进程组中的所有进程。

## signal

```c
typedef void Sigfunc(int);
Sigfunc *signal(int, Sigfunc *);
// 出错返回SIG_ERR， 成功返回信号之前的处理函数

#define SIG_ERR (void (*)())-1
#define SIG_DFL (void (*)())0
#define SIG_IGN (void (*)())1
```

## 中断的系统调用

系统调用分为两类：低速系统调用和其他系统调用。低速系统调用是可能会使进程记过阻塞的一类系统调用，它们包括：

* 读某些类型的文件（管道、终端设备以及网络设备），如果数据不存在可能会使调用者永远阻塞
* 在写这些类型的文件时，如果不能立即接收这些数据，可能使调用者永远阻塞
* 打开某些类型的文件，在某个条件发生前也可能会使调用者一直阻塞
* pause和wait函数
* 某些ioctl函数
* 某些进程间通信函数

假设一个读操作，它被中断，我们希望重新启动它

```c
again:
	if ((n = read(fd, buf, BUFFSIZE)) < 0)
    {
        if (errno == EINTR)
            goto again;
    }
```

为了方便应用程序不必处理被中断的系统调用，BSD引入了某些中断的系统调用的自动重启动。自动重启动的系统调用包括ioctl, read, readv, write, writev, wait和waitpid

## 可重入函数

造成函数不可重入的原因：(a) 已知它们使用静态数据结构，(b) 它们调用malloc或free (c) 它们是标准I/O函数。标准I/O库的很多实现都以不可重入方式使用全局数据结构。

本书中在信号处理程序中调用的printf函数，但这并不保证所期望的结果，信号处理程序可能中断主程序中的printf函数调用。

信号处理程序有可能改变errno变量

## kill和raise函数

```c
#include <signal.h>
int kill(pid_t pid, int signo);
int raise(int signo);
// 成功返回0，出错返回-1
```

1. pid>0 将信号发送给进程ID为pid的进程
2. pid==0 将该信号发送给与发送进程同一进程组的“所有进程”，并且发送进程有权限。这里的“所有进程”不包括系统进程集。对于大多数UNIX系统，系统进程集包括内核进程集以及init（pid 1）。
3. pid < 0 将信号发送给进程组ID等于pid绝对值的进程，并且发送进程有权限，不包括系统进程集。
4. pid == -1 将信号发送给有权限发送信号的所有进程，不包括系统进程集。

进程将信号发送给其他进程需要权限。超级用户可将信号发送给任一进程。非超级用户，基本规则是发送者的实际或有效用户ID必须等于接收者的实际或有效用户ID。如果支持_POSIX_SAVED_IDS，则检查接收者的设置用户ID（而不是有效用户ID）。

编号为0的信号定义为空信号，如果signo是0，则kill仍执行正常的错误检查，但不发送信号。这常被用来确定一个特定进程是否仍旧存在。如果向一个并不存在的进程发送空信号，kill返回-1并将errno设置为ESRCH。

应该注意的是，使用kill进行这种测试并不是原子操作，在kill向调用者返回测试结果时，被测试的进程此时可能已经终止，所以这种测试并无多大价值。

kill在返回之前，就将signo或其他未决的非阻塞信号传送至该进程。

## 信号集

```c
#include <signal.h>
int sigemptyset(sigset_t *set);
int sigfillset(sigset_t *set);
int sigaddset(sigset_t *set, int signo);
int sigdelset(sigset_t *set, int signo);
// 成功返回0，出错返回-1
int sigismember(const sigset_t *set, int signo);
// 若真返回0，若假返回0，出错返回-1
```

## sigprocmask

```c
int sigprocmask(int how, const sigset_t *restrict set, sigset_t *restrict oset);
// 成功返回0，出错返回-1
```

SIG_BLOCK 当前信号屏蔽字和set的并集

SIG_UNBLOCK set解除阻塞的信号

SIG_SETMASK 设置新的信号屏蔽字

在调用sigprocmask后如果有任何未决的、不再阻塞的信号，在sigprocmask返回前，至少会将其中一个信号递送给该进程。

## sigpending

```c
int sigpending(sigset_t *set);
// 成功返回0，出错返回-1
```

## sigaction

```c
int sigaction(int signo, const struct sigaction *restrict act, struct sigaction *restrict oact);
// 成功返回0，出错返回-1
```

