/*
 * NOTES:
 * exec函数是替换进程映像，即原有的实行的a.out进程被替换成了我们要执行的新的进程
 */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main()
{
    printf("Running ps with execlp\n");
    execlp("ps", "ps", "ax", 0);
    printf("Done.\n");
    exit(0);
}

// 注意观察最后一个进程。
// 注意Done也没有输出了，因为整个进程都被替换了
//  23194 ?        I      0:00 [kworker/0:0-eve]
//  23217 ?        I      0:00 [kworker/u256:0-]
//  23383 ?        I      0:00 [kworker/0:1-eve]
//  23413 ?        S      0:00 sleep 180
//  23415 ?        I      0:00 [kworker/u256:2-]
//  23425 pts/1    R+     0:00 ps ax