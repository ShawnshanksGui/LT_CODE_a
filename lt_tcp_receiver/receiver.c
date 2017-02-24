#include "receiver.h"

int main(int argc, char *argv[])
{
	int sock_id = 0;
	socklen_t client_addr_len;
	int recv_len = 0;
	char ctp_buf[RECLINE] = {'\0'};

	FILE *fp = NULL;

	struct sockaddr_in serv_addr;
	struct sockaddr_in client_addr;

	socklen_t serv_addr_len;

	client_addr_len = sizeof(client_addr);

	if(argc != 2)
	{
		usage(argv[0]);
	}

//	Fopen(fp, argv[2]);
	Socket(&sock_id);
	
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(atoi(argv[1]));
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	Bind(sock_id, (SA*)&serv_addr, sizeof(serv_addr));

//	printf("%d\n", sock_id);	

	while((recv_len = recvfrom(sock_id, ctp_buf, sizeof(ctp_buf), 0, (SA *)&client_addr, &client_addr_len)) > 0)
	{
	//	printf("hello, world");
	//		exit(0);
	printf("%d\n", recv_len);
		break;
	}
	printf("%d\n",recv_len);
	printf("hello,world");
//	while(1);
	close(sock_id);
	return 0;
}
