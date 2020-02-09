## socket

```c
#include <sys/socket.h>

int socket(int domain, int type, int protocol);
// Returns: file(socket) descriptor if OK, -1 on error
    
int shutdown(int sockfd, int how);
// Returns: 0 if OK, -1 on error
how参数：
  SHUT_RD 读端
  SHUT_WR 写端
  SHUT_RDWR 关闭读端和写端
```

* domain参数

| Domain    | Description          |
| --------- | -------------------- |
| AF_INET   | IPv4 Internet domain |
| AF_INET6  | IPv6 Internet domain |
| AF_UNIX   | UNIX domain          |
| AF_UNSPEC | unspecified          |

* type参数

| Type           | Description                                                  |
| -------------- | ------------------------------------------------------------ |
| SOCK_DGRAM     | fixed-length, connectionless, unreliable messages，默认的protocol是UDP |
| SOCK_RAW       | datagram interface to IP                                     |
| SOCK_SEQPACKET | fixed-length, sequenced, reliable, connection-oriented messages |
| SOCK_STREAM    | sequenced, reliable, bidirectional, connection-oriented byte streams, 默认的protocol是TCP |

* protocol参数

| Protocol     | Description                       |
| ------------ | --------------------------------- |
| IPPROTO_IP   | IPv4                              |
| IPPROTO_IPV6 | IPv6                              |
| IPPROTO_ICMP | Internet Control Message Protocol |
| IPPROTO_RAW  | Raw IP packets protocol           |
| IPPROTO_TCP  | Transmission Control Protocol     |
| IPPROTO_UDP  | User Datagram Protocol            |

## address

```c
struct sockaddr {
  sa_family_t sa_family;
  char sa_data[14];
};

struct in_addr {
  in_addr_t s_addr;
};

struct sockaddr_in {
  sa_family_t sin_family;
  in_prot_t sin_port;
  struct in_addr sin_addr;
};
```

尽管sockaddr_in 和 sockaddr_in6 结构相差较大，但它们均被强制转换成 sockaddr 结构输入到套接字程序中。



## Connection Establishment

###bind

```c
#include <sys/socket.h>
int bind(int sockfd,
        const struct sockaddr *addr,
        socklen_t len);
```

对于因特网域，如果指定IP地址为 **INADDR_ANY** （<netinet/in.h>中定义），套接字端点可以绑定到所有的系统网络接口上。这意味着可以接收这个系统的任何一个网卡的数据包。



```c
int getsockname(int sockfd,
               struct sockaddr* restrict addr,
               socklen_t *restrict alenp);
int getpeername(int sockfd,
               struct sockaddr *restrict addr,
               socklen_t *restrict alenp);
```

###connect

```c
int connect(int sockfd,
           const struct sockaddr *addr,
           socklen_t len);
// Returns: 0 if OK, -1 on error
```

###listen

```c
int listen(int sockfd, int backlog);
// Returns: 0 if OK, -1 on error
```

###accept

```c
int accept(int sockfd,
          struct sockaddr *restrict addr,
          socklen_t *restrict len);
// Returns: file descriptor if OK, -1 on error
```

###init_server

```c
void init_server()
{
  int fd = socket();
  bind();
  listen(fd, ...);
  return fd;
}
```

## Data Transfer

```c
#include <sys/socket.h>

ssize_t send(int sockfd, const void *buf, size_t nbytes, int flags);
ssize_t sendto(int sockfd, const void *buf, size_t nbytes, int flags, const struct sockaddr *destaddr, socklen_t destlen);
ssize_t sendmsg(int sockfd, const struct msghdr *msg, int flags);
// Returns numbers of bytes sent if OK, -1 on error

ssize_t recv(int sockfd, void *buf, size_t nbytes, int flags);
ssize_t recvfrom(int sockfd, void *restrict buf, size_t len, int flags, struct sockaddr *restrict addrlen);
ssize_t recvmsg(int sockfd, struct msghdr *msg, int flags);
```

































