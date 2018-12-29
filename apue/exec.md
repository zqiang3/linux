## exec系列函数 (execl/execlp/execle/execv/execvp)

**头文件**：<unistd.h>

**功能**：用exec函数可以把当前进程替换为一个新进程，且新进程与原进程有相同的PID。 

**原型**：

int execl(const char *path, const char *arg, ...);

int execlp(const char *file, const char *arg, ...);

int execle(const char *path, const char *arg, ..., char * const envp[]);

int execv(const char *path, char *const argv[]);

int execvp(const char *file, char *const argv[]);

**返回值**：成功返回0,失败返回-1 

注：exec系列函数底层都是通过execve系统调用实现 