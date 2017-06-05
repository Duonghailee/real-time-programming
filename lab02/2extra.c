#include<stdio.h>
#include<time.h>

int main (void){
    
    time_t time_raw;
    time (&time_raw);
    struct tm *tm = localtime(&time_raw);
    char str_date[80]; //store time string to display
    strftime(str_date, 80, "%d.%m.%Y %H:%M:%S", tm) ; //format date and time
    printf("%s\n",str_date );

}