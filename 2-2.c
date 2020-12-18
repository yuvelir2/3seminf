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
    dprintf(fd,"%s", argv[2]);
    if (close(fd) == -1)
    {
        perror("Unsucessful closing");
        return 45;
    }

    return 0;
}
