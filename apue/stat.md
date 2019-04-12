

链接：<https://blog.csdn.net/chun_1959/article/details/44851167>

stat系统调用系列包括了fstat、stat和lstat，它们都是用来返回“相关文件状态信息”的，三者的不同之处在于设定源文件的方式不同。首先介绍的是一个非常重要的结构体类型，名字叫做struct stat。可以说，没有这个struct stat的支持，上述三个系统调用将寸步难行。这个struct stat结构体在不同的UNIX/Linux系统中的定义是有小的区别的，但你完全不用担心，这并不会影响我们的使用。

struct stat结构体中在各个平台都一定有的域是：

st_mode 文件权限和文件类型信息

st_info 与该文件相关联的inode

st_dev 保存文件的设备

st_uid 文件属主的UID

st_gid 文件属主的GID

st_atime 文件上一次被访问的时间

st_ctime 文件的权限、属主、组或内容上一次被修改的时间

st_mtime 文件的内容上一次被修改的时间

st_nlink 该文件上硬链接的个数



```c
struct stat {
    dev_t st_dev;   // 文件的设备编号
    ino_t st_ino;   // 节点
    mode_t st_mode;    // 文件的类型和存取的权限
    nlink_t st_nlink;  // 连到该文件的硬连接数目，刚建立的文件值为1
    uid_t st_uid;   // 用户ID
    gid_t st_gid;   // 组ID
    dev_t st_rdev;  // （设备类型），若此文件为设备文件，则为其设备编号
    off_t st_size;  // 文件字节数（文件大小）
    unsigned long st_blksize;  // 块大小
    unsigned long st_blocks;   // 块数
    time_t st_atime;  // 最后一次访问时间
    time_t st_mtime;  // 最后一次修改时间
    time_t st_ctime;  // 最后一次改变时间
}
```

用于解释st_mode标志的掩码包括： 

        S_IFMT   0170000               文件类型的位遮罩 
        S_IFSOCK 0140000               scoket 
        S_IFLNK 0120000                符号连接 
        S_IFREG 0100000                一般文件 
        S_IFBLK 0060000                区块装置 
        S_IFDIR 0040000                目录 
        S_IFCHR 0020000                字符装置 
        S_IFIFO 0010000                先进先出 
        S_ISUID 04000                  文件的(set user-id on execution)位 
        S_ISGID 02000                  文件的(set group-id on execution)位 
        S_ISVTX 01000                  文件的sticky位 
        S_IRUSR(S_IREAD) 00400      文件所有者具可读取权限 
        S_IWUSR(S_IWRITE)00200      文件所有者具可写入权限 
        S_IXUSR(S_IEXEC) 00100      文件所有者具可执行权限 
        S_IRGRP 00040             用户组具可读取权限 
        S_IWGRP 00020             用户组具可写入权限 
        S_IXGRP 00010             用户组具可执行权限 
        S_IROTH 00004             其他用户具可读取权限 
        S_IWOTH 00002             其他用户具可写入权限 
        S_IXOTH 00001             其他用户具可执行权限
还有一些用于帮助确定文件类型的宏定义，这些和上面的宏不一样，这些是带有参数的宏，类似与函数的使用方法： 
S_ISBLK (st_mode) ：测试是否是特殊的块设备文件
S_ISCHR (st_mode) ：测试是否是特殊的字符设备文件
S_ISDIR (st_mode) ：测试是否是目录
S_ISFIFO (st_mode)：测试是否是FIFO设备
S_ISREG (st_mode)：测试是否是普通文件
S_ISLNK (st_mode) ：测试是否是符号链接

S_ISSOCK (st_mode)：测试是否是socket

**原型**

```c
int fstat(int fileds, struct stat *buf);
int stat(const char *path, struct stat *buf);
int lstat(const char *path, struct stat *buf);
```

fstat区别于另外两个系统调用的地方在于，fstat系统调用接受的是 一个“文件描述符”，而另外两个则直接接受“文件全路径”。文件描述符是需要我们用open系统调用后才能得到的，而文件全路经直接写就可以了。

stat和lstat的区别：当文件是一个符号链接时，lstat返回的是该符号链接本身的信息；而stat返回的是该链接指向的文件的信息.