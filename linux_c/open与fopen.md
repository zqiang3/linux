open和fopen的区别： 前者属于低级IO，后者是高级IO。 前者返回一个文件描述符，后者返回一个文件指针。 前者无缓冲，后者有缓冲。 前者与 read, write 等配合使用， 后者与 fread, fwrite等配合使用。 后者是在前者的基础上扩充而来的，在大多数情况下，用后者 

## open

```c
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
int open(const char *pathname, int flags);
int open(const char *pathname, int flags, mode_t mode);
返回值：成功返回新分配的文件描述符，出错返回-1并设置errno
```

access：访问模式，宏定义和含义如下：

O_RDONLY 1 只读打开

O_WRONLY 2 只写打开

O_RDWR 4 读写打开

还可选择以下模式与以上3种基本模式相与： 

O_CREAT     0x0100   创建一个文件并打开 

O_TRUNC     0x0200   打开一个已存在的文件并将文件长度设置为0，其他属性保持 

O_EXCL      0x0400   文件未使用                                         

O_APPEND    0x0800   追加打开文件                                  

O_TEXT      0x4000   打开文本文件翻译CR-LF控制字符                  

O_BINARY    0x8000   打开二进制字符，不作CR-LF翻译

mode 该参数仅在access=O_CREAT方式下使用，其取值如下： 

S_IFMT      0xF000   文件类型掩码                               

S_IFDIR     0x4000   目录                                       

S_IFIFO     0x1000   FIFO 专用                                  

S_IFCHR     0x2000   字符专用                                   

S_IFBLK     0x3000   块专用                                     

S_IFREG     0x8000   只为0x0000                                 

S_IREAD     0x0100   可读                                       

S_IWRITE    0x0080   可写                                       

S_IEXEC     0x0040   可执行 

## fopen

```c
FILE *fopen(char *filename, char *mode)
```

mode 打开模式：                                                     

r   只读方式打开一个文本文件                                    

rb  只读方式打开一个二进制文件                                  

w   只写方式打开一个文本文件                                    

wb  只写方式打开一个二进制文件                                  

a   追加方式打开一个文本文件                                    

ab  追加方式打开一个二进制文件                                  

r+  可读可写方式打开一个文本文件                                

rb+ 可读可写方式打开一个二进制文件                              

w+  可读可写方式创建一个文本文件                                

wb+ 可读可写方式生成一个二进制文件                              

a+  可读可写追加方式打开一个文本文件                            

ab+ 可读可写方式追加一个二进制文件 

## 区别

以可写的方式fopen一个文件时，如果文件不存在会自动创建，而open一个文件时**必须明确指定O_CREAT**才会创建文件，否则文件不存在就出错返回。  　　

以w或w+方式fopen一个文件时，如果文件已存在就截断为0字节，而open一个文件时必须明确指定O_TRUNC才会截断文件，否则直接在原来的数据上改写。 

## umask

```shell
$ umask
0002
```

用gcc编译生成一个可执行文件时，创建权限是0777，而最终的文件权限是0777 & ∼022 = 0755 

```shell
$ umask 0
```

## close

```c
#include <unistd.h>
int close(int fd);
返回值：成功返回0，出错返回-1并设置errno
```

参数fd是要关闭的文件描述符。需要说明的是，当一个进程终止时，内核对该进程所有尚未关闭的文件描述符调用close关闭，所以**即使用户程序不调用close，在终止时内核也会自动关闭它打开的所有文件**。但是对于一个长年累月运行的程序（比如网络服务器），打开的文件描述符一定要记得关闭，否则随着打开的文件越来越多，会占用大量文件描述符和系统资源。 

由open返回的文件描述符一定是**该进程尚未使用的最小描述符**。由于程序启动时自动打开文件描述符0、1、2，**因此第一次调用open打开文件通常会返回描述符3，再调用open就会返回4**。可以利用这一点**在标准输入、标准输出或标准错误输出上打开一个新文件，实现重定向的功能**。例如，首先调用close关闭文件描述符1，然后调用open打开一个常规文件，则一定会返回文件描述符1，**这时候标准输出就不再是终端，而是一个常规文件了**，再调用printf就不会打印到屏幕上，而是写到这个文件中了。 

```c
int main(int argc,char *argv[])
{
    int fd;

    if(argc < 2)
    {
        printf("./app filename\n");
        exit(1);
    }
    umask(0);//设置权限之前要讲默认权限关闭
    //创建一个文件,以可读可写方式打开,文件的权限为777
    fd = open(argv[1],O_CREAT | O_RDWR,0777);
    printf("%d\n",fd);
    close(fd);

    return 0;
}
```

