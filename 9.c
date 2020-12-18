#include <stdio.h>
#include <sys/vfs.h>

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s some.file\n", argv[0]);
        return 42;
    }
    struct statfs buffer;
    if ((statfs(argv[1], &buffer)) == -1)
    {
        perror("failed to statfs");
        return 42;
    }
    printf("total: %lu \n",buffer.f_blocks * buffer.f_bsize);
    printf("avaliable: %lu\n", buffer.f_bavail * buffer.f_bsize);
    printf("used: %lu\n",buffer.f_blocks * buffer.f_bsize - buffer.f_bavail * buffer.f_bsize);
    return 0;
}
