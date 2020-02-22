#include "bufferlib.h"
/* bufferlib.c - functions to buffer reads from RankLists file
 * 
 *      functions are
 *          buf_open(filename)  -  open file
 *              returns -1 on error
 *          buf_next()          -  return pointer to next struct
 *              return NULL on EOF
 *          buf_close()         -  close file
 *
 *      reads NRECS per read and then doles them out from the buffer
 *      尤其注意如何通过各个函数的返回值进行沟通       
 */
int fd_sb = -1;

int buf_open(char *filename)
{
    fd_sb = open(filename, O_CREAT | O_APPEND);
    cur_rec = num_recs = 0;
    return fd_sb;
}

ScoreBoard buf_next(void)
{
    ScoreBoard recp;
    if (fd_sb == -1)
        return NULLSB;
    /* 核心所在：
       1. 缓冲区未满时什么也不做
       2. 缓冲区满时，重新装填。若再无信息，则返回NULLUT，终止
    */
    if (cur_rec == num_recs && buf_reload() == 0)
        return NULLSB;
    recp = (ScoreBoard)&buf[cur_rec * RECORDSIZE];
    cur_rec++;
    return recp;
}
static int buf_reload(void)
{
    int amt_read;
    amt_read = read(fd_sb, buf, NRECS * RECORDSIZE); // 读入的字节数
    num_recs = amt_read / RECORDSIZE;
    cur_rec = 0;
    return num_recs;
}
void buf_close(void)
{
    if (fd_sb != -1)
        if (close(fd_sb) == -1)
        {
            perror("RankLists");
            exit(EXIT_FAILURE);
        }
}