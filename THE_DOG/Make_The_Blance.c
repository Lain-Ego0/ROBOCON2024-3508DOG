#include "Make_The_Blance.h"

//前翻--Roll 侧翻--Pitch 旋转--Yaw 
//加为逆时钟 负为顺时钟

/*************************************************************************
*  函数名称：The_Doge_Balance
*  功能说明：让DOG平衡
*  参数说明：无 
*  函数返回：无	 
*  备    注：无,P_stHi219m,P_stHi219m_FS
*************************************************************************/

keep_balance the_blance;//前翻--Roll
keep_balance the_blance1;//侧翻--Pitch
void The_Balance_cal(float tic)
{
	static float clu;
	static float tru;
	clu=P_stHi219m_FS.Roll-P_stHi219m.Roll;//前翻--Roll
	tru=0.6f*(P_stHi219m_FS.Pitch-P_stHi219m.Pitch);//侧翻--Pitch
	if(clu>0.1f||clu<-0.1f)
	{
		the_blance.lf1=-clu*tic;
		the_blance.lf2=clu*tic;
		the_blance.Rf3=clu*tic;
		the_blance.Rf4=-clu*tic;
			
		the_blance.lb1=-clu*tic;
		the_blance.lb2=clu*tic;
		the_blance.Rb3=clu*tic;
		the_blance.Rb4=-clu*tic;
	}
	if(tru>0.1f||tru<-0.1f)
	{
		the_blance1.lf1=tru*tic;
		the_blance1.lf2=-tru*tic;
		the_blance1.Rf3=tru*tic;
		the_blance1.Rf4=-tru*tic;
			
		the_blance1.lb1=-tru*tic;
		the_blance1.lb2=tru*tic;
		the_blance1.Rb3=-tru*tic;
		the_blance1.Rb4=tru*tic;
	}
	
}


