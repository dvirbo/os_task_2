#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>

void sig_handler(int signum)
{
    int i = 5;
    int j = 0;
    int k;
    switch (signum)
    {
    case SIGCHLD:
        printf("I am in sighandler\n");
        fflush(stdout);
        raise(SIGUSR1);
    case SIGUSR1:
        printf("I am in sighandler3333\n");
        fflush(stdout);
        k = i / j;
        printf("lalala\n");
        fflush(stdout);
        break;
    case SIGFPE:
        printf("I am in sighandler2\n");
        fflush(stdout);
        exit(1);
    }
}

int main(int argc, char *argv[])
{
    int status;
    int pid = fork();
    if (pid == -1)
    {
        return 1;
    }

    if (pid == 0)
    { // child pros
        while (1)
        {
            printf("os course is so fun\n");
            usleep(50000);
        }
    }
    else
    {
        kill(pid, SIGSTOP);
        int t;
        do
        {
            printf("Time in seconds for execution: ");
            scanf("%d", &t);

            if (t > 0)
            {
                kill(pid, SIGCONT);
                sleep(t);
                kill(pid, SIGSTOP);
            }
        } while (t > 0);

        kill(pid, SIGKILL);
        wait(NULL);
        
    }

    return 0;
}