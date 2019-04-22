## read/write
传统的read/write方式进行文件到socket的传输，流程是比较复杂的，其细节如下：
1. 调用read函数，文件数据被copy到内核缓冲区
2. read函数返回，数据从内核缓冲区copy到用户缓冲区
3. write函数调用，将数据从用户缓冲区copy到内核与socket相关的缓冲区
4. 数据从socket缓冲区copy到相关协议引擎

上面的步骤有4次上下文切换
1. 系统调用read()产生一个上下文切换：user mode -> kernel mode
2. read()调用返回，又产生一个上下文切换：kernel mode -> user mode
3. write()产生一个上下文切换：user mode -> kernel mode
4. write()返回，产生一个上下文切换：kernel mode -> user mode

使用传统的方式进行网络文件传输，文件数据实际上经过了四次copy的操作：
硬盘->内核buf->用户buf->socket相关缓冲区->协议引擎

## sendfile
```c
#include <sys/sendfile.h>
ssize_t sendfile(int out_fd, int in_fd, off_t *offset, size_t count);
```



sendfile系统调用提供了一种减少多次copy，提升文件传输性能的方法。sendfile系统调用是在2.1版本内核时引进的。
流程如下：

1. 调用sendfile，文件数据被copy到内核缓冲区
2. 从内核缓冲区copy至内核socket相关的缓冲区
3. 最后由socket相关缓冲区copy到协议引擎

在内核版本2.4之后，文件描述符结果被改变，sendfile实现了更简单的方式，系统调用方式仍然一样，细节与2.1版本的 不同之处在于，当文件数据被复制到内核缓冲区时，不再将所有数据copy到socket相关的缓冲区，而是仅仅将记录数据位置和长度相关的数据保存到 socket相关的缓存，而实际数据将由DMA模块直接发送到协议引擎，再次减少了一次copy操作。
