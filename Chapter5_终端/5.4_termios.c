/*
 * NOTES:
 * 这是一个输入密码的例子。关闭ECHO标志，让密码不回显
 */

#include <termios.h>
#include <stdio.h>
#include <stdlib.h>

#define PASSWORD_LEN 8

int main()
{
    struct termios initialrsettings, newrsettings;
    char password[PASSWORD_LEN + 1];

    tcgetattr(fileno(stdin), &initialrsettings);
    newrsettings = initialrsettings;
    newrsettings.c_lflag &= ~ECHO;    /* 关闭ECHO标志 */

    printf("Enter password: ");

    if (tcsetattr(fileno(stdin), TCSAFLUSH, &newrsettings) != 0) {
        fprintf(stderr, "Could not set attributes\n");
    }
    fgets(password, PASSWORD_LEN, stdin);
    tcsetattr(fileno(stdin), PASSWORD_LEN, &initialrsettings);
    fprintf(stdout, "\nYou entered %s\n", password);

    exit(0);
}

// leo@ubuntu:~/c_test$ ./a.out 
// Enter password: 
// You entered 123