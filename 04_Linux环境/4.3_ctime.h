/*
 * NOTES:
 * ctime把时间戳返回成一个local time的字符串
 */

#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    time_t timeval;

    (void)time(&timeval);
    printf("The date is: %s", ctime(&timeval));
    exit(0);
}

// leo@ubuntu:~/c_test$ ./a.out 
// The date is: Sat Apr 11 20:10:58 2020