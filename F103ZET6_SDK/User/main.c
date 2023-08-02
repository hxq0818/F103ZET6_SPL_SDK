#include "system.h"
#include "SysTick.h"
#include "led.h"
#include "usart.h"

//ʹ��Free RTOS��Ҫ�õ������ͷ�ļ������嵽 'RTOS_text.h' ����ȥ
//#include "FreeRTOS.h"
//#include "task.h"

#include "RTOS_text.h"




/*******************************************************************************
* �� �� ��         : main
* ��������		   : ������
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/
int main()
{
	SysTick_Init(72);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);//����ϵͳ�ж����ȼ�����4
	LED_Init();
	USART1_Init(115200);
	
	FreeRTOS_start_task();
	
}



