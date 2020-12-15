#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
  DIR* dirp;
  if (argc == 1)
  {
     argv[1] = ".";
  }
  if (argc == 2)
  {
     dirp = opendir(argv[1]);
     if (dirp == 0)
     {
        perror("idi svoey dorogoi stalker");
        return 42;
     }
  }
  if (argc > 2)
  {
     printf("suetu navel...,");
     return 42;
  }
  
  struct stat stat_buf;
  struct dirent *dir;
  
  printf("Type of File: ");
  while ((dir = readdir(dirp)) != NULL)
  {
     if (dir->d_type == DT_UNKNOWN)
     {
        if (lstat (dir->d_name, &stat_buf) == -1) 
        {
           perror("sueta...,");
           return 42;
        }
        switch (stat_buf.st_mode & S_IFMT)
        {
           case S_IFBLK: printf("block device    "); break;
           case S_IFCHR: printf("character device    ");break;
           case S_IFDIR: printf("directory    ");break;
           case S_IFIFO: printf("FIFO/pipe    ");break;
           case S_IFLNK: printf("symlink    ");break;
           case S_IFREG: printf("regular file    ");break;
           case S_IFSOCK: printf("socket    ");break;
           default: printf("et che takoe    ");break;
        }      
     }
     else
     {
        switch(dir->d_type)
        {
           case DT_BLK: printf("block device    ");break;
           case DT_DIR: printf("directory    ");break;
           case DT_CHR: printf("character device    ");break;
           case DT_FIFO: printf("FIFO/pipe    ");break;
           case DT_LNK: printf("symlink    ");break;
           case DT_REG: printf("regular file    ");break;
           case DT_SOCK: printf("socket    ");break; 
        }
     }
     printf("Name: %s \n", dir->d_name);
  }
  
  closedir(dirp);
  return 0;
}
