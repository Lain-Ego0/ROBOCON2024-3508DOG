#include "BASE_POINT.h"
/*************************************************************************

*************************************************************************/
/////////数据库
int stand_up_w=0;
int stand_up_w_db=0;
int stand_up_w_cb=0;
int sit_timer=0;
Moto_do_angle moto_angle;
/*************调参位置*************/
float stand_status[8]={-10,-170,10,170,-150,-5,145,15};
float sit_status[8]={-155,-105,155,105,-40,-155,40,155};
float sit_status_with_jump[8]={-18,93,18,-93,83,-18,-83,18};
float sit_status_with_down[8]={-155,-105,155,105,-40,-155,40,155};


/*************************************************************************
*  函数名称：DOG_kara
*  功能说明：刚开始让DOG电机初驱动，以及掉电后
*  参数说明：无 
*  函数返回：无	 
*  备    注：无
*************************************************************************/
void DOG_kara(void)
{
	Control_SetCurrentVal(CAN1,2,0);
	Control_SetCurrentVal(CAN1,1,0);	 
	Control_SetCurrentVal(CAN1,3,0);
	Control_SetCurrentVal(CAN1,4,0);
	Control_SetCurrentVal(CAN2,2,0);
	Control_SetCurrentVal(CAN2,1,0);
	Control_SetCurrentVal(CAN2,3,0);
	Control_SetCurrentVal(CAN2,4,0);
}
/*************************************************************************
*  函数名称：The_Moto_Do_angle
*  功能说明：让电机转角度(计算完后控制）
*  参数说明：无 
*  函数返回：无	 
*  备    注：测试函数以后封入各个功能
*************************************************************************/
void The_Moto_Do_angle(void)
{
  
	USE_CAN1_AngleCotrol_M3508(&Dog_Leglf1,moto_angle.lf1+stand_status[0]);
	USE_CAN1_AngleCotrol_M3508(&Dog_Leglf2,moto_angle.lf2+stand_status[1]);	
	USE_CAN1_AngleCotrol_M3508(&Dog_LegRf3,moto_angle.Rf3+stand_status[2]);
	USE_CAN1_AngleCotrol_M3508(&Dog_LegRf4,moto_angle.Rf4+stand_status[3]);
	
	USE_CAN2_AngleCotrol_M3508(&Dog_Leglb1,moto_angle.lb1+stand_status[4]);
	USE_CAN2_AngleCotrol_M3508(&Dog_Leglb2,moto_angle.lb2+stand_status[5]);
	USE_CAN2_AngleCotrol_M3508(&Dog_LegRb3,moto_angle.Rb3+stand_status[6]);
	USE_CAN2_AngleCotrol_M3508(&Dog_LegRb4,moto_angle.Rb4+stand_status[7]);
 }

 
/*************************************************************************
*  函数名称：stand_up_with_power
*  功能说明：让DOG站立
*  参数说明：无 
*  函数返回：无	 
*  备    注：无
*************************************************************************/
void stand_up_withP(void)
{
	if(stand_up_w<300) //站起给力(力控起立)
	{
		stand_up_w_db=-3000;stand_up_w++;stand_up_w_cb=5000;
		Control_SetCurrentVal(CAN1,1,-stand_up_w_cb);	
		Control_SetCurrentVal(CAN1,2,stand_up_w_db); 
		Control_SetCurrentVal(CAN1,3,stand_up_w_cb);
		Control_SetCurrentVal(CAN1,4,-stand_up_w_db);
					
		Control_SetCurrentVal(CAN2,1,stand_up_w_db);
		Control_SetCurrentVal(CAN2,2,-stand_up_w_cb);
		Control_SetCurrentVal(CAN2,3,-stand_up_w_db);
		Control_SetCurrentVal(CAN2,4,stand_up_w_cb);
	}
	else if(stand_up_w>=300&&stand_up_w<=2000)/////////蹲状态
	{
		stand_up_w++;
		USE_CAN1_AngleCotrol_M3508(&Dog_Leglf1,sit_status[0]);
		USE_CAN1_AngleCotrol_M3508(&Dog_Leglf2,sit_status[1]);	
		USE_CAN1_AngleCotrol_M3508(&Dog_LegRf3,sit_status[2]);
		USE_CAN1_AngleCotrol_M3508(&Dog_LegRf4,sit_status[3]);

		USE_CAN2_AngleCotrol_M3508(&Dog_Leglb1,sit_status[4]);
		USE_CAN2_AngleCotrol_M3508(&Dog_Leglb2,sit_status[5]);
		USE_CAN2_AngleCotrol_M3508(&Dog_LegRb3,sit_status[6]);
		USE_CAN2_AngleCotrol_M3508(&Dog_LegRb4,sit_status[7]);	
	}
	else if(stand_up_w>2000)////////////////////////////起立
	{
		USE_CAN1_AngleCotrol_M3508(&Dog_Leglf1,stand_status[0]);
		USE_CAN1_AngleCotrol_M3508(&Dog_Leglf2,stand_status[1]);	
		USE_CAN1_AngleCotrol_M3508(&Dog_LegRf3,stand_status[2]);
		USE_CAN1_AngleCotrol_M3508(&Dog_LegRf4,stand_status[3]);

		USE_CAN2_AngleCotrol_M3508(&Dog_Leglb1,stand_status[4]);
		USE_CAN2_AngleCotrol_M3508(&Dog_Leglb2,stand_status[5]);
		USE_CAN2_AngleCotrol_M3508(&Dog_LegRb3,stand_status[6]);
		USE_CAN2_AngleCotrol_M3508(&Dog_LegRb4,stand_status[7]);	
	}
}
/*************************************************************************
*  函数名称：stand_up_with_power
*  功能说明：让DOG站立
*  参数说明：无 
*  函数返回：无	 
*  备    注：无
*************************************************************************/
void stand_up(void)
{
	USE_CAN1_AngleCotrol_M3508(&Dog_Leglf1,stand_status[0]);
	USE_CAN1_AngleCotrol_M3508(&Dog_Leglf2,stand_status[1]);	
	USE_CAN1_AngleCotrol_M3508(&Dog_LegRf3,stand_status[2]);
	USE_CAN1_AngleCotrol_M3508(&Dog_LegRf4,stand_status[3]);

	USE_CAN2_AngleCotrol_M3508(&Dog_Leglb1,stand_status[4]);
	USE_CAN2_AngleCotrol_M3508(&Dog_Leglb2,stand_status[5]);
	USE_CAN2_AngleCotrol_M3508(&Dog_LegRb3,stand_status[6]);
	USE_CAN2_AngleCotrol_M3508(&Dog_LegRb4,stand_status[7]);		
}

