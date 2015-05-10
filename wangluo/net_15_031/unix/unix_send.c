#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>

int main(int argc, const char *argv[])
{
	int unix_socket,accept_u_fd;
	struct sockaddr_un addr;

	unix_socket = socket(AF_UNIX,SOCK_STREAM, 0);
	perror("socket");

	addr.sun_family = AF_UNIX;
	strncpy(addr.sun_path,"./unix",sizeof(addr.sun_path));

	if(0 > bind(unix_socket,(struct sockaddr *) &addr,sizeof(addr)) ){
		perror("bind");
		return 0;
	}
	perror("bind");

	if(0 > listen(unix_socket,10) ){
		perror("listen");
		return 0;
	}
	perror("listen");



	accept_u_fd = accept(unix_socket,NULL,NULL);	
	
	if(accept_u_fd < 0){
		perror("accept_u_fd");
		return 0;
	}
	perror("accept_u_fd");


	while(1){
		send(accept_u_fd,"123",4,0);
		sleep(1);
	}




	return 0;
}
