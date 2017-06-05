/* sleep_alarm.c
 *
 * This program demonstrates, that in this system
 * 1) If alarm is set that expires before the asked sleep
 *    is done, sleep  returns with a return value indicating
 *    the time that is left. 
 *    The program displays "Alarm received" and returns from
 *    the sleep after sleeping 5 seconds.
 * 2) If alarm is set that expires after the sleep
 *    sleep restores the alarm clock and signal handler.
 *    The program continues and displays "Program continues 
 *    in 1 second intervals. It also displays alarm received
 *    in 5 second intervals 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

static void alrm_handler(int);

int main(void) {
    int time_left;
    if (signal(SIGALRM, alrm_handler) == SIG_ERR) {
        fprintf(stderr, "\nCannot set signal handler");
        exit(0);
    }

    alarm (5);
    // time_left = sleep (10);      // This is case 1
    // printf("Sleep has returned. Time left = %d\n", time_left);
    
    while (2 < 3) {                // This is case 2
        printf("Program contiues\n");
        sleep(1);
    }
    return 0;
}

static void alrm_handler(int sig_no) {
    printf("Alarm is received \n");
    alarm(5);
    return ;
}
