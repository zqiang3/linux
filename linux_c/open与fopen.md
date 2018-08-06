open和fopen的区别： 前者属于低级IO，后者是高级IO。 前者返回一个文件描述符，后者返回一个文件指针。 前者无缓冲，后者有缓冲。 前者与 read, write 等配合使用， 后者与 fread, fwrite等配合使用。 后者是在前者的基础上扩充而来的，在大多数情况下，用后者 

## open

```c
int open(const char *path, int access, int mode);
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