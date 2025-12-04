#include "M3508.h"

//电机具体配置 初始化电机配置 Can数据解析加入电机位置 对应函数使用
//用户定义电机结构体
//前腿定义在can1,后退定义在can2

//can1
M3508_TypeDef Dog_Leglf1 = {1};//Dog_Leglf1前腿
M3508_TypeDef Dog_Leglf2 = {2};//Dog_Leglf2前腿
M3508_TypeDef Dog_LegRf3 = {3};//Dog_Legrf3前腿
M3508_TypeDef Dog_LegRf4 = {4};//Dog_Legrf4前腿
//can2
M3508_TypeDef Dog_Leglb1 = {1};//Dog_Leglb1前腿
M3508_TypeDef Dog_Leglb2 = {2};//Dog_Leglb2前腿
M3508_TypeDef Dog_LegRb3 = {3};//Dog_Legrb3前腿
M3508_TypeDef Dog_LegRb4 = {4};//Dog_Legrb4前腿


//电机参数初始化
void M3508_ParaInit(Leg_speed_PID speed[],Leg_position_PID position[])
{	
	//Dog_Leg前腿电机配置
	//左前1
	fnPID_SetPara_P_I_D(&Dog_Leglf1.SpeedPID,speed[0].kp_spd ,speed[0].kd_spd );
	fnPID_SetPara_IM(&Dog_Leglf1.SpeedPID,speed[0].minP);
	fnPID_SetPara_OM(&Dog_Leglf1.SpeedPID,speed[0].maxP);
	fnPID_SetPara_P_I_D(&Dog_Leglf1.AnglePID,position[0].kp_pos,position[0].kd_pos);
	fnPID_SetPara_IM(&Dog_Leglf1.AnglePID,position[0].minP);
	fnPID_SetPara_OM(&Dog_Leglf1.AnglePID,position[0].maxP);
	//左前2
	fnPID_SetPara_P_I_D(&Dog_Leglf2.SpeedPID,speed[1].kp_spd ,speed[1].kd_spd);
	fnPID_SetPara_IM(&Dog_Leglf2.SpeedPID,speed[1].minP);
	fnPID_SetPara_OM(&Dog_Leglf2.SpeedPID,speed[1].maxP);
	fnPID_SetPara_P_I_D(&Dog_Leglf2.AnglePID,position[1].kp_pos,position[1].kd_pos);
	fnPID_SetPara_IM(&Dog_Leglf2.AnglePID,position[1].minP );
	fnPID_SetPara_OM(&Dog_Leglf2.AnglePID,position[1].maxP);
	//右前3
	fnPID_SetPara_P_I_D(&Dog_LegRf3.SpeedPID,speed[2].kp_spd ,speed[2].kd_spd);
	fnPID_SetPara_IM(&Dog_LegRf3.SpeedPID,speed[2].minP);
	fnPID_SetPara_OM(&Dog_LegRf3.SpeedPID,speed[2].maxP);
	fnPID_SetPara_P_I_D(&Dog_LegRf3.AnglePID,position[2].kp_pos,position[2].kd_pos);
	fnPID_SetPara_IM(&Dog_LegRf3.AnglePID,position[2].minP);
	fnPID_SetPara_OM(&Dog_LegRf3.AnglePID,position[2].maxP);
	//右前4
	fnPID_SetPara_P_I_D(&Dog_LegRf4.SpeedPID,speed[3].kp_spd ,speed[3].kd_spd);
	fnPID_SetPara_IM(&Dog_LegRf4.SpeedPID,speed[3].minP);
	fnPID_SetPara_OM(&Dog_LegRf4.SpeedPID,speed[3].maxP);
	fnPID_SetPara_P_I_D(&Dog_LegRf4.AnglePID,position[3].kp_pos,position[3].kd_pos);
	fnPID_SetPara_IM(&Dog_LegRf4.AnglePID,position[3].minP);
	fnPID_SetPara_OM(&Dog_LegRf4.AnglePID,position[3].maxP);
	
	//Dog_Leg后腿电机配置
	//左后1
	fnPID_SetPara_P_I_D(&Dog_Leglb1.SpeedPID,speed[4].kp_spd ,speed[4].kd_spd);
	fnPID_SetPara_IM(&Dog_Leglb1.SpeedPID,speed[4].minP);
	fnPID_SetPara_OM(&Dog_Leglb1.SpeedPID,speed[4].maxP);
	fnPID_SetPara_P_I_D(&Dog_Leglb1.AnglePID,position[4].kp_pos,position[4].kd_pos);
	fnPID_SetPara_IM(&Dog_Leglb1.AnglePID,position[4].minP);
	fnPID_SetPara_OM(&Dog_Leglb1.AnglePID,position[4].maxP);
	//左后2
	fnPID_SetPara_P_I_D(&Dog_Leglb2.SpeedPID,speed[5].kp_spd ,speed[5].kd_spd);
	fnPID_SetPara_IM(&Dog_Leglb2.SpeedPID,speed[5].minP);
	fnPID_SetPara_OM(&Dog_Leglb2.SpeedPID,speed[5].maxP);
	fnPID_SetPara_P_I_D(&Dog_Leglb2.AnglePID,position[5].kp_pos,position[5].kd_pos);
	fnPID_SetPara_IM(&Dog_Leglb2.AnglePID,position[5].minP);
	fnPID_SetPara_OM(&Dog_Leglb2.AnglePID,position[5].maxP);
	//右后3
	fnPID_SetPara_P_I_D(&Dog_LegRb3.SpeedPID,speed[6].kp_spd ,speed[6].kd_spd);
	fnPID_SetPara_IM(&Dog_LegRb3.SpeedPID,speed[6].minP);
	fnPID_SetPara_OM(&Dog_LegRb3.SpeedPID,speed[6].maxP);
	fnPID_SetPara_P_I_D(&Dog_LegRb3.AnglePID,position[6].kp_pos,position[6].kd_pos);
	fnPID_SetPara_IM(&Dog_LegRb3.AnglePID,position[6].minP);
	fnPID_SetPara_OM(&Dog_LegRb3.AnglePID,position[6].maxP);
	//右后4
	fnPID_SetPara_P_I_D(&Dog_LegRb4.SpeedPID,speed[7].kp_spd ,speed[7].kd_spd);
	fnPID_SetPara_IM(&Dog_LegRb4.SpeedPID,speed[7].minP);
	fnPID_SetPara_OM(&Dog_LegRb4.SpeedPID,speed[7].maxP);
	fnPID_SetPara_P_I_D(&Dog_LegRb4.AnglePID,position[7].kp_pos,position[7].kd_pos);
	fnPID_SetPara_IM(&Dog_LegRb4.AnglePID,position[7].minP);
	fnPID_SetPara_OM(&Dog_LegRb4.AnglePID,position[7].maxP);

}


