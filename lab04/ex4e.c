#include<stdio.h>
#include<libio.h>
#include<string.h>

int main (int argc, char *argv[]){
    FILE *fp;
    char buff[5];
    fp = fopen(argv[1],"r");
    fread(buff,sizeof(buff),1,fp);

    fprintf(stdout, "File descriptor: %d\n", fp->_fileno);
    fprintf(stdout, "size of the file: %d\n",fp->_IO_read_end - fp->_IO_read_base);
    fprintf(stdout, "size of buffer: %d\n", fp->_IO_buf_end - fp->_IO_buf_base);

    if(fp->_flags & _IO_UNBUFFERED){
        fprintf(stdout, "The buffering mode is unbuffered\n");
    } else if(fp->_flags & _IO_LINE_BUF){
        fprintf(stdout, "The buffering mode is unbuffered\n");
    }
    else{
        fprintf(stdout, "The buffering mode is fully buffered\n");
    }
    fclose(fp);
    return 0;

}