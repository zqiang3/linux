```c
#include <sys/uio.h>
ssize_t readv(int fd, const struct iovec *iov, int iovcnt);
ssize_t writev(int fd, const struct iovec *iov, int iovcnt);
struct iovec {
    void *iov_base;  // starting address
    size_t iov_len;  // number of bytes to transfer
}
```

函数调用成功时返回读、写的总字节数，失败时返回-1并设置相应的errno。

在一次函数调用中，writev以顺序iov[0]、iov[1]至iov[iovcnt-1]从各缓冲区中聚集输出数据到fd，readv则将从fd读入的数据按同样的顺序散布到各缓冲区中，readv总是先填满一个缓冲区，然后再填下一个，因此，writev称为gather output，readv称为scatter input。