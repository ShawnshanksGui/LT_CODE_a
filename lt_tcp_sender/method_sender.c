#include "sender.h"


void usage(char *command)
{
	
	printf("usage:%s sender_add sender_port open_filename", command);
}

void Socket(int *sock_id)
{
	if(((*sock_id) = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
	{
		perror("Create socket falied\n");
		exit(0);
	}
}

void Fopen(FILE *fp, char *param)
{	
	if((fp = fopen(param, "r")) == NULL)
	{
		printf("Fopen file failed\n");
		exit(0);
	}
}

