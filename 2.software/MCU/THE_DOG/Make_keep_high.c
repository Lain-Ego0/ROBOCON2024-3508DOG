#include "Make_keep_high.h"
//激光雷达高度保持

keep_height the_high_status;
void keep_high(float now_heigh,float target_heigh,float tic)
{
	static float temp;
	temp=target_heigh-now_heigh;

	the_high_status.lf1=temp*tic;
	the_high_status.lf2=-temp*tic*1.0f;
	the_high_status.Rf3=-temp*tic;
	the_high_status.Rf4=temp*tic*1.0f;

	the_high_status.lb1=-temp*tic*1.0f;
	the_high_status.lb2=temp*tic;
	the_high_status.Rb3=temp*tic*1.0f;
	the_high_status.Rb4=-temp*tic;
}
