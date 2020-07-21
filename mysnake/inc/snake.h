#ifndef __SNAKE_H
#define __SNAKE_H

#include "list.h"
#include <stdbool.h>

#define DEFAULT_LENGTH 5
#define DEFAULT_BODY 'o'

typedef struct _snake
{
    List *list;
    char symbol;
    unsigned int length;
    int y_dir, x_dir; /* 上左-1，下右1 */
    int speed;
} * Snake;

Snake CreateSnake(int length, char symbol);
void InitSnake(Snake s);
void PrintSnake(Snake s);
void MoveSnake(Snake s);
bool HitBoundary(Snake s);
bool HitBody(Snake s);
void TurnUp(Snake s);
void TurnDown(Snake s);
void TurnLeft(Snake s);
void TurnRight(Snake s);
void EraseSnake(Snake s);
void DisposeSnake(Snake s);

#endif