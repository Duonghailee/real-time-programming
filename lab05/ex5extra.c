#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

int main(void){
    int fd, i = 0, from_chat;
    char chr ;
    pid_t pid;
    fd = open("test.txt", O_APPEND | O_CREAT | O_RDWR);
    pid = fork();
    if (pid == 0){ // this is a child
        from_chat = OpenChatFellow();
        while (read(from_chat, &chr, 1) > 0){
            write(STDOUT_FILENO, &chr, 1); //to terminal
            write(fd, &chr, 1);            // to file
            i++;
            if (i % 7 == 0){
                write(fd, "\n", 1);
            }
        }
        close(from_chat); //only the child uses OpenChatFellow so close it now
        exit(i); //terminate the process, close file descriptor, 
    } else { 
        int status = 0;
        wait(&status); // using wait to prevent child process to become a zombie
        printf("\nNumber of characters has been written to file is %d\n",  WEXITSTATUS(status));
        close(fd);
        _exit(0);
    }
    return 0;
}