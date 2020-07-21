/*
 * NOTES:
 * copy文件，把file.in copy到file.out，没有的话则新建file.out
 * 
 * 注意sizeof参数数组和指针的区别：
 */

// char block[1024];
// char *block2;
// char block3[] = {1,2,3};
// char block4[4];
// printf("%ld\n", sizeof(block));   // 1024
// printf("%ld\n", sizeof(block2));  // 8   就是指针的大小，64位机器
// printf("%ld\n", sizeof(block3));  // 3
// printf("%ld\n", sizeof(block4));  // 4

#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

int main()
{
    char block[1024];
    int in, out;
    int nread;

    in = open("file.in", O_RDONLY);
    out = open("file.out", O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
    while ((nread = read(in, block, sizeof(block))) > 0) {
        write(out, block, nread);
    }
    exit(0);
}
