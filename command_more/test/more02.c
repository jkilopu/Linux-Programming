/* more02.c - print the content of a file or information gradually 
 * usage: ./more02 filename or command | ./more02
 * bugs: 1. we must press Enter after press q.
 * what can be improved: 1. show pecentage of printed information
 *                       2. 
 */
#include <stdio.h>
#include <stdlib.h>
#define PAGELEN 24
#define LINELEN 512

void do_more(FILE *fp);
int see_more(FILE *fp_tty);

int main(int argc, char *argv[])
{
    char ch;
    FILE *fp;

    if (argc == 1) // if no argc, read from stdin for information and /dev/tty for commands, so that we can redirect
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
 * print the content of the file in lines
 * */
void do_more(FILE *fp)
{
    char line[LINELEN];
    int num_of_lines = 0;
    int reply;
    FILE *fp_tty;
    if ((fp_tty = fopen("/dev/tty", "r")) == NULL)
        exit(EXIT_FAILURE);
    while (fgets(line, LINELEN, fp)) // fgets() gets one line each time
    {
        if (num_of_lines == PAGELEN)
        {
            reply = see_more(fp_tty); //read command from tty
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
int see_more(FILE *cmd)
{
    int c;
    printf("\033[7m more? \033[m");
    while ((c = getc(cmd)) != EOF) //replace getchar() with getc() to read command
    {
        switch (c)
        {
        case ' ':
            return PAGELEN;
        case '\n':
            return 1;
        case 'q':
            return 0;
        default:
            break;
        }
    }
}