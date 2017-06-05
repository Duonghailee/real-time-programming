#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void){
	pid_t pid[5];
	int i = 4;
	int fd_arr[2], n;
	pipe(fd_arr);
	char chr = 'A';
	
	for(i ; i >= 0 ; i-- ){
		pid[i] = fork();
		if( pid[i] == 0) { // this is ith child
			close(fd_arr[0]); // close its read
			write(fd_arr[1], &chr,1);
			sleep(1);
			close(fd_arr[1]);
			exit(0); // terminate the chi
		}
		chr++;
	}
		// the last child reaches here and write result to screen
	close(fd_arr[1]);
	while(read(fd_arr[0], &chr, 1) > 0){
		write(STDOUT_FILENO, &chr, 1);
	}
	
	// parent continues from here
	// parent wait for childrens 
	while(wait(NULL) > 0);	
	exit(0);
}	