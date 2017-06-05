/* lab_client.c -- Program that simulates many clients. Is used to test the server
 * that is implemented as lab exercise
 */

#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    int socket_fd, n;
    struct sockaddr_un server_address, client_address;
    char request[20];
    char chr;
    int i;
    pid_t child;
    
    // Adress of the server
    server_address.sun_family = AF_UNIX;
    strcpy(server_address.sun_path, "server.sock");
    
    for (i = 0 ; i < 4 ; i++) {
        child = fork();
        if (child == 0 ) {
            // Create a socket
            if ((socket_fd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0) {
                perror("Client: Error in creating a socket ");
                exit(1);
            }  
            // Connect to the server
            if (connect(socket_fd, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
                perror("Client: Error in connection to the server ");
                exit(1);
            }
            // Write to the socket.
            sprintf(request, "%c %d", 'a' + i, i + 1);
            write(socket_fd, request, strlen(request)+1);
            // Read from the socket
            n = read(socket_fd, &chr, 1);  // reads what is available in the socket
            while ( n > 0 ) {
                printf("%c", chr);
                fflush(stdout);
                n = read(socket_fd, &chr, 1);  // reads what is available in the socket
            }
            if (n < 0)
                printf("Client: Error in read\n" );
            if (n == 0) {
                printf("(eof)" );
                fflush(stdout);
            }
            // Close the socket
            close(socket_fd);
            return 0;
        }
    }
    while(wait(NULL)>0);
    return 0;
}
