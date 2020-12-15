#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{
    struct stat stat_buf;
    if (argc != 2)
    {
        printf("che s argumentami leee: %s some.file\n", argv[0]);
        return 42;
    }

    if (lstat(argv[1], &stat_buf) == -1)
    {
        perror("ne robit");
        return 43;
    }
    printf("file type ");
    switch (stat_buf.st_mode & S_IFMT)
    {
    case S_IFBLK:  printf("block device\n");break;
    case S_IFCHR:  printf("character device\n");break;
    case S_IFDIR:  printf("directory\n");break;
    case S_IFIFO:  printf("FIFO/pipe\n");break;
    case S_IFLNK:  printf("symlink\n");break;
    case S_IFREG:  printf("regular file\n");break;
    case S_IFSOCK: printf("socket\n");break;
    default: printf("unknown?\n");break;
    }

    printf("mode: %06o\n", stat_buf.st_mode);
    printf("size: %llu\n", (unsigned long long)stat_buf.st_size);
    printf("space used: %llu\n", (unsigned long long)stat_buf.st_blocks * 512);
    printf("last file commit:   %s", ctime(&stat_buf.st_mtime));


    return 0;
}
