#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

static void ctrl_handler(int);

int main(void){
	int pid;
	
	if (signal(SIGALRM, ctrl_handler) == SIG_ERR){
		fprintf(stderr, "Cannot set signal handler\n");
	}	
	alarm(2);
	if (fork() == 0){
		sleep(2);
		printf("child pid: %d, parent pid: %d\n", getpid(), getppid());
	} else {
		wait(NULL);
	}	
		
	return 0;
}

static void ctrl_handler(int signo) {
	printf( "in signal handler with pid: %d\n", getpid());
}
