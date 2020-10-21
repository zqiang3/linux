

## 3. FILE I/O

```c
#include <fcntl.h>
int open(const char *pathname, int oflag, ... /* mode_t mode */ );
  
int create(const char *pathname, mode_t mode);
// Returns: file descriptor if OK, -1 on error
   
#include <unistd.h>
int close(int fields);
// Returns: 0 if OK, -1 on error                                        
off_t lseek(int fields, off+t offset, int whence);
// Returns: new file offset if OK, -1 on error
ssize_t read(int fields, void *buf, size_t nbytes);
// Returns: number of bytes read, 0 if end of file, -1 on error
ssize_t write(int fields, const void *buf, size_t nbytes);
// Returns: number of bytes written if OK, -1 on error

int dup(int fields);Ω
int dup2(int fields, int fields2);
// Both return: new file descriptor if OK, -1 on error
```



## 4. Files and Directories

```c
#include <sys/stat.h>
int stat(const char *restrict pathname, struct stat *restrict buf);
int fstat(int fields, struct stat *buf);
int lstat(const char *restrict pathname, struct stat *restrict buf);
// All three return: 0 if OK, -1 on error
```





## 5. Standard I/O Library

```c
#include <stdio.h>
void setbuf(FILE *restrict fp, char *restrict buf);
int setvbuf(FILE *restrict fp, char *restrict buf, int mode, size_t size);
// Returns: 0 if OK, nonzero on error

int fflush(FILE *fp);
// Returns: 0 if OK, EOF on error

FILE *fopen(const char *restrict pathname, const char *restrict type);
// Returns: file pointer if OK, NULL on error

int fclose(FILE *fp);
// Returns: 0 if OK, EOF on error

int getc(FILE *fp);
int fgetc(FILE *fp);
int getchar(void);

int putc(int c, FILE *fp);
int fputc(int c, FILE *fp);
int putchar(int c);

char *fgets(char *restrict buf, int n, FILE *restrict fp);
char *gets(char *buf);

int fputs(const char *restrict str, FILE *restrict fp);
int puts(const char *str);  // A new line character is appended
```



##  



## 8. Process Control

```c
#include <unistd.h>
pid_t getpid(void);
pid_t getppid(void);
uid_t getuid(void);
uid_t geteuid(void);
gid_t getgid(void);
gid_t getegid(void);

pid_t fork(void);
// Returns: 0 in child, process ID of child in parent, -1 on error

#include <sys/wait.h>
pid_t wait(int *statloc);
pid_t waitpid(pid_t pid, int *statloc, int options);
// Both return: process ID if OK, 0(see later), or -1 on error
int waitid(idtype_t idtype, id_t id, siginfo_t *infop, int options);
// Returns: 0 if OK, -1 on error

pid_t wait3(int *statloc, int options, struct rusage *rusage);
pid_t wait4(pid_t pid, int *statloc, int options, struct rusage *rusage);
// Both return: pocess ID if OK, 0 or -1 on error

#include <unistd.h>
int execl(const char *pathname, const char *arg0, ... /* (char *)0 */);
int execv(const char *pathname, char *const argv[]);
int execle(const char *pathname, const char *arg0, ... /* (char *)0, char *const envp[] */ );
int execve(const char *pathname, char *const argv[], char *const envp[]);
int execlp(const char *filename, const char *arg0, ... /* (char *)0 */ );
int execvp(const char *filename, char *const argv[]);
int fexecve(int fd, char *const argv[], char *const envp[]);
// All seven return: -1 on error, no return on success

int setuid(uid_t uid);
int setgid(gid_t gid);
// Both return: 0 if OK, -1 on error
```

## Interprocess Communication

```c
#include <sys/types.h>
#include <sys/stat.h>
int mkfifo(const char *pathname, mode_t mode);
// Returns: 0 if OK, -1 on error
```

