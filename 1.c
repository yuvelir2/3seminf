#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#ifdef S_BLKSIZE
#define BL_SIZE S_BLKSIZE
#else
#include <sys/param.h>
#define BL_SIZE DEV_BSIZE
#endif
const char *mode_to_str(mode_t file_mode)
{
    switch (file_mode & S_IFMT)
    {
    case S_IFBLK:  return ("block device\n");
    case S_IFCHR:  return ("character device\n");
    case S_IFDIR:  return ("directory\n");
    case S_IFIFO:  return ("FIFO/pipe\n");
    case S_IFLNK:  return ("symlink\n");
    case S_IFREG:  return ("regular file\n");
    case S_IFSOCK: return ("socket\n");
    default: return ("unknown?\n");
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
