#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

void sig_handler(int signum)
{
	int i=5;
	int j=0;
	int k;
	switch (signum) {
		case SIGCHLD:
			printf("I am in sighandler\n");
			fflush(stdout);
			raise(SIGUSR1);
		case SIGUSR1: 
			printf("I am in sighandler3333\n");
			fflush(stdout);
			k=i/j;
			printf("lalala\n");
			fflush(stdout);
			break;
		case SIGFPE:
			printf("I am in sighandler2\n");
			fflush(stdout);
			exit(1);
			}
}

void sig_handler2(int signum)
{
	printf("I am in sighandler2222\n");
	fflush(stdout);
	exit(1);
}

int main()
{
	int status;
	signal (SIGCHLD, sig_handler);
	signal (SIGUSR1, sig_handler);
	signal (SIGFPE, sig_handler);
	if (!(fork())) {
		exit(1);
	}
	wait(&status);

}