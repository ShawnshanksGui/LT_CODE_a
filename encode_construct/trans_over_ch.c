#include "construct_method.h"

int transmit_over_ch()
{
	double tmp = 0.0;

	tmp = (rand()%100000)/100000.0;
	if(tmp > PACKET_LOSS_RATE)
        return 1;
	else
		return 0;
}
