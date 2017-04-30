/***************************/
//author: Shawnshanks fei
//date:   2017.03.14
//theme:  header of lt_code source_Code
/***************************/

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
#define CODELINE 100
#define MAX_INDEX_LIST 80
//#define MAX_BYTE_LIST 10 //index storaged as bit 
//#define MAX_INPUT_SYMBOL_NUM 80
//#define LEN_EN_PACKET  112

//about above, replaced by below
#ifdef MAX_INDEX_LIST 
//******************************
#define MAX_BYTE_LIST MAX_INDEX_LIST/8
#define MAX_INPUT_SYMBOL_NUM MAX_INDEX_LIST
#define LEN_EN_PACKET 1+1+MAX_BYTE_LIST+CODELINE
//******************************
#endif

/*
#define C_ROBUST_SLT_DISTRI 0.1
#define DELTA 0.5
*/

#define C_ROBUST_SLT_DISTRI 0.1
#define DELTA 0.5

#define YES 1
#define NO 0

//*******************************
//*******decoder**********
#define MAX_EN_SYMBOL_RECV 16000
//*******************************

typedef unsigned char uchar;
typedef unsigned int  uint;

//*********************
//encoding symbol
typedef struct symbol{
    int d;
	char data[CODELINE];
	int index[MAX_INDEX_LIST];
}en_symbol;

//**********************
typedef struct de_sym{
	int d;
	char data[CODELINE];
	int index[MAX_INDEX_LIST];
}de_symbol;
//**********************
//**********************
typedef struct rip{
	int id_rip[MAX_INPUT_SYMBOL_NUM + 1000];
	int addr_rip[MAX_INPUT_SYMBOL_NUM + 1000];   //reflect to addr of de_buf[]
}rip_s;
//**********************

void usage(char *command);

void Socket(int *sock_id);

void Fopen_for_write(FILE **fp, char *param);

void Fopen_for_read(FILE **fp, char *param);

size_t Fwrite(void *, int, int, FILE *);

size_t Fread( void *, int, int, FILE *);

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
void set_packet_sent(char *, char *, int *, int);
void encode_lt(char symbol_raw[][CODELINE], char *, int, double *);
void get_raw_source(char buf[][CODELINE], int);


//decode part
/****************************************/
void pre_treat(char *, de_symbol *);
void get_amount(int *, int);
int  get_id(de_symbol);
int  judge_repeat_rip(int, int, int , int *);
int  judge_repeat_buf(int, struct de_sym, struct de_sym *);
void insert_rip(int, int, int, struct rip *);
void insert_buf(struct de_sym, struct de_sym *);
void get_sym_from_rip(de_symbol **, de_symbol *);
void sign_sucs(int , char *);
int  search_self_neighbor(de_symbol, de_symbol);
void update_buf(de_symbol *, de_symbol *);
int  success_judge_recvry(char *);
int  decode(char *, char symbol_recover[][CODELINE]);
/*****************************************/

#endif
