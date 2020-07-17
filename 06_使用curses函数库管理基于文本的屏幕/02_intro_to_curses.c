/*
 * NOTES:
 * 屏幕使用两个数据结构stdscr（屏幕将会是什么样）, curscr（屏幕当前的样子）。
 * 在调用refresh()时，比较这两个数据结构，并刷新屏幕
 * 
 * initscr()和endwin()用来创建和删除一些临时的数据结构
 */


#include <unistd.h>
#include <stdlib.h>
#include <curses.h>

int main()
{
    initscr();

    move(5, 15);
    printw("%s", "Hello World");
    refresh();

    sleep(2);

    endwin();
    exit(EXIT_SUCCESS);
}