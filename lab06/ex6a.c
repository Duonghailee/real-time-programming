#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
int main(void)
{
    pid_t pid;
    char buf[20];
    printf("Enter input (n = next, other input terminates):");
    fgets(buf, 20, stdin);
    while (buf[0] == 'n'){
        // using SIGCHLD signal in parent, 
        //signal(SIGCHLD,SIG_IGN); this lets kernel know that zombie died entry can be deposed now fro the table
        pid = fork();
        if (pid < 0) {
            perror("Fork:");
            exit(1);
        }
        if (pid == 0) {
            sleep(5); // This represents something real work
            exit(0);  // that is done for the client
        }
        waitpd(pid);
        printf("Enter input (n = next, other input terminates):");
        fgets(buf, 20, stdin);
    }
}