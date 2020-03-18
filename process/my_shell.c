/* 
 * my_shell.c --version 0.2
 * 功能： 接受一条命令，并在PATH中寻找程序，在收到exit命令前重复上述工作（且能忽略键盘发出的中断信号）
 * 
 * strsep()总结：
 * 1. 传入的必须是指向字符串的指针char*，不能是数组名char[]。
 * 2. 被分割数组会被修改（分隔符处被换为'\0'），而传入的指针会指向到分隔符的下一位
 * 3. ***传二级指针的原因：要修改指针的指向，且要判断是否指向NULL
 * 4. 注意分隔符可以有多个（分隔符连在一起的情况比较特殊）
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <signal.h>
#include <string.h>

#define MAX_LENGTH 20

void execute(char **argv);
char **to_argv(char src[], char seps[]);
int count_argv(char src[]);

int main(void)
{
    char argbuf[MAX_LENGTH];
    char **argv;
    char seps[] = " ", exit_str[] = "exit\n";

    /* 从标准输入读入字符串，并根据其判断是否退出*/
    while (fgets(argbuf, MAX_LENGTH, stdin) && strcmp(argbuf, exit_str) != 0)
    {
        argbuf[strlen(argbuf) - 1] = '\0';
        /* 转换为参数列表 */
        argv = to_argv(argbuf, seps);
        /* 执行程序 */
        execute(argv);
    }

    return 0;
}
/* 执行参数列表中的程序（带命令行参数） */
void execute(char **argv)
{
    pid_t new_pid;
    int exit_status; // 子进程退出时的状态

    new_pid = fork();
    /* 根据pid判断子、父进程 */
    switch (new_pid)
    {
    case -1:
        perror("fork failed");
        exit(EXIT_FAILURE);
        break;
    case 0:
        execvp(argv[0], argv);
        perror("execvp failed");
        exit(EXIT_FAILURE);
    default:
        /* 忽略来自键盘的中断信号 */
        signal(SIGINT, SIG_IGN);
        /* 等待子进程并获取子进程信号 */
        while (wait(&exit_status) != new_pid)
            ;
        free(argv);
    }
}
/* 分隔原始字符串并返回参数列表（最后需要free） */
char **to_argv(char src[], char seps[])
{
    int i = 0, j = 0, num;
    char **argv = NULL, *p = src;

    /* 计算参数个数以便分配空间 */
    num = count_argv(src);
    argv = (char **)malloc((num + 1) * sizeof(char *));
    /* 分解参数 */
    for (j = 0; j < num; j++)
    {
        argv[j] = strsep(&p, seps); // 新知识：strsep的使用
        // printf("%d %s\n", j, argv[j]);
    }
    argv[j] = NULL;
    return argv;
}
/* 计算参数的个数 */
int count_argv(char src[])
{
    int i = 0, cnt = 1;
    while (src[i] != '\0')
        if (src[i++] == ' ')
            cnt++;
    return cnt;
}