/*
 * NOTES:
 * signal函数可以自定义handler
 * sighandler_t signal(int signum, sighandler_t handler);
 */

#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void ouch(int sig)
{
    printf("OUCH! - I got signal %d\n", sig);
    signal(SIGINT, SIG_DFL);           /* 这个回复SIGINT信号的默认行为 */
}

int main()
{
    signal(SIGINT, ouch);              /* 自定义收到SIGINT信号时，要执行的函数 */

    while (1) {
        printf("Hello World\n");
        sleep(1);
    }
}

// 第一次ctrl+c执行了我们自定义的函数，然后让SIGINT恢复默认行为
// 第二次ctrl+c执行了默认行为

// leo@ubuntu:~/c_test$ ./a.out 
// Hello World
// ^COUCH! - I got signal 2
// Hello World
// ^C