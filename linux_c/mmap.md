# 概念

mmap是一种内存映射文件的方法，将文件映射到进程的地址空间。实现这样的映射后，进程可采用指针的方式读写操作这段内存，而系统自动将改动的数据写回到磁盘文件上，而不必再调用read write系统调用。相反，内核对这段区域数据的修改也反映到用户空间，从而实现不同进程间的文件共享。

# 虚拟内存区域

进程的虚拟地址空间，由多个虚拟内存区域构成。虚拟内存区域是进程的虚拟地址空间中的一个同质区间，即具有同样特性的连续地址范围。

linux内核使用vm_area_struct结构来表示一个独立的虚拟内存区域，由于每个不同质的虚拟内存区域功能和内部机制都不同，因此一个进程使用多个vm_area_struct结构来分别表示不同类型的虚拟内存区域。各个vm_area_struct结构使用链表或者树形结构链接，方便进程快速访问。

mmap函数就是要创建一个新的vm_area_struct结构，并将其与文件的物理磁盘地址相连。

# 优点

1. 对文件的读写操作跨过了页缓存，减少了一次数据拷贝，提高了效率。
2. 提供进程间共享内存及相互通信的方式。不管是父子进程还是无亲缘关系的进程，都可以将自身用户空间映射到同一个文件或匿名映射到同一片区域。从而通过各自对映射区域的改动，达到进程间通信和进程间共享的目的。
3. 可用于实现高效的大规模数据传输。内存空间不足，是制约大数据操作的一个方面，解决方案往往是借助硬盘空间协助操作，补充内存的不足。但是进一步会造成大量的文件I/O操作，极大影响效率。这个问题可以通过mmap映射很好的解决。换句话说，但凡是需要用磁盘空间代替内存的时候，mmap都可以发挥其功效。

# 使用细节

1. 内存的最小粒度是页，而进程虚拟地址空间和内存的映射也是以页为单位。page_size在32位系统中通常为4k字节。
2. 映射建立之后，即使文件关闭，映射依然存在。因为映射的是磁盘的地址，不是文件本身，和文件句柄无关。同时可用于进程间通信的有效地址空间不完全受限于被映射文件的大小，因为是按页映射。