//Can数据解析
void fnMotor_CanRecvDataDecode(CAN_TypeDef* canx,CanRxMsg * msg)
{
	if(canx == CAN1)
	{
		//根据对应ID,进行数据解析
		switch(msg->StdId)
		{
			case DOG_LEGLF_1_ID:
			{
				s_fnM3508_RawDataDecode(&Dog_Leglf1,msg);//原始数据解析
			}break;
			
			case DOG_LEGLF_2_ID:
			{
				s_fnM3508_RawDataDecode(&Dog_Leglf2,msg);//原始数据解析
			}break;
			
			case DOG_LEGRF_3_ID:
			{
				s_fnM3508_RawDataDecode(&Dog_LegRf3,msg);//原始数据解析
			}break;
			
			case DOG_LEGRF_4_ID:
			{
				s_fnM3508_RawDataDecode(&Dog_LegRf4,msg);//原始数据解析
			}break;
			default:{}break;
		  }
	}
	else if(canx == CAN2)
	{
		//根据对应ID,进行数据解析
		switch(msg->StdId)
		{
			case DOG_LEGLB_1_ID:
			{
				s_fnM3508_RawDataDecode(&Dog_Leglb1,msg);//原始数据解析
			}break;

			case DOG_LEGLB_2_ID:
			{
				s_fnM3508_RawDataDecode(&Dog_Leglb2,msg);//原始数据解析
			}break;

			case DOG_LEGRB_3_ID:
			{
				s_fnM3508_RawDataDecode(&Dog_LegRb3,msg);//原始数据解析
			}break;

			case DOG_LEGRB_4_ID:
			{
				s_fnM3508_RawDataDecode(&Dog_LegRb4,msg);//原始数据解析
			}break;
		default:{}break;
		}
	}
	
}

