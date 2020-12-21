#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>

int main(int argc, char *argv[])
{
    printf("process id: %d\n", getpid());
    printf("process parent id: %d\n", getppid());
    printf("user id: %d\n", getuid());
    printf("group id: %d\n", getgid());
    int groupcnt_max = sysconf(_SC_NGROUPS_MAX);
    gid_t *grp = (gid_t*)calloc(groupcnt_max, sizeof(gid_t));
    int groupcnt = getgroups(groupcnt_max, grp);
    struct group *grps;
    printf("grouos: ");
    for (int i = 0; i < groupcnt; ++i)
    {
	printf("%d", grp[i]);
	if (!(grps = getgrgid(grp[i])))
	    printf("error");
	printf("%s;", grps->gr_name);
    }
    return 0;
}
