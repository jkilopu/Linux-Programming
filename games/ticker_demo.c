/* ticker_demo.c
 *      demonstrates use of interval timer to generate regular
 *      signals, which are in turn caught and used to count down
 */
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

void countdown(int signum);
/* [ supposed from set_ticker.c ] */
int set_ticker(int n_msecs);

int main(void)
{
    signal(SIGALRM, countdown);
    if (set_ticker(500) == -1)
        perror("set_ticker");
    else
        for (;;)
            pause();

    return 0;
}
void countdown(int signum)
{
    static int num = 10;
    printf("%d..", num--);
    fflush(stdout);
    if (num < 0)
    {
        printf("DONE!\n");
        exit(EXIT_SUCCESS);
    }
}