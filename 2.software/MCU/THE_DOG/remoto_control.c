#include "remoto_control.h"

/*************************************************************************
 * 函数名称：need_remoto
 * 功能说明：遥控器控制逻辑
 * 参数说明：x - 控制指令
 * 函数返回：无
 * 备    注：遥控器的控制逻辑与键盘分开，遥控器优先
 *************************************************************************/

// 数据库
int stap = 0;
int stap1 = 0;

void need_remoto(int x) {
    switch (x) {
        case 1: // 掉电
            M3508_ParaInit(&state_kara_speed[0], &state_kara_position[0]);
            DOG_kara();

            // 判断第几次站立，防止反复站立给力
            if (stap1 == 0) {
                stap = 0;
            } else if (stap1 == 1) {
                stap = 2;
            }
            break;

        case 3: // 站立或者蹲下
            M3508_ParaInit(&state_kara1_speed[0], &state_kara1_position[0]);
            if (stap == 0) {
                stand_up_withP();
            } else if (stap == 1) {
                sit_down();
            } else if (stap == 2) {
                stand_up();
            }
            break;

        case 2:
            stap = 1;
            stap1 = 1;
            break;
    }
}

	
