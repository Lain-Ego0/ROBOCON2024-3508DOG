#include "main.h"

void BSP_Init(void);
void Hardware_Init(void);
void Task_Init(void);

int main(void)
{ 
	BSP_Init();//底层初始化
	Hardware_Init();//硬件初始化TIM_SetCompare1(TIM2,3000);
	Task_Init();//任务初始化
	vTaskStartScheduler(); //开始任务调度
	while(1);
}

//底层初始化函数
void BSP_Init(void)
{
	BSP_GPIO_Init();
	BSP_NVIC_Init();
	BSP_CAN_Init();
	BSP_TIM_Init();
	BSP_USART_Init();
	BSP_DMA_Init();
}

//硬件初始化
void Hardware_Init(void)
{
	Hi219m_ParaInit();
}		

//任务初始化
void Task_Init(void)
{
	P_shH219DataDecode_Binary = xSemaphoreCreateBinary();
	
	//主任务
	xTaskCreate(Task_Main,
				"Task_Main",
				300,
				NULL,
				5,
				NULL);
	
	//键盘控制任务
	xTaskCreate(key_contask,
				"key_contask",
				500,
				NULL,
				4,
				NULL);
	

	//遥控器获取键盘值任务
	xTaskCreate(Task_DataGet,
				"Task_DataGet",
				300,
				NULL,
				4,
				NULL);
	
	//陀螺仪数据解析任务
	xTaskCreate(Task_Hi219mDataDecode,
				"Task_Hi219mDataDecode",
				300,
				NULL,
				4,
				NULL);

	xTaskCreate(Task_TimeCount,
				"Task_TimeCount",
				300,
				NULL,
				4,
				NULL);
}
