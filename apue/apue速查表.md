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

```c
#include <sys/wait.h>
pid_t wait(int *statloc);
pid_t waitpid(pid_t pid, int *statloc, int options);
// Both return: process ID if OK, 0, or -1 on error
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
```

