/* 习题：父进程和子进程拥有相同的且指向位置的文件描述符，文件中会有几条记录？ */
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
int main(void)
{
    int fd, pid;

    char msg1[] = "Test 1 2 3 ..\n";
    char msg2[] = "Hello, hello\n";
    if((fd = creat("testfile", 0644)) == -1)
    {
        perror("create fail");
        return 0;
    }
    if(write(fd, msg1, strlen(msg1)) == -1)
    {
        perror("write fail");
        return 0;
    }

    if((pid = fork()) == -1)
    {
        perror("write fail");
        return 0;
    }
    if(write(fd, msg2, strlen(msg2)) == -1)
    {
        perror("write fail");
        return 0;
    }
    else
    {
        printf("%d\n", fd); // 看一看文件描述符是否相同
    }
    
    
    close(fd);
    return 1;
}
/* 答案：三条。
 * 因为父进程和子进程的文件描述符相同，任意一个进程write后偏移，另一个进程的write受前一个进程影响
 */