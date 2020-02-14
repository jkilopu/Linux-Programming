/* cp1.c - uses read and write with tunable buffer size 
 * usage: ./cp1 src dest
 * attention: oops() 
 */
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFSIZE 4096
#define COPYMODE 0644

void oops(char *s1, char *s2);

int main(int argc, char *argv[])
{
    int in_fd, out_fd;
    int n_chars;
    char buf[BUFSIZE];

    // check if the format is right
    if (argc != 3)
    {
        fprintf(stderr, "usage: ./cp1 sourcefile targetfile\n");
        exit(EXIT_FAILURE);
    }
    // open input and output file
    if ((in_fd = open(argv[1], O_RDONLY)) == -1)
        oops("Can't open ", argv[1]);
    // open output file with open() instead of creat() to solute many different situations and set mode.
    if ((out_fd = open(argv[2], O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
        oops("Can't open ", argv[2]);
    // write
    while ((n_chars = read(in_fd, buf, BUFSIZE)) > 0)   /* pay attention to the chars read */
        if (write(out_fd, buf, n_chars) != n_chars)
            oops("Write error to ", argv[2]);
    // check if read is successful
    if (n_chars == -1)
        oops("Read error from ", argv[1]);
    // close both file
    if (close(in_fd) == -1 || close(out_fd) == -1)
    {
        fprintf(stderr, "Error closing files");
        exit(EXIT_FAILURE);
    }

    return 0;
}
// output the error intelligently
void oops(char *s1, char *s2)
{
    fprintf(stderr, "Error: %s", s1);
    perror(s2);
    exit(EXIT_FAILURE);
}