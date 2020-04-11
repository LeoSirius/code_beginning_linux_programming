/*
 * NOTES:
 * 这个程序输出当前系统的所有环境变量。
 * 
 * 系统的环境变量储存在environ中，这是一个字符串指针的指针。一个环境变量就是“key=value”的字符串
 */

#include <stdlib.h>
#include <stdio.h>

extern char **environ;

int main()
{
    char **env = environ;

    while (*env) {
        printf("%s\n", *env);
        env++;
    }
    exit(0);
}