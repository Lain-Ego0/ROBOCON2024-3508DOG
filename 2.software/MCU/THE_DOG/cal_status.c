#include "cal_status.h"

/*************************************************************************
*  函数名称：数据
*  功能说明：数据和函数提前
*  参数说明：无 
*  函数返回：无	 
*  备    注：无
*************************************************************************/
int Frame_time=0;
float Frame_page=2;

//踏步
float Ttabu1[8]={0,26,42,-18,-99,-106,-49,-2};
float Ttabu2[8]={0,39,52,93,111,30,-8,-17};
float Ttabu3[8]={100,8,-16,36,0,26,54,115};
float Ttabu4[8]={-100,-90,-49,-5,0,46,31,-19};

float Ttabu5[8]={100,8,-16,36,0,26,54,115};
float Ttabu6[8]={-100,-90,-49,-5,0,46,31,-19};
float Ttabu7[8]={0,26,42,-18,-99,-106,-49,-2};
float Ttabu8[8]={0,39,52,93,111,30,-8,-17};

//前进
float go_force1[8]={0,26,42,-18,-99,-106,-49,-2};
float go_force2[8]={0,39,52,93,111,30,-8,-17};
float go_force3[8]={99,106,49,2,0,-26,-42,18};
float go_force4[8]={-111,-30,8,17,0,-39,-52,-93};

float go_force5[8]={111,30,-8,-17,0,39,52,83};
float go_force6[8]={-99,-106,-49,-2,0,26,42,-18};
float go_force7[8]={0,-39,-52,-83,-111,-30,8,17};
float go_force8[8]={0,-26,-42,18,99,106,49,2};

//后退
float go_back1[8]={0,-2,-49,-106,-99,-18,42,26};
float go_back2[8]={0,-17,-8,30,111,93,52,39};
float go_back3[8]={99,18,-42,-26,0,2,49,106};
float go_back4[8]={-111,-93,-52,-39,0,17,8,-30};

float go_back5[8]={111,83,52,39,0,-17,-8,30};
float go_back6[8]={-99,-18,42,26,0,-2,-49,-106};
float go_back7[8]={0,17,8,-30,-111,-83,-52,-39};
float go_back8[8]={0,2,49,106,99,18,-42,-26};

//左转
float go_left1[8]={0,-40,-80,-129,-142,-44,-16,14};
float go_left2[8]={0,-28,-25,11,111,100,52,26};
float go_left3[8]={73,77,39,5,0,-46,-31,19};
float go_left4[8]={-101,-8,18,37,0,-26,-55,-121};

float go_left5[8]={73,77,39,5,0,-46,-31,19};
float go_left6[8]={-101,-8,18,37,0,-26,-55,-121};
float go_left7[8]={0,-40,-80,-129,-142,-44,-16,14};
float go_left8[8]={0,-28,-25,11,111,100,52,26};

//右转
float go_right1[8]={0,26,42,-18,-99,-106,-49,-2};
float go_right2[8]={0,39,52,93,111,30,-8,-17};
float go_right3[8]={100,8,-16,36,0,26,54,115};
float go_right4[8]={-100,-90,-49,-5,0,46,31,-19};

float go_right5[8]={100,8,-16,36,0,26,54,115};
float go_right6[8]={-100,-90,-49,-5,0,46,31,-19};
float go_right7[8]={0,26,42,-18,-99,-106,-49,-2};
float go_right8[8]={0,39,52,93,111,30,-8,-17};

int tabu_page=3;
int xgo_page=3;
int xback_page=3;
int xleft_page=3;
int xright_page=3;


//int pint_Rf3[15]={};
//int pint_Rf4[15]={};

//int pint_lb1[15]={};
//int pint_lb2[15]={};
//int pint_Rb3[15]={};
//int pint_Rb4[15]={};

//static int tlf1_temp,tlf2_temp;
//static int tRf3_temp,tRf4_temp;
//static int tlb1_temp,tlb2_temp;
//static int tRb3_temp,tRb4_temp;


float tlf1=0,tlf2=0;
float tRf3=0,tRf4=0;
float tlb1=0,tlb2=0;
float tRb3=0,tRb4=0;

