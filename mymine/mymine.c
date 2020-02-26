#include <curses.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define MAPSIZE 10
#define ACTUAL_SIZE (MAPSIZE * 4 + 1)
#define SQUARE '@'
#define MINES '*'
#define BLANK ' '
#define TOVIR(__j__) ((__j__ - 1) / 4)
#define TOACT(__i__) (4 * __i__ + 1)
const int dir[8][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}, {1, -1}, {-1, 1}, {1, 1}, {-1, -1}};

void setup(void);
void start(void);

void init_curse(void);
void draw_square(int y, int x);
int **create_map(int size);
void draw_map(int size);
void put_number(int **m, int size);
void draw_number(int **m, int pos_y, int pos_x);

void examine(int **m, int pos_y, int pos_x);
void which_dir(int ch);
void move_curse(int y, int x, int dir_y, int dir_x);

void generate_mine(int **m, int size);
void draw_mine(int y, int x);
void swap(int *a, int *b);

void delete_map(int **m, int size);

int **map;
char ch;

int main(void)
{
    int get_y, get_x;
    setup();
    start();
    while ((ch = getchar()) != 'q')
    {
        if (ch == ' ')
        {
            getyx(stdscr, get_y, get_x);
            examine(map, get_y, get_x);
        }
        else
            which_dir(ch);
    }
    endwin();
    delete_map(map, MAPSIZE);
    return 0;
}
void setup(void)
{
    srand(time(NULL));
    initscr();
    clear();
    noecho();
    cbreak();
}
void start(void)
{
    if (map == NULL)
        map = create_map(MAPSIZE);
    draw_map(MAPSIZE);
    generate_mine(map, MAPSIZE);
    put_number(map, MAPSIZE);
    init_curse();
    refresh();
}
void examine(int **m, int pos_y, int pos_x)
{
    int y = TOVIR(pos_y), x = TOVIR(pos_x);
    if (m[y][x] == -1)
        draw_mine(pos_y, pos_x);
    else
        draw_number(m, pos_y, pos_x);
}
void init_curse(void)
{
    move(1, 1);
}
/* draw square with a center */
void draw_square(int pos_y, int pos_x)
{
    int k;
    for (k = 0; k < 8; k++)
        mvaddch(pos_y + dir[k][0], pos_x + dir[k][1], SQUARE);
}
/* create the map according to the size */
int **create_map(int size)
{
    int **m;
    m = (int **)malloc(sizeof(int *) * size);
    for (int i = 0; i < size; i++)
        m[i] = (int *)calloc(size, sizeof(int));
    return m;
}
void delete_map(int **m, int size)
{
    for (int i = 0; i < size; i++)
        free(m[i]);
    free(m);
}
void draw_map(int size)
{
    for (int i = 1; i < ACTUAL_SIZE; i += 4)
        for (int j = 1; j < ACTUAL_SIZE; j += 4)
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
    int move_y = 4 * dir_y + y, move_x = 4 * dir_x + x; // 移动后的位置
    if (move_x < ACTUAL_SIZE && move_y < ACTUAL_SIZE)
        move(move_y, move_x);
    refresh();
}
void generate_mine(int **m, int size)
{
    int a[MAPSIZE];
    int x, y, count;
    for (count = 0; count < 10;)
    {
        x = rand() % size;
        y = rand() % size;
        if (m[y][x] != -1)
        {
            m[y][x] = -1;
            count++;
        }
    }
}
void draw_mine(int pos_y, int pos_x)
{
    mvaddch(pos_y, pos_x, MINES);
    for (int k = 0; k < 8; k++)
    {
        if (k < 4)
            mvaddch(pos_y + dir[k][0], pos_x + dir[k][1], MINES);
        else
            mvaddch(pos_y + dir[k][0], pos_x + dir[k][1], BLANK);
    }
    move(pos_y, pos_x);
    refresh();
}
void put_number(int **m, int size)
{
    int i, j, k, count, x, y;
    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            if (m[i][j] == 0)
            {
                count = 0;
                for (k = 0; k < 8; k++)
                {
                    y = i + dir[k][0];
                    x = j + dir[k][1];
                    if ((y >= 0 && y < size) && (x >= 0 && x < size))
                    {
                        if (m[y][x] == -1)
                            count++;
                    }
                }
                m[i][j] = count;
            }
        }
    }
}
void draw_number(int **m, int pos_y, int pos_x)
{
    switch (m[pos_y][pos_x])
    {
    case 1:
        mvaddch(pos_y, pos_x, '1');
        break;
    case 2:
        mvaddch(pos_y, pos_x, '2');
        break;
    case 3:
        mvaddch(pos_y, pos_x, '3');
        break;
    case 4:
        mvaddch(pos_y, pos_x, '4');
        break;
    case 5:
        mvaddch(pos_y, pos_x, '5');
        break;
    case 6:
        mvaddch(pos_y, pos_x, '6');
        break;
    case 7:
        mvaddch(pos_y, pos_x, '7');
        break;
    case 8:
        mvaddch(pos_y, pos_x, '8');
        break;

    default:
        break;
    }
    move(pos_y, pos_x);
    refresh();
}
void swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}