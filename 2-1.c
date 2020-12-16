#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf ("input problems");
        return 42;
    }
    int fildescr, cfildescr = 0;
    int fd;
    fd = open(argv[1], O_WRONLY|O_CREAT|O_APPEND, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
    if (fildescr == -1)
    {
        perror("problem with opening");
        return 43;
    }


    int leng;
    leng = strlen(argv[2]);
    ssize_t i = 0, written;
    while (i < leng)
    {
        written = write(fd, argv[2] + i, leng);
        if (written < 0)
        {
            perror("error with writing");
            return 44;
        }
        i += written;
    }
    cfildescr = close(fildescr);
    if (cfildescr != 0)
    {
        perror("closing file didn't work out");
        return 45;
    }
    return 0;
}
