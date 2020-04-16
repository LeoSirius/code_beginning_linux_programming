/*
 * NOTES:
 * isatty判断fd是否指向终端，利用这个结果，可以在重定向输出时，把想让用户看到的直接输出到终端上
 * /dev/tty始终指向当前终端
 * getchoice函数中的输入输出都被指向了/dev/tty，所以即使是重定向输出，
 * 用户仍然能在终端上看到getchoice函数的输出
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

char *menu[] = {
    "a - add new record",
    "d - delete record",
    "q - quit",
    NULL,
};

int getchoice(char *greet, char *choices[], FILE *in, FILE *out);

int main()
{
    int choice = 0;
    FILE *input;
    FILE *output;

    if (!isatty(fileno(stdout))) {
        fprintf(stderr, "You are not a terminal, OK\n");
    }

    input = fopen("/dev/tty", "r");
    output = fopen("/dev/tty", "w");
    if (!input || !output) {
        fprintf(stderr, "Unable to open /dev/tty\n");
        exit(1);
    }

    do {
        choice = getchoice("Please select an action", menu, input, output);
        printf("You have chosen: %c\n", choice);
    } while (choice != 'q');
    exit(0);
}

int getchoice(char *great, char *choices[], FILE *in, FILE *out)
{
    int chosen = 0;
    int selected;
    char **option;

    do {
        fprintf(out, "Choice: %s\n", great);
        option = choices;
        while (*option) {
            fprintf(out, "%s\n", *option);
            option++;
        }
        /* skip 换行符 */
        do {
            selected = fgetc(in);
        } while (selected == '\n');

        option = choices;
        while (*option) {
            if (selected == *option[0]) {
                chosen = 1;
                break;
            }
            option++;
        }
        if (!chosen) {
            fprintf(out, "Incorrect choice, select again\n");
        }
    } while (!chosen);
    return selected;
}

// leo@ubuntu:~/c_test$ ./a.out > file
// You are not a terminal, OK
// Choice: Please select an action
// a - add new record
// d - delete record
// q - quit
// d
// Choice: Please select an action
// a - add new record
// d - delete record
// q - quit
// q

// leo@ubuntu:~/c_test$ cat file 
// You have chosen: d
// You have chosen: q