#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>



int main(int argc, char *argv[])
{
    pid_t pid;
    int i = 0;
    int fd;
    char  chr;
    char arg[1];

        fd = open("test.txt", O_RDWR|O_APPEND,0777);	
        //printf("%d",fd);
        sprintf(arg,"%d",fd);
        pid = fork();
        if(pid == 0){ //child
            execl(argv[0],argv[1],arg, (char *)0);
            perror("exec");
            exit(0);
        }
        //parent
        while(waitpid(-1, NULL, WNOHANG) == 0){
            printf("Parent is working\n");
            sleep(5);
        }
        printf("Child terminated\n");
        
        while(read(fd, &chr, 1)>0){
            write(STDIN_FILENO, &chr, 1);
        }
        write(1,"\n",1);
        close(fd);
        return 0;
}