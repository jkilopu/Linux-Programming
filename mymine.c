#include <curses.h>
#include <stdlib.h>

#define MAPSIZE 10
#define SQUARE '@'
const int dir[8][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}, {1, -1}, {-1, 1}, {1, 1}, {-1, -1}};

void init_curse(void);
void draw_square(int y, int x);
int **create_map(int size);
void draw_map(int size);

void which_dir(int ch);
void move_curse(int y, int x, int dir_y, int dir_x);

int main(void)
{
    int **map;
    char ch;
    initscr();
    clear();
    noecho();
    cbreak();

    map = create_map(MAPSIZE);
    draw_map(MAPSIZE);
    init_curse();
    refresh();
    while ((ch = getchar()) != 'q')
    {
        which_dir(ch);
    }
    endwin();
    return 0;
}
void init_curse(void)
{
    move(1, 1);
}
/* draw square with a center */
void draw_square(int y, int x)
{
    int k;
    for (k = 0; k < 8; k++)
        mvaddch(y + dir[k][0], x + dir[k][1], SQUARE);
}
/* create the map according to the size */
int **create_map(int size)
{
    int **m;
    m = (int **)malloc(sizeof(int *) * MAPSIZE);
    for (int i = 0; i < size; i++)
        m[i] = calloc(sizeof(int), MAPSIZE);
    return m;
}
void draw_map(int size)
{
    int actual_size = 4 * size + 1;
    for (int i = 1; i < actual_size; i += 4)
        for (int j = 1; j < actual_size; j += 4)
            draw_square(i, j);
}
void which_dir(int ch)
{
    int y, x;
    getyx(stdscr, y, x);
    switch (ch)
    {
    case 'w':
        move_curse(y, x, dir[0][0], dir[0][1]);
        break;
    case 's':
        move_curse(y, x, dir[1][0], dir[1][1]);
        break;
    case 'a':
        move_curse(y, x, dir[2][0], dir[2][1]);
        break;
    case 'd':
        move_curse(y, x, dir[3][0], dir[3][1]);
        break;
    default:
        break;
    }
}
void move_curse(int y, int x, int dir_y, int dir_x)
{
    int actual_y = 4 * dir_y + y, actual_x = 4 * dir_x + x;
    if (actual_x < MAPSIZE && actual_y < MAPSIZE)
        move(actual_y, actual_x);
    refresh();
}