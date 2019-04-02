## fork函数

调用一次，返回两次。在子进程中返回0，父进程中返回新子进程的进程ID。

## 为什么要将子进程ID返回给父进程？

理由是，父进程可能有多个子进程，没有一个系统调用可直接获得子进程ID。而子进程只有唯一的父进程，可通过getppid()获得父进程ID。

## 写时复制

父子进程共享数据段，堆，栈的内存区域，并将这些区域的访问权限修改为只读的。如果父子进程任一个试图修改某块数据，则只为修改区域对应的内存制作一个副本。

## 执行顺序

在fork调用之后，父子进程的执行顺序并不确定，这取决于内核的调度算法。如果要求父子进程之间相互同步，则需要某种形式的进程间通信。

## 程序示例

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int stable = 88;

char buf[] = "write to stdout\n";

int main(int argc, char *argv[])
{
    int var = 1;

    write(STDOUT_FILENO, buf, sizeof(buf - 1));  // sizeof(buf)包含\0

    pid_t pid;
    if(fork() == 0)
    {
        var++;
        stable++;
    }
    else
    {
        sleep(2);
    }

    printf("var=%d, stable=%d\n", var, stable);

    exit(0);
    
}
```

## vfork

vfork与fork都创建一个子进程，在子进程调用exec或exit之前，它在父进程的地址空间中运行。

vfork保证子进程先运行，在子进程调用exec或exit之后父进程才能被调度。

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int stable = 88;

char buf[] = "write to stdout\n";

int main(int argc, char *argv[])
{
    int var = 1;

    write(STDOUT_FILENO, buf, sizeof(buf)-1);
    printf("parent pid = %d\n", getpid());
    printf("before vfork\n");

    pid_t pid;
    if(vfork() == 0)
    {
        printf("child pid = %d\n", getpid());
        var++;
        stable++;
        _exit(0);
    }

    printf("continue parent\n");
    printf("var=%d, stable=%d\n", var, stable);

    exit(0);
    
}
```

## 父进程终止时，子进程由init进程领养

操作过程大致如下：在一个进程终止时，内核逐个检查所有的活动进程，若发现一个进程是正要终止进程的子进程，则将该进程的父进程ID修改为1。

当子进程终止时，内核为每个终止子进程保存了少量的信息，父进程可通过wait或waitpid获取这些信息。这些信息至少包括进程ID，进程的终止状态，进程的CPU运行时间。

## 僵死进程

进程已终止，但其父进程尚未对其做善后处理的进程称为僵死进程(zombie)。ps命令将僵死进程的状态打印为Z。