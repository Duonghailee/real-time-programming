#include <stdio.h>
#include <unistd.h> 
#include <fcntl.h>  

int main (void) {
    char chr;
    while(chr != 'Q'){
        read(STDIN_FILENO, &chr, 1);
        write(STDIN_FILENO, &chr, 1);
    }
}