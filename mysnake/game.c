#include "game.h"
#include "snake.h"
#include "food.h"
#include "record.h"
#include "scoreboard.h"
#include "settings.h"
#include "fatal.h"
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>
#include <ncurses.h>

// 全局变量（好像信号处理函数不能传参，暂时用着全局变量吧）
Snake snake;
Food food;
int key;
Scoreboard scoreboard;
Record current_record;

void setup(void)
{
    initscr();
    crmode();
    clear();

    scoreboard = CreateScoreboard(RECORD_MAX_NUM);
    // 读取记录
    ReadScoreboard(scoreboard);
    // 玩家登录
    Login();
    noecho();
    // 显示记录
    int number = ShowScoreboardWithCurrentRecord(scoreboard, current_record, RECORD_1ST_Y, RECORD_1ST_X);
    ShowRecord(current_record, number, RECORD_1ST_Y + scoreboard->size + 3, RECORD_1ST_X);

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
    // 刷新
    refresh();
    // 设置信号
    signal(SIGALRM, DetactAndMove);
    // 设置以定时发送信号
    set_ticker(DEFAULT_SPEED);
}

void Login(void)
{
    char name[NAME_MAX_LENGTH + 1];
    mvaddstr(LOWER_BONDARY / 3, RIGHT_BONDARY / 2 - 3, "Your name: ");
    refresh();
    getnstr(name, NAME_MAX_LENGTH + 1);
    mvaddnstr(LOWER_BONDARY / 3, RIGHT_BONDARY / 2 - 3, "                                              ", NAME_MAX_LENGTH + 11);
    mvaddstr(RECORD_1ST_Y + scoreboard->size + 2, RECORD_1ST_X, "You:");
    refresh();
    current_record = CreateRecord(name);
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
        do
            key = getchar();
        while (key != 'r' && key != 'q');
        if (key == 'r')
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
        // Score increase
        if (current_record->score + 10 < SCORE_MAX)
            current_record->score += 10;
        // Sort and show
        int number = ShowScoreboardWithCurrentRecord(scoreboard, current_record, RECORD_1ST_Y, RECORD_1ST_X);
        ShowRecord(current_record, number, RECORD_1ST_Y + scoreboard->size + 3, RECORD_1ST_X);
        refresh();
    }
    signal(SIGALRM, DetactAndMove);
}

void Restart(void)
{
    current_record->score = 0;
    int number = ShowScoreboardWithCurrentRecord(scoreboard, current_record, RECORD_1ST_Y, RECORD_1ST_X);
    ShowRecord(current_record, number, RECORD_1ST_Y + scoreboard->size + 3, RECORD_1ST_X);
    refresh();
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
    DestroyScoreboard(scoreboard);
    free(current_record);
    // delete fodd
    free(food);
}
