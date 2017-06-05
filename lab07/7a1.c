#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <signal.h>

static void signal_handler(int);

int main(int argc, char *argv[])
{	
	pid_t pid;
	void(*old_handler) (int);
	
	old_handler = signal(SIGALRM, signal_handler);
	if (old_handler == SIG_ERR)
		fprintf(stderr, "\nCannot set signal handler");
	alarm(1);
	pid = fork();
	if( pid == 0){ // child
		sleep(5);
		printf("child id is:  %d and parent id is: %d." ,getpid(), getppid());
	} else {
		wait(NULL); // wait for the child to terminate
	}
	return 0;
}
	

void signal_handler(int sig_no){
	fprintf(stdout,"process handle with alarm signal: %d", getpid());
}
	
	
	