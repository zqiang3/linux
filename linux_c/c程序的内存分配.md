## APUE示意图

[![cmem.png](https://i.postimg.cc/cJkgvSbF/cmem.png)](https://postimg.cc/cKY4zVZ3)

## 例子

```c
#include <stdlib.h>

int a = 0;  // 全局初始化区
char *p1;   // 全局未初始化区

int main(int argc, char *argv[])
{
    int b;             // 栈
    char s[] = "abc";  // 栈
    char *p2;          // 栈
    char *p3 = "123";        // p3在栈上，123456在常量区
    static int c = 0;        // 全局静态初始化区
    char *pp = "123";        // pp和p3指向的地址是一样的
    p1 = (char *)malloc(10); // 10字节数据在堆上
    p2 = (char *)malloc(20); // 20字节数据在堆上
}
```

代码区：存放程序的代码，是只读的

常量区：存放常量，如10，字符串常量"123"

全局初始化区：设为初始值

全局未初始化区：统一设为0值

堆区：动态申请的内存

栈区：存放函数内的局部变量，形参。