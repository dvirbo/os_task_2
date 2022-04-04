#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
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
		k = i/j;
		break;

	case SIGFPE: // div in zero
		printf("I am in SIGFPE\n");
		fflush(stdout);
		exit(1);
	}
}


int main()
{
	signal(SIGCHLD, sig_handler);
	signal(SIGUSR1, sig_handler);
	signal(SIGUSR2, sig_handler);
	signal(SIGFPE, sig_handler);
	if (!(fork()))
	{
		perror("can't fork");
		exit(1);
	}
	wait(NULL);
}