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
    struct termios init_settings, new_settings;
    char password[PASSWORD_LEN + 1];

    tcgetattr(fileno(stdin), &init_settings);
    new_settings = init_settings;
    new_settings.c_lflag &= ~ECHO;    /* 关闭ECHO标志 */

    printf("Enter password: ");

    if (tcsetattr(fileno(stdin), TCSAFLUSH, &new_settings) != 0) {
        fprintf(stderr, "Could not set attributes\n");
    }

    fgets(password, PASSWORD_LEN, stdin);
    tcsetattr(fileno(stdin), PASSWORD_LEN, &init_settings);
    fprintf(stdout, "\nYou entered %s\n", password);

    exit(0);
}

// leo@ubuntu:~/c_test$ ./a.out 
// Enter password: 
// You entered 123