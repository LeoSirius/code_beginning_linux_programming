/*
 * NOTES:
 * utsname是存放系统信息的结构体
 */

#include <sys/utsname.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    char computer[256];
    struct utsname uts;

    if (gethostname(computer, 256) != 0 || uname(&uts)) {
        fprintf(stderr, "Could not get host information\n");
        exit(1);
    }

    printf("Computer host name: %s\n", computer);
    printf("sysname: %s\n", uts.sysname);
    printf("machine: %s\n", uts.machine);
    printf("nodename: %s\n", uts.nodename);
    printf("version: %s\n", uts.version);
    printf("release: %s\n", uts.release);

    exit(0);
}

// leo@ubuntu:~/c_test$ ./a.out 
// Computer host name: ubuntu
// sysname: Linux
// machine: x86_64
// nodename: ubuntu
// version: #37~18.04.1-Ubuntu SMP Fri Mar 27 15:58:10 UTC 2020
// release: 5.3.0-45-generic
