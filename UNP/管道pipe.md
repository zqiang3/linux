# pipe

## 1概念

管道是一种最基本的IPC机制，作用于有血缘关系的进程之间。调用pipe系统函数可创建一个管道。

**特性**

1. 本质是一个伪文件（内核缓冲区）
2. 由两个文件描述符引用，一个为读端，一个为写端。
3. 数据从写端注入，从读端流出。

**局限性**

1. 数据自己读不能自己写
2. 不可反复读到，数据一旦读走就不在了
3. 半双工通信，数据只在单方向流动
4. 只能在公共祖先的进程间使用

## 原理

管道是内核使用环形队列在内核缓冲区（4k大小）实现。

## pipe

1. 父进程调用pipe函数创建管道，得到两个文件描述符，分别指向管道的读端和写端。
2. 调用fork创建子进程，子进程拥有同样的读写文件描述符
3. 父进程关闭管道读端，子进程关闭管道写端。数据从读端流入管道，从写端流出，这样就实现了进程间通信。

## 管道的读写分析

假设都是阻塞I/O操作，没有设置O_NONBLOCK标志

1. 如果所有指向管道写端的文件描述符都关闭了（管道写端引用计数为0），而仍然有进程从管道的读端读数据，那么管道中剩余的数据都被读取后，再次read会返回0，就像读到文件末尾一样。
2. 如果有指向管道写端的文件描述符没关闭（管道写端引用计数大于0），而持有管道写端的进程也没有向管道中写数据，这时有进程从管道读端读数据，那么管道中剩余的数据都被读取后，再次read会阻塞，直到管道中有数据可读了才读取数据并返回。
3. 如果所有指向管道读端的文件描述符都关闭了（管道读端引用计数为0），这时有进程向管道的写端write，那么该进程会收到信号SIGPIPE，通常会导致进程异常终止。当然也可以对SIGPIPE信号实施捕捉，不终止进程。
4. 如果有指向管道读端的文件描述符没关闭（管道读端引用计数大于0），而持有管道读端的进程也没有从管道中读数据，这时有进程向管道写端写数据，那么在管道被写满时再次write会阻塞，直到管道中有空位置了才写入数据并返回。





# FIFO

**FIFO的打开规则**

a FIFO for reading normally blocks until some other process opens the same FIFO for writing, and vice versa.

如果当前打开操作是为读而打开FIFO时，若已经有相应进程为写而打开该FIFO，则当前打开操作将成功返回；否则，可能阻塞直到有相应进程为写而打开该FIFO（当前打开操作设置了阻塞标志）；或者，成功返回（当前打开操作没有设置阻塞标志）。 

如果当前打开操作是为写而打开FIFO时，如果已经有相应进程为读而打开该FIFO，则当前打开操作将成功返回；否则，可能阻塞直到有相应进程为读而打开该FIFO（当前打开操作设置了阻塞标志）；或者，返回ENXIO错误（当前打开操作没有设置阻塞标志）。 

**阻塞问题**

对于以只读方式（O_RDONLY）打开的FIFO文件，而且open调用是阻塞的（即第二个参数为O_RDONLY），除非有一个进程以写方式打开同一个FIFO，否则它不会返回；如果open调用是非阻塞的的（即第二个参数为O_RDONLY | O_NONBLOCK），则即使没有其他进程以写方式打开同一个FIFO文件，open调用将成功并立即返回。

对于以只写方式（O_WRONLY）打开的FIFO文件，而且open调用是阻塞的（即第二个参数为O_WRONLY），open调用将被阻塞，直到有一个进程以只读方式打开同一个FIFO文件为止；如果open调用是非阻塞的（即第二个参数为O_WRONLY | O_NONBLOCK），open总会立即返回，但如果没有其他进程以只读方式打开同一个FIFO文件，open调用将返回-1，并且FIFO也不会被打开。

## 查看PIPE_BUF

```c
ulimit -a
core file size          (blocks, -c) 0
data seg size           (kbytes, -d) unlimited
scheduling priority             (-e) 0
file size               (blocks, -f) unlimited
pending signals                 (-i) 7975
max locked memory       (kbytes, -l) 64
max memory size         (kbytes, -m) unlimited
open files                      (-n) 65535
pipe size            (512 bytes, -p) 8
POSIX message queues     (bytes, -q) 819200
real-time priority              (-r) 0
stack size              (kbytes, -s) 8192
cpu time               (seconds, -t) unlimited
max user processes              (-u) 7975
virtual memory          (kbytes, -v) unlimited
file locks                      (-x) unlimited
```

## 写入管道

链接：<https://blog.csdn.net/xiangguiwang/article/details/80716181>

 POSIX.1规定当写入管道的长度小于PIPE_BUF字节时必须是原子的：即写入数据作为连续序列写入管道。 超过PIPE_BUF字节的写入可能是非原子的：内核可能会将数据与其他进程写入的数据交错。 POSIX.1要求PIPE_BUF至少为512字节。(在Linux上，PIPE_BUF为4096字节）。在实践中取决于文件描述符是否为非阻塞（O_NONBLOCK），管道中是否有多个写入器，以及n要写入的字节数：

情况1：O_NONBLOCK disabled, n <= PIPE_BUF

    所有n个字节都以原子方式写入; write可能会阻止如果没有空间来立即写入n个字节。

情况2：O_NONBLOCK enabled, n <= PIPE_BUF

    如果有空间向管道写入n个字节，则立即write成功，写入全部n个字节; 否则失败，并将errno设置为EAGAIN。

情况3：O_NONBLOCK disabled, n > PIPE_BUF
    写入是非原子化的：write的数据可能会被写入（2）与其他进程交错; write阻塞，直到写入了n个字节。

情况4：O_NONBLOCK enabled, n > PIPE_BUF

​    如果管道已满，则写入（2）失败，并将errno设置为EAGAIN。 否则，可能会写入1到n个字节（即可能发生“部分写入”;调用者应该检查write（2）的返回值以查看实际写入的字节数），并且可以将这些字节与其他进程写入。