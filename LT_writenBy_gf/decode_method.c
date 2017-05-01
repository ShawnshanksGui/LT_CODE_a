#include "construct_method.h"
//static int ripple[MAX_EN_SYMBOL_RECV];
//static char symbol_recover[MAX_INPUT_SYMBOL][CODELINE];
//static char buf[][MAX_INPUT_SYMBOL][CODELINE];
//static char packet[LEN_EN_PACKET];

void pre_treat(char *ptr_packet, de_symbol *_data)
{
	int i = 0;
	int k = 0;
	int mm = 0;
	int tmp = 0;

	_data->d = ptr_packet[0];

	for(i = 2; i < 2+MAX_BYTE_LIST; i++)
		for(mm = 0; mm < 8; mm++)
		{	
			if((tmp = ((unsigned char)ptr_packet[i]) & (0x1<<mm)) != 0)
			{	
				_data->index[k] = (i-2)*8 + mm + 1;  //index starts from 0,
				k++;
			}
		}

	for(i = 2+MAX_BYTE_LIST, k = 0; i < LEN_EN_PACKET; i++, k++)
		_data->data[k] = ptr_packet[i];
}

/*************************************/
//methods of function decode

void get_amount(int *amount, int d)
{
	*amount = d;
}
/*
int get_id(de_symbol monkey)
{	
	int i, k;

	for(i = 0; i < MAX_INDEX_LIST; i++)
	{
		if (monkey.index[i] != 0)
			for(k = 0; k < 8; k++)
			{
				if((monkey.index[i] >> k) == (uchar)1)
					return (i*8 + k + 1);
			}
	}
	
	//error happened!!!!!!!!!
	printf("error: get_id !!!!!!!\n");
	exit(0);
}
*/

int get_id(de_symbol monkey)
{
	int i = 0;

	for(i = 0; i < MAX_INPUT_SYMBOL_NUM; i++)
	{
		if(monkey.index[i] > 0)
			return monkey.index[i];
	}
	printf("monkey.d = %d\n", monkey.d);
	printf("error: get_id");
	exit(0);
}

//********************************************
int judge_repeat_rip(int id, int start, int end, int *array_id)
{
	int i = start;

	for(i = start; i < end; i++)
	{
		if(array_id[i] == id)
			return 1;
	}
	return 0;
}

int judge_repeat_buf(int num,struct de_sym _data,struct de_sym *buf_array)
{
	int i = 0;
	int k = 0;

	for(i = 0; i < num; i++)
	{
		if(_data.d == buf_array[i].d)
			for(k = 0; k < CODELINE; k++)
			{
				if(_data.data[k] != buf_array[i].data[k])
					break;
				else if(k == CODELINE - 1)
					return 1;
			}
	}
	return 0;
}
//********************************************

//********************************************
void insert_rip(int id, int addr_buf, int addr_rip, struct rip *ripple)
{
	ripple->id_rip[addr_rip] = id;
	ripple->addr_rip[addr_rip] = addr_buf;
}

void insert_buf(struct de_sym _data, struct de_sym *ptr)
{
	int i = 0;

	ptr->d = _data.d;
	for(i = 0; i < CODELINE; i++)
		ptr->data[i] = _data.data[i];
	for(i = 0; i < MAX_INDEX_LIST; i++)
		ptr->index[i] = _data.index[i];
}
//********************************************

void get_sym_from_rip(de_symbol **sym_from_rip, de_symbol *symbol_buf)
{
	*sym_from_rip = symbol_buf;
}

void sign_sucs(int id, char *sign)
{
	sign[(id-1)/8] |= (uchar)1<<((id-1) % 8);//start from 0 --->subscript
}

int search_self_neighbor(de_symbol aa, de_symbol bb)
{
	int i = 0;

	int _id	= get_id(aa);
	
	for(i = 0; i < MAX_INDEX_LIST; i++)
	{
		if(_id == bb.index[i])
			return 1;
	}
	return 0; // not found!!!
}

void update_buf(de_symbol *sym_from_rip, de_symbol *sym_from_buf)
{
	int i = 0;
	int tmp = 0;
	for(i = 0; i < CODELINE; i++)
		sym_from_buf->data[i] ^= sym_from_rip->data[i];
	sym_from_buf->d--; 

	tmp = get_id(*sym_from_rip);
	for(i = 0; i < MAX_INPUT_SYMBOL_NUM; i++)
	{
		if(sym_from_buf->index[i] == tmp)
		{
			sym_from_buf->index[i] = 0;
			break;
		}
	}
}

int success_judge_recvry(char *sign)
{
	int i = 0;

	for(i = 0; i < MAX_INDEX_LIST; i++)
	{
		if(sign[i] != 0xff)
			return 0;
	}
	return 1;
}

