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
    //R/W for user, R/O for group and others
    int fd = open(argv[1], O_WRONLY|O_CREAT|O_APPEND, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
    if (fd == -1)
    {
        perror("failed to open");
        return 43;
    }
    ssize_t i = 0, written, len;
    len = strlen(argv[2]);
    while (i < len)
    {
        written = write(fd, argv[2] + i, len - i);
        if (written < 0)
        {
            perror("error with writing");
            close(fd);
            return 44;
        }
        i += written;
    }
    if (close(fd) == -1)
    {
        perror("failed to close the file");
        return 45;
    }
    return 0;
}
