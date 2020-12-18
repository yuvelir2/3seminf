#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Usage: %s source file target file\n", argv[0]);
        return 42;
    }
    struct stat stat_buf;
    if (lstat(argv[1], &stat_buf) == -1)
    {
        perror("failed to lstat");
        return 43;
    }
    if ((stat_buf.st_mode & S_IFMT) != S_IFREG)
    {
        printf("not regular file");
        return 44;
    }
    //R for everyone
    int fd1 = open(argv[1], O_RDONLY);
    if (fd1 == -1)
    {
        perror("failed to open source file");
        return 45;
    }
    //R/W for user, R/O for group and others
    int fd2 = open(argv[2], O_WRONLY|O_CREAT|O_TRUNC, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
    if (fd2 == -1)
    {
        perror("failed to open target file");
        return 46;
    }
    while (1)
    {
        uint8_t buf[32768];
        ssize_t buf_size = read(fd1, buf, sizeof(buf));
        if (buf_size == -1)
        {
            perror("failed to read a block");
            close(fd1);
            close(fd2);
            return 48;
        }
        if (buf_size == 0)
        {
            break;
        }
        size_t lcl_buf_size = (size_t)buf_size;
        size_t smb_written = 0;
        while (smb_written < lcl_buf_size)
        {
            ssize_t res = write(fd2, &buf[smb_written], lcl_buf_size - smb_written);
            if (res == -1)
            {
                perror("failed to write");
                close(fd1);
                close(fd2);
                return 49;
            }
            smb_written += (size_t)res;
        }
    }
    fsync(fd2);
    close(fd1);
    close(fd2);
    return 0;
}
