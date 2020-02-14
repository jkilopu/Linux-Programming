/* write02.c - 
 * improvement: 1. support write through user name and each tty
 *              2. 
 * mistake: 1. fread()和read()均会自动偏移，我不知道...（没从write01中看出来）
 *          2. fread()的返回值不是读取字节的大小，而是读取的个数
 *          3. 判断条件总是搞来搞去，弄不清（或许在纸上画一下会好一些）
 * */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <utmp.h>

#define BUFSIZE 4096

void oops(char *s1, char *s2);

int main(int argc, char *argv[])
{
    struct utmp info;
    FILE *fp_utmp;
    int fd_tty;
    int utsize = sizeof(struct utmp);
    char dev[16] = "/dev/", mesg[BUFSIZE];
    int is_found = 999; /* 记得初始化啊！！！ */

    // open utmp file
    if ((fp_utmp = fopen(UTMP_FILE, "r")) == NULL)
        oops("Can't open ", UTMP_FILE);
    // check if command paraments are used correctly
    if (argc != 2 && argc != 3)
    {
        fprintf(stderr, "usage: ./write02 user (terminal)\n");
        exit(EXIT_FAILURE);
    }
    // find user
    while ((fread(&info, utsize, 1, fp_utmp)) == 1) /* 这里必须先读*/
    {
        if (info.ut_type == USER_PROCESS && (is_found = strcmp(info.ut_user, argv[1])) == 0)
            break;
        /* 不要fseek()! */
    }
    // found the user?
    if (is_found != 0)
    {
        fprintf(stderr, "%s is not logged in.\n", argv[1]);
        exit(EXIT_FAILURE);
    }
    /* examine paraments */
    if (argc == 2)
    {
        if ((fd_tty = open(strncat(dev, info.ut_line, 10), O_WRONLY) == -1))
        {
            perror(dev);
            exit(EXIT_FAILURE);
        }
    }
    else if (argc == 3)
    {
        // find terminal    /* 这里必须先比较 */
        while ((is_found = (strcmp(info.ut_line, argv[2]) != strcmp(info.ut_user, argv[1]))) != 0 && (fread(&info, utsize, 1, fp_utmp) == 1) || (info.ut_type != USER_PROCESS))
            ;
        // found the terminal?
        if (is_found == 0)
        {
            // open terminal
            if ((fd_tty = open(strncat(dev, info.ut_line, 10), O_WRONLY) == -1))
                oops("Can't open ", dev);
        }
        else
        {
            fprintf(stderr, "%s is not logged in on %s.\n", argv[1], argv[2]);
            exit(EXIT_FAILURE);
        }
    }
    // send message
    while (fgets(mesg, BUFSIZ, stdin) != NULL)
        if (write(fd_tty, mesg, strlen(mesg)) == EOF)
            break;
    if (fclose(fp_utmp) == -1 || close(fd_tty) == -1)
        oops("Can't close", "");

    return 0;
}
// output the error intelligently
void oops(char *s1, char *s2)
{
    fprintf(stderr, "Error: %s", s1);
    perror(s2);
    exit(EXIT_FAILURE);
}