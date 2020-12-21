#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Usage: %s some.file string\n", argv[0]);
        return 42;
    }
    //R/W for user, R/O for group and others
    int fd = open(argv[1], O_WRONLY|O_CREAT|O_APPEND, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
    if (fd == -1)
    {
        perror("failed to open");
        return 43;
    }
    size_t len = strlen(argv[2]), i = 0;
    while (i < len)
    {
        ssize_t written = write(fd, argv[2] + i, len - i);
        if (written < 0)
        {
            perror("error with writing");
            close(fd);
            return 44;
        }
        i += (size_t)written;
    }
    if (close(fd) == -1)
    {
        perror("failed to close the file");
        return 45;
    }
    return 0;
}
