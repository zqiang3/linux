## 文件和目录

```c
#include <sys/stat.h>
int stat(const char *restrict pathname, struct stat *restrict buf);
int stat(int fd, struct stat *buf);
int lstat(const char *restrict pathname, struct stat *restrict buf);
// All three return: 0 if OK, -1 on error

int chmod(const char *pathname, mode_t mode);
int fchmod(int fd, mode_t mode);
// Both return: 0 if OK, -1 on error

int chown(const char *pathname, uid_t owner, gid_t group);
int fchown(int fd, uid_t owner, gid_t group);
int lchown(const char *pathname, uid_t owner, gid_t group);
// All three return: 0 if OK, -1 on error
// 设为-1时，不改变其值

int mkdir(const char *pathname, mode_t mode);
int rmdir(const char *pathname);
Both return: 0 if OK, -1 on error

DIR *opendir(const char *pathname);
struct dirent *readdir(DIR *dp);
void rewinddir(DIR *dp);
int closedir(DIR *dp);
long telldir(DIR *dp);
void seekdir(DIR *dp, long loc);

int chdir(const char *pathname);
int fchdir(int fd);
// 0 if OK, -1 on error
```





## 进程控制原语

```c
#include <stdlib.h>
void exit(int status);
void _Exit(int status);
#include <unistd.h>
void _exit(int status);

#include <stdlib.h>
int atexit(void(*func)(void));  // Return: 0 if OK, nonzero on error

#include <stdlib.h>
void *malloc(size_t size);
void *calloc(size_t nobj, size_t size);
void *realloc(void *ptr, size_t newsize);
// All three return: pointer if OK, NULL on error
void free(void *ptr);

#include <sys/wait.h>
pid_t wait(int *statloc);
pid_t waitpid(pid_t pid, int *statloc, int options);
// Both return: process ID if OK, 0, or -1 on error
```

## 线程

```c
#include <pthread.h>

pthread_t pthread_self(void);  // Returns: the thread ID of the calling thread
int pthread_equal(pthread_t tid1, pthread_t pid2);

int pthread_create(pthread_t *restrict tidp, const pthread_attr_t *restrict attr, void *(*start_rin)(void *), void *restrict arg);  
void pthread_exit(void *rval_ptr);
int pthread_join(pthread_t thread, void **rval_ptr);  
int pthread_cancel(pthread_t tid);
// Return: 0 if OK, error number on failure

void pthread_cleanup_push(void (*rtn)(void *), void *arg);
void pthread_cleanup_pop(int execute);

int pthread_mutex_init(pthread_mutex_t *restrict mutex, const pthread_mutexattr_t *restrict attr);
int pthread_mutex_destroy(pthread_mutex_t *mutex);
int pthread_mutex_lock(pthread_mutex_t *mutex);
int pthread_mutex_trylock(pthread_mutex_t *mutex);
int pthread_mutex_unlock(pthread_mutex_t *mutex);
// Both return: 0 if OK, error number on failure
```

## signal

```c
#include <signal.h>

void (*signal(int signo, void (*func)(int))) (int);
// Returns: previous disposition of signal if OK, SIG_ERR on error

int kill(pid_t pid, int signo);
int raise(int signo);
// Both return: 0 if OK, -1 on error

unsigned int alarm(unsigned int sec);
// Returns: 0 or number of seconds until previously set alarm
int pause(void);  // Returns: -1 with errno set to EINTR
// Returns: pid or 0 if OK, -1 on error
```

## 高级内存分配

```c
#include <stdlib.h>
void *malloc(size_t size);  
void *calloc(size_t nr, size_t size); 
void *realloc(void *ptr, size_t size);
 // Both three return: NULL on error
void free(void *ptr);

#include <unistd.h>
int brk(void *end);  // Returns: 0 if OK, -1 on error
void *sbrk(intptr_t increment);

#include <sys/mman.h>
void *mmap(void *start, size_t len, int prot, int flags, int fd, off_t offset);
int munmap(void *start, size_t len);
```
