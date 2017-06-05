#include <stdio.h>
#include <unistd.h> 
#include <fcntl.h>  

int main (void) {
    int fellow_desc;
    fellow_desc = OpenChatFellow();
    char chr_fellow;

    while(1){
        read(fellow_desc, &chr_fellow, 1);
        write(STDIN_FILENO, &chr_fellow, 1);
    }
    close(fellow_desc);
}