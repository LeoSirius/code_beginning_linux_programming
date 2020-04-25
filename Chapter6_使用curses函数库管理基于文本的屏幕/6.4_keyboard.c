/*
 * NOTES:
 * ncurses中的函数除了能控制屏幕，还能控制键盘
 * echo(), noecho()开启和关闭回显
 * cbreak(), nocbreak()关闭和开启行编辑
 */

#include <unistd.h>
#include <stdlib.h>
#include <curses.h>
#include <string.h>

#define PW_LEN 256
#define NAME_LEN 256

int main()
{
    char name[NAME_LEN];
    char password[PW_LEN];
    const char *real_password = "xyzzy";
    int i = 0;

    initscr();

    move(5, 10);
    printw("%s", "Please login:");

    move(7, 10);
    printw("%s", "User name: ");
    getstr(name);

    move(8, 10);
    printw("%s", "Password: ");
    refresh();

    /* 用户出入密码，关闭行编辑，关闭回显 */
    cbreak();
    noecho();

    memset(password, '\0', sizeof(password));
    while (i < PW_LEN) {
        password[i] = getch();
        if (password[i] == '\n') break;
        move(8, 20 + i);
        addch('*');
        refresh();
        ++i;
    }

    /* 开启回显 */
    echo();
    nocbreak();

    move(11, 10);
    if (strncmp(real_password, password, strlen(real_password)) == 0)
        printf("%s", "Correct");
    else
        printf("%s", "Wrong");
    printw("%s", password);
    refresh();
    sleep(2);

    endwin();
    exit(EXIT_SUCCESS);
}