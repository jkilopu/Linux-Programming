/*
 * redirect_to_file.c
 * 我的代码（已删除）：当>或<作为命令行参数使用时，仍然会被当作重定向...（因此不能在shell中模拟重定向）
 */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <wait.h>

int main(void)
{
    pid_t pid;
    int fd;

    printf("About to run who into a file\n");
    /* create a new process or quit */
    if ((pid = fork()) == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    /* child does the work */
    if (pid == 0)
    {
        /* 第一种方式 */
        close(1);                                  // close
        fd = open("userlist", O_CREAT | O_WRONLY); // then open
        /* 第二种方式 */
        // fd = creat("userlist", 0644);
        // dup2(fd, 1);
        execlp("who", "who", NULL); // and run
        perror("execlp");
        exit(EXIT_FAILURE);
    }
    /* parent waits then reports */
    if (pid != 0)
    {
        wait(NULL);
        printf("Done running who, results in userlist\n");
    }

    return 0;
}