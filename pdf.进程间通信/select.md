提供屏蔽和解除屏蔽信号的功能，从而实现关键代码的运行不被打断。

```c
int select(int nfds, fd_set *rdfds, fd_set *wtfds, fd_set *exfds, struct timeval *timeout)
```

1. ndfs：select中监视的文件句柄数，一般设为要监视的文件中的最大文件号加一。 
2. rdfds：select（）监视的可读文件句柄集合，当rdfds映象的文件句柄状态变成可读时系统告诉select函数返回。 
3. wtfds: select（）监视的可写文件句柄集合，当wtfds映象的文件句柄状态变成可写时系统告诉select函数返回。 
4. exfds：select（）监视的异常文件句柄集合，当exfds映象的文件句柄上有特殊情况发生时系统会告诉select函数返回。 
5. timeout：select（）的超时结束时间。 

## timeout

这个参数使select处于三种状态

1. 第一，若将NULL以形参传入，即不传入时间结构，就是将select置于阻塞状态， 一定等到监视文件描述符集合中某个文件描述符发生变化为止； 
2. 第二，若将时间值设为0秒0毫秒，就变成一个纯粹的非阻塞函数，不管文件描述符是否有变化， 都立刻返回继续执行，文件无变化返回0，有变化返回一个正值； 
3. 第三，timeout的值大于0，这就是等待的超时时间，即select在timeout时间内阻塞， 超时时间之内有事件到来就返回了，否则在超时后不管怎样一定返回，返回值同上述。 

