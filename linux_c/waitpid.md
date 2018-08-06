## 僵尸进程

系统调用exit后，该进程并非马上消失，而是留下一个叫僵尸进程的数据结构。它放弃了几乎所有的内存空间，没有任何可执行代码，也不能被调度，仅仅在进程列表保留位置，而且不占用任何内存空间。

## 代码示例

```c
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    pid_t pid, pw;
    pid = fork();
    if(pid < 0)
    {
        puts("fork error");
        exit(1);
    }
    else if(pid == 0)
    {
        printf("this is child process, pid: %d\n", getpid());
        sleep(5);
        exit(1);
    }
    else
    {
        pw = wait(NULL);
        printf("catch a child process, pid is %d\n", pw);
    }

    exit(0);
}

```

