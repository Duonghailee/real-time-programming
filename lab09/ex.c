#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

static inline void error(const char *msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}

int main(void)
{
    int pid;
    int pipes_1[2];
    int pipes_2[2];
    int pipes_3[2];
    pipe(pipes_1);
    pipe(pipes_2);
    pipe(pipes_3);

    if ((pid = fork()) == 0)
    {
        dup2(pipes_1[1], 1);
        close(pipes_1[0]);
        close(pipes_1[1]);
        close(pipes_2[0]);
        close(pipes_2[1]);
        close(pipes_3[0]);
        close(pipes_3[1]);
        execlp("sed", "sed", "s/[^a-zA-Z]/ /g", "test.txt", (char *)NULL);
        error("Failed to exec sed");
    }
    printf("sed:  %d\n", pid);

    if ((pid = fork()) == 0)
    {
        dup2(pipes_1[0], 0);
        dup2(pipes_2[1], 1);
        close(pipes_1[0]);
        close(pipes_1[1]);
        close(pipes_2[0]);
        close(pipes_2[1]);
        close(pipes_3[0]);
        close(pipes_3[1]);
        execlp("tr", "tr", "[A-Z]", "[a-z]", (char *)NULL);
        error("Failed to exec tr");
    }
    printf("tr:   %d\n", pid);

    if ((pid = fork()) == 0)
    {
        dup2(pipes_2[0], 0);
        dup2(pipes_3[1], 1);
        close(pipes_1[0]);
        close(pipes_1[1]);
        close(pipes_2[0]);
        close(pipes_2[1]);
        close(pipes_3[0]);
        close(pipes_3[1]);
        execlp("awk", "awk", "{for(i = 1; i <= NF; i++) {print $i;}}", (char *)NULL);
        error("Failed to exec awk");
    }
    printf("awk:  %d\n", pid);

    if ((pid = fork()) == 0)
    {
        dup2(pipes_3[0], 0);
        close(pipes_1[0]);
        close(pipes_1[1]);
        close(pipes_2[0]);
        close(pipes_2[1]);
        close(pipes_3[0]);
        close(pipes_3[1]);
        execlp("sort", "sort", (char *)NULL);
        error("Failed to exec sort");
    }
    printf("sort: %d\n", pid);

    close(pipes_1[0]);
    close(pipes_1[1]);
    close(pipes_2[0]);
    close(pipes_2[1]);
    close(pipes_3[0]);
    close(pipes_3[1]);

    int status;
    int corpse;
    while ((corpse = wait(&status)) > 0)
        printf("PID %d died 0x%.4X\n", corpse, status);

    return 0;
}