//电机控制函数 ************************************************************

//电机速度控制函数 ************
void USE_CAN1_SpeedCotrol_M3508( M3508_TypeDef* st_data,float target_speed)
{
	float ctrl_val;
	
	fnPID_SetTarget(&st_data->SpeedPID,target_speed);//设置目标
	fnPID_SetFeedback(&st_data->SpeedPID,st_data->RecvData.Rotate_FliterSpeed);//获取反馈值;
	fnPID_Calc(&st_data->SpeedPID);//PID计算
	
	ctrl_val = fnPID_GetOutput(&st_data->SpeedPID);//获取控制量
	
	Control_SetCurrentVal(CAN1,st_data->CAN_ID,ctrl_val);//控制执行电机
}


void USE_CAN2_SpeedCotrol_M3508( M3508_TypeDef* st_data,float target_speed)
{
	float ctrl_val;
	
	fnPID_SetTarget(&st_data->SpeedPID,target_speed);//设置目标
	fnPID_SetFeedback(&st_data->SpeedPID,st_data->RecvData.Rotate_FliterSpeed);//获取反馈值;
	fnPID_Calc(&st_data->SpeedPID);//PID计算
	
	ctrl_val = fnPID_GetOutput(&st_data->SpeedPID);//获取控制量
	
	Control_SetCurrentVal(CAN2,st_data->CAN_ID,ctrl_val);//控制执行电机
}

//电机角度控制函数 ************************************************************3508电机角度控制函数 双环PID控制
/////////////////////////角度环前环 ******
void USE_CAN1_ArmMotorCotrol_M3508( M3508_TypeDef* st_data,float target_speed)
{
	float ctrl_val;
	
	fnPID_SetTarget(&st_data->SpeedPID,target_speed);//设置目标
	fnPID_SetFeedback(&st_data->SpeedPID,st_data->RecvData.Rotate_FliterSpeed);//获取反馈值;
	fnPID_Calc(&st_data->SpeedPID);//PID计算
	
	ctrl_val = fnPID_GetOutput(&st_data->SpeedPID);//获取控制量 
	
	Control_SetCurrentVal(CAN1,st_data->CAN_ID,ctrl_val);//控制执行电机
}

void USE_CAN2_ArmMotorCotrol_M3508( M3508_TypeDef* st_data,float target_speed)
{
	float ctrl_val;
	
	fnPID_SetTarget(&st_data->SpeedPID,target_speed);//设置目标
	fnPID_SetFeedback(&st_data->SpeedPID,st_data->RecvData.Rotate_FliterSpeed);//获取反馈值;
	fnPID_Calc(&st_data->SpeedPID);//PID计算
	
	ctrl_val = fnPID_GetOutput(&st_data->SpeedPID);//获取控制量 
	
	Control_SetCurrentVal(CAN2,st_data->CAN_ID,ctrl_val);//控制执行电机
}

/////////////////////////角度后环 ******

