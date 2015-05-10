#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>

int main(int argc, const char *argv[])
{
	int unix_socket,accept_u_fd;
	struct sockaddr_un accept_addr;
	char buf[128];

	unix_socket = socket(AF_UNIX,SOCK_STREAM, 0);
	perror("socket");


	accept_addr.sun_family = AF_UNIX;
	strncpy(accept_addr.sun_path,"./unix",sizeof(accept_addr.sun_path));


	if( 0 > connect(unix_socket,(struct sockaddr *)&accept_addr,sizeof(accept_addr)) ){
		perror("connect");
	}
	perror("connect");

	while(1){
		recv(unix_socket,buf,sizeof(buf),0);
		puts(buf);
	}




	return 0;
}
