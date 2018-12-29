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