void Supplementary_Frame(void);
void Supplementary_Framecal(float rate_ball,int now_angle,int target_angle,int temp_num);
/*************************************************************************
*  函数名称：cal_status_angle
*  功能说明：总计算最后导入角度的数据
*  参数说明：无 
*  函数返回：无	 
*  备    注：无
*************************************************************************/
void cal_status_angle(int x_time,int y_time,int Do_tabu)
{ 
	
	if(x_time==1&&y_time==1&&Do_tabu==0)//平衡站立
	{
		//M3508_ParaInit(&state_kara_speed[0],&state_kara_position[0]);
		high_elsa=0;
		moto_angle.lf1=the_blance.lf1+the_blance1.lf1+the_high_status.lf1;
		moto_angle.lf2=the_blance.lf2+the_blance1.lf2+the_high_status.lf2;
		moto_angle.Rf3=the_blance.Rf3+the_blance1.Rf3+the_high_status.Rf3;
		moto_angle.Rf4=the_blance.Rf4+the_blance1.Rf4+the_high_status.Rf4;

		moto_angle.lb1=the_blance.lb1+the_blance1.lb1+the_high_status.lb1;//yt;
		moto_angle.lb2=the_blance.lb2+the_blance1.lb2+the_high_status.lb2;//xt;
		moto_angle.Rb3=the_blance.Rb3+the_blance1.Rb3+the_high_status.Rb3;
		moto_angle.Rb4=the_blance.Rb4+the_blance1.Rb4+the_high_status.Rb4;
	}
	else if(x_time==1&&y_time==1&&Do_tabu==1)//踏步
	{
		high_elsa=5;
		if(tabu_page>7){tabu_page=0;}
		if(tabu_page<0){tabu_page=7;}
		moto_angle.lf1=the_blance.lf1+the_blance1.lf1+the_high_status.lf1+0.9f*Ttabu1[tabu_page];
		moto_angle.lf2=the_blance.lf2+the_blance1.lf2+the_high_status.lf2+Ttabu2[tabu_page];
		moto_angle.Rf3=the_blance.Rf3+the_blance1.Rf3+the_high_status.Rf3+Ttabu3[tabu_page];//+xt
		moto_angle.Rf4=the_blance.Rf4+the_blance1.Rf4+the_high_status.Rf4+Ttabu4[tabu_page];//+yt

		moto_angle.lb1=the_blance.lb1+the_blance1.lb1+the_high_status.lb1+Ttabu5[tabu_page];
		moto_angle.lb2=the_blance.lb2+the_blance1.lb2+the_high_status.lb2+Ttabu6[tabu_page];
		moto_angle.Rb3=the_blance.Rb3+the_blance1.Rb3+the_high_status.Rb3+Ttabu7[tabu_page];
		moto_angle.Rb4=the_blance.Rb4+the_blance1.Rb4+the_high_status.Rb4+Ttabu8[tabu_page];
	}
	else if(x_time==2&&y_time==1&&Do_tabu==0)//前进
	{
		//Supplementary_Frame();
		//M3508_ParaInit(&state_kara_speed[1],&state_kara_position[1]);
		if(xgo_page>7){xgo_page=0;}
		if(xgo_page<0){xgo_page=7;}
		high_elsa=-8;
		moto_angle.lf1=the_blance.lf1+the_blance1.lf1+the_high_status.lf1+go_force1[xgo_page];//
		moto_angle.lf2=the_blance.lf2+the_blance1.lf2+the_high_status.lf2+go_force2[xgo_page];
		moto_angle.Rf3=the_blance.Rf3+the_blance1.Rf3+the_high_status.Rf3+1.0f*go_force3[xgo_page];
		moto_angle.Rf4=the_blance.Rf4+the_blance1.Rf4+the_high_status.Rf4+1.0f*go_force4[xgo_page];

		moto_angle.lb1=the_blance.lb1+1.0f*the_blance1.lb1+the_high_status.lb1+1.1f*go_force5[xgo_page];
		moto_angle.lb2=the_blance.lb2+1.0f*the_blance1.lb2+the_high_status.lb2+1.1f*go_force6[xgo_page];
		moto_angle.Rb3=the_blance.Rb3+1.0f*the_blance1.Rb3+the_high_status.Rb3+1.0f*go_force7[xgo_page];
		moto_angle.Rb4=the_blance.Rb4+1.0f*the_blance1.Rb4+the_high_status.Rb4+1.0f*go_force8[xgo_page];
	}
	else if(x_time==3&&y_time==1&&Do_tabu==0)//后退
	{
		//Supplementary_Frame();
		//M3508_ParaInit(&state_kara_speed[1],&state_kara_position[1]);
		if(xback_page>7){xback_page=0;}
		if(xback_page<0){xback_page=7;}
		high_elsa=-8;
		moto_angle.lf1=the_blance.lf1+the_blance1.lf1+the_high_status.lf1+1.2f*go_back1[xback_page];
		moto_angle.lf2=the_blance.lf2+the_blance1.lf2+the_high_status.lf2+1.2f*go_back2[xback_page];
		moto_angle.Rf3=the_blance.Rf3+the_blance1.Rf3+the_high_status.Rf3+1.2f*go_back3[xback_page];
		moto_angle.Rf4=the_blance.Rf4+the_blance1.Rf4+the_high_status.Rf4+1.2f*go_back4[xback_page];

		moto_angle.lb1=the_blance.lb1+the_blance1.lb1+the_high_status.lb1+0.9f*go_back5[xback_page];
		moto_angle.lb2=the_blance.lb2+the_blance1.lb2+the_high_status.lb2+0.9f*go_back6[xback_page];
		moto_angle.Rb3=the_blance.Rb3+the_blance1.Rb3+the_high_status.Rb3+0.9f*go_back7[xback_page];
		moto_angle.Rb4=the_blance.Rb4+the_blance1.Rb4+the_high_status.Rb4+0.9f*go_back8[xback_page];
	}
	else if(x_time==1&&y_time==2&&Do_tabu==0)//左转
	{
		if(xleft_page>7){xleft_page=0;}
		if(xleft_page<0){xleft_page=7;}
		high_elsa=5;
		moto_angle.lf1=the_blance.lf1+the_blance1.lf1+the_high_status.lf1+go_left1[xleft_page];
		moto_angle.lf2=the_blance.lf2+the_blance1.lf2+the_high_status.lf2+go_left2[xleft_page];
		moto_angle.Rf3=the_blance.Rf3+the_blance1.Rf3+the_high_status.Rf3+go_left3[xleft_page];
		moto_angle.Rf4=the_blance.Rf4+the_blance1.Rf4+the_high_status.Rf4+go_left4[xleft_page];

		moto_angle.lb1=the_blance.lb1+the_blance1.lb1+the_high_status.lb1+1.2f*go_left5[xleft_page];
		moto_angle.lb2=the_blance.lb2+the_blance1.lb2+the_high_status.lb2+1.2f*go_left6[xleft_page];
		moto_angle.Rb3=the_blance.Rb3+the_blance1.Rb3+the_high_status.Rb3+1.2f*go_left7[xleft_page];
		moto_angle.Rb4=the_blance.Rb4+the_blance1.Rb4+the_high_status.Rb4+1.2f*go_left8[xleft_page];
	}
	else if(x_time==1&&y_time==3&&Do_tabu==0)//右转
	{
		if(xright_page>7){xright_page=0;}
		if(xright_page<0){xright_page=7;}
		high_elsa=5;
		moto_angle.lf1=the_blance.lf1+the_blance1.lf1+the_high_status.lf1+go_right1[xright_page];
		moto_angle.lf2=the_blance.lf2+the_blance1.lf2+the_high_status.lf2+go_right2[xright_page];
		moto_angle.Rf3=the_blance.Rf3+the_blance1.Rf3+the_high_status.Rf3+go_right3[xright_page];
		moto_angle.Rf4=the_blance.Rf4+the_blance1.Rf4+the_high_status.Rf4+go_right4[xright_page];

		moto_angle.lb1=the_blance.lb1+the_blance1.lb1+the_high_status.lb1+1.2f*go_right5[xright_page];
		moto_angle.lb2=the_blance.lb2+the_blance1.lb2+the_high_status.lb2+1.2f*go_right6[xright_page];
		moto_angle.Rb3=the_blance.Rb3+the_blance1.Rb3+the_high_status.Rb3+1.2f*go_right7[xright_page];
		moto_angle.Rb4=the_blance.Rb4+the_blance1.Rb4+the_high_status.Rb4+1.2f*go_right8[xright_page];
	}
	else if(x_time==2&&y_time==2&&Do_tabu==0)//增加左偏移
	{ 
		M3508_ParaInit(&state_kara_speed[0],&state_kara_position[0]);
		high_elsa=15;
		if(xleft_page>7){xleft_page=0;}
		if(xleft_page<0){xleft_page=7;}
		M3508_ParaInit(&state_kara_speed[0],&state_kara_position[0]);
		moto_angle.lf1=the_blance.lf1+the_blance1.lf1+the_high_status.lf1+go_left1[xleft_page];
		moto_angle.lf2=the_blance.lf2+the_blance1.lf2+the_high_status.lf2+go_left2[xleft_page];
		moto_angle.Rf3=the_blance.Rf3+the_blance1.Rf3+the_high_status.Rf3+go_left3[xleft_page];
		moto_angle.Rf4=the_blance.Rf4+the_blance1.Rf4+the_high_status.Rf4+go_left4[xleft_page];

		moto_angle.lb1=the_blance.lb1+the_blance1.lb1+the_high_status.lb1+1.2f*go_left5[xleft_page];
		moto_angle.lb2=the_blance.lb2+the_blance1.lb2+the_high_status.lb2+1.2f*go_left6[xleft_page];
		moto_angle.Rb3=the_blance.Rb3+the_blance1.Rb3+the_high_status.Rb3+1.2f*go_left7[xleft_page];
		moto_angle.Rb4=the_blance.Rb4+the_blance1.Rb4+the_high_status.Rb4+1.2f*go_left8[xleft_page];
	}
	else if(x_time==2&&y_time==3&&Do_tabu==0)//增加右偏移
	{ 
		M3508_ParaInit(&state_kara_speed[0],&state_kara_position[0]);
		high_elsa=15;
		if(xright_page>7){xright_page=0;}
		if(xright_page<0){xright_page=7;}
		moto_angle.lf1=the_blance.lf1+the_blance1.lf1+the_high_status.lf1+go_right1[xright_page];
		moto_angle.lf2=the_blance.lf2+the_blance1.lf2+the_high_status.lf2+go_right2[xright_page];
		moto_angle.Rf3=the_blance.Rf3+the_blance1.Rf3+the_high_status.Rf3+go_right3[xright_page];
		moto_angle.Rf4=the_blance.Rf4+the_blance1.Rf4+the_high_status.Rf4+go_right4[xright_page];

		moto_angle.lb1=the_blance.lb1+the_blance1.lb1+the_high_status.lb1+1.2f*go_right5[xright_page];
		moto_angle.lb2=the_blance.lb2+the_blance1.lb2+the_high_status.lb2+1.2f*go_right6[xright_page];
		moto_angle.Rb3=the_blance.Rb3+the_blance1.Rb3+the_high_status.Rb3+1.2f*go_right7[xright_page];
		moto_angle.Rb4=the_blance.Rb4+the_blance1.Rb4+the_high_status.Rb4+1.2f*go_right8[xright_page];
	}

}

