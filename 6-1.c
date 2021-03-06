#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>

const char *dir_type(u_int8_t type)
{
    switch (type)
    {
    case DT_FIFO:   return "FIFO";
    case DT_CHR:    return "CHARACTER SPECIAL";
    case DT_DIR:    return "DIRECTORY";
    case DT_BLK:    return "BLOCK SPECIAL";
    case DT_REG:    return "REGULAR";
    case DT_LNK:    return "SYMBOLIC LINK";
    case DT_SOCK:   return "SOCKET";
    case DT_WHT:    return "WHITEOUT";
    default: return "unknown?";
    }
}

const char *is_type(mode_t file_mode)
{
    switch (file_mode & S_IFMT)
    {
    case S_IFBLK:  return "BLOCK SPECIAL";
    case S_IFCHR:  return "CHARACTER SPECIAL";
    case S_IFDIR:  return "DIRECTORY";
    case S_IFIFO:  return "FIFO";
    case S_IFLNK:  return "SYMBOLIC LINK";
    case S_IFREG:  return "REGULAR";
    case S_IFSOCK: return "SOCKET";
    default:       return "unkwown?";
    }
}

int main(int argc, char *argv[])
{
    if (argc > 2)
    {
        printf("Usage: %s [dir]", argv[0]);
        return 42;
    }
    const char *dirp = (argc == 2) ? argv[1] : ".";
    DIR *dir_str = opendir(dirp);
    if (dir_str == NULL)
    {
        perror("failed to opendir");
        return 43;
    }

    struct dirent *dir;
    struct stat stat_buf;
    while ((dir = readdir(dir_str)) != NULL)
    {
        const char *type_str = "unknown";
        if (dir->d_type == DT_UNKNOWN)
        {
            if (lstat(dir->d_name, &stat_buf) == -1)
            {
                perror("failed to lstat");
                closedir(dir_str);
                return 44;
            }
            type_str = is_type(stat_buf.st_mode);
        }
        else
        {
            type_str = dir_type(dir->d_type);
        }
        printf("%-20s %s\n", type_str, dir->d_name);
    }
    if (closedir(dir_str))
    {
	perror("failed to close");
	return 45;
    }
    return 0;
}
