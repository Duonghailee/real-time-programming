#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <signal.h>

// Number of children
#define N 5

// Global variable that indicates how many children have terminated
int n = 0;

// Write signal handler for signal SIGCHLD here.
static void signal_handler(int);
// Signal handler increments n.

int main(int argc, char *argv[])
{
    int fd, i;
    char fd_str[10], n_str[2];
    char str[5][5] = {"AAAA", "BBBB", "CCCC", "DDDD", "EEEE"};
    char chr;
    pid_t pid[5];

    // Install signal handler
    void (*old_handler)(int);
    old_handler = signal(SIGCHLD, signal_handler);
    if (old_handler == SIG_ERR)
        fprintf(stderr, "\nCan not set signal handler");

    // Open the file data.txt
    fd = open("data.txt", O_RDWR | O_APPEND | O_CREAT, 0777);
    sprintf(fd_str, "%d\n", fd);
    

    // Create N children that start to run a separate
    for (i = 0; i < 5; i++)
    {
        sprintf(n_str, "%d\n", n);
        pid[i] = fork();
        if (pid[i] == 0)
        {
            execl(argv[0], "child.exe", fd_str, n_str, str[i], (char *)0);
        }
    }

    // executable file child.exe. Pass the file descriptor,
    // the number of writes and the string that the child
    // program writes to the file.

    // Parent process waits for the children in the following loop.
    // Signal causes pause to return
    while (n < N)
    {
        pause();
        printf("Child term %d\n", n);
    }
    close(fd);
    // Parent process displays the contents from the file
    return 0;
}

static void signal_handler(int signo)
{
    n++;
}