/*
 * NOTES:
 * 
 * 父进程向管道中写数据，子进程从管道中读取数据
 * 
 * popen是一个高级函数，管道的底层函数时pipe
 * int pipe(int fd[2]);
 * 向fd[1]写的数据可以从fd[0]中读出来。顺序遵循队列FIFO。
 */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main()
{
    int data_processed;
    int file_pipes[2];
    const char some_data[] = "123";
    char buffer[BUFSIZ + 1];
    pid_t fork_result;

    memset(buffer, 0, sizeof(buffer));

    if (pipe(file_pipes) == 0) {
        fork_result = fork();
        if (fork_result == -1) {
            fprintf(stderr, "Fork failure");
            exit(EXIT_FAILURE);
        }

        if (fork_result == 0) {
            data_processed = read(file_pipes[0], buffer, BUFSIZ);
            printf("Read %d bytes: %s\n", data_processed, buffer);
            exit(EXIT_SUCCESS);
        } else {
            data_processed = write(file_pipes[1], some_data, strlen(some_data));
            printf("Wrote %d bytes\n", data_processed);
        }
    }
    exit(EXIT_SUCCESS);
}

// leo@ubuntu:~/c_test$ ./a.out 
// Wrote 3 bytes
// leo@ubuntu:~/c_test$ Read 3 bytes: 123