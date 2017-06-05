#include <stdio.h>
#include <string.h>

int main (void){
    FILE *stream;
    int fd = OpenRandomGenerator();
    int num;
    int count = 0, i = 0;
    stream = fdopen(fd, "r");
    for(i; i< 7 ; i++){
        fscanf(stream, "%d", &num);
        if(num < 20){
            count++;
        }
        fprintf(stdout,"%d\n",num);
    }
    fprintf(stdout,"There are %d number < 20\n", count);
}