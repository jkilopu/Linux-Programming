/*
 * sub_sort.c 输入文本（文件或键盘），储存在字符数组中，以行为单位排序（调用sort命令），再储存在字符数组中，输出到标准输出中
 * 知识点：pipe（in、out）、读入输入、write（已经搞错好多次了）
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <wait.h>

int main(int argc, char *argv[])
{
    char buf[BUFSIZ];

    /* 读入 */
    if (argc == 2)
    {
        /* 从文件读入 */
        int fd = open(argv[1], O_RDONLY);
        if (fd == -1)
        {
            perror("open");
            exit(EXIT_FAILURE);
        }
        while (read(fd, buf, BUFSIZ) > 0)
            ;
    }
    else if (argc == 1)
    {
        /* 从标准输入读入 */
        int i;
        for (i = 0; i < BUFSIZ && (buf[i] = getchar()) != EOF; i++) // 似乎只能用这种方法
            ;
        buf[i] = '\0';
    }
    else
    {
        perror("Wrong usage");
        exit(EXIT_FAILURE);
    }

    /* 创建管道 */
    int pipe_in[2], pipe_out[2];
    if (pipe(pipe_in) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    if (pipe(pipe_out) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    /* fork */
    pid_t new_pid;
    if ((new_pid = fork()) == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (new_pid == 0)
    {
        close(pipe_in[0]);
        close(pipe_out[1]);
        /* 重定向 */
        if (dup2(pipe_in[1], 1) == -1)
        {
            perror("dup2");
            exit(EXIT_FAILURE);
        }
        close(pipe_in[1]);
        if (dup2(pipe_out[0], 0) == -1)
        {
            perror("dup2");
            exit(EXIT_FAILURE);
        }
        close(pipe_out[0]);
        execlp("sort", "sort", NULL);
        perror("execlp");
        exit(EXIT_FAILURE);
    }
    else
    {
        close(pipe_in[1]);
        close(pipe_out[0]);

        /* 写入原始字符串 */
        if (write(pipe_out[1], buf, strlen(buf)) != strlen(buf)) // write一定要写大小相当的呀！！！！！！！！
        {
            perror("write");
            exit(EXIT_FAILURE);
        }
        close(pipe_out[1]);
        wait(NULL);

        /* 读取 */
        while (read(pipe_in[0], buf, BUFSIZ) > 0)
            ;
        close(pipe_in[0]);

        /* 输出 */
        printf("%s", buf);
    }

    return 0;
}