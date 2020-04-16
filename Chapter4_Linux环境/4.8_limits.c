/*
 * NOTES：
 * 这个程序打印一些系统资源limit信息
 * 注意编译时需要加 -lm 把math库加进来，不然log会报错
 */

#include <sys/types.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void work()
{
    /* 这个函数向tmpfile进行输出，并做一些浮点运算，模拟对cpu造成一些压力 */
    FILE *f;
    int i;
    double x = 4.5;

    f = tmpfile();
    for (int i = 0; i < 1000; ++i) {
        fprintf(f, "Do some output\n");
        if (ferror(f)) {
            fprintf(stderr, "Error writing to temporary file\n");
            exit(1);
        }
        for (i = 0; i < 1000000; ++i)
            x = log(x * x + 3.21);
    }
}

int main()
{
    struct rusage r_usage;
    struct rlimit r_limit;
    int priority;

    work();
    getrusage(RUSAGE_SELF, &r_usage);

    printf("CPU usage: User = %ld.%06ld, System = %ld.%06ld\n",
        r_usage.ru_utime.tv_sec, r_usage.ru_utime.tv_usec,
        r_usage.ru_stime.tv_sec, r_usage.ru_stime.tv_usec
    );

    priority = getpriority(PRIO_PROCESS, getpid());
    printf("Current priority = %d\n", priority);

    getrlimit(RLIMIT_FSIZE, &r_limit);
    printf("Current FSIZE limit: soft = %ld, hard = %ld\n",
        r_limit.rlim_cur, r_limit.rlim_max
    );

    /* 重新设置limit后，再调用work就会失败，因为文件超过limit大小了 */
    r_limit.rlim_cur = 2048;
    r_limit.rlim_max = 4096;
    printf("Setting a 2K file size limit\n");
    setrlimit(RLIMIT_FSIZE, &r_limit);

    work();
    exit(0);
}

// leo@ubuntu:~/c_test$ ./a.out 
// CPU usage: User = 0.030115, System = 0.003764
// Current priority = 0
// Current FSIZE limit: soft = -1, hard = -1
// Setting a 2K file size limit