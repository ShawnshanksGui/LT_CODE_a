#include "stdio.h"
#include "string.h"
#include "errno.h"
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>
#include <arpa/inet.h>

typedef struct sockaddr SA;

#define RECLINE 20

void usage(char *command);

void Socket(int *sock_id);

void Fopen(FILE *fp, char *param);

void Bind(int sock_id, SA *ptr_addr, int len);
