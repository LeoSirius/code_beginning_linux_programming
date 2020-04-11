/*
 * NOTES:
 * time()返回当前时间戳。如果参数的非空指针，则会把返回值也存到这个指针里
 */

#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    int i;
    time_t the_time;

    for (int i = 0; i <= 5; i++) {
        the_time = time((time_t *)0);
        printf("The time is %ld\n", the_time);
        sleep(2);
    }
    exit(0);
}

// leo@ubuntu:~/c_test$ ./a.out 
// The time is 1586620314
// The time is 1586620316
// The time is 1586620318
// The time is 1586620320
// The time is 1586620322
// The time is 1586620324