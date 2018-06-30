提供屏蔽和解除屏蔽信号的功能，从而实现关键代码的运行不被打断。

```c
#include <signal.h>
int sigpromask(int how, const sigset_t *set, sigset_t *oldset)
```

