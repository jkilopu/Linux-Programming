/* ls1.c
 * purpose: list contents of directories
 * action : use . else list files in args
 * attention: 1. Although open, read can manipulate directory, but you have to figure out the kind of directory
 *            2. readdir is not a systemcall
 */
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
void do_ls(char dirname[]);
int main(int argc, char *argv[])
{
    if (argc == 1)
        do_ls(".");
    else
        while (--argc)
        {
            printf("%s:\n", *++argv);
            do_ls(*argv);
        }

    return 0;
}
void do_ls(char dirname[])
/*
 * list files in directory called dirname
 */
{
    DIR *dir_ptr;                            /* rhe directory */
    struct dirent *direntp; /* each entry */ //注意是指针啊！

    if ((dir_ptr = opendir(dirname)) == NULL)
        fprintf(stderr, "ls1: Can't open %s\n", dirname);
    else
    {
        while ((direntp = readdir(dir_ptr)) != NULL)
            printf("%s\n", direntp->d_name);
        closedir(dir_ptr);
    }
}