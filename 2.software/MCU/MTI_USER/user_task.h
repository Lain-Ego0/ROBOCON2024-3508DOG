#ifndef __USER_TASK_H__
#define __USER_TASK_H__

#include "main.h"

extern SemaphoreHandle_t P_shH219DataDecode_Binary;

void Task_Main(void *Parameters);
void Task_Hi219mDataDecode(void *Parameters);
void Task_TimeCount(void *Parameters);
void Task_MiniPCDataDecode(void *Parameters);
void Task_JudgeDataDecode(void *Parameters);
void Task_OverPower(void *Parameters);
void Task_DataGet(void *Parameters);
void key_contask(void *Parameters);
extern int xt,yt;
extern int high_elsa;
extern int if_jump;
#endif
