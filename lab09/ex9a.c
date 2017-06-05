#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int main (void){
    pid_t pid;
    int fd_arr[2], i, n;
    char chr;
    pipe(fd_arr);
    pid = fork();
    if(pid == 0){ // this is child
        close(fd_arr[0]); // child close its read
        // write to the pipe from 0...9
        for(i = 0; i < 10; i++ ){
            chr = '0' + i;
            write(fd_arr[1], &chr, 1);
            sleep(1);
        }
        close(fd_arr[1]);
		exit(0);
    }
    //parent from here
    //reading from the pipe and display to the screen
    //parent close its write
    close(fd_arr[1]);
    while(read(fd_arr[0], &chr, 1) > 0){
        write(STDOUT_FILENO, &chr, 1);
    }
    close(fd_arr[0]);
    write(STDOUT_FILENO,"\n",1);
    exit(0);
}