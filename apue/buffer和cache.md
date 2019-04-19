### 什么是buffer（缓冲）？什么是cache（缓存）？

A buffer is something that has yet to be written to disk.

A cache is something that has been read from the disk and stored for later use.

### free命令

```bash
free -m
###
             total       used       free     shared    buffers     cached
Mem:          7869       7651        218          1        191       5081
-/+ buffers/cache:       2378       5490
Swap:          478        139        339
```

```
total1：表示物理 内存总量
used1：表示总计分配给缓存（包含buffers 与cache ）使用的数量，但其中可能部分缓存并未实际使用
free1：未被分配的内存
shared1：共享内存，一般系统不会用到，这里也不讨论
buffers1： 系统分配但未被使用的buffers 数量
cached1：系统分配但未被使用的cache 数量
used2：实际使用的buffers 与cache 总量，也是实际使用的内存总量
free2：未被 使用的buffers 与cache 和未被分配的内存之和，这就是系统当前实际可用内存
```

Cache：高速缓存，是位于CPU与主内存间的一种容量较小但速度很高的存储器。由于CPU的速度远高于主内存，CPU直接从内存中存取数据要等待一定时间周期，Cache中保存着CPU刚用过或循环使用的一部分数据，当CPU再次使用该部分数据时可从Cache中直接调用，这样就减少了CPU的等待时间，提高了系统的效率。Cache又分为一级Cache（L1 Cache）和二级Cache（L2 Cache），L1 Cache集成在CPU内部，L2 Cache早期一般是焊在主板上，现在也都集成在CPU内部，常见的容量有256KB或512KB L2 Cache

查看CPU 的L1 L2 L3

```bash
ls -al /sys/devices/system/cpu/cpu0/cache
```

buffer ：作为buffer cache的内存，是块设备的读写缓冲区 

cache：作为page cache的内存， 文件系统的cache

**如何释放cache memory**

```bash
# To free pagecache:
echo 1 > /proc/sys/vm/drop_caches
# To free dentries and inodes:
echo 2 > /proc/sys/vm/drop_caches
# To free pagecache, dentries and inodes:
echo 3 > /proc/sys/vm/drop_caches
```

- 缓存（cached）是把读取过的数据保存起来，重新读取时若命中（找到需要的数据）就不要去读硬盘了，若没有命中就读硬盘。其中的数据会根据读取频率进行组织，把最频繁读取的内容放在最容易找到的位置，把不再读的内容不断往后排，直至从中删除
- 缓冲（buffers）是根据磁盘的读写设计的，把分散的写操作集中进行，减少磁盘碎片和硬盘的反复寻道，从而提高系统性能。linux有一个守护进程定期 清空缓冲内容（即写入磁盘），也可以通过sync命令手动清空缓冲。举个例子吧：我这里有一个ext2的U盘，我往里面cp一个3M的MP3，但U盘的灯 没有跳动，过了一会儿（或者手动输入sync）U盘的灯就跳动起来了。卸载设备时会清空缓冲，所以有些时候卸载一个设备时要等上几秒钟

**buffer是即将要被写入磁盘的，而cache是被从磁盘中读出来的**