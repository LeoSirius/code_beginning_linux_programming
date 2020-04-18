#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <curses.h>

void printw_at(int y, int x, char *str)
{
    move(y, x);
    printw("%s", str);
}

int main()
{
    const char witch_one[] = " First Witch  ";
    const char witch_two[] = " Second Witch ";
    const char *scan_ptr;

    initscr();

    
    attron(A_BOLD);
    printw_at(5, 15, "Macbeth");
    attroff(A_BOLD);
    refresh();
    sleep(1);

    
    attron(A_STANDOUT);
    printw_at(8, 15, "Thunder and Lightning");
    attroff(A_STANDOUT);
    refresh();
    sleep(1);

    printw_at(10, 10, "When shall we three meet again");
    printw_at(11, 23, "In thunder, lightning, or in rain?");
    printw_at(13, 10, "When the hurlyburly's done.");
    printw_at(14, 23, "When the battle's lost and won.");
    refresh();
    sleep(1);

    /* 打印演员名字 */
    attron(A_DIM);
    scan_ptr = witch_one + strlen(witch_one) - 1; // 指向最后一个字符
    while (scan_ptr != witch_one) {
        move(10, 10);
        insch(*scan_ptr--);
    }
    scan_ptr = witch_two + strlen(witch_two) - 1;
    while (scan_ptr != witch_two) {
        move(13, 10);
        insch(*scan_ptr--);
    }
    attroff(A_DIM);
    refresh();
    sleep(1);

    /* 最后把光标移到右下角，并结束程序 */
    move (LINES - 1, COLS - 1);
    refresh();
    sleep(1);

    endwin();
    exit(EXIT_SUCCESS);
}
