![](E:\learn\linux\pictures\exit.png)

从图中可以看出，_exit 函数的作用是：直接使进程停止运行，清除其使用的内存空间，并清除其在内核的各种数据结构；exit 函数则在这些基础上做了一些小动作，在执行退出之前还加了若干道工序。exit() 函数与 _exit() 函数的最大区别在于exit()函数在调用exit  系统调用前要检查文件的打开情况，把文件缓冲区中的内容写回文件。也就是图中的“清理I/O缓冲”。



```c
#include <stdlib.h>
void exit(int status);

#include <unistd.h>
void _exit(int status);
```

函数传入值：status 是一个整型的参数，可以利用这个参数传递进程结束时的状态。一般来说，0表示正常结束；其他的数值表示出现了错误，进程非正常结束。在实际编程时，父进程可以利用wait 系统调用接收子进程的返回值，从而针对不同的情况进行不同的处理。



## 实例

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

