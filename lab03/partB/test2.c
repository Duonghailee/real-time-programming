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
    fd = open("/dev/tty", O_RDONLY);
    print_flags(fd);
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
    if(access_mode == O_APPEND){
        printf("Access mode is append\n");
    } else{
        printf("Access mode is not append\n");
    }

    //read a character 
    if(read(0, &chr, 1)>0){
        printf("Read succeeded. Character was %c\n",chr);
    } else{
        perror("Read failed: ");
    }

    //write a Character
    chr = 'A';
    if(write(fd, &chr, 1)>0){
        printf("Write succeeded\n");
    } else{
        perror("Write failed: ");
    }

}