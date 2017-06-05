#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>


/* compile this one as an object file and pass its name to the commandline to be an environment variable for the parent to the child process */
int main (int argc, char *argv[]) {	
	char buff[6] = "AAAAA";
	int i;
	//printf("child here argv[1]:%s\n",argv[1]);
    int fd = atoi(argv[1]);// here fd = atoi(argv[1]); the second argument passd to the CL remove the - '0' and the pointer
	lseek(fd,0L,SEEK_SET);//lseek to begining of the file before writing
    for(i=0; i< 5; i++){
        write(fd, buff, 5);	
        sleep(1);
    }
   // printf("Child fd:%d\n",fd);
	/*  return something to flush though this is not needed as we use system call */
	return 0;
}