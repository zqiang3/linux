stdin等是FILE *类型，属于标准I/O，在<stdio.h>

STDIN_FILENO等是文件描述符，是非负整数，一般定义为0, 1, 2，属于没有buffer的I/O，直接调用系统调用，在<unistd.h>