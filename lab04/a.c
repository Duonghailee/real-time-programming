#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
int main (void) {	
	//FILE *file;	
	int buffSize = 5;
	char buffer[buffSize];
	char ch = 'a';
	int i = 0;
	setvbuf(stdout, buffer, _IOFBF, buffSize);	
	for (i = 0; i < 13; i++) {
		fputc(ch, stdout);		
		ch++;
		sleep(1);
	}
	
	//fflush(stdout);
	return 0;
	
	//exit(0);
}