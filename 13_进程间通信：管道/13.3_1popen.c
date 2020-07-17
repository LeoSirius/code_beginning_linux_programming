/*
 * NOTES:
 * 这次用w通过管道，向程序中写数据。
 * 调用这个程序在shell中相当于
 * $ echo "Once upon a time, there was..." | od -c
 */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main()
{
    FILE *write_fp;
    char buffer[BUFSIZ+1];

    sprintf(buffer, "Once upon a time, there was...\n");
    write_fp = popen("od -c", "w");
    if (write_fp != NULL) {
        fwrite(buffer, sizeof(char), strlen(buffer), write_fp);
        pclose(write_fp);
        exit(EXIT_SUCCESS);
    }
    exit(EXIT_FAILURE);
}

// 可以看到结果同
// $ echo "Once upon a time, there was..." | od -c
// 是一样的

// leo@ubuntu:~/c_test$ ./a.out 
// 0000000   O   n   c   e       u   p   o   n       a       t   i   m   e
// 0000020   ,       t   h   e   r   e       w   a   s   .   .   .  \n
// 0000037
// leo@ubuntu:~/c_test$ echo "Once upon a time, there was..." | od -c
// 0000000   O   n   c   e       u   p   o   n       a       t   i   m   e
// 0000020   ,       t   h   e   r   e       w   a   s   .   .   .  \n
// 0000037