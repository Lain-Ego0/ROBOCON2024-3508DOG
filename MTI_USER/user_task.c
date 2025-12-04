#include "user_task.h"
#include "imu_data_decode.h"
#include "remote.h"

//信号量
////////////陀螺仪
SemaphoreHandle_t P_shH219DataDecode_Binary;
int P_stHi219m_time=0;//初始平衡设定记录时间
////////////运行逻辑
int tf=0,tb=0,bl=0,br=0;//t-前后，b-左右
int tabu=0;
int Do_anglefb=1,Do_anglelr=1;//计算逻辑
int Do_tabu=0;
int page_timeplus=0;//时序逻辑
////////////高度时间
int uphigh_time=0,downhigh_time=0;
////////////目标值
int target_high=0;//高度目标
int high_elsa=0;
int xt=0,yt=0;
////////////////特殊状态
int if_jump=0;//跳跃

//主控制任务，整车运动参数控制
void Task_Main(void *Parameters)
{
	portTickType CurrentControlTick = 0;//当前系统时间	
	while(1)
	{	

		need_remoto(fnRemote_GetSwitchVal(Left_Switch));
		vTaskDelayUntil(&CurrentControlTick, 1/ portTICK_RATE_MS); //控制任务运行周期  1ms运行一次
	}
}

//计时任务
void Task_TimeCount(void *Parameters)
{
	portTickType CurrentControlTick = 0;//当前系统时间	
	
	while(1)
	{

		vTaskDelayUntil(&CurrentControlTick, 1/ portTICK_RATE_MS); //控制任务运行周期  1ms运行一次
	}
	
}

//陀螺仪数据解析任务
void Task_Hi219mDataDecode(void *Parameters)
{
	BaseType_t stError=pdFALSE;
	uint16_t i = 0;
	uint8_t ch;
	
	while(1)
	{
		if(P_shH219DataDecode_Binary!=NULL)
		{
			stError=xSemaphoreTake(P_shH219DataDecode_Binary,portMAX_DELAY);	//获取信号量
			if(stError==pdTRUE)												//获取信号量成功
			{
				for (i = 0;i < P_uintH219BuffLength;i++)  
				{  
					ch = P_uintH219MDataBuffer[i]; 
					Packet_Decode(ch);
					
					fnHi219m_DataDecode(&P_stHi219m); //获取陀螺仪值
				} 
			}
		}
		else if(stError==pdFALSE)
		{
			vTaskDelay(10);      //延时10ms，也就是10个时钟节拍	
		}
	}
}


//////数值读取
void Task_DataGet(void *Parameters)
{
	portTickType CurrentControlTick = 0;//当前系统时间	
	
	while(1)
	{	
		P_stHi219m_time++;
		///////////////////////////////////////////////////跳变值获取
		Key_Jump_Flag_Get(&P_stRemoteData_Recv,KEYNumber_Q,1);
		Key_Jump_Flag_Get(&P_stRemoteData_Recv,KEYNumber_E,6);
		Key_Jump_Flag_Get(&P_stRemoteData_Recv,KEYNumber_R,1);
		Key_Jump_Flag_Get(&P_stRemoteData_Recv,KEYNumber_F,100);
		Key_Jump_Flag_Get(&P_stRemoteData_Recv,KEYNumber_G,1);
		Key_Jump_Flag_Get(&P_stRemoteData_Recv,KEYNumber_Z,1);
		Key_Jump_Flag_Get(&P_stRemoteData_Recv,KEYNumber_X,2);	
		Key_Jump_Flag_Get(&P_stRemoteData_Recv,KEYNumber_C,1);
		Key_Jump_Flag_Get(&P_stRemoteData_Recv,KEYNumber_B,1);
		Key_Jump_Flag_Get(&P_stRemoteData_Recv,KEYNumber_V,1);
		Key_Jump_Flag_Get(&P_stRemoteData_Recv,KEYNumber_Shift,1);
		Key_Jump_Flag_Get(&P_stRemoteData_Recv,KEYNumber_Ctrl,2);
		Key_Jump_Flag_Get(&P_stRemoteData_Recv,KEYNumber_Switch,100);
		Key_Jump_Flag_Get(&P_stRemoteData_Recv,KEYNumber_MouseLeft,1);
		///////////////////////////////////////////////////初始平衡值获取
		if(P_stHi219m_time<=1500)
		{
			P_stHi219m_FS.Yaw=P_stHi219m.Yaw;
			P_stHi219m_FS.Pitch=P_stHi219m.Pitch;
			P_stHi219m_FS.Roll=P_stHi219m.Roll;
			P_stHi219m_FS.Round=P_stHi219m.Round;
		}
		if(P_stHi219m_time>=1500)
		{
			The_Balance_cal(3.0);////陀螺仪计算Kp
			P_stHi219m_time=2000;
		}	
		keep_high(TF_distance,10.0+target_high+high_elsa,2.0);

		vTaskDelayUntil(&CurrentControlTick, 1/ portTICK_RATE_MS); //控制任务运行周期  1ms运行一次
	}
}

