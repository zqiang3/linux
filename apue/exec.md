## exec系列函数 (execl/execlp/execle/execv/execvp)

**头文件**：<unistd.h>

**功能**：用exec函数可以把当前进程替换为一个新进程，且新进程与原进程有相同的PID。 

**原型**：

```c
#include <unistd.h>

int execl(const char *path, const char *arg0, ... /* (char *)0 */ );
int execv(const char *path, char *const argv[]);
int execle(const char *path, const char *arg, ... /* (char *)0, char *const envp[] */ );

int execlp(const char *file, const char *arg0, ... /* (char *)0 */ );
int execvp(const char *file, char *const argv[]);
int execve(const char *file, char *const argv[], char *const envp[]);
// All six return -1 on error, no return on success
```

**返回值**：

注：exec系列函数底层都是通过execve系统调用实现 