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
#include "game.h"
#include "snake.h"
#include "food.h"
#include "fatal.h"
#include <stdio.h>

extern Snake snake;
extern int key;

int main(void)
{
    setup();

    while ((key = getchar()) != 'q')
    {
        if (key == 'w')
            if (snake->y_dir != 1)
                TurnUp(snake);
        if (key == 's')
            if (snake->y_dir != -1)
                TurnDown(snake);
        if (key == 'a')
            if (snake->x_dir != 1)
                TurnLeft(snake);
        if (key == 'd')
            if (snake->x_dir != -1)
                TurnRight(snake);
    }

    wrapup();
    return 0;
}