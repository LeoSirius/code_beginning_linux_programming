/*
 * NOTES:
 * dup会把参数的fd，复制给一个最小可用的空闲fd
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
    __pid_t fork_result;

    if (pipe(file_pipes) == 0) {
        fork_result = fork();
        if (fork_result == (__pid_t)-1) {
            fprintf(stderr, "Fork failure");
            exit(EXIT_FAILURE);
        }

        if (fork_result == (__pid_t)0) {
            close(0);                // 关闭标准输入0
            dup(file_pipes[0]);      // 把files_pipes[0]的值复制给0，即0接上了管道的输出
            close(file_pipes[0]);    // 关闭原管道的写fd[1]  和读fd[0]
            close(file_pipes[1]);

            execlp("od", "od", "-c", (char *)0);   // od使用的标准输入0，其实变成了管道的输出
        } else {
            close(file_pipes[0]);    // 父进程不从管道读，先关掉读fd[0]
            data_processed = write(file_pipes[1], some_data, strlen(some_data));
            close(file_pipes[1]);    // 父进程写完后，再关闭管道的写fd[1]

            printf("%d - wrote %d bytes\n", (int)getpid(), data_processed);
        }
    }
    exit(EXIT_SUCCESS);

}

// leo@ubuntu:~/c_test$ ./a.out 
// 46680 - wrote 3 bytes
// leo@ubuntu:~/c_test$ 0000000   1   2   3
// 0000003