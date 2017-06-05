#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
int main(void)
{
    pid_t pid;
    int i = 0;
    int status ;
    for(i ; i < 6; i++ ){
        pid = fork();
        if(pid > 0){ //parent
          //wait(NULL);
            wait(&status);
            sleep(1);
            int es = WEXITSTATUS(status);
            printf("\nexit status was: %d",es);
            es++;
            exit(es);
        }
    }
    sleep(1);
    exit(0);
}