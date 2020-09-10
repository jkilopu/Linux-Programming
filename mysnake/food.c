#include "food.h"
#include "snake.h"
#include "settings.h"
#include "fatal.h"
#include <ncurses.h>
#include <stdlib.h>

extern Interface interface;

bool HitFood(Snake s, Food f)
{
    if (s->list->head->y == f->y && s->list->head->x == f->x)
        return true;
    return false;
}
Food PutFood(Snake s)
{
    Food f = (Food)malloc(sizeof(struct _food));
    if (f == NULL)
        FatalError("Out of space!");
    int y, x;
    do
    {
        y = rand() % (interface.lower_boundary - 2) + 1; /* 产生1～interface.lower_boundary-2的数字 */
        x = rand() % (interface.right_boundary - 2) + 1;
    } while (OnSnake(s, y, x));
    f->y = y, f->x = x;
    f->symbol = FOOD;
    mvaddch(f->y, f->x, f->symbol);
    return f;
}