#ifndef _Make_keep_high_H__
#define _Make_keep_high_H__

#include "main.h"


typedef struct keep_height
{
	int lf1;
	int lf2;
	int Rf3;
	int Rf4;
	int lb1;
	int lb2;
	int Rb3;
	int Rb4;
} keep_height;

void keep_high(float now_heigh,float target_heigh,float tic);

extern keep_height the_high_status;
#endif

