/* switch-echo.c - switch echo and non-echo mode */
#include <stdio.h>
#include <termio.h>
#include <stdlib.h>
int main(void)
{
    char str[50];
    int fd;
    struct termios settings;

    // get status
    if (tcgetattr(0, &settings) == -1)
    {
        perror("tcgetattr");
        exit(EXIT_FAILURE);
    }
    // examine and turn off echo
    if (settings.c_lflag & ECHO)   //检查用&与
        settings.c_lflag &= ~ECHO; // 关闭用&（与）、～取反
    if (tcsetattr(0, TCSANOW, &settings) == -1)
    {
        perror("tcgetattr");
        exit(EXIT_FAILURE);
    }
    // test
    fgets(str, 20, stdin);
    fputs(str, stdout);
    // turn on echo
    settings.c_lflag |= ECHO; // 打开用|（或）
    if (tcsetattr(0, TCSANOW, &settings) == -1)
    {
        perror("tcgetattr");
        exit(EXIT_FAILURE);
    }
    // test
    fgets(str, 20, stdin);
    fputs(str, stdout);

    return 0;
}