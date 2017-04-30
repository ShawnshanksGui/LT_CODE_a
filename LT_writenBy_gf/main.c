#include "construct_method.h"
/*
int main()
{	
	//struct symbol *code_struct = NULL;
//	code_struct = (struct symbol *)malloc(sizeof(struct symbol));
	

//	fun_banana(code_struct);
	
	int k = 0;
	int _decd_finish_flag = 0;
	
	char *en_packet = malloc(sizeof(char) * LEN_EN_PACKET);

	char buf[MAX_INPUT_SYMBOL_NUM][CODELINE] = {'\0'};

//	get_raw_source(buf, MAX_INPUT_SYMBOL_NUM);
//	k = MAX_INPUT_SYMBOL_NUM;
	k = 20;
	get_raw_source(buf, k);

//	while(!_decd_finish_flag)
//	{	
	encode_lt(buf, en_packet, k);	
	procedure_over_channel(en_packet);
	decode_lt(en_packet, );
//	}

	return 0;
}
*/

int main()
{
	int i         = 0;
	int k         = 0;
	char tmp      = '\0';
	int sign_sucs = 0;
	int num_sent  = 0;
	int sent_real = 0;

	double _cdf[MAX_INPUT_SYMBOL_NUM + 1] = {0.0}; 
	char en_packet[LEN_EN_PACKET] = {'\0'};

	char sym_presv[2*MAX_INPUT_SYMBOL_NUM][CODELINE];

	char source_array[MAX_INPUT_SYMBOL_NUM][CODELINE];
//	memset(source_array, 0, sizeof(source_array));

	FILE *fp ;
	
	srand((int)time(NULL));
	memset(source_array, 0, sizeof(source_array));
/*
	Fopen_for_write(&fp, "hello.txt");
	for(i = 0; i < MAX_INPUT_SYMBOL_NUM; i++)
		for(k = 0; k < CODELINE; k++)
		{
			tmp = 'a' + (rand() % 25) + 1;
			Fwrite(&tmp, sizeof(char), 1, fp);			
		}
*/

	struct timeval starttime,endtime;
	double timepast;

	gettimeofday(&starttime, NULL);

	get_raw_source(source_array, 1000000);

//#pragma omp parallel  
//{
	get_cdf_final(_cdf, MAX_INPUT_SYMBOL_NUM);

	while(sign_sucs == 0 && num_sent < 1200000)
	{	
		memset(en_packet, 0, sizeof(en_packet));
		encode_lt(source_array, en_packet, MAX_INPUT_SYMBOL_NUM, _cdf);
		
		if(!transmit_over_ch())
		{	
			num_sent++;
			continue;
		}
		num_sent++;
		sent_real++;
		sign_sucs = decode(en_packet, sym_presv);
		
		//test
////		printf("num_sent = %d,  ", num_sent);
////		printf("sent_real = %d\n", sent_real);
	}

	//redundancy of the result!!!!
	printf("num_sent = %d,  ", num_sent);
	printf("input_symbol = %d\n", MAX_INPUT_SYMBOL_NUM);
	printf("the redundancy == %lf\n", (num_sent-MAX_INPUT_SYMBOL_NUM)/(float)MAX_INPUT_SYMBOL_NUM);		

	gettimeofday(&endtime,NULL);
	timepast=((double)(endtime.tv_sec-starttime.tv_sec)*1000000
		     +(double)(endtime.tv_usec-starttime.tv_usec))/1000000;
////	printf("the whole processing time of the program is %lf seconds\n",timepast);
//}
	return 0;
}		











