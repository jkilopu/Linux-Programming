/* show_screen_size.c - an application of ioctl.h
 * purpose: show the size of screen in row and col or in pixel
 * TIOCGWINSZ: 函数代码？
 */
#include <stdio.h>
#include <sys/ioctl.h>
void print_screen_dimensions(void);
int main(void)
{
    print_screen_dimensions();

    return 0;
}
void print_screen_dimensions(void)
{
    struct winsize wbuf;
    //长宽、像素
    if (ioctl(0, TIOCGWINSZ, &wbuf) != -1)  // 为啥填写0？
    {
        printf("%d rows x %d cols\n", wbuf.ws_row, wbuf.ws_col);
        printf("%d wide x %d tall\n", wbuf.ws_xpixel, wbuf.ws_ypixel);  // 为啥是0，0？
    }
}