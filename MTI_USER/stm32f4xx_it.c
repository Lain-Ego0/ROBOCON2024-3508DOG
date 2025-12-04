#include "stm32f4xx_it.h"
#include "main.h"
#include "task.h"

CanRxMsg CAN1DataRecv; //CAN1数据接收结构体
CanRxMsg CAN2DataRecv; //CAN2数据接收结构体

//////////////////////////////////////

//////////////请注释清楚，每个都要！！！！

/////////////////////////////////////can口

/*************************************************************************
*  函数名称：CAN1_RX0_IRQHandler
*  功能说明：CAN1接收中断服务函数
*  参数说明：无
*  函数返回：无	 
*  备    注：电机CAN传送数据解析
*************************************************************************/

void CAN1_RX0_IRQHandler(void)/////////////////////////////////////can口数据读取，将数据存入相应结构体
{   
//	CPU_SR_ALLOC();
//	OS_CRITICAL_ENTER();	//进入临界区
	
	if(CAN_GetITStatus(CAN1,CAN_IT_FMP0)!= RESET)
	{
		CAN_Receive(CAN1, CAN_FIFO0, &CAN1DataRecv);	//接收数据
		
		fnMotor_CanRecvDataDecode(CAN1,&CAN1DataRecv);	//电机处理数据
		
		CAN_ClearITPendingBit(CAN1, CAN_IT_FF0);	//清除中断标志位
		CAN_ClearFlag(CAN1, CAN_FLAG_FF0); 	//清除标志位
	}
//	
//	OS_CRITICAL_EXIT();	//退出临界区
}

/*************************************************************************
*  函数名称：CAN1_TX_IRQHandler
*  功能说明：CAN1发送中断服务函数
*  参数说明：无
*  函数返回：无	 
*  备    注：无
*************************************************************************/

void CAN1_TX_IRQHandler(void) //CAN TX//////////////////////////////发送中断(未写入)
{
//	CPU_SR_ALLOC();
//	OS_CRITICAL_ENTER();	//进入临界区
	
    if(CAN_GetITStatus(CAN1,CAN_IT_TME)!= RESET) 
    {
        CAN_ClearITPendingBit(CAN1,CAN_IT_TME);
    }
		
//	OS_CRITICAL_EXIT();	//退出临界区
}

/*************************************************************************
*  函数名称：CAN2_RX0_IRQHandler
*  功能说明：CAN2接收中断服务函数
*  参数说明：无
*  函数返回：无	 
*  备    注：电机CAN传送数据解析
*************************************************************************/

void CAN2_RX0_IRQHandler(void)/////////////////////////////////////can口数据读取，将数据存入相应结构体
{   
//	CanRxMsg P_stCAN2DataRecv;
	if(CAN_GetITStatus(CAN2,CAN_IT_FMP0)!= RESET)
	{
		CAN_Receive(CAN2, CAN_FIFO0, &CAN2DataRecv);	//接收数据
		
		fnMotor_CanRecvDataDecode(CAN2,&CAN2DataRecv);	//电机处理数据
		
		CAN_ClearITPendingBit(CAN2, CAN_IT_FF0);	//清除中断标志位
		CAN_ClearFlag(CAN2, CAN_FLAG_FF0); 	//清除标志位
		 
	}
}

/*************************************************************************
*  函数名称：CAN2_TX_IRQHandler
*  功能说明：CAN2发送中断服务函数
*  参数说明：无
*  函数返回：无	 
*  备    注：无
*************************************************************************/

void CAN2_TX_IRQHandler(void) //CAN TX//////////////////////////////发送中断(未写入)
{
    if(CAN_GetITStatus(CAN2,CAN_IT_TME)!= RESET) 
    {
        CAN_ClearITPendingBit(CAN2,CAN_IT_TME);
    }
}

//////////////////////////////////////////////////////////////////////////串口


