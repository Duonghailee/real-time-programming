#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>

int main(void){

    int fellow_desc;
    while (1){
        
        fellow_desc = OpenChatFellow();
        char chr_fellow;
        read(fellow_desc, &chr_fellow, 1);
        putchar(chr_fellow); 
        if(chr_fellow == 'Q'){
            break;
        }
    }
    close(fellow_desc);
}

