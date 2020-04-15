#include "list.h"
#include "fatal.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>
#include <curses.h>
#include <signal.h>

struct _snake
{
    List *list;
    char symbol;
    unsigned int length;
    int y_dir, x_dir; /* 上左-1，下右1 */
    int speed;
};
typedef struct _snake *Snake;
typedef struct _food
{
    int y, x;
    char symbol;
} * Food;

void setup(void);
void start(void);
int set_ticker(int n_msecs);
void DrawBoundary(void);
Snake CreateSnake(int length, char symbol);
void InitSnake(Snake s);
void PrintSnake(Snake s);
void DetactAndMove(int signum);
void MoveSnake(Snake s);
bool HitBoundary(Snake s);
bool HitBody(Snake s);
bool HitFood(Snake s, Food f);
Food PutFood(Food f);
void TurnUp(Snake s);
void TurnDown(Snake s);
void TurnLeft(Snake s);
void TurnRight(Snake s);
void EraseSnake(Snake s);
void DisposeSnake(Snake s);
void Restart(void);
void wrapup(void);

#define RIGHT_BONDARY 100
#define LOWER_BONDARY 50
#define DEFAULT_SPEED 100
#define DEFAULT_LENGTH 5
#define DEFAULT_BODY 'o'
#define BLANK ' '
#define WALL '#'
#define FOOD '*'
#define INITIAL_X 10
#define INITIAL_Y 10
#define INITIAL_DIRECTION_X 1
#define INITIAL_DIRECTION_Y 0