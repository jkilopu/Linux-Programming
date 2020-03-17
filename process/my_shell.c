/* 
 * my_shell.c version 0.1
 * 功能： 接受一条命令，并在PATH中寻找程序，执行后死亡
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
#include <string.h>

#define MAX_LENGTH 20

char **to_argv(char src[], char seps[]);
int count_argv(char src[]);

int main(void)
{
    pid_t new_pid;
    char file[MAX_LENGTH];
    char **argv;
    char seps[] = " ";

    /* 从标准输入中获取输入 */
    fgets(file, MAX_LENGTH, stdin);
    file[strlen(file) - 1] = '\0';
    /* 转换为参数列表（同时将file变为{filename + '\0' + ....}）*/
    argv = to_argv(file, seps);

    /* fork出子程序 */
    new_pid = fork();
    if (new_pid == 0)
    {
        execvp(file, argv);
    }
    else
    {
        wait(NULL);
        return 0;
    }
}
char **to_argv(char src[], char seps[])
/* 分隔原始字符串并返回参数列表（最后需要free） */
{
    int i = 0, j = 0, num;
    char **argv = NULL, *p = src;

    /* 计算参数个数以便分配空间 */
    num = count_argv(src);
    argv = (char **)malloc((num + 1) * sizeof(char *));
    /* */
    for (j = 0; j < num; j++)
    {
        argv[j] = strsep(&p, seps); // 新知识：strsep的使用
        // printf("%d %s\n", j, argv[j]);
    }
    argv[j] = NULL;
    return argv;
}
int count_argv(char src[])
/* 计算参数的个数 */
{
    int i = 0, cnt = 1;
    while (src[i] != '\0')
        if (src[i++] == ' ')
            cnt++;
    return cnt;
}