#include "system.h"
#include "SysTick.h"
#include "led.h"
#include "usart.h"

//使用Free RTOS需要用到的相关头文件，定义到 'RTOS_text.h' 里面去
//#include "FreeRTOS.h"
//#include "task.h"

#include "RTOS_text.h"




/*******************************************************************************
* 函 数 名         : main
* 函数功能		   : 主函数
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/
int main()
{
	SysTick_Init(72);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);//设置系统中断优先级分组4
	LED_Init();
	USART1_Init(115200);
	
	FreeRTOS_start_task();
	
}



