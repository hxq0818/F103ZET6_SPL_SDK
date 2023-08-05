#include "time.h"
/*! ʹ��Free RTOSϵͳʱ����Ҫ�õ�ͷ�ļ�!*/
#include "FreeRTOS.h"		//FreeRTOSʹ��		  
#include "task.h" 

/*******************************************************************************
* �� �� ��         : TIM6_Init
* ��������		   : TIM6��ʼ������
* ��    ��         : per:��װ��ֵ
					 psc:��Ƶϵ��
* ��    ��         : ��
*******************************************************************************/
void TIM6_Init(u16 per,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6,ENABLE);//ʹ��TIM4ʱ��
	
	TIM_TimeBaseInitStructure.TIM_Period=per;   //�Զ�װ��ֵ
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc; //��Ƶϵ��
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //�������ϼ���ģʽ
	TIM_TimeBaseInit(TIM6,&TIM_TimeBaseInitStructure);
	
	TIM_ITConfig(TIM6,TIM_IT_Update,ENABLE); //������ʱ���ж�
	TIM_ClearITPendingBit(TIM6,TIM_IT_Update);
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM6_IRQn;//��ʱ���ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;//��ռ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;		//�����ȼ�
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	
	
	TIM_Cmd(TIM6,ENABLE); //ʹ�ܶ�ʱ��	
}
/*******************************************************************************
* �� �� ��         : TIM6_IRQHandler
* ��������		   : TIM6�жϺ���
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/
extern void xPortSysTickHandler(void);
void TIM6_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM6,TIM_IT_Update))
	{
		if(xTaskGetSchedulerState()!=taskSCHEDULER_NOT_STARTED)//ϵͳ�Ѿ�����
    {
        xPortSysTickHandler();	
    }
	}
	TIM_ClearITPendingBit(TIM6,TIM_IT_Update);	
}


