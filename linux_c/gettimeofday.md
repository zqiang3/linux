## 简介

为了获取某函数调用耗时.在C语言中可以使用函数gettimeofday()函数来得到时间。它的精度可以达到微秒, 且在x86-64平台gettimeofday()已不是系统调用,不会陷入内核, 多次调用不会有性能损失 

## 原型

```c
#include <sys/time.h>
int gettimeofday(struct timeval *tv, struct timezone *tz)
```

## 说明

1. gettimeofday()会把目前的时间用tv 结构体返回，当地时区的信息则放到tz所指的结构中 
2. struct timeval结构体为时间变量, 包括两个成员变量:tv_sec(秒), tv_usec(微秒); 第二个结构体为时区, 本示例没有用到可以置为NULL 

```c
struct timeval {
    long tv_sec;
    long tv_usec;
}
```