void USE_CAN1_AngleCotrol_M3508( M3508_TypeDef* st_data,float target_angle)
{
	float pid_output;
	
	fnPID_SetTarget(&st_data->AnglePID,target_angle);//设置角度环目标值
	fnPID_SetFeedback(&st_data->AnglePID,st_data->RecvData.Shaft_Angle);//获取角度反馈
	fnPID_Calc(&st_data->AnglePID);//计算PID输出
	
	pid_output = fnPID_GetOutput(&st_data->AnglePID);//获取角度环输出
	
	USE_CAN1_ArmMotorCotrol_M3508(st_data,pid_output);//将角度环输出作为速度环目标值
}
void USE_CAN2_AngleCotrol_M3508( M3508_TypeDef* st_data,float target_angle)
{
	float pid_output;
	
	fnPID_SetTarget(&st_data->AnglePID,target_angle);//设置角度环目标值
	fnPID_SetFeedback(&st_data->AnglePID,st_data->RecvData.Shaft_Angle);//获取角度反馈
	fnPID_Calc(&st_data->AnglePID);//计算PID输出
	
	pid_output = fnPID_GetOutput(&st_data->AnglePID);//获取角度环输出
	
	USE_CAN2_ArmMotorCotrol_M3508(st_data,pid_output);//将角度环输出作为速度环目标值
}

/////////////////////////////////////////以上为主要配置
//**************************************************************************************
/////////////////////////////////////////以下为主要配置

