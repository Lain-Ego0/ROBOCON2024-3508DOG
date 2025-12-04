#ifndef _PID_STATES_H__
#define _PID_STATES_H__

#include "main.h"
//void need_remoto(int x,int y,int t,int b);

//typedef struct{		// 腿部PID
//    float kp_spd;		//速度环
//    float kd_spd;
//		int minP;
//	  int maxP;
//} Leg_speed_PID;

//typedef struct{		// 腿部PID
//    float kp_pos;		//位置环
//    float kd_pos;
//		int minP;
//	  int maxP;
//} Leg_position_PID;
typedef struct
{
	int lf1;
	int lf2;
	int Rf3;
	int Rf4;
	int lb1;
	int lb2;
	int Rb3;
	int Rb4;
}get_Target;

extern Leg_speed_PID state_kara_speed[];
extern Leg_position_PID state_kara_position[];
extern Leg_speed_PID state_kara1_speed[];
extern Leg_position_PID state_kara1_position[];
extern Leg_speed_PID state_kara2_speed[];
extern Leg_position_PID state_kara2_position[];
extern Leg_speed_PID state_kara3_speed[];
extern Leg_position_PID state_kara3_position[];
extern Leg_speed_PID state_kara4_speed[];
extern Leg_position_PID state_kara4_position[];
extern Leg_speed_PID state_kara5_speed[];
extern Leg_position_PID state_kara5_position[];
extern Leg_speed_PID state_kara6_speed[];
extern Leg_position_PID state_kara6_position[];
#endif
