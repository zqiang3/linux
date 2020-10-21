##  文件和目录

```c


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

```c
#include <fcntl.h>
int fcntl(int filedes, int cmd, ... /* struct flock *flockptr */);  // 出错返回-1
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



```

## Process Control

### Changing User IDs and Group IDs

rules:

1. 如果进程有超级用户权限（进程的real user id是super uid），将real user id, effective user id saved set-user-id设为uid
2. 如果没有超级用户权限，但是文件的uid等于进程的real user id或者是saved set-user-id，则只将有效用户id设为uid。
3. 如果上述两种情况都不符合，则返回-1, 并将errno 设为EPERM



内核维护的id说明：

1. 只有超级用户权限的进程可以修改real user id。real user id是在login的时候设置的。意思是，登录的时候，你是哪个用户，real user id就是谁。比如，你登录用zhangqiang, 则real user id就是对应zhangqiang这个用户的id。
2. 有效用户id可以由exec函数设置（在程序文件设置set-user-id位设置的情况）。如果该位没设置，euid保留为现在的值。可以通过调用 setuid来设置euid为ruid或saved set-uset-id。不能随意改变euid的值。
3. saved set-user-id是由exec从euid拷贝的。如果文件的set-user-id位设置了，

### user id和group id分类

user id 分为

1) real user id

2) effective user id

3) sticky user id

group id 也类似分为：

1) real group id 

2) effective group id 

3) sticky group id

RUID 是进程创建者的user id，只有root用户可以修改

euid是进程执行过程中实际拥有哪个有效用户的权限，这个用户的user id就是euid

suid是程序属主的user id, 设置sticky位之后，当执行这个程序时，不管执行者的uid是多少，euid都会变成那个程序属主的uid

你以什么身份执行一个程序，这个进程就属于谁，这个相当容易理解。

set-user-ID位被设置，也就是文件权限位第三位是s的时候 ，exec会把进程的effective user id设置为文件所有者ID



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
