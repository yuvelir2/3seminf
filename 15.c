#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int last_signal;

void signaler(int sg)
{
    last_signal = sg;
}
int main()
{
    if (signal(SIGINT, signaler) == SIG_ERR)
    {
        perror("failed to read the signal");
        return 42;
    }
    if (signal(SIGQUIT, signaler) == SIG_ERR)
    {
        perror("failed to read the signal");
        return 43;
    }
    if (signal(SIGTERM, signaler) == SIG_ERR)
    {
        perror("failed to read the signal");
        return 44;
    }
    while(1)
    {
        printf("i will rise from the ashes\n");
        pause();
        switch (last_signal)
        {
            case SIGQUIT:
                printf("unable to stop process\n");
                break;
            case SIGINT:
                printf("unable to stop process\n");
                break;
            case SIGTERM:
                printf("unable to stop process\n");
                break;
            default:
                printf("unknown signal");
                break;
        }
    }
    return 0;
}
