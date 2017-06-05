/* read_timeaout.c
 * If we want to use SIGALRM signal to implement timeout, we need
 * to use setjmp and longjmp functions to cope with the race 
 * condition. The reason for this is that we cannot atomically go to 
 * the read and open the signal mask. There is no such read function.
 * This example program demonstrates the implementation of timeout.
 *  
 * In the demonstration we ause 5 seconds timeout. But signal handler
 * for signal SIGUSR1 takes 10 seconds to execute. Signal SIGALRM
 * is blocked during this time. So the timeout is deferred.
 *  
 * Most important things to observe are
 *  1) We use sigsetjmp and siglongjmp instead of setjmp and longjmp,
 *     because longjmp does not restore signal mask. The longjmp is 
 *     called from the signal handler where signal is blocked.
 *  2) This method causes a problem when we have other signals too in
 *     the program. If SIGALRM is delivered when handler of other signal 
 *     is executed, the program never return back to this handler. 
 *     That's why we need to block other signals when installing signal 
 *     handler for SIGALRM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <setjmp.h>

#define SAVE_MASK 1

void sigusr1_handler(int);
void sigalrm_handler(int);

jmp_buf sig_return_info;

int main(void) {
    char chr;
    int result;
    struct sigaction sigact;

    // It would be better to use sigaction also here 
    if (signal(SIGALRM, sigalrm_handler) == SIG_ERR) {
        fprintf(stderr, "\nCannot set signal handler");
        exit(0);
    }
    
    // Now we have to use sigaction to be able to block
    // other signals
    sigemptyset(&sigact.sa_mask);
    sigaddset(&sigact.sa_mask, SIGALRM);
    sigact.sa_flags = 0;
    sigact.sa_handler = sigusr1_handler;
    sigaction(SIGUSR1, &sigact, NULL);
 
    if (sigsetjmp(sig_return_info, SAVE_MASK) != 0) {
        printf("Read was timed out \n"); 
        print_signals_in_mask();
        exit(1);
    }
 
    alarm(5);
    raise(SIGUSR1);
    // In this case read never retuns here
    if ((result=read(STDIN_FILENO, &chr, 1)) <0 ){
        fprintf(stderr, "Error has happened\n");
    }
    alarm(0);   //remove the timer
    if (result == 0 )
        fprintf(stderr, "End of file is found\n");
    if (result > 0 )
        fprintf(stderr, "A character was read and it was %c\n", chr);
    return 0;
}

void sigalrm_handler(int sig_no) {
  	fprintf(stderr, "Signal SIGALRM is cathed\n");
   	siglongjmp(sig_return_info, 1);
}

void sigusr1_handler(int sig_no) {
    time_t start_time, end_time;
    fprintf(stderr, "Signal SIGUSR1 is cathed\n");
    end_time = time(NULL) + 10;
    while(time(NULL) < end_time)
        sleep(1);
    fprintf(stderr, "Signal handler for SIGUSR1 completed\n");
}

// For testing purposes
void print_signals_in_mask() {
    int i;
    sigset_t signals;
    sigprocmask(0, NULL, &signals);
    for ( i = 0 ; i < 32 ; i++) {
        if (sigismember(&signals, i))
            printf("%d ", i);
    }
    printf("\n");
}




