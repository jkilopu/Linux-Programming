/* rotate.c: map a->b, b->ch, ... , z->a 
 *  purpose: useful for showing tty modes
 */
#include <stdio.h>
#include <ctype.h>
int main(void)
{
    int ch;

    while ((ch = getchar()) != EOF)
    {
        if (ch == 'z')
            ch = 'a';
        else if (islower(ch))
            ch++;
        putchar(ch);
    }

    return 0;
}