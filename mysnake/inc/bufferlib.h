#ifndef _buflib_h
#define _buflib_h

#include "mysnake.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <utmp.h>

#define NRECS 16
#define NULLSB ((ScoreBoard)NULL)
#define RECORDSIZE sizeof(struct _board)

// 使用静态全局变量的好处是，在主程序中函数的参数减少，封装更彻底
static char buf[NRECS * RECORDSIZE];
static int num_recs, cur_rec;

// 五大过程，四大函数：打开、读入、指向、重填、关闭
int buf_open(char *filename);
ScoreBoard buf_next(void);
static int buf_reload(void);
void buf_close(void);

#endif