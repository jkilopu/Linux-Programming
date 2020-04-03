/*
 * extract_substring.c
 * 功能：取出源字符串中的第一个字串
 * 缺陷：无法判断'.'连续的情况
 */
#include <regex.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void extract_substring(char *dest, const char src[], int start, int end);

int main(void)
{
    char re[] = "([a-zA-Z0-9_.-]+)@([a-zA-Z0-9_.-]+\.[a-zA-Z0-9])";                           // 判断是否可能为一个e-mail
    char str[] = "123456@qq.com";                                                           // 源字符串
    char e_mail[strlen(str) + 1], login_name[strlen(str) + 1], website_name[strlen(str) + 1]; // 储存各种属性
    regex_t re_t;
    const size_t nmatch = 3; // 比substr的个数多1
    regmatch_t pmatch[3];    // 与nmatch保持一致

    /* 编译 */
    if (regcomp(&re_t, re, REG_EXTENDED) != 0)
    {
        perror("regcomp");
        exit(EXIT_FAILURE);
    }
    /* 匹配、分配 */
    if (regexec(&re_t, str, nmatch, pmatch, 0) == REG_NOMATCH)
    {
        perror("No match");
        exit(EXIT_FAILURE);
    }
    else /* 拷贝至相应空间 */
    {
        extract_substring(e_mail, &str, pmatch[0].rm_so, pmatch[0].rm_eo);
        extract_substring(login_name, &str, pmatch[1].rm_so, pmatch[1].rm_eo);
        extract_substring(website_name, &str, pmatch[2].rm_so, pmatch[2].rm_eo);
    }

    /* 输出 */
    printf("e-mail: %s, login_name: %s, website_name: %s\n", e_mail, login_name, website_name);

    /* 记得free */
    regfree(&re_t);
    return 0;
}
void extract_substring(char *dest, const char *src, int start, int end)
{
    strncpy(dest, &src[start], end - start); // 拷贝src中位置从[start,end)的元素
    dest[end - start] = '\0';                // 必须手动添加'\0'
}