#include <stdio.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>

const char *dir_type(__uint8_t type)
{
    switch (type)
    {
    case DT_FIFO:   return "FIFO";                  break;
    case DT_CHR:    return "CHARACTER SPECIAL";     break;
    case DT_DIR:    return "DIRECTORY";             break;
    case DT_BLK:    return "BLOCK SPECIAL";         break;
    case DT_REG:    return "REGULAR";               break;
    case DT_LNK:    return "SYMBOLIC LINK";         break;
    case DT_SOCK:   return "SOCKET";                break;
    case DT_WHT:    return "WHITEOUT";              break;
    default: return "unknown?";                     break;
    }
}

const char *is_type(mode_t file_mode)
{

    switch (file_mode & S_IFMT)
    {
    case S_IFBLK:  return "BLOCK SPECIAL";          break;
    case S_IFCHR:  return "CHARACTER SPECIAL";      break;
    case S_IFDIR:  return "DIRECTORY";              break;
    case S_IFIFO:  return "FIFO";                   break;
    case S_IFLNK:  return "SYMBOLIC LINK";          break;
    case S_IFREG:  return "REGULAR";                break;
    case S_IFSOCK: return "SOCKET";                 break;
    default:       return "unkwown?";               break;
    }
}

int main(int argc, char *argv[])
{
    if (argc > 2)
    {
        printf("Usage: %s [dir]", argv[1]);
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
        if (dir->d_type == DT_UNKNOWN)
        {
            if (lstat(dir->d_name, &stat_buf) == -1)
            {
                perror("failed to lstat");
                closedir(dir_str);
                return 44;
            }
            printf("%-20s", is_type(stat_buf.st_mode));
        }
        else
        {
            printf("%-20s", dir_type(dir->d_type));
        }
        printf("%s\n", dir->d_name);
    }
    closedir(dir_str);
    return 0;
}