//////////////////键盘控制
void key_contask(void *Parameters)
{
	portTickType CurrentControlTick = 0;//当前系统时间	
	while(1)
	{	
		if(fnRemote_GetSwitchVal(Left_Switch)==2)
		{
			
			Do_anglefb=1;
			Do_anglelr=1;
			Do_tabu=0;
			//回复函数
			
			//一共7套PID参数，越大PID越激进，建议参数3-4左右，以下为调用测试。
			/*
			if(P_stRemoteData_Recv.Flag_Key[7]==0)M3508_ParaInit(&state_kara_speed[0],&state_kara_position[0]);
			else if(P_stRemoteData_Recv.Flag_Key[7]==1)M3508_ParaInit(&state_kara1_speed[0],&state_kara1_position[0]);
			else if(P_stRemoteData_Recv.Flag_Key[7]==2)M3508_ParaInit(&state_kara2_speed[0],&state_kara2_position[0]);
			else if(P_stRemoteData_Recv.Flag_Key[7]==3)M3508_ParaInit(&state_kara3_speed[0],&state_kara3_position[0]);
			else if(P_stRemoteData_Recv.Flag_Key[7]==4)M3508_ParaInit(&state_kara4_speed[0],&state_kara4_position[0]);
			else if(P_stRemoteData_Recv.Flag_Key[7]==5)M3508_ParaInit(&state_kara5_speed[0],&state_kara5_position[0]);
			else if(P_stRemoteData_Recv.Flag_Key[7]==6)M3508_ParaInit(&state_kara6_speed[0],&state_kara6_position[0]);
			*/
			
			/*键盘对应值获取以及运行  现移植回遥控器DJI DT7*/
//			if(P_stRemoteData_Recv.Key.W==1){tf++;if(tf>=60){xgo_page+=1;tf=0;}Do_anglefb=2;}//tlf1--;tlf2++;t=0;}}//go_force();
//			if(P_stRemoteData_Recv.Key.S==1){tb++;if(tb>=75){xback_page+=1;tb=0;}Do_anglefb=3;}//tlf1++;tlf2--;t=0;}}//go_back();
//			if(P_stRemoteData_Recv.Key.A==1){bl++;if(bl>=50){xleft_page+=1;bl=0;}Do_anglelr=2;}//go_left();
//			if(P_stRemoteData_Recv.Key.D==1){br++;if(br>=70){xright_page+=1;br=0;}Do_anglelr=3;}//go_right();
//			if(P_stRemoteData_Recv.Key.Q==1){tabu++;if(tabu>=50){tabu_page+=1;tabu=0;}Do_tabu=1;}
//			if(P_stRemoteData_Recv.Key.E==1){xt++;if(xt>=100){tlf1-=1;xt=0;}}
//	        if(P_stRemoteData_Recv.Key.R==1){target_high=0;}
//			if(P_stRemoteData_Recv.Key.F==1){if_jump=1;}
//			if(P_stRemoteData_Recv.Key.Z==1){downhigh_time++;if(downhigh_time>=25){target_high--;downhigh_time=0;}}
//			if(P_stRemoteData_Recv.Key.X==1){uphigh_time++;if(uphigh_time>=25){target_high++;uphigh_time=1;}}
		
			if(fnRemote_GetSensingVal(LeftSensing_Y)>=600)//go_force();
			{
				M3508_ParaInit(&state_kara4_speed[0],&state_kara4_position[0]);//PID参数
				tf++;
				if(tf>=65)
			    {
					xgo_page+=1;
					tf=0;
				}
				Do_anglefb=2;
			}	
			if(fnRemote_GetSensingVal(LeftSensing_Y)<-600)//go_back();
			{
				M3508_ParaInit(&state_kara3_speed[0],&state_kara3_position[0]);//PID参数
				tb++;
				if(tb>=70)
				{
					xback_page+=1;
					tb=0;
				}
				Do_anglefb=3;
			}				
			if(fnRemote_GetSensingVal(LeftSensing_X)>=500)//go_left();
	        {
				M3508_ParaInit(&state_kara4_speed[0],&state_kara4_position[0]);//PID参数
				bl++;
				if(bl>=60)
				{
					xleft_page+=1;
					bl=0;
				}
				Do_anglelr=2;
			}
			if(fnRemote_GetSensingVal(LeftSensing_X)<-500)//go_right();
			{
				M3508_ParaInit(&state_kara4_speed[0],&state_kara4_position[0]);//PID参数
				br++;
				if(br>=75)
				{
					xright_page+=1;
					br=0;
				}
				Do_anglelr=3;
			}
/****************************************挑战杯用*******************************************/
			// 机械臂前伸
			if (fnRemote_GetSensingVal(RightSensing_Y) >= 600) {
//				tf++;
				TIM_SetCompare1(TIM4, 75);
				TIM_SetCompare2(TIM4, 100);
//				if (tf >= 65) {
//					xgo_page += 1;
//					tf = 0;
//				}
//				Do_anglefb = 2;
			}

			// 机械臂归位
			if (fnRemote_GetSensingVal(RightSensing_Y) < -600) {
//				tb++;
				TIM_SetCompare1(TIM4, 50);
				TIM_SetCompare2(TIM4, 70);
//				if (tb >= 70) {
//					xback_page += 1;
//					tb = 0;
//				}
//				Do_anglefb = 3;
			}

			// 夹爪打开
			if (fnRemote_GetSensingVal(RightSensing_X) >= 500) {
//				bl++;
				TIM_SetCompare3(TIM4, 90);
//				if (bl >= 60) {
//					xleft_page += 1;
//					bl = 0;
//				}
//				Do_anglelr = 2;
			}

			// 夹爪关闭
			if (fnRemote_GetSensingVal(RightSensing_X) < -500) {
//				br++;
				TIM_SetCompare3(TIM4, 130);
//				if (br >= 75) {
//					xright_page += 1;
//					br = 0;
//				}
//				Do_anglelr = 3;
			}                        
/****************************************挑战杯用*********************************************/			
			
			/***********cal_status_angle之前必须要有陀螺仪计算*************/
			
			//主角度控制函数
			cal_status_angle(Do_anglefb,Do_anglelr,Do_tabu);
			if(if_jump==0){The_Moto_Do_angle();}
			else if(if_jump==1){sit_down_with_jump();}
			/**/
	  }
		vTaskDelayUntil(&CurrentControlTick, 1/ portTICK_RATE_MS); //控制任务运行周期  1ms运行一次
	}
}



