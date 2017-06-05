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
	pid = fork();
	if( pid == 0){ // child
		//sleep(5);
		alarm(5);
		execl(argv[1],argv[1],(char *)0);
	
		printf("child id is:  %d and parent id is: %d." ,getpid(), getppid());
	} else {
		wait(NULL); // wait for the child to terminate
	}

}
	

void signal_handler(int sig_no){
	printf("Signal received");
}
	
	
	