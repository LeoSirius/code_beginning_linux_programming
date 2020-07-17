/*
 * NOTES:
 * 注意，编译需要 -lcurses
 */

#include <stdio.h>
#include <term.h>
#include <curses.h>
#include <stdlib.h>

int main()
{
    int nrows, ncolumns;

    /* 将终端类型设置为第一个参数指向的类型，如果第一个参数是NULL，则用环境变量TERM的值 */
    setupterm(NULL, fileno(stdout), (int*)0);
    nrows = tigetnum("lines");
    ncolumns = tigetnum("cols");

    printf("This terminal has %d columns and %d rows\n", ncolumns, nrows);
    exit(0);
}

// leo@ubuntu:~/c_test$ ./a.out 
// This terminal has 130 columns and 33 rows