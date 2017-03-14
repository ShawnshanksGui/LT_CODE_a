#include "construct_method.h"

void
set_packet_sent(char *en_symbol, char *en_packet, int *en_list, int d)
{
//	int num_byte_list = 0;
	int i = 0;

//	num_byte_list = ceil(d/8);

	en_symbol[0] = d;
	for(i = 0; i < d; i++)
		en_packet[2+(i/8)] |= (unsigned char)1 << (en_list[i]%8);

	for(i = 0; i < d; i++)
		en_packet[2 + MAX_BYTE_LIST + i] = en_symbol[i];
}


void 
encode_lt(char symbol_raw[][CODELINE], char *en_packet, int k)
{
	struct symbol *ptr_en_sym;
	ptr_struct_ensym = (struct symbol*)malloc(sizeof(struct symbol));
	
	get_d(&(ptr_struct_ensym->d), k);
	get_index(ptr_struct_ensym->index, ptr_struct_ensym->d, k);
	get_data(symbol_raw, ptr_struct_ensym);
	set_packet_sent(ptr_struct_ensym->data, en_packet, 
					ptr_struct_ensym->index, ptr_struct_ensym->d);
}

void get_raw_source(char buf[][CODELINE], int symbol_num)
{
	FILE *fp = NULL;
	int readlen = 0;
	int i = 0;
	char *ptr_char = NULL;

	Fopen_for_read(&fp, "hello.txt");

	ptr_char = buf[i];
	while((readlen = fread(ptr_char, sizeof(char), CODELINE, fp)) > 0)
	{	
		i++;
		if(i > symbol_num)
		{
			break;
		}
		ptr_char = buf[i];
	}
}


int main()
{	
	/*struct symbol *code_struct = NULL;
	code_struct = (struct symbol *)malloc(sizeof(struct symbol));
	

	fun_banana(code_struct);
	*/
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
//		procedure_over_channel(en_packet);
//		decode_lt(en_packet);
//	}

	return 0;
}
