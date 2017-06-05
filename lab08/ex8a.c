#include "MultiSensorSimulator.h"
#include <string.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/time.h>
#include <unistd.h>

#define k_SENSOR_AMOUNT 10

int max(int *ar, int n){
        int temp_max = -1;
        int i;
        for (i = 0; i < n; i++) {
                if (ar[i] > temp_max || temp_max == -1)
                        temp_max = ar[i];
        }
        return temp_max;
}

int main(void) {
        int fds[k_SENSOR_AMOUNT];
        int done[k_SENSOR_AMOUNT] = {0};
        Tmeas meas;
        fd_set fdset;
        int n = 0, max_fd;
        int remain;
        int count = 0;
        struct timespec sum_ts, ts;
        memset(&sum_ts, 0, sizeof(struct timespec));
        StartSimulator(fds, 5);
        max_fd = max(fds, k_SENSOR_AMOUNT) + 1;

        while (1) {
                FD_ZERO(&fdset);
                remain = 0;
                int i;
                for (i = 0; i < k_SENSOR_AMOUNT; i++) {
                        if (done[i] == 0) {
                                FD_SET(fds[i], &fdset);
                                remain++;
                        }
                }
                if (remain == 0) break;

                n = select(max_fd, &fdset, NULL, NULL, NULL);
                if (n > 0) {
                        for (i = 0; i < k_SENSOR_AMOUNT; i++) {
                                if (!FD_ISSET(fds[i], &fdset))
                                        continue;
                                if (read(fds[i], &meas, sizeof(Tmeas)) == 0) {
                                        done[i] = 1;
                                        printf("completed: %d\n", fds[i]);
                                        continue;
                                }
                                count++;
                                clock_gettime(CLOCK_REALTIME, &ts);
                                ts = diff_timespec(&meas.moment, &ts);
                                increment_timespec(&sum_ts, &ts);
                                printf("count: %2d, fd: %2d - value: %3d - %2ld s, %ld ns.\n",
                                                count, fds[i], meas.value, ts.tv_sec, ts.tv_nsec);
                        }
                }
        }
        printf("Count: %d, Sum of delay: %lf s.\n", count, (long long)sum_ts.tv_nsec * 1e-9);
        return 0;

}
