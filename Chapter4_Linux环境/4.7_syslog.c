/*
 * NOTES:
 */

#include <syslog.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    int logmask;

    /* 第三个参数facility表示哪种类型的程序在log */
    openlog("logmask", LOG_PID | LOG_CONS, LOG_USER);
    syslog(LOG_INFO, "informative message, pid = %d", getpid());
    syslog(LOG_DEBUG, "debug message, should appear");

    logmask = setlogmask(LOG_UPTO(LOG_NOTICE));
    syslog(LOG_DEBUG, "debug message should not appear");

    exit(0);
}

// 在var/log/syslog文件中，可以看到以下新加的内容
// Apr 16 06:41:41 ubuntu logmask[32516]: informative message, pid = 32516
// Apr 16 06:41:41 ubuntu logmask[32516]: debug message, should appear
