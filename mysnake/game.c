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
Interface interface;

void setup(void)
{
    initscr();
    crmode();
    clear();
    ChooseInterfaceSize();

    scoreboard = CreateScoreboard(RECORD_MAX_NUM);
    // 玩家登录
    Login();
    noecho();

    srand(time(NULL));
    start();
}

void start(void)
{
    // 读取记录
    ReadScoreboard(scoreboard);
    // 显示记录
    int number = ShowScoreboardWithCurrentRecord(scoreboard, current_record, RECORD_1ST_Y, RECORD_1ST_X(interface.right_boundary));
    mvaddstr(RECORD_1ST_Y + SHOWED_MAX_NUM + 2, RECORD_1ST_X(interface.right_boundary), "You:");
    ShowRecord(current_record, number, RECORD_1ST_Y + SHOWED_MAX_NUM + 3, RECORD_1ST_X(interface.right_boundary));
    // 画墙
    DrawBoundary();
    // 构建、画蛇
    snake = CreateSnake(DEFAULT_LENGTH, DEFAULT_BODY);
    PrintSnake(snake);
    // 放食物
    food = PutFood(snake);
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
    mvaddstr(interface.lower_boundary / 3, interface.right_boundary / 2 - 3, "Your name: ");
    refresh();
    getnstr(name, NAME_MAX_LENGTH + 1);
    mvaddnstr(interface.lower_boundary / 3, interface.right_boundary / 2 - 3, "                                              ", NAME_MAX_LENGTH + 11);
    refresh();
    current_record = CreateRecord(name);
}

void ChooseInterfaceSize(void)
{
    int y = 0, x = 0;
    getmaxyx(stdscr, y, x);
    if (y < 30 || x < 30)
    {
        nocrmode();
        endwin();
        FatalError("Screen too small!");
    }
    /* This ratio seems ok,
     * it leaves enough space for scoreboard 
     */
    interface.lower_boundary = y * INTERFACE_SCR_RATIO_Y;
    interface.right_boundary = x * INTERFACE_SCR_RATIO_X;
}

void DrawBoundary(void)
{
    int i;
    // 上下边
    for (i = 0; i < interface.right_boundary; i++)
    {
        mvaddch(0, i, WALL);
        mvaddch(interface.lower_boundary - 1, i, WALL);
    }
    // 左右边
    for (i = 0; i < interface.lower_boundary; i++)
    {
        mvaddch(i, 0, WALL);
        mvaddch(i, interface.right_boundary - 1, WALL);
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
        // save name-score data
        SaveData();
        // remove food
        mvaddch(food->y, food->x, BLANK);
        // game over massage
        mvaddstr(interface.lower_boundary / 3, interface.right_boundary / 2 - 3, "Game Over! ");
        refresh();
        sleep(2);
        mvaddstr(interface.lower_boundary / 3, interface.right_boundary / 2 - 3, "Restart?  ");
        refresh();
        do
            key = getchar();
        while (key != 'r' && key != 'q');
        if (key == 'r')
        {
            mvaddstr(interface.lower_boundary / 3, interface.right_boundary / 2 - 3, "          ");
            Restart();
        }
        else
        {
            wrapup();
            exit(0);
        }
    }
    else if (HitFood(snake, food))
    {
        // add the body to tail
        Add(snake->list, snake->list->tail->y + snake->y_dir, snake->list->tail->x + snake->x_dir);
        // remove and delete food
        free(food);
        // reput food
        food = PutFood(snake);
        // Score increase
        if (current_record->score + 10 < SCORE_MAX)
            current_record->score += 10;
        // Sort and show
        int number = ShowScoreboardWithCurrentRecord(scoreboard, current_record, RECORD_1ST_Y, RECORD_1ST_X(interface.right_boundary));
        ShowRecord(current_record, number, RECORD_1ST_Y + SHOWED_MAX_NUM + 3, RECORD_1ST_X(interface.right_boundary));
        refresh();
    }
    signal(SIGALRM, DetactAndMove);
}

void SaveData(void)
{
    int found = FindRecord(scoreboard->records, scoreboard->size, current_record->name);
    WriteScoreboard(scoreboard, current_record, found);
}

void Restart(void)
{
    current_record->score = 0;
    mvaddnstr(RECORD_1ST_Y + scoreboard->size + 3, RECORD_1ST_X(interface.right_boundary), "                                          ", NUM_MAX_LENGTH + NAME_MAX_LENGTH + SCORE_MAX_LENGTH + 4);
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
    nocrmode();
    echo();
    endwin();
    DisposeSnake(snake);
    DestroyScoreboard(scoreboard);
    free(current_record);
    // delete fodd
    free(food);
}
