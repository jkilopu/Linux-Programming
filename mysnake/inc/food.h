#ifndef __FOOD_H
#define __FOOD_H

#include "snake.h"
#include <stdbool.h>

#define FOOD '*'

typedef struct _food
{
    int y, x;
    char symbol;
} * Food;

bool HitFood(Snake s, Food f);
Food PutFood(Food f);

#endif