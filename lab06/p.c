#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int main (int agrc, char *argv[]) {	
	char buff[6] = "AAAAA";
	int i;
    int fd = atoi(argv[1]); //fd is passed here
    for(i=0; i< 5; i++){
        lseek(fd,0L,SEEK_SET);
        write(fd, buff, 5);	
        sleep(1);
    }
    return 0;
}