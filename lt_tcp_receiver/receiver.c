#include "receiver.h"
#include "assert.h"

int main(int argc, char *argv[])
{
	int sock_id = 0;
	socklen_t client_addr_len;
	int recv_len = 0;
	char ctp_buf[RECLINE] = {'\0'};

	FILE *fp = NULL;
	
	int count_flag = 0;
	struct sockaddr_in serv_addr;
	struct sockaddr_in client_addr;

	socklen_t serv_addr_len;

	client_addr_len = sizeof(client_addr);

	if(argc != 3)
	{
		usage(argv[0]);
	}

	Fopen(&fp, argv[2]);
	
	assert(fp != NULL); 

	Socket(&sock_id);
	
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(atoi(argv[1]));
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	Bind(sock_id, (SA*)&serv_addr, sizeof(serv_addr));

//	printf("%d\n", sock_id);	
	fwrite("aaaaaaaaaa",sizeof(char), 10, fp);
//	exit(0);

	while((recv_len = recvfrom(sock_id, ctp_buf, sizeof(ctp_buf), 0, (SA *)&client_addr, &client_addr_len)) > 0 && count_flag <= 4)
	{
		printf("%s\n", ctp_buf);
//		fwrite("aaaaaaaaaa", sizeof(char), 10, fp);
		fwrite(ctp_buf, sizeof(char), 10, fp);
		bzero(ctp_buf, sizeof(ctp_buf));
	
		count_flag++;
	}

//	fwrite("aaaaaaaaaa",sizeof(char), 10, fp);
//	printf("%d\n",recv_len);
//	printf("hello,world");
//	while(1);
	close(sock_id);
	fclose(fp);
	return 0;
}
