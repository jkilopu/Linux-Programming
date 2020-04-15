/* write0.c 
 * 
 * purpose: send messages to another terminal
 * method: open the other terminal for output then
 *      copy from stdin to that terminal
 * shows: a terminal is just a file supporting regular I/O
 * usage: ./write0 ttyname(/dev/pts/NUMBER)
 *        如果该终端的w权限关闭，必须用sudo
 * 总结:(很重要)
 * 1. 终端一般为tty，pts为虚拟终端。一个tty下可以有很多个pts（虚拟终端）
 * 2. 要向一个终端发送信息,必须拥有该终端的w权限。（eg：默认tty的拥有者为root，zhongming没有tty的w权限，发送消息时显示permission denied）
 * 3. 要在一个终端中收到消息，必须拥有该终端的r权限。（eg：默认tty的拥有者为root，zhongming没有tty的r权限，在该终端下登陆后无法收到消息）
 */
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#define BUFSIZE 4096
int main(int argc, char *argv[])
{
    int fd;
    char buf[BUFSIZE];

    /* check args */
    if (argc != 2)
    {
        fprintf(stderr, "usage: ./write0 ttyname\n");
        exit(EXIT_FAILURE);
    }
    /* open device */
    if ((fd = open(argv[1], O_WRONLY)) == -1)
    {
        perror(argv[1]);
        exit(EXIT_FAILURE);
    }
    /* loop until EOF on input */
    while (fgets(buf, BUFSIZE, stdin) != NULL)
        if (write(fd, buf, strlen(buf)) == EOF)
            break;
    close(fd);

    return 0;
}