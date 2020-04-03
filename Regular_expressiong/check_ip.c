/*
 * check_ip.c
 * 判断字符串是否符合ip地址规范（不考虑地址的范围）
 */
#include <regex.h>
#include <stdlib.h>
#include <stdio.h>

int main(void)
{
    char re[] = "^([0-9]{1,3}\.)([0-9]{1,3}\.){2}([0-9]{1,3})$";
    char str[] = "198.123.45.1";
    regex_t re_t;
    
    /* 编译正则表达式 */
    if (regcomp(&re_t, re, REG_EXTENDED | REG_NOSUB) != 0)
    {
        perror("regcomp");
        exit(EXIT_FAILURE);
    }
    /* 匹配并判断*/
    if (regexec(&re_t, str, 0, NULL, REG_NOSUB) == REG_NOMATCH) // 不需要传入nmatch和pmatch
        printf("Not match\n");
    else
        printf("(%s) in format\n", str);

    regfree(&re_t);
    return 0;
}