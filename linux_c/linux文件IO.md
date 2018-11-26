## 示例

```c
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

char *filename = "foo.txt";
int fd;
fd = open(filename, O_RDONLY | O_CREAT, 0666);
fd = open("temp.txt", O_RDONLY | O_CREAT | O_EXCL, 0666);  # 测试O_EXCL
fd = open(filename, O_RDONLY | O_TRUNC, 0666);  # 测试O_TRUNC标志位
if (fd < 0)
{
    perror("open");
    exit(1);
}
```

## open

```c
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

int open( const char * pathname, int flags);
int open( const char * pathname,int flags, mode_t mode);
```

**flags**

1. O_RDONLY 以只读方式打开文件
2. O_WRONLY 以只写方式打开文件
3. O_RDWR 以可读写方式打开文件。上述三种旗标是互斥的，也就是不可同时使用，但可与下列的旗标利用OR(|)运算符组合。
4. O_CREAT 若欲打开的文件不存在则自动建立该文件。
5. O_EXCL 如果O_CREAT也被设置，此指令会去检查文件是否存在。文件若不存在则建立该文件，否则将导致打开文件错误。此外，若O_CREAT与O_EXCL同时设置，并且欲打开的文件为符号连接，则会打开文件失败。
6. O_TRUNC 若文件存在并且以可写的方式打开时，此旗标会令文件长度清为0，而原来存于该文件的资料也会消失。
7. O_APPEND 当读写文件时会从文件尾开始移动，也就是所写入的数据会以附加的方式加入到文件后面。
8. O_NONBLOCK 以不可阻断的方式打开文件，也就是无论有无数据读取或等待，都会立即返回进程之中。
9. O_NDELAY 同O_NONBLOCK。

**文件描述符**

open 返回的文件描述符一定是最小的未被使用的描述符。

**文件权限**

创建文件时的权限会受到umask 值所影响, 因此该文件权限应该为 (mode-umaks).

## read

```c
ssize_t read(int fd, void * buf, size_t count);
```

**说明**

read()会把参数fd所指的文件传送count 个字节到buf 指针所指的内存中 

**返回值**

返回值为实际读取到的字节数, 如果返回0, 表示已到达文件尾或是无可读取的数据。若参数count 为0, 则read()不会有作用并返回0 



## write

```c
ssize_t write (int fd, const void * buf, size_t count);
```

**说明**

write()会把参数buf所指的内存写入count个字节到参数放到所指的文件内 

**返回值**

如果顺利write()会返回实际写入的字节数。当有错误发生时则返回-1，错误代码存入errno中 

## 示例

```c
#include <stdio.h>
#include <unistd.h>
#define MAX 1000

int main(int argc, char *argv[])
{
    char buf[MAX];
    int n;
    while( (n = read(STDIN_FILENO, buf, MAX)) > 0)
        write(STDOUT_FILENO, buf, n);     
    
    return 0;
}
```
## truncate
```c
int truncate(const char *path, off_t len);
```
