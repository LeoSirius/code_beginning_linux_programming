/*
 * NOTES:
 * 5.2中的menu要输入换行符，才会继续进行，也就是说，其实行编辑的。
 * 现在我们通过终端控制，来实现用户按下选项之后立即反馈的效果
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <termios.h>

char *menu[] = {
    "a - add new record",
    "d - delete derecord",
    "q - quit",
    NULL,
};

int getchoice(char *greet, char *choices[], FILE *in, FILE *out);

int main()
{
    int choice = 0;
    FILE *input;
    FILE *output;
    struct termios initial_settings, new_settings;

    if (!isatty(fileno(stdout))) {
        fprintf(stderr, "You are not a terminal, OK\n");
        exit(1);
    }

    input = fopen("/dev/tty", "r");
    output = fopen("/dev/tty", "w");
    if (!input || !output) {
        fprintf(stderr, "Unable to open /dev/tty\n");
        exit(1);
    }

    // 下面取出终端设置，并修改
    tcgetattr(fileno(input), &initial_settings);
    new_settings = initial_settings;
    new_settings.c_lflag &= ~ICANON;  // 关掉标准模式（canonical），标准模式即行标记模式
    new_settings.c_lflag &= ~ECHO;    // 关掉屏幕回显
    new_settings.c_cc[VMIN] = 1;      // VMIN --  Minimum number of characters for noncanonical read (MIN).
    new_settings.c_cc[VTIME] = 0;     // VTIME -- Timeout in deciseconds for noncanonical read (TIME).
    new_settings.c_lflag &= ~ISIG;    // 禁用INTR, QUIT, SUSP, or DSUSP等信号
    if (tcsetattr(fileno(input), TCSANOW, &new_settings) != 0) {
        fprintf(stderr, "could not set attributes\n");
    }

    do {
        choice = getchoice("Please select an action", menu, input, output);
        printf("You have chosen: %c\n", choice);
    } while (choice != 'q');

    /* 还原设置 */
    tcsetattr(fileno(input), TCSANOW, &initial_settings);

    exit(0);
}

int getchoice(char *greet, char *choices[], FILE *in, FILE *out)
{
    int chosen = 0;
    int selected;
    char **option;

    do {
        fprintf(out, "Choice: %s\n", greet);
        option = choices;
        while (*option) {
            fprintf(out, "%s\n", *option);
            ++option;
        }
        do {
            selected = fgetc(in);
        } while (selected == '\n' || selected == '\r');   // \r是回车，也需要跳过

        option = choices;
        while (*option) {
            if (selected == *option[0]) {
                chosen = 1;
                break;
            }
            ++option;
        }
        if (!chosen) {
            fprintf(out, "Incorrect choice, select again\n");
        }
    } while (!chosen);
    return selected;
}

// 可以看到，按下选项后直接做出了反应，不需要回车

// leo@ubuntu:~/c_test$ ./a.out 
// Choice: Please select an action
// a - add new record
// d - delete derecord
// q - quit
// You have chosen: a
// Choice: Please select an action
// a - add new record
// d - delete derecord
// q - quit
// You have chosen: q