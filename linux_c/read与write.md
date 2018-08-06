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