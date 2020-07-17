/*
 * NOTES:
 * stdscr是WINDOW的一个实例，WINDOW还可以创建其他窗口实例
 */

#include <unistd.h>
#include <stdlib.h>
#include <curses.h>

int main()
{
    WINDOW *new_window_ptr;
    WINDOW *popup_window_ptr;
    int x_loop, y_loop;
    char a_letter = 'a';

    initscr();

    move(5,5);
    printw("%s", "Testing multuple windows");
    refresh();

    /* 先用字符填充屏幕 */
    for (y_loop = 0; y_loop < LINES - 1; y_loop++) {
        for (x_loop = 0; x_loop < COLS - 1; x_loop++) {
            mvwaddch(stdscr, y_loop, x_loop, a_letter);
            a_letter++;
            if (a_letter > 'z')
                a_letter = 'a';
        }
    }
    refresh();
    sleep(2);

    /* 新建一个窗口，然后填充一些字符 */
    new_window_ptr = newwin(10, 20, 5, 5);
    mvwprintw(new_window_ptr, 2, 2, "%s", "Hello World");
    mvwprintw(new_window_ptr, 5, 2, "%s", "Notice how very long lones wrap inside the window");
    wrefresh(new_window_ptr);
    sleep(2);

    /* 更改背景窗口，从字母换成数字 */
    a_letter = '0';
    for (y_loop = 0; y_loop < LINES - 1; y_loop++) {
        for (x_loop = 0; x_loop < COLS - 1; x_loop++) {
            mvwaddch(stdscr, y_loop, x_loop, a_letter);
            a_letter++;
            if (a_letter > '9')
                a_letter = '0';
        }
    }
    refresh();
    sleep(2);

    /* 如果直接刷新，不会有任何变化，因为newwindow没有变过。touch一次之后再刷新，就能刷新到前面 */
    touchwin(new_window_ptr);
    wrefresh(new_window_ptr);
    sleep(2);

    /* 我们再创建一个popup window */
    popup_window_ptr = newwin(10, 20, 8, 8);
    box(popup_window_ptr, '|', '-');
    mvwprintw(popup_window_ptr, 5, 2, "Pop Up Window");
    wrefresh(popup_window_ptr);
    sleep(2);

    /* 最后再刷新、关闭 */

    touchwin(new_window_ptr);
    wrefresh(new_window_ptr);
    sleep(2);

    wclear(new_window_ptr);
    wrefresh(new_window_ptr);
    sleep(2);
    delwin(new_window_ptr);

    touchwin(popup_window_ptr);
    wrefresh(popup_window_ptr);
    sleep(2);
    delwin(new_window_ptr);

    touchwin(stdscr);
    refresh();
    sleep(2);
    endwin();

    exit(0);
}