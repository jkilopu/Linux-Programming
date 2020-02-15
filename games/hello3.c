/* hello3.c
 * purpose: using refresh and sleep for animated effects, and show how to use erase, time.
 * outline: initialize, draw stuff, wrap up
 */
#include <stdio.h>
#include <curses.h>
#include <unistd.h> //for sleep()
int main(void)
{
    int i;
    initscr();

    clear();
    for (i = 0; i < LINES; i++)
    {
        move(i, i * 2);
        if (i % 2 == 1)
            standout();
        addstr("Hello, world!");
        if (i % 2 == 1)
            standend();
        refresh();
        sleep(1);
        move(i, i * 2);
        addstr("               ");
    }

    endwin();
    return 0;
}