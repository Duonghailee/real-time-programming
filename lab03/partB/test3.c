#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

//prototype
void print_flags(int fd);

//main function
int main (void) {
    int fd;
    int file_flags;
    int chr;
    
    fd = open("/dev/tty", O_RDONLY); //read only, write will show error

   // print_flags(fd);

    //set file_flags O_NONBLOCK, O_APPEND for the terminal
    file_flags = fcntl(fd, F_GETFL, 0);
	file_flags = file_flags | O_NONBLOCK;
	file_flags = file_flags | O_APPEND;
	fcntl (fd, F_SETFL, file_flags);	

	print_flags(fd);

    //try to read one character from the opened terminal
    if(read(fd, &chr, 1)>0){
        printf("Read succeeded. Character was %c\n",chr);
    } else{
        perror("Read failed: ");
    }

    close(fd);
}

//print_flags function
void print_flags(int fd){
    int access_mode, file_flags;
    char chr;

    file_flags = fcntl(fd, F_GETFL, 0);
    access_mode = file_flags & O_ACCMODE;

    //checking O_NONBLOCK
    if(file_flags & O_NONBLOCK){
        printf("now is non blocking mode\n");
    } else{
        printf("Now is in blocking mode\n");
    }

     //checking O_APPEND
    if (file_flags & O_APPEND) {		
		printf(" Mode is Append\n");
	} else {
		printf("Mode is not Append\n");
	}	
	

    //checking settings on the file
    if (access_mode == O_WRONLY) {		
		printf("Access mode is Write only\n");		
	} else if (access_mode == O_RDONLY){
		printf("Access mode is RDONLY\n");
	} else {
		printf("Access mode is Read and write\n");
	}
    
}