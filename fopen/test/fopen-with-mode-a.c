/* fopen-with-mode-a.c 
 *     utility: check if fopen uses O_APPEND
 *      result: text
 *  conclusion: yes, it uses O_APPEND
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(void)
{
    FILE *fp_1, *fp_2;
    int i;
    char mesg_1[] = "I am Isaac.\n";
    char mesg_2[] = "This is Norman.\n";

    // open file
    if ((fp_1 = fopen("text", "a")) == NULL)
    {
        perror("text");
        exit(EXIT_FAILURE);
    }
    if ((fp_2 = fopen("text", "a")) == NULL)
    {
        perror("text");
        exit(EXIT_FAILURE);
    }
    // write string to file alternately（交替的）
    for (i = 0; i < 3; i++)
    {
        if ((fwrite(mesg_1, strlen(mesg_1), 1, fp_1)) != 1) // the size writen(strlen(mesg_1)) needs to be exact.
        {
            perror(mesg_1);
            exit(EXIT_FAILURE);
        }
        if ((fwrite(mesg_2, strlen(mesg_2), 1, fp_2)) != 1)
        {
            perror(mesg_2);
            exit(EXIT_FAILURE);
        }
    }
    // close file
    fclose(fp_1);
    fclose(fp_2);

    return 0;
}