/*
 * NOTES:
 * 生产者向fifo中写10mb字节，消费者读取10mb。
 * 如果fifo空，read默认会阻塞。
 */
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>

#define FIFO_NAME "/tmp/my_fifo"
#define BUFFER_SIZE PIPE_BUF
#define TEN_MEG (1024 * 1024 * 10)   // 10mb

int main()
{
    int pipe_fd;
    int res;
    int open_mode = O_WRONLY;
    int bytes_sent = 0;
    char buffer[BUFFER_SIZE + 1];

    if (access(FIFO_NAME, F_OK) == -1) {
        res = mkfifo(FIFO_NAME, 0777);
        if (res != 0) {
            fprintf(stderr, "Could not create fifo %s\n", FIFO_NAME);
            exit(EXIT_FAILURE);
        }
        printf("Process %d opening FIFO O_WRONLY\n", getpid());
        pipe_fd = open(FIFO_NAME, open_mode);
        printf("Process %d result %d\n", getpid(), pipe_fd);

        if (pipe_fd == -1)
            exit(EXIT_FAILURE);

        while (bytes_sent < TEN_MEG) {
            res = write(pipe_fd, buffer, BUFFER_SIZE);
            if (res == -1) {
                fprintf(stderr, "Write error on pipe");
                exit(EXIT_FAILURE);
            }
            bytes_sent += res;
        }
        close(pipe_fd);
    }
    printf("Process %d finished\n", getpid());
    exit(EXIT_SUCCESS);
}

// leo@ubuntu:~/c_test$ ./producer &
// [1] 47703
// leo@ubuntu:~/c_test$ Process 47703 opening FIFO O_WRONLY
// ./consumer 
// Process 47705 opening FIFO O_RDONLY
// Process 47703 result 3
// Process 47705 result 3
// Process 47703 finished
// Process 47705 finished, 10485760 bytes read
// [1]+  Done                    ./producer