#include "system.h"
#include "SysTick.h"
#include "led.h"
#include "usart.h"

//使用Free RTOS需要用到的相关头文件，定义到 'RTOS_text.h' 里面去
//#include "FreeRTOS.h"
//#include "task.h"
#include "RTOS_text.h"
#include "time6.h"

#include "st7789v.h"
#include "cst816t.h"
#include "pic.h"

/*******************************************************************************
* 函 数 名         : main
* 函数功能		   : 主函数
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/
int main()
{
	WRCACE_InitTypedef WRCACE_InitStruct;
	WRCACE_InitStruct.Adaptive_Brightness_Goal=0x10;
	WRCACE_InitStruct.Color_Enhancement_Cmd=1;
	WRCACE_InitStruct.Color_Enhancement_Extent=11;
	
	SysTick_Init(72);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);//设置系统中断优先级分组4
	LED_Init();
	USART1_Init(115200);
	
	TIM6_Init(1000-1,72-1);  //定时1ms
	
	ST7789V_LcdInit();
	ST7789V_AdaptiveBrightnessColorEnhancementInit(&WRCACE_InitStruct);
	printf("ST7789V Ready!\n");
	ST7789V_FillLcdScreen(0,0,LCD_W,LCD_H,WHITE,USE_HORIZONTAL);
	CST816T_Init();
	printf("CST816T Ready!\n");
	
	ST7789V_LcdShowPicture(11,20,217,240,gImage_fu,USE_HORIZONTAL);
	FreeRTOS_start_task();
	while(1)
	{
		
	}
}



