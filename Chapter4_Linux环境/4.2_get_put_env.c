/*
 * DESC:
 * 
 * NOTES:
 * 环境变量以“key=value”的形式存在
 * getenv()的参数是key字符串，返回value字符串
 * putget()的参数是“key=value”字符串
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    char *var, *value;

    if (argc == 1 || argc > 3) {
        fprintf(stderr, "usage: environ var value\n");
        exit(1);
    }

    var = argv[1];
    value = getenv(var);
    if (value) {
        printf("Variable %s has value %s\n", var, value);
    } else {
        printf("Variable %s has no value\n", var);
    }

    /* 如果加文件名是3个参数，则用putenv设置环境变量 */
    if (argc == 3) {
        char *string;
        value = argv[2];
        string = malloc(strlen(var) + strlen(value) + 2);
        if (!string) {
            fprintf(stderr, "out of memory\n");
            exit(1);
        }

        strcpy(string, var);
        strcat(string, "=");
        strcat(string, value);

        printf("Calling putenv with: %s\n", string);
        if (putenv(string) != 0) {
            fprintf(stderr, "putenv failed\n");
            free(string);
            exit(1);
        }

        value = getenv(var);
        if (value)
            printf("New value of %s is %s\n", var, value);
        else
            printf("New value of %s is null\n", var);
    }
    exit(0);
}

// leo@ubuntu:~/c_test$ ./a.out MY_NAME leo
// Variable MY_NAME has no value
// Calling putenv with: MY_NAME=leo
// New value of MY_NAME is leo