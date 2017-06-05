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
	struct sockaddr_un saddru;
	unlink("server.sock");
	server_socket = socket(AF_UNIX, SOCK_STREAM, 0);
	saddru.sun_family = AF_UNIX;
	strcpy(saddru.sun_path, "server.sock");
	bind(server_socket, (struct sockaddr*)&saddru, 
			sizeof(saddru));
	listen(server_socket, SOMAXCONN);
	while ((client_socket = accept(server_socket, 
					NULL, 0)) >= 0){
		pid = fork();
		if (pid == 0) {
			pid = fork();
			if (pid > 0) {
				close(client_socket);
				exit(0);
			}
			if (pid == 0) {
				read(client_socket, &buf, 4);
				sscanf(buf, "%c %d", &ch, &t);
				/*printf("%d\n",t);*/
				for (i = 0; i < 10; i++) {
					write(client_socket, &ch, 1);
					sleep(t);
				}
				close(client_socket);
				close(server_socket);
				exit(0);	
			}
		}
		wait(NULL);
		close(client_socket);
	}
	return 0;
}
