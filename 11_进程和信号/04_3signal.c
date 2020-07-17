/*
 * NOTES:
 * sigaction是处理信号的一个更新的接口
 * 
 * 注意这个程序没有在ouch中恢复信号的处理，要退出按ctrl + \
 */

#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void ouch(int sig)
{
    printf("OUCH! - I got signal %d\n", sig);
}

int main()
{

    struct sigaction act;
    act.sa_handler = ouch;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;

    sigaction(SIGINT, &act, 0);

    while (1) {
        printf("Hello World\n");
        sleep(1);
    }
}