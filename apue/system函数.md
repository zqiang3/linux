## 标准库说明

**头文件**

<unistd.h>

**函数定义**

```c
#include <unistd.h>
int system(const char* string)
```

## 函数说明

曾经的曾经，被system()函数折磨过，之所以这样，是因为对system()函数了解不够深入。只是简单的知道用这个函数执行一个系统命令，这远远不够，它的返回值、它所执行命令的返回值以及命令执行失败原因如何定位，这才是重点。

system() executes a command specified in command by calling /bin/sh -c command, and returns after the command has been completed. During execution of the command, SIGCHLD will be blocked, and SIGINT and SIGQUIT will be ignored.

system() 函数会调用fork()产生子进程，由子进程来调用/bin/sh-c string来执行参数string字符串所代表的命令。/bin/sh 一般是一个软连接，指向某个具体的shell，比如bash，-c选项是告诉shell从字符串command中读取命令； 在该command执行期间，SIGCHLD是被阻塞的，好比在说：hi，内核，这会不要给我送SIGCHLD信号，等我忙完再说； 在该command执行期间，SIGINT和SIGQUIT是被忽略的，意思是进程收到这两个信号后没有任何动作。

实际上system()函数执行了三步操作：

1. fork一个子进程

2. 在子进程中调用exec函数去执行command

3. 在父进程中调用wait去等待子进程结束


## 示例

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void check_error_system(const char *cmd);

int main()
{
    check_error_system("mkdir $HOME/smartdir");
    check_error_system("mkdir $HOME/smartdir/files");
    check_error_system("cp test.c $HOME/smartdir/files");
}

void check_error_system(const char *cmd)
{
    int ret;
    ret = system(cmd);
    if(ret < 0)
    {
        perror("system error");
        exit(1);
    }
}
```



## 源码

```c
int system(const char * cmdstring) 
{ 
　　pid_t pid; 
　　int status; 
　　if(cmdstring == NULL) 
　　{ 
　　　　return (1); //如果cmdstring为空，返回非零值，一般为1 
　　} 
　　if((pid = fork())<0) 
　　{ 
 　　　　status = -1; //fork失败，返回-1 
　　} 
　　else if(pid == 0) 
　　{ 
　　　　execl("/bin/sh", "sh", "-c", cmdstring, (char *)0); 
　　　　_exit(127); // exec执行失败返回127，注意exec只在失败时才返回现在的进程，成功的话现在的进程就不存在啦~~ 
　　} 
　　else //父进程 
　　{ 
　　　　while(waitpid(pid, &status, 0) < 0) 
　　　　{ 
　　　　　　if(errno != EINTR) 
　　　　　　{ 
　　　　　　　　status = -1; //如果waitpid被信号中断，则返回-1 
　　　　　　　　break; 
　　　　　　} 
　　　　} 
　　} 
　　return status; //如果waitpid成功，则返回子进程的返回状态 
} 
```

## 参考链接

https://www.cnblogs.com/tdyizhen1314/p/4902560.html