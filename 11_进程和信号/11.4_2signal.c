/*
 * NOTES:
 * 这个程序是子进程在sleep5秒后发一个SIGALRM信号给父进程
 * 
 * int kill(pid_t pid, int sig);函数给pid进程发sig信号。
 * 注意一个用户只能给自己userid的进程发信号。superuser可以给所有进程发信号
 * 
 * pause()函数会挂起一个进程，直到有一个信号出现
 */

#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

static int alarm_fired = 0;

void ding(int sig)
{
    alarm_fired = 1;
}

int main()
{
    pid_t pid;

    printf("alarm application starting\n");

    pid = fork();
    switch (pid) {
        case -1:
            perror("fork failed");
            exit(1);
        case 0:
            sleep(5);
            kill(getppid(), SIGALRM);
            exit(0);
    }

    printf("waiting for alarm to go off\n");
    signal(SIGALRM, ding);

    pause();
    if (alarm_fired)
        printf("Ding\n");
    
    printf("done\n");
    exit(0);
}

// leo@ubuntu:~/c_test$ ./a.out 
// alarm application starting
// waiting for alarm to go off
// Ding
// done