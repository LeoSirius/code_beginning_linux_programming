#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    pid_t pid;
    char *message;
    int n;

    printf("fork program starting\n");
    pid = fork();
    switch (pid) {
        case -1:
            perror("fork failed");
            exit(1);
        case 0:
            message = "This is the child";
            n = 5;
            break;
        default:
            message = "This is the parent";
            n = 3;
            break;
    }

    for (; n > 0; n--) {
        puts(message);
        sleep(1);
    }

    exit(0);
}

// parent输出3次后，退出返回了shell，child输出了5次。
// leo@ubuntu:~/c_test$ ./a.out 
// fork program starting
// This is the parent
// This is the child
// This is the parent
// This is the child
// This is the parent
// This is the child
// leo@ubuntu:~/c_test$ This is the child
// This is the child