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

