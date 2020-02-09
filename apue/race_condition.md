A race condition occurs when multiple processes are trying to do something with shared data and the final outcome depends on the order in which the process run. The **fork** function is a lively breeding ground for race conditions, if any of the logic after the fork either explicitly or implicity depends on whether the parent or child runs first after the fork. In general, we cannot predict which process runs first. Even if we knew which process would run first, what happens after that proces starts running depends on the system load and the kernel's scheduling algorithm.



## 进程间同步

```c
TELL_WAIT();

if ((pid = fork()) < 0) {
  err_sys("fork error");
} else if (pid == 0) {
  /* child */
  TELL_PARENT(getppid());
  WAIT_PARENT();
  exit(0);
}

TELL_CHILD(pid);
WAIT_CHILD();

exit(0);

```

