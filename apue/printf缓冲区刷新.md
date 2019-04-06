用printf()输出时是先输出到缓冲区，然后再从缓冲区送到屏幕上。linux下缓冲区刷新到屏幕这一步一般可以通过一下方式触发:
1. 使用fflush（stdout）强制刷新标准输出缓冲区。
2. 缓冲区已满。
3. scanf()要在缓冲区里取数据时会先将缓冲区刷新。
4. \n进入缓冲区时。
5. 程序结束时。

## 代码示例
```c
c
#include <stdio.h>

void test1();
void test2();

int main(int argc, char *argv)
{
    test2();
}


// printf 遇到换行符刷新缓冲区
void test1()
{
    printf("hello, this is first line");
    // printf("hello, this is first line\n");
    sleep(5);
    printf("this is second line\n");
}


// printf 从标准输入读数据时刷新标准输出的缓冲区
void test2()
{
    printf("hello, this is first line");
    // printf("hello, this is first line\n");
    int a;
    scanf("%d", &a);
    printf("this is second line\n");
}
```

