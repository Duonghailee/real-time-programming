#include <stdio.h>
#include <string.h>


int main (void){
    int i = 0;
    char str[] = "hello world.!";
    char buffer[5];
    setbuf(stdout,buffer);
    setvbuf(stdout,buffer,_IOFBF,5);

    for(i;i<13;i++){
       fputc(str[i],stdout);
       sleep(1);
    }
    //a. when is terminated by fflush, 3 last char are succeed written,
    // fully buffer write is done when buffer is full, 
    //fflush(stdout);

    //b. using only exit(0)
    // exit(0);

    //c. retunn 0 case
   return 0;
    
}