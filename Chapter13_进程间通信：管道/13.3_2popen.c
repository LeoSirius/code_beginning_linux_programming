/*
 * NOTES:
 * 如果要从管道中读入的数据太大，一个buffer装不下，可以多次读取
 */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main()
{
    FILE *read_fp;
    char buffer[BUFSIZ + 1];
    int chars_read;

    memset(buffer, '\0', sizeof(buffer));
    read_fp = popen("ps ax", "r");
    if (read_fp != NULL) {
        chars_read = fread(buffer, sizeof(char), BUFSIZ, read_fp);
        while (chars_read > 0) {
            buffer[chars_read - 1] = '\0';
            printf("Reading %d: - \n %s\n", BUFSIZ, buffer);
            chars_read = fread(buffer, sizeof(char), BUFSIZ, read_fp);
        }
        pclose(read_fp);
        exit(EXIT_SUCCESS);
    }
    exit(EXIT_FAILURE);
}


// leo@ubuntu:~/c_test$ ./a.out 
// Reading 8192: - 
//     PID TTY      STAT   TIME COMMAND
//      1 ?        Ss     0:15 /sbin/init auto noprompt
//      2 ?        S      0:00 [kthreadd]
// ...
//  36888 pts/1    S+     0:00 ./a.out
//  36889 pts/1    S+     0:00 sh -c ps ax
//  36890 pts/1    R+     0:00 ps ax