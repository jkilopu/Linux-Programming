#ifndef _mysnake_h
#define _mysnake_h

#include "list.h"
#include "fatal.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>
#include <curses.h>
#include <signal.h>

#define RIGHT_BONDARY 50
#define LOWER_BONDARY 25
#define DEFAULT_SPEED 80
#define DEFAULT_LENGTH 5
#define DEFAULT_BODY 'o'
#define BLANK ' '
#define WALL '#'
#define FOOD '*'
#define INITIAL_X 10
#define INITIAL_Y 10
#define INITIAL_DIRECTION_X 1
#define INITIAL_DIRECTION_Y 0

#define NAMELEN 10
#define BOARDLENS 5
#define RECORDLENS 20
#define SCORELENS 6
#define BOARDTITLE "RankLists"
#define SCORE 10

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
typedef struct _board
{
    char name[NAMELEN];
    int score, rank;
    time_t recordtime;
} * ScoreBoard;

// 全局变量（好像信号处理函数不能传参，暂时用着全局变量吧）
extern int fd_sb;
Snake snake;
Food food;
int ch;
ScoreBoard *scoreboard;
struct _board player;

void setup(void);
void AddPlayer(ScoreBoard* sb, int length);
void ReadScoreBoard(ScoreBoard *sb, int length);
void start();
int set_ticker(int n_msecs);
ScoreBoard* CreateBoard(int length);
void DrawBoard(int length);
int DrawRecord(ScoreBoard* sb, int length);
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
void WriteRecorde(int fd, ScoreBoard* sb, int length);
void DisposeBoard(ScoreBoard* sb, int length);
void endgame(void);
void wrapup(void);
int Comp(const void *a, const void *b);

#endif /* _mysnake_h */