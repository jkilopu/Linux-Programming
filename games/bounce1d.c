/* bounce1d.c
 * purpose: animation with user controlled speed and direction
 *    note: the handler does the animation
 *          the main program reads keyboard input
 * compile: gcc bounce1d.c set_ticker.c -lcurses -o bounce1d
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curses.h>
#include <signal.h>

/* some global settings main and the handler use */
#define MESSAGE "hello"
#define BLANK "     "
int row; /* current row */
int col; /* current column */
int dir; /* where we are going*/

void move_msg(int signum);
int set_ticker(int n_msecs);

int main(void)
{
    int delay;  /* bigger => slower */
    int ndelay; /* new delay*/
    int ch;     /* user input */

    initscr();
    crmode(); // ==cbreak, 除了 DELETE 或 CTRL 等仍被视为特殊控制字元外一切输入的字元将立刻被一一读取
    noecho();
    clear();

    row = 10; /* start here */
    col = 0;
    dir = 1;     /* add 1 to row number */
    delay = 200; /* 200ms = 0.2 seconds */

    move(row, 0);    /* get into position */
    addstr(MESSAGE); /* draw message */
    signal(SIGALRM, move_msg);
    set_ticker(delay);

    for (;;)
    {
        ndelay = 0;
        ch = getch();
        if (ch == 'Q')
            break;
        if (ch == ' ')
            dir = -dir;
        if (ch == 'f' && delay > 2)
            ndelay = delay / 2;
        if (ch == 's')
            ndelay = delay * 2;
        if (ndelay > 0)
            set_ticker(delay = ndelay);
    }
    endwin();
}
void move_msg(int signum)
{
    signal(SIGALRM, move_msg); /* reset, just in case ??? in case what? */
    move(row, col);
    addstr(BLANK);
    col += dir;      /* move to new column */
    move(row, col);  /* then set cursor */
    addstr(MESSAGE); /* redo message */
    refresh();       /* and who it*/
    /* now handle borders */
    if (dir == -1 && col <= 0)
        dir = 1;
    else if (dir == 1 && col + strlen(MESSAGE) >= COLS)
        dir = -1;
}