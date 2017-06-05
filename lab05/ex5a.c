#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <sys/types.h>
#include <sys/wait.h>


int main(void){
    int i, j, pid;
    pid_t childs[5];
    char chr;
    struct rlimit resource_limit;
    getrlimit(RLIMIT_NPROC, &resource_limit);
    //number of process, soft and hard limit
    printf("Number of process : %d\n", (resource_limit.rlim_cur + resource_limit.rlim_max));

    for (i = 0; i < 5; i++) {
        childs[i] = fork();
        if (childs[i] == 0) { // this is child i
            for (j = 0; j < 5; j++){
                chr = 'A' + i;
                write(STDOUT_FILENO, &chr, 1);
                sleep(1);
            }
            exit(0);
        }
    }

    while ((pid = waitpid(-1, NULL, 0)) > 0){ // -1 in first parameter, what ever child first terminates
        printf("\nA Child %d has terminated\n", pid);
    }
    return 0;
}