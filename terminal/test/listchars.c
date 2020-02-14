/* listchars.c 
 * purpose: list individually all the chars seen on input 
 * output: char and ASCII code, one pair per line
 * input: stdin, until the letter Q
 * usage: ./listchar.c > log and type hello or ./listchars < listchars-test > log
 * notes***: useful to show that buffer/editing exist
 * 
 */
#include <stdio.h>
int main(void)
{
    int ch, n = 0;

    while ((ch = getchar()) != 'Q') //if input is a document, != EOF
        printf("char %3d is %c code %d\n", n++, ch, ch);

    return 0;
}
/* result: see log
 * 结论:
 * 1. 键入时,输入被缓冲(按回车才刷新)
 * 2. 回车的ASCII码应该是13,log中显示却是10
 * */