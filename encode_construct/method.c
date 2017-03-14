#include "construct_method.h"

#include "stdio.h"
#include "math.h"
#include "assert.h"
#include "stdlib.h"

/*
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

void Fopen_for_write(FILE **fp, char *param)
{
	if((*fp = fopen(param, "w")) == NULL)
	{
		perror("Open file failed\n");
		exit(0);
	}
}

void Fopen_for_read(FILE **fp, char *param)
{
	if((*fp = fopen(param, "r")) == NULL)
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
*/
/****************************************************/
double get_tau(int i, int k)
{
	double tau;
	double R;
	double temp;

	temp = floor((double)k/R);
	R = C_ROBUST_SLT_DISTRI*log((double)k/(double)DELTA)*sqrt(k);

	if((double)i <  temp - 1)
		tau = R/(i*k);
	else if((double)i == temp)
		tau = R*log(R/DELTA)*k;
	else if((double)i > temp && (double)i < k)
		tau = 0.0;
	else
	{
		printf("get_tau error happened!!!!!!!!");
		exit(0);
	}
	return tau;
}

double get_beta(int k)
{
	int i;
//	double sum_ideal_solit;
	double beta;

	for(i = 1; i <= k; i++)
	{
		beta += (get_ideal_slt_distri(i, k) + get_tau(i, k));
	 }
	return beta;
}

double get_ideal_slt_distri(int i, int k)
{
	if(1 == i)
		return (double)(1/k);
	else if(i > 1 && i <= k)
		return (double)(1/(i*(i-1)));
	else
	{
		printf("error: get ideal slt-distribution\n");
		exit(0);
	}
}


void get_robust_slt_distri_pro(double *ptr_distri, int k)
{
	int i = 0;
	double beta = 0.0;

	beta = get_beta(k);
	assert(beta != 0.0);

	for(i = 1; i <= k; i++)
	{
		//reduce computing compplexity//
	//	beta = get_beta(k, i); //deserve improvement
		//***************************//
		ptr_distri[i] = (get_ideal_slt_distri(i, k) + get_tau(i, k)) / beta;
	}
}

void get_cdf(double *ptr_cdf, double *ptr_distri_pro, int k)
{
	int i = 0;
	ptr_cdf[0] = 0;

	for(i = 1; i <= k; i++)
	{
		ptr_cdf[i] += ptr_distri_pro[i] + ptr_cdf[i-1];
	}
}

void interval_judge(int *ptr_d, double value, double *cdf_distri, int k)
{
	int i;
	for(i = 1; i <= k; i++)
	{
		if(value < cdf_distri[i] && value > cdf_distri[i-1])
		{
			*ptr_d = i;
			break;
		}
	}
}

void get_cdf_final(double *cdf_distri, int k)
{
	double robust_distri_pro[k+1];
//	double cdf_distri[k+1];
//	double value;
	get_robust_slt_distri_pro(robust_distri_pro, k);	
	get_cdf(cdf_distri, robust_distri_pro, k);
//	value = (double)((random() % 100000))/100000.0;
//	interval_judge(ptr_d, value, cdf_distri, k);
}

void get_d(int *ptr_d, double *cdf_distri, int k)
{
	double value;

	value = (double)((random() % 100000))/100000.0;
	interval_judge(ptr_d, value, cdf_distri, k);
}
/*
//test//

int main()
{
	int d = 0;
	int k = 10;
	int i = 0;
	double cdf_distri[k+1];	
	get_cdf_final(cdf_distri, k);
	for(i = 0; i < 20; i++)
	{
		get_d(&d, cdf_distri, k);
		printf("d = %d\n", d);
	}
	return 0;
}
*/
/****************************************************/

/****************************************************/
//get_index
void get_index(int *index, int d, int k)
{
	int i = 0;
	int j = 0;
	int num = 0;
	int flag_success = 0;  //flag of preventing from repeating select

	for(i = 0; i < d; i ++)
	{
		while(!flag_success)
		{
			flag_success = 1;
			num = random()%k;
			for(j = 0; j < i; j++)
			{
				if(num == index[j])
				{
					 flag_success = 0;
				}
			}
		}
		index[i] = num;
		flag_success = 0;
	}
}


void get_data(char symbol_raw[][CODELINE], struct symbol *ptr)
{
	int i = 0;
	int j = 0;

	for(i = 0; i < ptr->d; i++)
	{
		for(j = 0; j < CODELINE; j++)
			ptr->data[j] ^= symbol_raw[ptr->index[i]][j]; //module 2 + operator
	}
}

int main()
{
	char symbol_raw[10][10] = {1,1,0,0,0,0,0,0,0,1};
	struct symbol ensymbol = {10, {0,0,0,0,0,1,1,1,1,1}, 
							 {0,1,2,3,4,5,6,7,8,9}};
	struct symbol *ptr;
	*ptr = ensymbol;
	get_data(symbol_raw, ptr);

	return 0;
}
/****************************************************/







