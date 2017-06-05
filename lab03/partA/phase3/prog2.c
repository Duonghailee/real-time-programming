#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>


int main (void) {	
	int fd;
	char buff[5] = "AAAA";
	int i;
	fd = open("exlog.txt", O_WRONLY|O_CREAT|O_APPEND);
	for(i = 0; i < 100000; i++) {		
		write(fd, buff, 4);	
        //lseek(fd,0L, SEEK_END);
	}
	close(fd);
}
