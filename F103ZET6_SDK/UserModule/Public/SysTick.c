#include "SysTick.h"

static u8  fac_us=0;							//us��ʱ������			   
static u16 fac_ms=0;							//ms��ʱ������


//��ʼ���ӳٺ���
//SYSTICK��ʱ�ӹ̶�ΪAHBʱ�ӣ�������������SYSTICKʱ��Ƶ��ΪAHB/8
//SYSCLK:ϵͳʱ��Ƶ��
//��ȷ��ʱ��ʼ��
void SysTick_Init(uint8_t SysClk)
{
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);
	fac_us=SysClk/8;
	fac_ms=fac_us*1000;
}					    

//��ȷ��ʱ������΢��
void Correct_DelayUs(uint32_t Time)
{
	uint32_t temp;	    	 
	SysTick->LOAD=Time*fac_us; 					//ʱ�����	  		 
	SysTick->VAL=0x00;        					//��ռ�����
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;	//��ʼ����	  
	do
	{
		temp=SysTick->CTRL;
	}while((temp&0x01)&&!(temp&(1<<16)));		//�ȴ�ʱ�䵽��   
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;	//�رռ�����
	SysTick->VAL =0X00;      					 //��ռ�����	 
}
//��ȷ���뼶����ʱ
void Correct_DelayMs(uint16_t Time)
{
	uint32_t temp;		   
	SysTick->LOAD=(u32)Time*fac_ms;				//ʱ�����(SysTick->LOADΪ24bit)
	SysTick->VAL =0x00;							//��ռ�����
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;	//��ʼ����  
	do
	{
		temp=SysTick->CTRL;
	}while((temp&0x01)&&!(temp&(1<<16)));		//�ȴ�ʱ�䵽��   
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;	//�رռ�����
	SysTick->VAL =0X00;       					//��ռ�����	  
}


