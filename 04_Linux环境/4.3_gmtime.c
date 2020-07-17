/*
 * NOTES:
 * gmtime把时间戳分解成一个tm结构体
 */
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    struct tm *tm_ptr;
    time_t the_time;

    time(&the_time);
    tm_ptr = gmtime(&the_time);

    printf("Raw time is %ld\n", the_time);
    printf("gmtime gives:\n");
    printf("date: %02d/%02d/%02d\n", tm_ptr->tm_year, tm_ptr->tm_mon, tm_ptr->tm_mday);
    printf("time: %02d:%02d:%02d\n", tm_ptr->tm_hour, tm_ptr->tm_min, tm_ptr->tm_sec);
    exit(0);
}

// leo@ubuntu:~/c_test$ ./a.out 
// Raw time is 1586621020
// gmtime gives:
// date: 120/03/11
// time: 16:03:40