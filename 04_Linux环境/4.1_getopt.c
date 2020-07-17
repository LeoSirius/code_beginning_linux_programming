/*
 * DESC:
 * 
 * NOTES:
 * 一个使用实例在最下面
*/

#include <stdio.h>
#include <unistd.h>
#include <getopt.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int opt;

    /* optstr f后面的冒号表示f选项需要一个参数。在没有为f提供选项时，返回？，
     * 如果最前面后冒号，则在没有为f提供选项时，返回：
     */
    while ((opt = getopt(argc, argv, ":if:lr")) != -1) {
        switch (opt) {
            case 'i':
            case 'l':
            case 'r':
                printf("option: %c\n", opt);
                break;
            case 'f':
                printf("filename: %s\n", optarg);
                break;
            case ':':
                printf("option needs a value\n");
                break;
            case '?':
                printf("unknown option: %c\n", optopt); /* 遇到的未知选项会被保存在optopt中 */
                break;
        }
    }
    /* getopt实际上会重写argv数组，把所有选项的argument放到后面 */
    for (int i = 0; i < argc; ++i)
        printf("i = %d, argv[i] = %s\n", i, argv[i]);
    exit(0);
}

// leo@ubuntu:~/c_test$ ./a.out -i -lr 'hi here' -f fred.c -q
// option: i
// option: l
// option: r
// filename: fred.c
// unknown option: q
// i = 0, argv[i] = ./a.out
// i = 1, argv[i] = -i
// i = 2, argv[i] = -lr
// i = 3, argv[i] = -f
// i = 4, argv[i] = fred.c
// i = 5, argv[i] = -q
// i = 6, argv[i] = hi here