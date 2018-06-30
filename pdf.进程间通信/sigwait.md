wait for a signal

```c
#include <signal.h>
int sigwait(const sigset_t *set, int *sig);
```

*Description*

The sigwait() function suspends execution of the calling thread until the delivery of one of the signals specified in the signal set *set*. The function accepts the signal (removes it from the pending list of signals), and returns the signal number in*sig*.