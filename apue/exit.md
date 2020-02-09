

## 进程终止的方式

Linux 系统一共有 8 种进程终止方式，其中 5 种为正常终止方式：

> 1）从 main() 函数返回；
>
> 2）调用 exit(3) 函数；
>
> 3）调用 _exit(2) 或 _Exit(2) 函数；
>
> 4）最后一个线程从其启动例程返回；
>
> 5）从最后一个线程调用 pthread_exit(3) 函数。

剩下的 3 种为异常终止方式：

> 6）调用 abort(3) 函数；
>
> 7）接收到一个信号；
>
> 8）最后一个线程对取消请求作出响应。

小伙伴们一定要把这八种进程终止方式背下来，对于我们后面学习信号、多进程和多线程是有好处的。



1. 在 main() 函数中执行 return 语句，可以将一个 int 值作为程序的返回值返回给调用者，一般是 shell。返回 0 表示程序正常结束，返回 非零值 表示程序异常结束。
2. 在 main() 函数中执行 return 语句相当于调用 exit(3) 函数，exit(3) 是专门用于结束进程的，它依赖于 _exit(2) 或 _Exit(2) 系统调用。程序中任何地方调用 exit(3) 都会退出，但 return 语句只有在 main() 函数中才能结束进程，在其它函数中执行 return 语句只能退出当前函数。
3. _exit(2) 和 _Exit(2) 函数都是系统调用，在程序中的任何地方调用它们程序都会立即结束。
4. 第 4、5 条 等到讨论线程的时候再说，总之进程就是线程的容器，最后一个线程的退出会导致整个进程的消亡。
5. abort(3) 函数一般用在程序中出现了不可预知的错误时，为了避免异常影响范围扩大，直接调用 abort(3) 函数自杀。实际上 abort(3) 函数也是通过信号实现的。



## exit Functions

* Executing a return from main function.
* Calling the exit function.
* Calling the _exit or _Exit function.
* Executing a return from the start routine of the last thread in the process.
* Calling the pthread_exit function from the last thread in the process.



### calling of exit

`exit` function is defined by ISO C and includes the calling of all exit handlers that have been registered by calling atexit and **closing all standard I/O streams**. ISO C does not deal with file descriptors, multiple processes (parents and children), and job control, the definition of this function is incomplete for a UNIX system.

### calling of _exit or _Exit

ISO C defines _Exit to provide a way for a process to terminate without running exit handlers or signal handlers. Whether standard I/O streams are flushed are flushed depends on the implementation. On UNIX systems,  _Exit and _exit are synonymous and **do not flush standard I/O streams**. The _exit function is called by exit and handles the UNIX system-specific details; _exit is specified by POSIX.1.



## return

return 语句可被用来使正在执行分支程序返回到调用它方法。表示中止当前函数的运行，并将操作权返回给调用者，如果是在main函数中，表示将操作权返回给操作系统。   

return 指令一个是返回一个指定数据给主调函数，另外的一个作用就是 结束 所在函数的执行，return 不是必须要返回一个值。



## exit

exit()函数用于在程序运行的过程中随时结束程序，exit的参数state是返回给操作系统，返回0表示程序正常结束，非0表示程序非正常结束。main函数结束时也会隐式地调用exit函数。exit函数运行时首先会执行由atexit()函数登记的函数，然后会做一些自身的清理工作，同时刷新(flush)所有输出流、关闭所有打开的流并且关闭通过标准I/O函数tmpfile()创建的临时文件。



## Start Routine

每个进程都会有一个返回值的，进程开始时是由系统的一个启动函数掉用了main函数的：   
int nMainRetVal = main(); 
当从main函数退出后，启动函数便调用exit函数，并且把nMainRetVa传递给它。所以，任何时候都会调用exit函数的，正常情况下，main函数不会调用exit函数的，而是由return 0； 返回值给nMainRetVal的，exit再接收这个值作为参数的。所以，正常情况下是以exit(0)退出的。
如果，你程序发生异常，你可以在main函数中调用exit(1)，强制退出程序，强制终止进程。非0表示不正常退出。



## what happens if the parent terminate before the child?

`init` 进程会接替原父进程成为新的父进程。具体方式是每当一个进程退出，内核遍历所有进程，若发现有它的子进程还在运行，就将其父进程id改为1(the process ID of init)。通过这样的方式，内核保证所有的进程都有父进程。



## what happens if the child process terminate before the parent?

对每一个终止的进程，内核保留了一小部分的信息，这些信息包括进程id，进程的终止状态，进程的CPU占用时间。内核丢弃了进程使用的所有内存，关闭打开的文件。父进程可通过`wait`或`waitpid`调用获取这些信息。

在UNIX系统中，当子进程退出，但父进程还没有调用`wait`回收子进程时，就称为`zombie`。





## exit与_exit的区别

在UNIX系统中,   `_exit`  不会将缓冲区内容写回文件(flush)，`exit`则取决于实现。



## 补充理解

可以把子进程当做父进程的一个函数，子进程的返回值可以通过`exit()`返回给父进程。

执行`exit`或`_exit`的效果取决于实现。

在UNIX系统中,   `_exit`  不会将缓冲区内容写回文件(flush)。

如果实现会同时关闭I/O流，那么，文件的内存对象也会被清理。

关闭进程时，一定会关闭文件I/O。

## 实例

### 验证_exit不会刷新缓冲区

```c
#include <stdio.h>
#include <stdlib.h>

int main()
{
  printf("first line\n");
  printf("second line");
  _exit(0);
  // exit(0);
}
```

结果：不输出任何内容

标准输出是行缓冲的，因此在执行`_exit()`前，标准I/O的缓冲并未输出。执行`_exit`，并不刷新缓冲区，因此缓冲区被自动丢弃。





```c
#include "apue.h"

int main(void)
{
    pid_t pid;
    pid = fork();
    if (pid < 0)
        err_sys("fork");
    else if (pid == 0)  // child
    {
        printf("this is _exit test\n");
        printf("_exit printf content in the buffer");
        _exit(0);  // <unistd.h>
    }
    else
    {
        printf("this is exit test\n");
        printf("exit printf content in the buffer");
        exit(0);  // <stdlib.h>
    }
}
```

