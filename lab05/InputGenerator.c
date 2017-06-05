// This is very simple input generator.
// A separate process generates input at 1 second 
// time intervals. Input is characters A B C, ..., Z.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int OpenChatFellow() {
    pid_t pid;
    int fd_arr[2];
    int i;
    char chr;

    //This part is done only by parent
    pipe(fd_arr);
    pid = fork();
    if (pid < 0) {
        perror("Process creation error");
    }
    if (pid > 0) {
        close (fd_arr[1]); // parent closes it's read end of the pipe
        return fd_arr[0];
    }
    if (pid == 0)  {   // this is child
    	 close (fd_arr[0]); 
         // writing to the pipe
         for( i = 0 ; i < 26 ; i++) {
            chr = 'a' + i;
         	write(fd_arr[1], &chr, 1);
         	sleep(2);
            
         }
         close(fd_arr[1]);
         exit (0);
    }
}
