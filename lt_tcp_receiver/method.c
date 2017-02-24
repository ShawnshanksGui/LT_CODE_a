#include "receiver.h"

void usage(char *command)
{
	printf("usage:%s receiver_port\n", command);
}

void Socket(int *sock_id)
{
	if(((*sock_id) = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
	{
		perror("Create socket failed\n");
		exit(0);
	}
}

void Fopen(FILE *fp, char *param)
{
	if((fp = fopen(param, "r")) == NULL)
	{
		perror("Open file failed\n");
		exit(0);
	}
}

void Bind(int sock_id, SA *ptr_addr, int len)
{
	if(bind(sock_id, ptr_addr, len) < 0)
	{
		perror("Bind socket failed\n");
		exit(0);
	}
}

