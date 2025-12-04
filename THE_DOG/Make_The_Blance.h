#ifndef _MAKE_THE_BALANBCE_H__
#define _MAKE_THE_BALANBCE_H__
#include "M3508.h"
#include "main.h"

typedef struct keep_balance
{
	float lf1;
	float lf2;
	float Rf3;
	float Rf4;
	float lb1;
	float lb2;
	float Rb3;
	float Rb4;
} keep_balance;


void The_Balance_cal(float tic);
extern keep_balance the_blance;
extern keep_balance the_blance1;

#endif
