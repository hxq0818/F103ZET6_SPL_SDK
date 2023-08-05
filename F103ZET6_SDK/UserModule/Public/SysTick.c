#include "SysTick.h"

static u8  fac_us=0;							//us延时倍乘数			   
static u16 fac_ms=0;							//ms延时倍乘数


//初始化延迟函数
//SYSTICK的时钟固定为AHB时钟，基础例程里面SYSTICK时钟频率为AHB/8
//SYSCLK:系统时钟频率
//精确延时初始化
void SysTick_Init(uint8_t SysClk)
{
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);
	fac_us=SysClk/8;
	fac_ms=fac_us*1000;
}					    

//精确延时函数，微秒
void Correct_DelayUs(uint32_t Time)
{
	uint32_t temp;	    	 
	SysTick->LOAD=Time*fac_us; 					//时间加载	  		 
	SysTick->VAL=0x00;        					//清空计数器
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;	//开始倒数	  
	do
	{
		temp=SysTick->CTRL;
	}while((temp&0x01)&&!(temp&(1<<16)));		//等待时间到达   
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;	//关闭计数器
	SysTick->VAL =0X00;      					 //清空计数器	 
}
//精确毫秒级的延时
void Correct_DelayMs(uint16_t Time)
{
	uint32_t temp;		   
	SysTick->LOAD=(u32)Time*fac_ms;				//时间加载(SysTick->LOAD为24bit)
	SysTick->VAL =0x00;							//清空计数器
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;	//开始倒数  
	do
	{
		temp=SysTick->CTRL;
	}while((temp&0x01)&&!(temp&(1<<16)));		//等待时间到达   
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;	//关闭计数器
	SysTick->VAL =0X00;       					//清空计数器	  
}


