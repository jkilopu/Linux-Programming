#include <stdio.h>
#include <curses.h>
#include <math.h>
#define R 10
int main(void)
{
    int x, y;
    double distance;
    initscr();

    clear();
    // 圆心
    move(LINES / 2, COLS / 2);
    addch('#');
    // 画圆（效率低）
    for (y = LINES / 2 - R; y <= LINES / 2 + R; y++)
    {
        for (x = COLS / 2 - R; x <= COLS / 2 + R; x++)
        {
            distance = hypot(x - COLS / 2, y - LINES / 2);
            // printf("%lf\n", distance);
            if (R == (int)(distance + 0.5))
            {
                move(y, x);
                addch('@');
            }
        }
    }
    refresh();
    getch();

    endwin();
    return 0;
}