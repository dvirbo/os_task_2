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
		printf("I am in SIGCHLD\n");
		fflush(stdout);
		raise(SIGUSR2);

	case SIGUSR2:
		printf("I am in SIGUSR2\n");
		fflush(stdout);
		raise(SIGUSR1);
		break;

	case SIGUSR1:
		printf("I am in SIGUSR1\n");
		fflush(stdout);
		k = i / j;
		break;

	case SIGFPE: // div in zero
		printf("I am in SIGFPE\n");
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
			printf("insert 0 to exit..\n");
			printf("Time in seconds for execution:");

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

	signal(SIGCHLD, sig_handler);
	signal(SIGUSR1, sig_handler);
	signal(SIGUSR2, sig_handler);
	signal(SIGFPE, sig_handler);
	if (!(fork()))
	{
		exit(1);
	}
	wait(NULL);

	return 0;
}
/* sources:
 https://code-vault.net/lesson/o4r7yiy9xg:1603732432692
 another code from moudle..
 
 */
