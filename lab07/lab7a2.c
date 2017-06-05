#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

static void ctrl_handler(int);

int main(void){
	
	pid_t pid;
    pid = fork();
    if (pid == 0) {
        alarm(5);
        execl("./7a2", "7a2", (char *)0);
    } else {
        wait(NULL);
    }
}

static void ctrl_handler(int signo) {
	printf("Signal received\n");
}
