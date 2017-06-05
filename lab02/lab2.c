#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>

int main(void){
    
    while(1){
        char chr;
        read(STDIN_FILENO,&chr,1);
        if(chr == 'Q'){
            break;
        }
    }
}

