/* mysnake.c version 0.1 
 * usage: ./mysnake
 * 功能：（1）贪吃蛇的基本实现、（2）重新开始游戏
 * 框架：随时准备读取用户输入（处于阻断状态），利用set_ticker()函数定时（很短）发送信号，收到信号时检测蛇的状态并移动(DetectAndMove())（蛇只有在移动时才会有状态的改变）
 * 知识点:1.经典信号的部分使用
 *       2.发出信号的时间函数的使用
 *       3.链表的添加与删除
 *       4.判断状态
 *       5.malloc()与free()
 * 总结：1. 链表的操作很重要，第一个遇到的问题是没有注意蛇产生过程的特点（我的实现方法为从尾到头）
 *      2. 如果malloc的大小不对，短时间内可能没问题，最后一定会在某个奇怪的地方segmentation fault
 */
#include "mysnake.h"
#include "bufferlib.h"

int main(void)
{
    setup();

    while ((ch = getch()) != 'q')
    {
        if (ch == 'w')
            if (snake->y_dir != 1)
                TurnUp(snake);
        if (ch == 's')
            if (snake->y_dir != -1)
                TurnDown(snake);
        if (ch == 'a')
            if (snake->x_dir != 1)
                TurnLeft(snake);
        if (ch == 'd')
            if (snake->x_dir != -1)
                TurnRight(snake);
    }

    wrapup();
    return 0;
}
void setup(void)
{
    initscr();
    clear();

    if ((fd_sb = buf_open("RankLists")) == -1) /* 打开记录版 */
        Error("Can't open RankLists");
    scoreboard = CreateBoard(BOARDLENS); /* 构建记录板 */
    AddPlayer(scoreboard, BOARDLENS);
    srand(time(NULL));
    start();
}
void AddPlayer(ScoreBoard *sb, int length)
{
    // 构建记录版
    // 询问并添加当前玩家信息
    mvaddstr(LOWER_BONDARY / 3, RIGHT_BONDARY / 2 - 3, "Your name?");
    echo();
    nocrmode();
    scanw("%s", player.name); // 还不知道超过限定怎么解决
    mvaddstr(LOWER_BONDARY / 3, RIGHT_BONDARY / 2 - 3, "                              ");
    strncpy(sb[length - 1]->name, player.name, NAMELEN);
    player.rank = length;
}
void ReadScoreBoard(ScoreBoard *sb, int length)
{
    ScoreBoard tmp;
    for (int i = 0; i < length; i++)
        if ((tmp = buf_next()) != NULL)
        {
            free(sb[i]);
            sb[i] = tmp;
        }
}
void start(void)
{
    // 无回显、无缓冲
    noecho();
    crmode();
    // 读取记录
    ReadScoreBoard(scoreboard, BOARDLENS);
    // 画记录版
    DrawBoard(BOARDLENS);
    player.rank = DrawRecord(scoreboard, BOARDLENS);
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
ScoreBoard *CreateBoard(int length)
{
    ScoreBoard *sb = (ScoreBoard *)calloc(length, sizeof(ScoreBoard));
    if (sb == NULL)
        FatalError("Out of space!");
    for (int i = 0; i < length; i++)
    {
        sb[i] = (ScoreBoard)calloc(1, sizeof(struct _board));
        if (sb[i] == NULL)
            FatalError("Out of space!");
    }
    return sb;
}
void DrawBoard(int length)
{
    // 标题
    mvaddstr(1, RIGHT_BONDARY + RECORDLENS / 2 - sizeof(BOARDTITLE) / 2, BOARDTITLE);
    // 上下边
    mvaddnstr(0, RIGHT_BONDARY + 1, "____________________", RECORDLENS);
    mvaddnstr(length + 2, RIGHT_BONDARY + 1, "--------------------", RECORDLENS);
    // 左右边
    for (int i = 1; i <= length + 1; i++)
    {
        mvaddch(i, RIGHT_BONDARY + 1, '|');
        mvaddch(i, RIGHT_BONDARY + RECORDLENS, '|');
    }
    refresh();
}
int DrawRecord(ScoreBoard *sb, int length)
{
    for (int i = 0; i < length; i++)
    {
        // 只打印有用户名的用户
        if (strlen(sb[i]->name) != 0)
        {
            mvaddch(i + 2, RIGHT_BONDARY + 3, i + 1 + '0');                                  /* 打印排名 */
            mvaddstr(i + 2, RIGHT_BONDARY + 5, sb[i]->name);                                 /* 打印用户名 */
            mvprintw(i + 2, RIGHT_BONDARY + 1 + RECORDLENS - SCORELENS, "%d", sb[i]->score); /* 移动并在屏幕上格式化输出字符串 */
        }
    }
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
void DetactAndMove(int signum)
{
    signal(SIGALRM, SIG_IGN);
    MoveSnake(snake);
    // show
    refresh();
    if (HitBoundary(snake) || HitBody(snake))
        endgame();
    else if (HitFood(snake, food))
    {

        // length increase
        snake->length++;
        // add the body to tail
        Add(snake->list, snake->list->tail->y + snake->y_dir, snake->list->tail->x + snake->x_dir);
        // remove and delete food
        free(food);
        // reput food
        food = PutFood(food);
        // 当前用户分数增加
        scoreboard[player.rank - 1]->score += SCORE;
        // 重画记录
        DrawRecord(scoreboard, BOARDLENS);
    }
    signal(SIGALRM, DetactAndMove);
}
void MoveSnake(Snake s) /* 只操作链表的头和尾实现蛇的移动 */
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
    return (s->list->head->y == 0 || s->list->head->y == LOWER_BONDARY - 1 || s->list->head->x == 0 || s->list->head->x == RIGHT_BONDARY - 1);
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
bool HitFood(Snake s, Food f)
{
    return (s->list->head->y == f->y && s->list->head->x == f->x); // 只用一行就能判断
}
Food PutFood(Food f)
{
    f = (Food)malloc(sizeof(struct _food));
    if (f == NULL)
        FatalError("Out of space!");
    f->y = rand() % (LOWER_BONDARY - 2) + 1; /* 产生1～LOWER_BONDARY-2的数字 */
    f->x = rand() % (RIGHT_BONDARY - 2) + 1;
    f->symbol = FOOD;
    mvaddch(f->y, f->x, f->symbol);
    refresh();
    return f;
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
void DisposeBoard(ScoreBoard *sb, int length)
{
    for (int i = 0; i < length; i++)
        free(sb[i]);
    free(sb);
}
void WriteRecorde(int fd, ScoreBoard *sb, int length)
{
    for (int i = 0; i < length; i++)
        write(fd, sb[i], sizeof(struct _board));
}
void endgame(void)
{
    set_ticker(0);                                                              /* time stop */
    mvaddch(food->y, food->x, BLANK);                                           /* remove food */
    mvprintw(LOWER_BONDARY / 3, RIGHT_BONDARY / 2 - 6, "Game Over! q to quit"); /* game over massage */
    refresh();
}
void wrapup(void)
{
    endwin();
    buf_close();
    DisposeSnake(snake);
    WriteRecorde(fd_sb, scoreboard, BOARDLENS);
    DisposeBoard(scoreboard, BOARDLENS);
    // delete fodd
    free(food);
}
/* 给qsort用*/
int Comp(const void *a, const void *b)
{
    return ((ScoreBoard)a)->score > ((ScoreBoard)b)->score ? true : false;
}