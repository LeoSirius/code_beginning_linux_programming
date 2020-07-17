/*
 * DESC:
 * 我们用内存映射的方法在内存中修改文件的内容，原data.txt中一个字符被修改了
 * 
 * NOTES:
 * mmap是一种内存映射文件的方法，即将一个文件或者其他对象映射到进程的地址空间，
 * 实现文件磁盘地址和进程虚拟地址空间中一段虚拟地址的一一对应关系；实现这样的映射关系后，
 * 进程就可以采用指针的方式读写操作这一块内存，而系统会自动回写脏页面到对应的文件磁盘上，
 * 即完成了对文件的操作而不必调用read，write等系统调用函数，相反，内核空间堆这段区域的修改也直接反应到用户空间，
 * 从而可以实现不同进程间的文件共享。
 * 
 * 例如，data.txt中原来的内容是
 * abcdefghijklmnopqrstuvwxyz
 * 
 * 程序执行后，变成
 * abcdefghijklmnopqrst9vwxyz
 */

#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <error.h>

#define BUF_SIZE 100

int main(int argc, char **argv)
{
    int fd, nread, i;
    struct stat sb;
    char *mapped;

    /* 打开文件 */
    if ((fd = open("data.txt", O_RDWR)) < 0)
        perror("open");

    /* 获取文件属性 */
    if ((fstat(fd, &sb)) == -1)
        perror("fstat");

    /* 将文件映射至进程的地址空间 */
    if ((mapped = (char *)mmap(NULL, sb.st_size, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0)) == (void *)-1)
        perror("mmap");
    close(fd);

    printf("%s", mapped);

    /* 修改一个字符，并同步到磁盘文件 */
    mapped[20] = '9';
    if ((msync((void *)mapped, sb.st_size, MS_SYNC)) == -1)
        perror("mysync");

    /* 释放映射区 */
    if ((munmap((void *)mapped, sb.st_size)) == -1)
        perror("munmap");

    return 0;
}