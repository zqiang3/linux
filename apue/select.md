## 链接

<http://man7.org/linux/man-pages/man2/select.2.html>

## DESCRIPTION

select() and pselect() allow a program to monitor multiple file descriptors, waiting until one or more of the file descriptors become "ready" for some class of I/O operation (e.g., input possible). A file descriptor is considered ready if it is possible to perform a corresponding I/O operation without blocking.

select() can monitor only file descriptors numbers that are less than FD_SETSIZE; poll(2) does not have this limitation.

## SYNOPSIS

```c
int select(int nfds, fd_set *rdfds, fd_set *wtfds, fd_set *exfds, struct timeval *timeout)
// Returns: number of file descriptors ready, -1 on error, 0 if the timeout expires
```

1. ndfs：select中监视的文件句柄数，一般设为要监视的文件中的最大文件号加一。 
2. rdfds：select（）监视的可读文件句柄集合
3. wtfds: select（）监视的可写文件句柄集合
4. exfds：select（）监视的异常文件句柄集合，当exfds映象的文件句柄上有特殊情况发生时系统会告诉select函数返回。 
5. timeout：select（）的超时结束时间。 
6. select每次返回都会改变文件句柄集

## 处理函数

```c
FD_ZERO(fd_set *set)  清除一个文件描述符集 
FD_SET(int fd,fd_set *set)  将一个文件描述符加入文件描述符集中 
FD_CLR(int fd,fd_set *set)  将一个文件描述符从文件描述符集中清除 
FD_ISSET(int fd,fd_set *set)  测试该集中的一个给定位是否有变化 

```



## timeout

这个参数使select处于三种状态

1. 第一，若将NULL以形参传入，即不传入时间结构，就是将select置于阻塞状态， 一定等到监视文件描述符集合中某个文件描述符发生变化为止； 
2. 第二，若将时间值设为0秒0毫秒，就变成一个纯粹的非阻塞函数，不管文件描述符是否有变化， 都立刻返回继续执行，文件无变化返回0，有变化返回一个正值； 
3. 第三，timeout的值大于0，这就是等待的超时时间，即select在timeout时间内阻塞， 超时时间之内有事件到来就返回了，否则在超时后不管怎样一定返回，返回值同上述。 
4. 注意当每次循环执行到select时，原来tv的值会被清零，必须重新设置

