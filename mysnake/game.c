#include "game.h"
#include "snake.h"
#include "food.h"
#include "settings.h"
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>
#include <ncurses.h>

// 全局变量（好像信号处理函数不能传参，暂时用着全局变量吧）
Snake snake;
Food food;
int key;

void setup(void)
{
    initscr();
    noecho();
    crmode();
    clear();

    srand(time(NULL));
    start();
}
void start(void)
{
    // 画墙
    DrawBoundary();
    // 构建、画蛇
    snake = CreateSnake(DEFAULT_LENGTH, DEFAULT_BODY);
    PrintSnake(snake);
    // 放食物
    food = PutFood(food);
    // 设置信号
    signal(SIGALRM, DetactAndMove);
    // 设置以定时发送信号
    set_ticker(DEFAULT_SPEED);
}
void DrawBoundary(void)
{
    int i;
    // 上下边
    for (i = 0; i < RIGHT_BONDARY; i++)
    {
        mvaddch(0, i, WALL);
        mvaddch(LOWER_BONDARY - 1, i, WALL);
    }
    // 左右边
    for (i = 0; i < LOWER_BONDARY; i++)
    {
        mvaddch(i, 0, WALL);
        mvaddch(i, RIGHT_BONDARY - 1, WALL);
    }
    refresh();
}
void DetactAndMove(int signum)
{
    signal(SIGALRM, SIG_IGN); // 避免重入
    MoveSnake(snake);
    // show
    refresh();
    if (HitBoundary(snake) || HitBody(snake))
    {
        set_ticker(0);
        // remove food
        mvaddch(food->y, food->x, BLANK);
        // game over massage
        mvaddstr(LOWER_BONDARY / 3, RIGHT_BONDARY / 2 - 3, "Game Over! ");
        refresh();
        sleep(2);
        mvaddstr(LOWER_BONDARY / 3, RIGHT_BONDARY / 2 - 3, "Restart?  ");
        refresh();
        if ((key = getchar()) == 'r')
        {
            mvaddstr(LOWER_BONDARY / 3, RIGHT_BONDARY / 2 - 3, "          ");
            Restart();
        }
    }
    else if (HitFood(snake, food))
    {
        // add the body to tail
        Add(snake->list, snake->list->tail->y + snake->y_dir, snake->list->tail->x + snake->x_dir);
        // remove and delete food
        free(food);
        // reput food
        food = PutFood(food);
    }
    signal(SIGALRM, DetactAndMove);
}
void Restart(void)
{
    // erase and delete snake
    EraseSnake(snake);
    DisposeSnake(snake);
    // delete food
    free(food);
    // set again
    start();
}
void wrapup(void)
{
    set_ticker(0);
    endwin();
    DisposeSnake(snake);
    // delete fodd
    free(food);
}