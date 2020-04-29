/*
 * NOTES:
 * system可以启动一个新的进程。system用shell来启动要执行的命令
 */

#include <stdlib.h>
#include <stdio.h>

int main()
{
    printf("Running ps with system\n");
    system("ps ax");
    printf("Done.\n");
    exit(0);
}

// 注意看最后3个进程
//  22612 ?        Ssl    0:00 /usr/sbin/cups-browsed
//  23138 ?        S      0:00 sleep 180
//  23194 ?        I      0:00 [kworker/0:0-eve]
//  23217 ?        I      0:00 [kworker/u256:0-]
//  23254 ?        I      0:00 [kworker/0:3-cgr]
//  23314 pts/1    S+     0:00 ./a.out
//  23315 pts/1    S+     0:00 sh -c ps ax
//  23316 pts/1    R+     0:00 ps ax
// Done.