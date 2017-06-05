#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/time.h>
#include <time.h>

#define INFO_VALUE 1991

struct timespec after;

void rt_handler(int signo, siginfo_t *info, void* p ) {
	clock_gettime(CLOCK_REALTIME, &after);
	return;
}
int main(void) {
	int fds[2];
	pid_t pid;
	sigval_t value;
	struct timespec res, now, ts;
	struct sigaction sa;
	sigset_t mask, non_block;

	clock_getres(CLOCK_REALTIME, &res);
	printf("Real time clock resolution: %ld s %ld ns\n", res.tv_sec, res.tv_nsec);

	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigemptyset(&mask);
	sigaddset(&mask, SIGRTMIN);
	sigprocmask(SIG_BLOCK, &mask, &non_block);
	sa.sa_sigaction = rt_handler;
	sigaction(SIGRTMIN, &sa, NULL);


	pipe(fds);

	if ((pid = fork()) < 0)
		perror("error forking\n");
	if (pid == 0) {
		close(fds[1]);
		sigsuspend(&non_block);
		if (read(fds[0], &ts, sizeof(struct timespec)) > 0)
			printf("Delay was: %.2lf us\n", ((after.tv_sec - ts.tv_sec) * 1e9 + (after.tv_nsec - ts.tv_nsec)) * 1e-3);
		close(fds[0]);
		exit(0);
	} else {
		close(fds[0]);
		value.sival_int = INFO_VALUE;
		sigqueue(pid, SIGRTMIN, value);
		clock_gettime(CLOCK_REALTIME, &now);
		write(fds[1], &now, sizeof(struct timespec));
		wait(NULL);
		close(fds[1]);
		exit(0);
	}

	return 0;
}
