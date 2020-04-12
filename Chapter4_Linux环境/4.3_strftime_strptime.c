/*
 * NOTES:
 * strftime和strptime是一对函数
 * strftime把tm结构体的中的时间按照格式写到buf字符串中
 * strptime则相反，把buf字符串中按格式读出来，写到tm结构体中。
 * strptime会返回buf中没有处理的剩下部分
 */

#define _XOPEN_SOURCE   /* 使用strptime必须定义这个宏 */

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    struct tm *tm_ptr, timestruct;
    time_t the_time;
    char buf[256];
    char *remain;

    (void) time(&the_time);
    tm_ptr = localtime(&the_time);
    strftime(buf, 256, "%A %d %B, %I:%M %p", tm_ptr);

    printf("strftime gives: %s\n", buf);

    strcpy(buf, "Thu 26 July 2007, 17:53 wiil do fine");
    printf("calling strptime with: %s\n", buf);
    tm_ptr = &timestruct;
    remain = strptime(buf, "%a %d %b %Y, %R", tm_ptr);
    printf("strptime consumed up to: %s\n", remain);

    printf("strptime gives:\n");
    printf("date: %02d/%02d/%02d\n", tm_ptr->tm_year, tm_ptr->tm_mon, tm_ptr->tm_mday);
    printf("time: %02d:%02d\n", tm_ptr->tm_hour, tm_ptr->tm_min);

    exit(0);
}

// leo@ubuntu:~/c_test$ ./a.out 
// strftime gives: Sunday 12 April, 02:14 AM
// calling strptime with: Thu 26 July 2007, 17:53 wiil do fine
// strptime consumed up to:  wiil do fine
// strptime gives:
// date: 107/06/26
// time: 17:53