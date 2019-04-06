实际用户ID：登录用户的uid

有效用户ID：进程根据有效用户ID决定对资源的访问权限。一般情况下，有效用户ID等于实际用户ID，当set-user-id位设置时，有效用户ID等于文件所有者的uid，而不是实际用户ID。

```c
#include <unistd.h>
int setuid(uid_t uid);
int setgid(gid_t gid);
// Both return: 0 if OK, -1 on error

int setreuid(uid_t ruid, uid_t euid);
int setregid(uid_t rgid, uid_t egid);
// Both return: 0 if OK, -1 on error

int seteuid(uid_t uid);
int setegid(gid_t gid);
// Both return: 0 if OK, -1 on error                                                                                                                                                             uid_t getuid(void);
gid_t getgid(void);
uid_t geteuid(void);
gid_t getegid(void);
// 这四个系统调用不会失败
```

