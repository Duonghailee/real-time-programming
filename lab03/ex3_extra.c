#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

int main (int argc, char *argv[40]){
    struct stat buff;
    struct stat state;
    stat(argv[1], &buff); // read file type
    stat(argv[1], &state); //read current mode
    if(S_ISREG(buff.st_mode)){
        printf("Is regular file\n");
    }
    if(S_ISDIR(buff.st_mode)){
        printf("Is directory file\n");
    }
    if(S_ISCHR(buff.st_mode)){
        printf("Is character special file\n");
    }

    //mask out 12 bits contain access right
    printf("file mode is: %o\n",state.st_mode & 07777);
    return 0;

}