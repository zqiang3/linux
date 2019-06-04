```c
#include <unistd.h>
int pipe(int fd[2]);  // Returns: 0 if OK, -1 on error
FILE *popen(const char *command, const char *type);  // Returns: file pointer if OK, NULL on error
int pclose(FILE *stream);  // Returns: termination status of shell or -1 on error
```



# 4 Pipes and FIFOs

