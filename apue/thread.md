## 线程标识

```c
#include <pthread.h>
int pthread_equal(pthread_t tid1, ptrhead_t tid2);
// Returns: nonzero if equal, 0 otherwise
pthread_t pthread_self(void);
// Returns: the thread ID of the calling thread
```



## 线程创建

```c
#include <pthread.h>
int pthread_create(pthread_t *restrict tidp,
                  const pthread_attr_t *restrict attr,
                  void *(*start_rtn)(void *),
                  void *restrict arg);
// Returns: 0 if OK, error number on failure
```



## 线程终止

```c
#include <pthread.h>
void pthread_exit(void *rval_ptr);
int pthread_join(pthread_t thread, void **rval_ptr);
// Returns: 0 if OK, error number on failure
int pthread_cancel(pthread_t tid);
// Returns: 0 if OK, error number on failure
void pthread_cleanup_push(void (*rtn)(void *), void *arg);
void pthread_cleanup_pop(int execute);
int pthread_detach(pthread_t tid);
// Returns: 0 if OK, error number on failure
```



## example

###Creatation

```c
#include "apue.h"

void printids(const char *);

void * foo(void *arg)
{
    println("in foo");
    printids("newthread");
    return NULL;
}

void
printids(const char *s)
{
    pid_t pid;
    pthread_t tid;

    pid = getpid();
    tid = pthread_self();
    printf("in %s, pid = %d, tid = %lu, tid = 0x%lx\n", s, pid, (long)tid, (long)tid);
}

int main()
{
    pthread_t tid;
    int ret;
    ret = pthread_create(&tid, NULL, foo, NULL);
    printf("ret = %d\n", ret);
    printids("main");
    sleep(1);
    println("finished");
    return 0;
}
```



### Termination

返回普通值

```c
#include "apue.h"

void *
thread1(void *arg)
{
    sleep(3);
    println("thread1");
    return (void *)1;
}

void *
thread2(void *arg)
{
    sleep(2);
    println("thread2");
    sleep(5);
    pthread_exit((void *)2);
}

int main()
{
    pthread_t tid1, tid2;
    void *retval;
    int ret1, ret2;
    if ((pthread_create(&tid1, NULL, thread1, NULL)) != 0)
        err_sys("pthread_create failure");
    if ((pthread_create(&tid2, NULL, thread2, NULL)) != 0)
        err_sys("pthread_create failure");

    int ret;
    errno = 0;
    if ((ret = pthread_join(tid1, &retval)) != 0)
    {
        printf("ret = %d, errno = %d\n", ret, errno);
        err_sys("pthread_join failure");
    }
    printf("ret1 = %d\n", (int)retval);
    if ((ret = pthread_join(tid2, &retval)) != 0)
    {
        printf("ret = %d, errno = %d\n", ret, errno);
        err_sys("pthread_join failure");
    }
    printf("ret2 = %d\n", (int)retval);

    sleep(1);
    println("finished");



    return 0;
}
```



返回结构体

```c
#include "apue.h"

struct foo {
    int a, b, c, d;
};



void
printfoo(const char *s, const struct foo *fp)
{
    printf("%s", s);
    printf(" structure at 0x%lx\n", (long)fp);
    printf(" foo.a = %d\n", fp->a);
    printf(" foo.b = %d\n", fp->b);
    printf(" foo.c = %d\n", fp->c);
    printf(" foo.d = %d\n", fp->d);
}

void *
thread1(void *arg)
{
    struct foo *f;
    f = (struct foo *)malloc(sizeof(struct foo));
    f->a = 1;
    f->b = 1;
    f->c = 1;
    f->d = 1;
    printfoo("thread1", f);
    println("thread1");
    pthread_exit((void *)f);
}

void *
thread2(void *arg)
{
    println("thread2");
    sleep(2);
    pthread_exit((void *)0);
}

int main()
{
    pthread_t tid1, tid2;
    void *retval;
    struct foo *fp;
    int ret1, ret2;
    if ((pthread_create(&tid1, NULL, thread1, NULL)) != 0)
        err_sys("pthread_create failure");
    if ((pthread_create(&tid2, NULL, thread2, NULL)) != 0)
        err_sys("pthread_create failure");

    int ret;
    errno = 0;
    if ((ret = pthread_join(tid1, (void *)&fp)) != 0)
    {
        printf("ret = %d, errno = %d\n", ret, errno);
        err_sys("pthread_join failure");
    }
    printfoo("parent", fp);
    if ((ret = pthread_join(tid2, (void *)&fp)) != 0)
    {
        printf("ret = %d, errno = %d\n", ret, errno);
        err_sys("pthread_join failure");
    }

    sleep(1);
    println("finished");

    return 0;
}
```

cleanup

```c
#include "apue.h"

void cleanup(void *arg)
{
    printf("arg is %s\n", (char *)arg);

}

void * fnc1(void *arg)
{
    println("fnc1");
    pthread_cleanup_push(cleanup, "cleanup 1");
    pthread_cleanup_push(cleanup, "cleanup 2");
    println("register done");

    if (arg)
        //return (void *)1;
        pthread_exit((void *)2);

    pthread_cleanup_pop(1);
    pthread_cleanup_pop(2);

    //return (void *)2;
    pthread_exit((void *)2);
}

int main()
{
    pthread_t tid;
    int ret;
    if ((ret = pthread_create(&tid, NULL, fnc1, (void *)2)) != 0)
        err_sys("pthread_create fail");

    void *rval;
    if ((ret = pthread_join(tid, &rval)) != 0)
        err_sys("pthread_join fail");

    printf("rval = %d\n", (int)rval);
    println("hello, world");
    return 0;
}
```