/*************************************************************************
*  函数名称：Supplementary_Frame
*  功能说明：补帧算法,让动作流畅,以及避免两点间直线
*  参数说明：无 
*  函数返回：无	
*  备    注：无
*************************************************************************/
void Supplementary_Frame(void)
{
	Frame_time++;
	if(Frame_time>=0&&Frame_time<=150*Frame_page){Supplementary_Framecal(1,go_force1[0],go_force1[1],11);Supplementary_Framecal(1,go_force2[0],go_force2[1],12);}
	else if(Frame_time>150*Frame_page&&Frame_time<=300*Frame_page){Supplementary_Framecal(1,go_force1[1],go_force1[2],11);Supplementary_Framecal(1,go_force2[1],go_force2[2],12);}
	else if(Frame_time>450*Frame_page&&Frame_time<=600*Frame_page){Supplementary_Framecal(1,go_force1[2],go_force1[3],11);Supplementary_Framecal(1,go_force2[2],go_force2[3],12);}
	else if(Frame_time>600*Frame_page&&Frame_time<=750*Frame_page){Supplementary_Framecal(1,go_force1[3],go_force1[4],11);Supplementary_Framecal(1,go_force2[3],go_force2[4],12);}
	else if(Frame_time>750*Frame_page&&Frame_time<=900*Frame_page){Supplementary_Framecal(1,go_force1[4],go_force1[5],11);Supplementary_Framecal(1,go_force2[4],go_force2[5],12);}
	else if(Frame_time>900*Frame_page&&Frame_time<=1050*Frame_page){Supplementary_Framecal(1,go_force1[5],go_force1[0],11);Supplementary_Framecal(1,go_force2[5],go_force2[0],12);Frame_time=0;}	
}

void Supplementary_Framecal(float rate_ball, int now_angle, int target_angle, int temp_num) {
// 通过余数来减少帧数，求 x*y = 200*Frame_page
    if (Frame_time % 50 == 0) {
        switch (temp_num) {
            case 11: {
                tRf3++;
                tlf1 += rate_ball * ((target_angle - now_angle) / 6 * Frame_page);
                break;
            }
            case 12: {
                tlf2 += rate_ball * ((target_angle - now_angle) / 6 * Frame_page);
                break;
            }
        }
    }

    // 当 Frame_time 为特定值时，重置 tlf1 和 tlf2
    if (Frame_time == 0 || Frame_time == 150 * Frame_page || Frame_time == 300 * Frame_page ||
        Frame_time == 450 * Frame_page || Frame_time == 600 * Frame_page ||
        Frame_time == 750 * Frame_page || Frame_time == 900 * Frame_page ||
        Frame_time == 1050 * Frame_page) {
        tlf1 = 0;
        tlf2 = 0;
    }
}

