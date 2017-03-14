#ifndef ENCODE_CONSTRUCT 

#define ENCODE_CONSTRUCT 100

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "math.h"
#include "assert.h"

#include "errno.h"
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>
#include <arpa/inet.h>

typedef struct sockaddr SA;
#define CODELINE 10
#define MAX_BYTE_LIST 20
#define MAX_INPUT_SYMBOL_NUM 1000
#define LEN_EN_PACKET 220

#define C_ROBUST_SLT_DISTRI 0.1
#define DELTA 0.5

struct symbol{
    int d;
	char data[CODELINE];
	int index[MAX_BYTE_LIST];
};

void usage(char *command);

void Socket(int *sock_id);

void Fopen(FILE **fp, char *param);

void Bind(int sock_id, SA *ptr_addr, int len);

/*******************************/
//get degree d
double get_tau(int, int);

double get_beta(int);

double get_ideal_slt_distri(int, int);

void get_robust_slt_distri_pro(double *, int);

void get_cdf_distri(double *, double *, int);

void interval_judge(int *, double, double *, int);

void get_cdf_final(double *, int);

void get_d(int *, double *, int);
/********************************/

/**************************************/
//get_index
void get_index(int *, int, int);
/*************************************/

/*************************************/
void get_data(char symbol_raw[][CODELINE], struct symbol *);
/*************************************/
#endif
