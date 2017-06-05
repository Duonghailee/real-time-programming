#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
int main(void)
{
    pid_t c1,c2;
    int i = 0;
    char buf[20];
    printf("Enter input (n = next, other input terminates):");
    fgets(buf, 20, stdin);
    while (buf[0] == 'n'){
        c1 = fork();
        if(c1 == 0){ //child 1
            c2 = fork();
            if(c2 > 0){
                exit(0);
            }
            sleep(5); // This represents something real work
            exit(0); 
        } 
        wait(NULL); // or waitpid(pid);
        printf("Enter input (n = next, other input terminates):");
        fgets(buf, 20, stdin);
    }
}