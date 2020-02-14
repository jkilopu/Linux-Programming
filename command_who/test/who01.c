/* who01.c -- basic implementation of who */
#include <stdio.h>
#include <stdlib.h>
#include <utmp.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#define SIZE 4096
void show_info(struct utmp *putmp);
char* transfer_time(int32_t timeval);
int main(void)
{
    int fd, reclen = sizeof(struct utmp);
    struct utmp information;

    // 打开utmp文件
    if ((fd = open(UTMP_FILE, O_RDONLY)) == -1)
    {
        perror(UTMP_FILE);
        exit(EXIT_FAILURE);
    }
    // 读取、输出到屏幕
    while (read(fd, &information, reclen) == reclen)
        show_info(&information);
    // 关闭文件
    if (close(fd) == -1)
    {
        perror(UTMP_FILE);
        exit(EXIT_FAILURE);
    }

    return 0;
}
void show_info(struct utmp *putmp)
{
    if (putmp != NULL)
            printf("%-10.10s %-10.10s %s", putmp->ut_user, putmp->ut_line, transfer_time(putmp->ut_time));
}
// 借助中间变量及升级，使ctime的参数类型符合
char* transfer_time(int32_t timeval)
{
    time_t tmp = timeval;
    return ctime(&tmp) + 4;
}