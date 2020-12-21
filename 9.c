#include <stdio.h>
#include <sys/vfs.h>
#include <sys/statvfs.h>

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s some.file\n", argv[0]);
        return 42;
    }
    struct statvfs buffer;
    if ((statvfs(argv[1], &buffer)) == -1)
    {
        perror("failed to statvfs");
        return 42;
    }
    printf("total: %lu \n",buffer.f_blocks * buffer.f_frsize);
    printf("available: %lu\n", buffer.f_bavail * buffer.f_frsize);
    printf("free: %lu\n", buffer.f_bfree * buffer.f_frsize);
    printf("used: %lu\n",buffer.f_blocks * buffer.f_frsize - buffer.f_bavail * buffer.f_frsize);
    return 0;
}
