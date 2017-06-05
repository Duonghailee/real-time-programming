#include <stdio.h>
#include <unistd.h> //reading from keyboard, STDIN_FILENO
#include <fcntl.h>  // change file mode

int main (void) {

    int fellow_desc; //variable for prototype OpenChatFellow
    fellow_desc = OpenChatFellow(); 
    char chr_fellow;
    char chr;
  
    //change fellow TO UN BLOCK MODE
    int file_flags; // utilize to change mode to non blocking mode of file,in UNIX kb is also a fileno
    file_flags = fcntl(fellow_desc, F_GETFL); // read current file flags
    file_flags = file_flags | O_NONBLOCK; //add O_NONBLOCK bit
    fcntl(fellow_desc, F_SETFL, file_flags); // write new flags back
    read(fellow_desc, &chr_fellow, 1); //read a char from the fellow

    // change keyboard to UNBLOCK mode
    file_flags = fcntl(STDIN_FILENO, F_GETFL);
	file_flags = file_flags | O_NONBLOCK;
	fcntl (STDIN_FILENO, F_SETFL, file_flags);


    while (chr != 'Q'){
        if(read(fellow_desc, &chr_fellow, 1) > 0){ // read a char from the fellow success 
            write(STDOUT_FILENO,&chr_fellow,1); // write a char from fellow to screen
        }
        if(read(STDIN_FILENO, &chr, 1) > 0 ){; // read a char from the keyboard
            write(STDIN_FILENO,&chr, 1); // write a char to screen
        }
    }
   
    close(fellow_desc);
    
}