#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

int main(void){
    int fd, i, from_chat;
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
        exit(0);
    }
    else { // this is a parent process
        while (read(STDOUT_FILENO, &chr, 1) > 0 && chr != 'Q' && chr != 'q') {
            write(STDOUT_FILENO, &chr, 1);
        }
        wait(NULL);
        while (read(fd, &chr, 1) > 0) {
            write(STDOUT_FILENO, &chr, 1);
        }
        close(fd);
        exit(0);
    }
    return 0;
}