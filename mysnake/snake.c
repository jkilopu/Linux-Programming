#include "snake.h"
#include "settings.h"
#include "fatal.h"
#include <ncurses.h>
#include <stdlib.h>

Snake CreateSnake(int length, char symbol)
{
    Snake s;
    if (((s = (Snake)malloc(sizeof(struct _snake))) == NULL)) // 空间的大小要正确啊！不然在后面的操作就有可能segmentation fault了
        FatalError("Out of space!");
    s->length = length, s->symbol = symbol;
    if ((s->list = (List *)calloc(2, sizeof(Node *))) == NULL)
        FatalError("Out of space!");
    InitSnake(s);
    return s;
}
void InitSnake(Snake s)
{
    int i;
    for (i = 0; i < s->length; i++)
        InsertHead(s->list, INITIAL_Y, INITIAL_X + i); // 不能用Add()!!!
    s->speed = DEFAULT_SPEED;
    s->y_dir = INITIAL_DIRECTION_Y;
    s->x_dir = INITIAL_DIRECTION_X;
}
void PrintSnake(Snake s)
{
    Node *p = s->list->head;
    while (p)
    {
        mvaddch(p->y, p->x, s->symbol);
        p = p->next;
    }
    refresh();
}
/* 只操作链表的头和尾实现蛇的移动 */
void MoveSnake(Snake s)
{
    // move head
    InsertHead(s->list, s->list->head->y + s->y_dir, s->list->head->x + s->x_dir);
    mvaddch(s->list->head->y, s->list->head->x, s->symbol);
    // move tail
    mvaddch(s->list->tail->y, s->list->tail->x, BLANK);
    DeleteTail(s->list);
    // put cursor back
    move(LOWER_BONDARY, 0);
}
bool HitBoundary(Snake s)
{
    if (s->list->head->y != 0 && s->list->head->y != LOWER_BONDARY - 1 && s->list->head->x != 0 && s->list->head->x != RIGHT_BONDARY - 1)
        return false;
    return true;
}
bool HitBody(Snake s)
{
    Node *p = s->list->head;
    while (p = p->next)
    {
        if (s->list->head->x == p->x && s->list->head->y == p->y)
            return true;
    }
    return false;
}
void TurnUp(Snake s)
{
    s->y_dir = -1;
    s->x_dir = 0;
}
void TurnDown(Snake s)
{
    s->y_dir = 1;
    s->x_dir = 0;
}
void TurnLeft(Snake s)
{
    s->y_dir = 0;
    s->x_dir = -1;
}
void TurnRight(Snake s)
{
    s->y_dir = 0;
    s->x_dir = 1;
}
void EraseSnake(Snake s)
{
    Node *p = s->list->head;
    while (p)
    {
        mvaddch(p->y, p->x, BLANK);
        p = p->next;
    }
}
void DisposeSnake(Snake s)
{
    Node *p = s->list->head, *tmp;
    // delete the snake
    while (p)
    {
        tmp = p->next;
        free(p);
        p = tmp;
    }
    // delete the list
    free(s->list);
    free(s);
}