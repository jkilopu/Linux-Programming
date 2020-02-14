/* more01.c - print the content of a file gradually 
 * usage: ./more01 filename
 * bugs: 1. we must press Enter after press q.
 *       2. when use redirect(重定向), the see_more goes goes wrong, 
 *          becaue we get "ch" from stdin instead of tty.
 */
#include <stdio.h>
#include <stdlib.h>
#define PAGELEN 24
#define LINELEN 512

void do_more(FILE *fp);
int see_more(void);

int main(int argc, char *argv[])
{
    char ch;
    FILE *fp;

    if (argc == 1) // if no argc, read from stdin, so that we can redirect
        do_more(stdin);
    else
        while (--argc)
            if ((fp = fopen(*++argv, "r")) != NULL) //read the file one by one
            {
                do_more(fp);
                fclose(fp);
            }
            else
            {
                perror(*argv);
                exit(EXIT_FAILURE);
            }

    return 0;
}
/* 
 * read PAGELEN lines, then call see_more() for further instruction
 */
void do_more(FILE *fp)
{
    char line[LINELEN];
    int num_of_lines = 0;
    int reply;
    while (fgets(line, LINELEN, fp)) // fgets() gets one line each time
    {
        if (num_of_lines == PAGELEN)
        {
            reply = see_more();
            if (reply == 0)
                break;
            num_of_lines -= reply; // reset count
        }
        if (fputs(line, stdout) == EOF)
            exit(EXIT_FAILURE);
        num_of_lines++;
    }
}
/*
 * print message and wait for further command
 * q means quit, space means yes, CR means one line
 */
int see_more(void)
{
    int ch;
    printf("\033[7m more? \033[m"); /* reverse on a vt100 */ //no need '\n
    while ((ch = getchar()) != EOF)
    {
        if (ch == ' ')
            return PAGELEN;
        if (ch == '\n')
            return 1;
        if (ch == 'q')
            return 0;
    }
}