#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#ifdef S_BLKSIZE
#define BL_SIZE S_BLKSIZE
#else
#include <sys/param.h>
#define BL_SIZE DEV_BSIZE
#endif

const char *mode_to_str(mode_t file_mode)
{
    switch (stat_buffer.st_mode & S_IFMT)
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
}


int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s some.file\n", argv[0]);
        return 42;
    }
    struct stat stat_buffer;
    if (lstat(argv[1], &stat_buffer) == -1)
    {
        perror("failed to lstat");
        return 43;
    }
    printf("file type %s\n", mode_to_str(stat_buffer.st_mode));
    printf("mode: %06o\n", stat_buffer.st_mode);
    printf("size: %llu\n", (unsigned long long)stat_buffer.st_size);
    printf("space used: %llu\n", (unsigned long long)stat_buffer.st_blocks * BL_SIZE);
    printf("last file modification UTC+03:00:   %s", ctime(&stat_buffer.st_mtime));
    return 0;
}
