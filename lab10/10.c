#include <sys/un.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wait.h>
#include <unistd.h>

int main(){
	int server_socket, client_socket;
	char buf[4];
	char ch;
	int t, i;
	pid_t pid;
	struct sockaddr_un saddru;//initial sturct socket address
	unlink("server.sock");
	server_socket = socket(AF_UNIX, SOCK_STREAM, 0); // set up server
	saddru.sun_family = AF_UNIX; //type
	strcpy(saddru.sun_path, "server.sock");
	bind(server_socket, (struct sockaddr*)&saddru, //bind 
			sizeof(saddru));
	listen(server_socket, SOMAXCONN); //start listning to client
	while ((client_socket = accept(server_socket, //accept request from client true
					NULL, 0)) >= 0){
		pid = fork(); // fork a child that serves the client
		if (pid == 0) { // this is chils
			read(client_socket, &buf, 4);
			sscanf(buf, "%c %d", &ch, &t); // read each char and each time t to perform write each corresponding char and sleep for a certain time t
			for (i = 0; i < 10; i++) {
				write(client_socket, &ch, 1);
				sleep(t);
			}
			close(client_socket);
			close(server_socket);
			exit(0);	
		}
		wait(NULL); //parent continues here to wait for all children
		close(client_socket);
	}
	return 0;
}
