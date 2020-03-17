/* pipe管道测试 */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <wait.h>

int main(void)
{
    int fd_pipe[2];
    pid_t new_pid;
    char buf[BUFSIZ] = {0};

    if(pipe(fd_pipe) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    if((new_pid = fork()) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    if(new_pid == 0)
    {
        close(fd_pipe[1]);
        while(read(fd_pipe[0], buf, BUFSIZ) != 0)
            printf("%s", buf);
    }
    else
    {
        close(fd_pipe[0]);
        write(fd_pipe[1], "Hello, world!\n", 14);
        wait(NULL);
    }

    return 0;
}