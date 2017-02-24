#include "sender.h"

int main(int argc, char *argv[])
{
	int sock_id = 0;
	FILE *fp = NULL;
	struct sockaddr_in serv_addr;
	socklen_t serv_addr_len;

	int x = 0; //realted to fcntl 
	int length_sent = 0; //related to sendto
	
	char ctp_buf[DATALINE] = {'r'};

	if(argc != 4)
	{
		usage(argv[0]);
	}

	Fopen(fp, argv[3]);
	Socket(&sock_id);

/* the fllowing block can be inverted into one line of code*/
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(atoi(argv[2]));
	inet_pton(AF_INET, argv[1], &serv_addr.sin_addr);
	serv_addr_len = sizeof(serv_addr);
/**********************************************************/

//	x = fcntl(sock_id, F_GETFL, 0);
//	fcntl(sock_id, F_SETFL, x|O_NONBLOCK);

	length_sent = sendto(sock_id, ctp_buf, 
		10, 0, (SA *)&serv_addr, sizeof(serv_addr));
	if(length_sent)
	{
//		printf("%s\n",(SA *)&serv_addr);
		printf("%d\n", length_sent);

		printf("hello, world");
	}
	

	return 0;

}
