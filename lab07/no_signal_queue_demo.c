/* no_signal_queue_demo.c
 * This program tests whether the blocked signals are queued or not.
 *   
 * It blocks the signal SIGINT for ten seconds. During that time
 * the user can press CNTRL + C (and thus generate signals SIGINT)
 * one or more times. After ten seconds the program opens the mask.
 * Then you always see only one message "Signal caught", even if
 * you have pressed CNTRL + C many times. This shows that in this
 * system signals are not queued. 
 *
 * In the latter part of the program we open the mask. Then you will
 * message "Signal caught" as many times as you press CNTRL + C 
 * during the next ten seconds.    
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>

void ctrl_handler(int);

int main(void) {
    time_t end_time;
    sigset_t mask, oldmask;
    sigemptyset(&mask);
    sigaddset(&mask, SIGINT);
    sigprocmask(SIG_BLOCK, &mask, &oldmask);
  
    if (signal(SIGINT, ctrl_handler) == SIG_ERR) {
        fprintf(stderr, "\nCannot set signal handler");
        exit(0);
    }
    
    // Signal is blocked. So we get the message "Interrupt caught"
    // only once after 10 seconds. Signals are missed in this case.
    printf("Signal SIGINT is now blocked\n");
    end_time = time(NULL) + 10;
    while (time(NULL) < end_time) {
        sleep(1);
        //printf("Program contiues\n");
    }   
  
    // Signal is not blocked. So we get the message "Interrupt caught"
    // as many times as we press CNTRL + C during 10 seconds
    sigprocmask(SIG_SETMASK, &oldmask, NULL);
    printf("Signal SIGINT is not blocked\n");
    end_time = time(NULL) + 10;
    while (time(NULL)  < end_time) {
        sleep(1);
    }
    return 0;
}

void ctrl_handler(int sig_no) {
    printf("Interrupt caught\n");
    return;
}