//电机电调设置控制电流值--直接控制电流,电流会直接提供力,会直接提供加速度
void Control_SetCurrentVal(CAN_TypeDef *CANx,uint8_t motor_id,int16_t cm_i)//输出电流值,并发送
{ 
	static CanSend_Type MotorSendData1_4;
	static CanSend_Type MotorSendData5_8;
	static CanSend_Type MotorSendData1_4_CAN2;
	static CanSend_Type MotorSendData5_8_CAN2;
	
	//若ID为1-4之间则使用标识符0x200，id为5-8之间时使用标识符0x1ff
	
	if (CANx==CAN1)
	{
		MotorSendData1_4.CANx = 1;
		MotorSendData5_8.CANx = 1;
		MotorSendData1_4.SendCanTxMsg.StdId = MOTOR_CANSEND_IDENTIFIER1_4;
		MotorSendData1_4.SendCanTxMsg.DLC = 8;
		MotorSendData1_4.SendCanTxMsg.IDE = CAN_ID_STD;
		MotorSendData1_4.SendCanTxMsg.RTR = CAN_RTR_Data;
		
		MotorSendData5_8.SendCanTxMsg.StdId = MOTOR_CANSEND_IDENTIFIER5_8;
		MotorSendData5_8.SendCanTxMsg.DLC = 8;
		MotorSendData5_8.SendCanTxMsg.IDE = CAN_ID_STD;
		MotorSendData5_8.SendCanTxMsg.RTR = CAN_RTR_Data;
		
		switch(motor_id)
		{
			case 1:
			{
				MotorSendData1_4.SendCanTxMsg.Data[0] = (uint8_t)(cm_i >> 8);
				MotorSendData1_4.SendCanTxMsg.Data[1] = (uint8_t)cm_i;
			}break;
			
			case 2:
			{
				MotorSendData1_4.SendCanTxMsg.Data[2] = (uint8_t)(cm_i >> 8);
				MotorSendData1_4.SendCanTxMsg.Data[3] = (uint8_t)cm_i;
			}break;
			
			case 3:
			{
				MotorSendData1_4.SendCanTxMsg.Data[4] = (uint8_t)(cm_i >> 8);
				MotorSendData1_4.SendCanTxMsg.Data[5] = (uint8_t)cm_i;
			}break;
			
			case 4:
			{
				MotorSendData1_4.SendCanTxMsg.Data[6] = (uint8_t)(cm_i >> 8);
				MotorSendData1_4.SendCanTxMsg.Data[7] = (uint8_t)cm_i;
			}break;
			
			case 5:
			{
				MotorSendData5_8.SendCanTxMsg.Data[0] = (uint8_t)(cm_i >> 8);
				MotorSendData5_8.SendCanTxMsg.Data[1] = (uint8_t)cm_i;
			}break;
			
			case 6:
			{
				MotorSendData5_8.SendCanTxMsg.Data[2] = (uint8_t)(cm_i >> 8);
				MotorSendData5_8.SendCanTxMsg.Data[3] = (uint8_t)cm_i;
			}break;
			
			case 7:
			{
				MotorSendData5_8.SendCanTxMsg.Data[4] = (uint8_t)(cm_i >> 8);
				MotorSendData5_8.SendCanTxMsg.Data[5] = (uint8_t)cm_i;
			}break;
			
			case 8:
			{
				MotorSendData5_8.SendCanTxMsg.Data[6] = (uint8_t)(cm_i >> 8);
				MotorSendData5_8.SendCanTxMsg.Data[7] = (uint8_t)cm_i;
			}break;
				
		}

		//数据发送
		s_fnMotor_CANSend(CANx,(CanTxMsg* )&(MotorSendData1_4.SendCanTxMsg));
		s_fnMotor_CANSend(CANx,(CanTxMsg* )&(MotorSendData5_8.SendCanTxMsg));	
	}
	
	//为can2
		
	else
	{
		MotorSendData1_4_CAN2.CANx = 2;
		MotorSendData5_8_CAN2.CANx = 2;
		MotorSendData1_4_CAN2.SendCanTxMsg.StdId = MOTOR_CANSEND_IDENTIFIER1_4;
		MotorSendData1_4_CAN2.SendCanTxMsg.DLC = 8;
		MotorSendData1_4_CAN2.SendCanTxMsg.IDE = CAN_ID_STD;
		MotorSendData1_4_CAN2.SendCanTxMsg.RTR = CAN_RTR_Data;
		
		MotorSendData5_8_CAN2.SendCanTxMsg.StdId = MOTOR_CANSEND_IDENTIFIER5_8;
		MotorSendData5_8_CAN2.SendCanTxMsg.DLC = 8;
		MotorSendData5_8_CAN2.SendCanTxMsg.IDE = CAN_ID_STD;
		MotorSendData5_8_CAN2.SendCanTxMsg.RTR = CAN_RTR_Data;
		

		
		switch(motor_id)
		{
			case 1:{
				MotorSendData1_4_CAN2.SendCanTxMsg.Data[0] = (uint8_t)(cm_i >> 8);
				MotorSendData1_4_CAN2.SendCanTxMsg.Data[1] = (uint8_t)cm_i;
			}break;
			
			case 2:{
				MotorSendData1_4_CAN2.SendCanTxMsg.Data[2] = (uint8_t)(cm_i >> 8);
				MotorSendData1_4_CAN2.SendCanTxMsg.Data[3] = (uint8_t)cm_i;
			}break;
			
			case 3:{
				MotorSendData1_4_CAN2.SendCanTxMsg.Data[4] = (uint8_t)(cm_i >> 8);
				MotorSendData1_4_CAN2.SendCanTxMsg.Data[5] = (uint8_t)cm_i;
			}break;
			
			case 4:{
				MotorSendData1_4_CAN2.SendCanTxMsg.Data[6] = (uint8_t)(cm_i >> 8);
				MotorSendData1_4_CAN2.SendCanTxMsg.Data[7] = (uint8_t)cm_i;
			}break;
			
			case 5:{
				MotorSendData5_8_CAN2.SendCanTxMsg.Data[0] = (uint8_t)(cm_i >> 8);
				MotorSendData5_8_CAN2.SendCanTxMsg.Data[1] = (uint8_t)cm_i;
			}break;
			
			case 6:{
				MotorSendData5_8_CAN2.SendCanTxMsg.Data[2] = (uint8_t)(cm_i >> 8);
				MotorSendData5_8_CAN2.SendCanTxMsg.Data[3] = (uint8_t)cm_i;
			}break;
			
			case 7:{
				MotorSendData5_8_CAN2.SendCanTxMsg.Data[4] = (uint8_t)(cm_i >> 8);
				MotorSendData5_8_CAN2.SendCanTxMsg.Data[5] = (uint8_t)cm_i;
			}break;
			
			case 8:{
				MotorSendData5_8_CAN2.SendCanTxMsg.Data[6] = (uint8_t)(cm_i >> 8);
				MotorSendData5_8_CAN2.SendCanTxMsg.Data[7] = (uint8_t)cm_i;
			}break;
				
		}

		//数据发送
		s_fnMotor_CANSend(CANx,(CanTxMsg* )&(MotorSendData1_4_CAN2.SendCanTxMsg));
		s_fnMotor_CANSend(CANx,(CanTxMsg* )&(MotorSendData5_8_CAN2.SendCanTxMsg));	
	}
}

