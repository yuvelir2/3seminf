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
    size_t len = strlen(argv[2]);
    int cnt = dprintf(fd,"%s", argv[2]);
    if (cnt == -1)
    {
	perror("failed to dprintf");
	close(fd);
	return 44;
    }
    else if (cnt < len)
    {
	perror("unsuccessful to write");
	close(fd);
	return 45;
    }  
    if (close(fd) == -1)
    {
        perror("Unsucessful closing");
        return 46;
    }
    return 0;
}
