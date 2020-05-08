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

int main()
{
    int pipe_fd;
    int res;
    int open_mode = O_RDONLY;
    char buffer[BUFFER_SIZE + 1];
    int bytes_read = 0;

    memset(buffer, 0, sizeof(buffer));

    printf("Process %d opening FIFO O_RDONLY\n", getpid());
    pipe_fd = open(FIFO_NAME, open_mode);
    printf("Process %d result %d\n", getpid(), pipe_fd);

    if (pipe_fd == -1)
        exit(EXIT_FAILURE);

    do {
        res = read(pipe_fd, buffer, BUFFER_SIZE);
        bytes_read += res;
    } while (res > 0);

    printf("Process %d finished, %d bytes read\n", getpid(), bytes_read);
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