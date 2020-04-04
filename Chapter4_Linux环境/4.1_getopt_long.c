/*
 * DESC:
 * 
 * NOTES:
 * getopt_long比getopt多了两个参数。
 * 第一个是option结构体的数组，最后必须是4个0
 * 一个使用实例在最下面
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define _GNU_SOURCE
#include <getopt.h>

int main(int argc, char *argv[])
{
    int opt;
    struct option longopts[] = {
        {"initialize", 0, NULL, 'i'},
        {"file", 1, NULL, 'f'},
        {"list", 0, NULL, 'l'},
        {"restart", 0, NULL, 'r'},
        {0,0,0,0},
    };

    while ((opt = getopt_long(argc, argv, ":if:lr", longopts, NULL)) != -1) {
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
    exit(0);
}

// leo@ubuntu:~/c_test$ ./a.out --init -l --file=read.c
// option: i
// option: l
// filename: read.c