//3508电机原始数据解析函数
static void s_fnM3508_RawDataDecode(M3508_TypeDef* st_data,CanRxMsg * msg)
{
	uint8_t i;
	int32_t temp_sum = 0;
	int16_t diff_val = 0;
	
	st_data->RecvData.Encoder_Val = (int16_t)((msg->Data[0]<<8)|(msg->Data[1]));//编码器值
	st_data->RecvData.Rotate_Speed = (int16_t)((msg->Data[2]<<8)|(msg->Data[3]));//电机反馈速度
	st_data->RecvData.Armature_Current = (int16_t)((msg->Data[4]<<8)|(msg->Data[5]));//电机反馈电流
	st_data->RecvData.Motor_Temperature = (int8_t)(msg->Data[6]);//电机温度

		//角度连续化处理	
	diff_val = st_data->RecvData.Encoder_Val - st_data->RecvData.Last_Encoder_Val;//获取前后两次编码器角度差值
	
	st_data->RecvData.Last_Encoder_Val = st_data->RecvData.Encoder_Val;//获取差值后记录上一次编码器值
	//记录旋转圈数
	if(diff_val < -4000)
	{
		st_data->RecvData.Number_Of_Turns ++;
	}
	else if(diff_val > 4000)
	{
		st_data->RecvData.Number_Of_Turns --;
	}
	//获取连续化处理后的转子角度
	st_data->RecvData.Rotate_Angle = st_data->RecvData.Number_Of_Turns * 360.f + st_data->RecvData.Encoder_Val/8192.f * 360.f;
	//转子角度除以电机减速比，就是电机轴转过的角度
	st_data->RecvData.Shaft_Angle = st_data->RecvData.Rotate_Angle/MOTOR_3508_REDUCTIONRATE;

	//电机速度滤波
	st_data->RecvData.Rotate_SpeedBuf[st_data->RecvData.Rotate_BufCount ++] = st_data->RecvData.Rotate_Speed;
	
	if(st_data->RecvData.Rotate_BufCount == ROTATE_SPEEDBUF_LEN)
	{
		st_data->RecvData.Rotate_BufCount = 0;
	}
	
	for(i = 0;i < ROTATE_SPEEDBUF_LEN; i++)
	{
		temp_sum +=	st_data->RecvData.Rotate_SpeedBuf[i];
	}
	st_data->RecvData.Rotate_FliterSpeed = (int32_t)(temp_sum/ROTATE_SPEEDBUF_LEN);

}


//底层CAN发送函数
static void s_fnMotor_CANSend(CAN_TypeDef *CANx, CanTxMsg *stMotorSendData)
{
	uint16_t i=0;
	u8 nMailBox=0;
	nMailBox=CAN_Transmit(CANx, stMotorSendData);
	while((CAN_TransmitStatus(CANx,nMailBox)==CAN_TxStatus_Failed)&&(i<0XFFF))
	{
		i++;	//等待发送结束
	}
}


