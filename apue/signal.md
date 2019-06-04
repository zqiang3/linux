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

## pause

```c
#include <unistd.h>
int pause(void);
// -1, 并将errno设置为EINTR
```



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

struct sigaction {
    void (*sa_handler)(int);
    sigset_t sa_mask;
    int sa_flags;
    void (*sa_sigaction)(int, siginfo_t *, void *);
};
```

sa_handler字段包含了一个信号捕捉函数的地址

sa_mask字段说明了一个信号集，这一信号集添加到信号屏蔽字中。从信号捕捉函数返回时再将进程的信号屏蔽字恢复。在信号处理程序被调用时，操作系统建立的新信号屏蔽字包括正被递送的信号。



进入信号处理函数后，系统自动将当前信号加入到信号屏蔽字，避免被同一信号中断。

可使用sigaction，将想要屏蔽的信号加入到屏蔽信号集，这样，在处理函数中就不会被这些信号中断。从信号处理函数返回后，系统再将这些信号从屏蔽信号集中去除。

## sigsuspend

```c
int sigsuspend(const sigset_t *mask);
// sigsuspend() always returns -1, with errno set to indicate the error(normally, EINTR).
```

sigsuspend()临时用mask代替调用线程的信号屏蔽集，然后将线程挂起，直到有信号投递（信号的动作是触发一个信号处理程序或者是终止进程）。

```
sigsuspend() temporarily replaces the signal mask of the calling
       thread with the mask given by mask and then suspends the thread until
       delivery of a signal whose action is to invoke a signal handler or to
       terminate a process.

If the signal terminates the process, then sigsuspend() does not
       return.  If the signal is caught, then sigsuspend() returns after the
       signal handler returns, and the signal mask is restored to the state
       before the call to sigsuspend().

It is not possible to block SIGKILL or SIGSTOP; specifying these
       signals in mask, has no effect on the thread's signal mask.
```

## abort

```c
#include <stdlib.h>
void abort(void);  // 无返回值
```

APUE: 进程可以捕捉SIGABRT，可在进程终止前由其执行必要的清理操作。如果在信号处理程序中进程并未终止自己，则当信号处理程序返回时，abort终止该进程。



**abort 函数首先解除进程对 SIGABRT 信号的阻止，然后向调用进程发送该信号。**abort 函数会导致进程的异常终止除非 SIGABRT 信号被捕捉并且信号处理句柄没有返回。

**如果 abort 函数导致进程终止，则所有打开的流都将关闭并刷新。**

如果SIGABRT信号被忽略，或被返回的处理程序捕获，则abort（）函数仍将终止进程。 它通过恢复 SIGABRT 的默认配置，然后再次发送信号来做到这一点。

**函数实现**



**函数实现解析**

首先看是否将执行默认动作，若是则冲洗所有标准 I/O 流。这并不等价于对所有打开的流调用 fclose （因为只冲洗，并不关闭它们），但是当进程终止时，系统会关闭所有打开的文件。如果进程捕捉此信号并返回，那么因为进程可能产生了更多的输出，所以再一次冲洗所有的流。不进行冲洗处理的唯一条件是如果进程捕捉此信号，然后调用 _exit 或 _Exit。这种情况下，任何未冲洗的内存中的标准 I/O 缓存都被丢弃。我们假定捕捉此信号，而且 _exit 或 _Exit 的调用者并不想要冲洗缓冲区。



## Linux信号机制分析

软中断信号(signal)用来通知进程发生了异步事件，在软件层次上是对中断机制的一种模拟。在原理上，一个进程收到一个信号与处理器收到一个中断请求可以说是一样的。信号是进程间通信机制中唯一的异步通信机制，一个进程不必通过任何操作来等待信号的到达，进程也不知道信号什么时候到达。

### 信号在目标进程中注册

在进程表的表项中有一个软中断信号域，该域中每一位对应一个信号。内核给一个进程发送信号，是在进程所在的进程表荐的信号域设置对应于该信号上的位。如果信号发送给一个正在睡眠的进程，如果进程睡眠在可被中断的优先级上，则唤醒进程；否则仅设置进程表中信号域相应的位，非典不唤醒进程。如果发送给一个处于可运行状态的进程，则只置相应的域即可。