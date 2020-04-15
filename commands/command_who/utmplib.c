/* utmplib.c - functions to buffer reads from utmp file
 * 
 *      functions are
 *          utmp_open(filename)  -  open file
 *              returns -1 on error
 *          utmp_next()          -  return pointer to next struct
 *              return NULL on EOF
 *          utmp_close()         -  close file
 *
 *      reads NRECS per read and then doles them out from the buffer
 *      尤其注意如何通过各个函数的返回值进行沟通       
 */
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <utmp.h>

#define NRECS 16
#define NULLUT ((struct utmp *)NULL)
#define UTSIZE (sizeof(struct utmp))

// 使用静态全局变量的好处是，在主程序中函数的参数减少，封装更彻底
static char utmpbuf[NRECS * UTSIZE];
static int num_recs, cur_rec;
static int fd_utmp = -1;

int utmp_open(char *filename);
struct utmp *utmp_next(void);
static int utmp_reload(void);
void utmp_close(void);
// 五大过程，四大函数：打开、读入、指向、重填、关闭
int utmp_open(char *filename)
{
    fd_utmp = open(filename, O_RDONLY);
    cur_rec = num_recs = 0;
    return fd_utmp;
}

struct utmp *utmp_next(void)
{
    struct utmp *recp;
    if (fd_utmp == -1)
        return NULLUT;
    /* 核心所在：
       1. 缓冲区未满时什么也不做
       2. 缓冲区满时，重新装填。若再无信息，则返回NULLUT，终止
    */
    if (cur_rec == num_recs && utmp_reload() == 0)
        return NULLUT;
    recp = (struct utmp *)&utmpbuf[cur_rec * UTSIZE];
    cur_rec++;
    return recp;
}
static int utmp_reload(void)
{
    int amt_read;
    amt_read = read(fd_utmp, utmpbuf, NRECS * UTSIZE); // 读入的字节数
    num_recs = amt_read / UTSIZE;
    cur_rec = 0;
    return num_recs;
}
void utmp_close(void)
{
    if (fd_utmp != -1)
        if (close(fd_utmp) == -1)
        {
            perror(UTMP_FILE);
            exit(EXIT_FAILURE);
        }
}