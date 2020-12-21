#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
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
    case S_IFBLK:  return "block device ";
    case S_IFCHR:  return "character device ";
    case S_IFDIR:  return "directory";
    case S_IFIFO:  return "FIFO/pipe ";
    case S_IFLNK:  return "symlink ";
    case S_IFREG:  return "regular file ";
    case S_IFSOCK: return "socket ";
    default: return "unknown? ";
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
    printf("last status change: %s", asctime(gmtime(&stat_buffer.st_ctime)));
    printf("last access time : %s", asctime(gmtime(&stat_buffer.st_atime)));
    printf("last modification time: %s", asctime(gmtime(&stat_buffer.st_mtime)));
    return 0;
}