void USART1_IRQHandler(void)//////////////////////////////////////////////串口接收中断运用于DBUS接收器(遥控器),使用了DMA未访问cpu直接写入内存;
{
//	CPU_SR_ALLOC();
//	OS_CRITICAL_ENTER();	//进入临界区
	
	static uint32_t rx_len = 0;
	
	if(USART_GetITStatus(USART1, USART_IT_IDLE) != RESET)
	{
		//clear the idle pending flag 
		(void)USART1->SR;
		(void)USART1->DR;
		
		//Target is Memory0
		if(DMA_GetCurrentMemoryTarget(DMA2_Stream2) == 0)
		{
			DMA_Cmd(DMA2_Stream2, DISABLE);
			rx_len = REMOTE_DATA_RX_LEN - DMA_GetCurrDataCounter(DMA2_Stream2);
			DMA2_Stream2->NDTR = (uint16_t)REMOTE_DATA_RX_LEN;     //relocate the dma memory pointer to the beginning position
			DMA2_Stream2->CR |= (uint32_t)(DMA_SxCR_CT);                  //enable the current selected memory is Memory 1
			DMA_Cmd(DMA2_Stream2, ENABLE);
			if(rx_len == REMOTE_DATAFRAME_LEN)
			{
				fnRemote_RawDataDecode(&P_stRemoteData_Recv,P_uintRemote_Data_Buf[0]);
			}
		}
		//Target is Memory1
		else 
		{
			DMA_Cmd(DMA2_Stream2, DISABLE);
			rx_len = REMOTE_DATA_RX_LEN - DMA_GetCurrDataCounter(DMA2_Stream2);
			DMA2_Stream2->NDTR = (uint16_t)REMOTE_DATA_RX_LEN;      //relocate the dma memory pointer to the beginning position
			DMA2_Stream2->CR &= ~(uint32_t)(DMA_SxCR_CT);                  //enable the current selected memory is Memory 0
			DMA_Cmd(DMA2_Stream2, ENABLE);
			if(rx_len == REMOTE_DATAFRAME_LEN)
			{
				fnRemote_RawDataDecode(&P_stRemoteData_Recv,P_uintRemote_Data_Buf[1]);
			}
		}
	}    
//	OS_CRITICAL_EXIT();	//退出临界区
}

/////////////////////////////////////////////////////////////////////////陀螺仪hi219m UART8 TX:PE1  RX:PE0
void UART8_IRQHandler(void)
{
	BaseType_t xHigherPriorityTaskWoken;
	if(USART_GetITStatus(UART8,USART_IT_IDLE) != RESET)//防止非空闲中断时进入
	{
		UART8->DR;
		UART8->SR;
		DMA_Cmd(DMA1_Stream6, DISABLE); 
		
		P_uintH219BuffLength = HI219M_RX_BUF_LEN-(DMA1_Stream6->NDTR);
        //重启DMA
		DMA_ClearFlag(DMA1_Stream6, DMA_FLAG_TCIF6 | DMA_FLAG_HTIF6);
		while(DMA_GetCmdStatus(DMA1_Stream6) != DISABLE);
		DMA_SetCurrDataCounter(DMA1_Stream6, HI219M_RX_BUF_LEN);
		DMA_Cmd(DMA1_Stream6, ENABLE);
		
		if(P_shH219DataDecode_Binary!=NULL)//若未创建切换任务会死机
		{
			xSemaphoreGiveFromISR(P_shH219DataDecode_Binary,&xHigherPriorityTaskWoken);	//释放二值信号量
			portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
		}		
	}
}

// 从这里到下面为激光雷达计算函数
#define TF_HEADER 0x59

float ch;
float TF_distance = 0;             // TF_测距数据
float TF_strength = 0;             // TF_信号强度
float TF_temperature = 0;          // TF_温度
int TF_checksum = 0;             // TF_自检
float TF_flage = 0x00;              // TF_测距状态
float TF_uart_data;
int TF_dat[9];
int TF_num = 0;
int ass = 256;

void USART6_IRQHandler(void) {
    if (USART_GetITStatus(USART6, USART_IT_RXNE) == SET) {
        USART_ClearITPendingBit(USART6, USART_IT_RXNE);
        ch = USART_ReceiveData(USART6);
        // 仅需将USART_ReceiveData(USART6)换成其他接收函数就行

        TF_dat[TF_num] = ch;

        if (TF_num) {
            if (TF_dat[1] != TF_HEADER) {
                TF_num = 0;
                // 2、若第二个数不是 0x59，则TF_num清零，下一次重新检测第一个数
            } else {
                TF_num++;
                // 3、第一和第二个数均满足要求，开始将获得的数，逐位赋给TF_dat[2~8]
            }
        }

        if (TF_dat[0] != TF_HEADER) {
            TF_num = 0;
        } else if (TF_num == 0) {
            TF_num = 1;
            // 1、若第一个数满足要求0x59，则下一次接收并检测第二个函数
        }

        if (TF_num == 9) {
            // 获得完9位数后
            TF_num = 0;
            TF_checksum = TF_dat[0] + TF_dat[1] + TF_dat[2] + TF_dat[3] + TF_dat[4]
                          + TF_dat[5] + TF_dat[6] + TF_dat[7];

            if ((TF_checksum % ass) == TF_dat[8]) {
                // TF_dat[8]是自检位，满足要求后根据公式计算距离等
                TF_distance = TF_dat[3] << 8 | TF_dat[2];
                TF_strength = TF_dat[5] << 8 | TF_dat[4];
                TF_temperature = TF_dat[7] << 8 | TF_dat[6];
                TF_flage = 1;
            }
        }
    }
}


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
	
