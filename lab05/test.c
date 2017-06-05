#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

int main (void){
    int i;
    for(i = 0; i< 3; i++){
        fork();
        printf("%d\n",i);
    }
    return 0;
}