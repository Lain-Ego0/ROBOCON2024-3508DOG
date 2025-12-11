#ifndef _BASE_POINT_H__
#define _BASE_POINT_H__
#include "M3508.h"
#include "main.h"

typedef struct Moto_do_angle
{
	float lf1;
	float lf2;
	float Rf3;
	float Rf4;
	float lb1;
	float lb2;
	float Rb3;
	float Rb4;
} Moto_do_angle;

extern float sit_status[8];
extern float stand_status[8];

void DOG_kara(void);
void stand_up_withP(void);
void stand_up(void);
void sit_down(void);

void The_Moto_Do_angle(void);
void sit_down_with_jump(void);
extern int stand_up_w;
extern  Moto_do_angle moto_angle;

#endif