//********************************************
int decode(char *ptr_packet, char symbol_recover[][CODELINE])
{	
	de_symbol _data_tmp;

	int i            = 0;
	int num_procs    = 0;
	int amount_insym = 0;
	int id_symbol    = 0;
	int sign_success = 0;
	
	de_symbol *sym_from_ripple;
	
//	static char sign[MAX_BYTE_LIST] = {'\0'}; 
	//sign of success:all bits are 1
	static int _addr_buf   	    = 0;
	static int _addr_rip_insert = 0;
	static int _addr_rip_procs  = 0;
		
//	static struct rip ripple = {{0},{0}};
	static struct rip ripple;
	static de_symbol de_buf[MAX_EN_SYMBOL_RECV];
//	memset(de_buf, 0, sizeof(de_symbol));

	memset(&_data_tmp, 0, sizeof(de_symbol)); //reset to zero
	pre_treat(ptr_packet, &_data_tmp);
	get_amount(&amount_insym, _data_tmp.d);
	
	assert(amount_insym >= 1);  //check

	if(amount_insym == 1)
	{
		id_symbol = get_id(_data_tmp);
		//******************************
		//for test 
////		printf("input_symbol = %d\n", id_symbol);
		//******************************
		if(NO == judge_repeat_rip(id_symbol, 0, 
		   _addr_rip_insert, ripple.id_rip))
		//should search all ripple set
		{
			//insert id and addr into ripple
////			printf("success of output: d of original = 1");
			insert_rip(id_symbol, _addr_buf, _addr_rip_insert, &ripple);
			_addr_rip_insert++;

			insert_buf(_data_tmp, &de_buf[_addr_buf]); 
			_addr_buf++;   
			//*****************************//
			//***check the final result****//
			strncpy(symbol_recover[id_symbol-1],_data_tmp.data,CODELINE);
			//*****************************//
		}
		//***********************
//		sign_sucs(id_symbol, sign);  //wrong location
		//***********************
	}
	else if(NO == judge_repeat_buf(_addr_buf, _data_tmp, de_buf))
	{		
		insert_buf(_data_tmp, &de_buf[_addr_buf]);
		_addr_buf++;
		
		for(i = 0; i < _addr_rip_insert; i++)
		{
//			if(de_buf[ripple.addr_rip[i]].d > 0 && YES==search_self_neighbor
//				(de_buf[_addr_buf-1], de_buf[ripple.addr_rip[i]]))

			if(de_buf[ripple.addr_rip[i]].d > 0 && YES==search_self_neighbor
			              (de_buf[ripple.addr_rip[i]], de_buf[_addr_buf-1]))
			{
				update_buf(&de_buf[ripple.addr_rip[i]], &de_buf[_addr_buf-1]);
			}
			if(de_buf[_addr_buf-1].d == 1)
			{
				if(NO == judge_repeat_rip(get_id(de_buf[_addr_buf-1]), 0,
				  _addr_rip_insert, ripple.id_rip))
				{
					insert_rip(get_id(de_buf[_addr_buf-1]),_addr_buf-1,
						   _addr_rip_insert,&ripple);
					_addr_rip_insert++;
////            		printf("success of output: d of original_data != 1:abnormal:,hello, world id = %d\n", get_id(de_buf[_addr_buf-1]));
					//*******//
					//check the final result****/
					strncpy(symbol_recover[get_id(de_buf[_addr_buf-1])-1],de_buf[_addr_buf-1].data,CODELINE);
					//******//
					num_procs++;
					break;
				}
			}
		}
	}
	
//	_num_buf_count
//	while(_addr_rip_procs < _addr_rip_insert && num_procs > 0)
	while(_addr_rip_procs < _addr_rip_insert)
	{
	//	memset(sym_from_ripple, 0, sizeof(de_symbol));
		get_sym_from_rip(&sym_from_ripple,
		                &de_buf[ripple.addr_rip[_addr_rip_procs]]);
		assert(sym_from_ripple != NULL);  //check
		_addr_rip_procs++;
//		sign_sucs(id_symbol, sign);


	//*******************************************
//		sign_sucs((get_id(*sym_from_ripple)), sign); 
	//*******************************************


		for(i = 0, num_procs = 0; i < _addr_buf; i++)
		{
			if(de_buf[i].d != 0)
			{
				if(YES==search_self_neighbor(*sym_from_ripple, de_buf[i])) 
				//this encoding_symbol has it as a neighbor
				{
					if(de_buf[i].d != 1)
						update_buf(sym_from_ripple, &de_buf[i]); 
					//operand:exclusive or and update d
				}
				if(de_buf[i].d == 1)
				{
					if(NO == judge_repeat_rip(get_id(de_buf[i]), 0, 
					   _addr_rip_insert, ripple.id_rip)) 
					{
						insert_rip(get_id(de_buf[i]), i, 
								  _addr_rip_insert,&ripple);
						_addr_rip_insert++;
						//****************
						//check the final result
						strncpy(symbol_recover[get_id(de_buf[i])-1],de_buf[i].data,CODELINE);
						//****************
////						printf("success of input: d of orignal_data != 1:normal: this_id of input symbol= %d\n", get_id(de_buf[i]));
						num_procs++;
					//	sign_sucs((get_id(*sym_from_ripple)), sign);
					}
					//attention: judge repeat
				}
			//	sign_sucs((get_id(*sym_from_ripple)), sign);
			}
		}
//		sign_success = success_judge_recvry(sign);

		if(_addr_rip_procs >= _addr_rip_insert && 0 == num_procs)
			break;  //waiting for next packet to recover!!!!!!!
	}
	if(MAX_INPUT_SYMBOL_NUM == _addr_rip_insert)
		return 1;
	else
		return 0;
//	return sign_success;
}
/************************************************/

/**********************/
//test for ptr_treat!!!!!!!!!!!!!
/*
int main()
{
//	de_symbol aa = {10, {'\0'}, {0}};
	int i = 0;

	packet[0] = 10;
	for(i = 2; i < 102; i++)
		packet[i] = 0x0f;
	for(i = 102; i < 302; i++)
		packet[i] = 'a';

	pre_treat(packet, &aa);
//	pre_treat(packet, ptr_desym);	
	return 0;
}
*/
/*************/
#include "construct_method.h"
#include "construct_method.h"
#include "construct_method.h"
