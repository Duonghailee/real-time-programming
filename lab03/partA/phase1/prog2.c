#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int main (void) {	
	int fd;
	char buff[5] = "BBBB";
	int i;
	fd = open("exlog.txt", O_WRONLY|O_CREAT);
	for(i = 0; i < 100000; i++) {		
		write(fd, buff, 4);		
	}
	close(fd);
}