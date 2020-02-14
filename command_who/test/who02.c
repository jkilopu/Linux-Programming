/* who02.c - who with buffered reads
 *      - surpresses empty records
 *      - formats time nicely
 *      - buffers input(using utmplib)
 *      - alternative: show host
 *      - attention: 尤其注意如何通过各个函数的返回值进行沟通
 */
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <time.h>
#include <utmp.h>

#define SHOWHOST

int utmp_open(char *filename);
struct utmp *utmp_next(void);
int utmp_reload(void);
void utmp_close(void);
void show_info(struct utmp *putmp);
char *transfer_time(int32_t timeval);

int main(void)
{
    struct utmp *utbufp; /* holds pointer to next rec */

    if (utmp_open(UTMP_FILE) == -1)
    {
        perror(UTMP_FILE);
        exit(EXIT_FAILURE);
    }
    while ((utbufp = utmp_next()) != ((struct utmp *)NULL))
        show_info(utbufp);
    utmp_close();
    return 0;
}
// show_info没有更改
void show_info(struct utmp *putmp)
{
    if (putmp != NULL)
    {
        // 只输出登陆的用户
        if (putmp->ut_type == USER_PROCESS)
            // 对齐，其中-10.10意思为左对齐，限制字符10个，不足10个补空格
            printf("%-10.10s %-10.10s %s", putmp->ut_user, putmp->ut_line, transfer_time(putmp->ut_time));
    }
}
// transfer_time没有更改
char* transfer_time(int32_t timeval)
{
    time_t tmp = timeval;
    return ctime(&tmp) + 4;
}