/*************************************************************************
*  函数名称：sit_down
*  功能说明：让DOG坐下
*  参数说明：无 
*  函数返回：无	 
*  备    注：无
*************************************************************************/
void sit_down(void)
{
	USE_CAN1_AngleCotrol_M3508(&Dog_Leglf1,sit_status[0]);
	USE_CAN1_AngleCotrol_M3508(&Dog_Leglf2,sit_status[1]);	
	USE_CAN1_AngleCotrol_M3508(&Dog_LegRf3,sit_status[2]);
	USE_CAN1_AngleCotrol_M3508(&Dog_LegRf4,sit_status[3]);
	
	USE_CAN2_AngleCotrol_M3508(&Dog_Leglb1,sit_status[4]);
	USE_CAN2_AngleCotrol_M3508(&Dog_Leglb2,sit_status[5]);
	USE_CAN2_AngleCotrol_M3508(&Dog_LegRb3,sit_status[6]);
	USE_CAN2_AngleCotrol_M3508(&Dog_LegRb4,sit_status[7]);	
}

/*************************************************************************
*  函数名称：sit_down
*  功能说明：让DOG坐下
*  参数说明：无 
*  函数返回：无	 
*  备    注：无
*************************************************************************/
void sit_down_with_jump(void)
{
	sit_timer++;
	if(sit_timer>=2000){if_jump=0;sit_timer=0;}
	USE_CAN1_AngleCotrol_M3508(&Dog_Leglf1,sit_status_with_jump[0]+stand_status[0]);
	USE_CAN1_AngleCotrol_M3508(&Dog_Leglf2,sit_status_with_jump[1]+stand_status[1]);	
	USE_CAN1_AngleCotrol_M3508(&Dog_LegRf3,sit_status_with_jump[2]+stand_status[2]);
	USE_CAN1_AngleCotrol_M3508(&Dog_LegRf4,sit_status_with_jump[3]+stand_status[3]);
	
	USE_CAN2_AngleCotrol_M3508(&Dog_Leglb1,sit_status_with_jump[4]+stand_status[4]);
	USE_CAN2_AngleCotrol_M3508(&Dog_Leglb2,sit_status_with_jump[5]+stand_status[5]);
	USE_CAN2_AngleCotrol_M3508(&Dog_LegRb3,sit_status_with_jump[6]+stand_status[6]);
	USE_CAN2_AngleCotrol_M3508(&Dog_LegRb4,sit_status_with_jump[7]+stand_status[7]);	
}

/*************************************************************************
*  函数名称：jump_up
*  功能说明：让DOG起跳
*  参数说明：无 
*  函数返回：无	 
*  备    注：无
*************************************************************************/
void jump_up(void)
{
	int jump_waits=0;
	if(jump_waits<=1200)
	{
		sit_down_with_jump();
	}
}




