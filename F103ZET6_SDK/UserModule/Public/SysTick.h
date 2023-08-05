#ifndef _SysTick_H
#define _SysTick_H

#include "system.h"

/*
*Parameter:SysClk
*					ϵͳʱ��Ƶ�ʣ���AHBԤ��Ƶ���ʱ��
*Role     :
*         ��ȷ��ʱ��ʼ��
*/
void SysTick_Init(u8 SYSCLK);
/*
*Parameter:Time
*					usʱ��(1800,000)
*Role     :
*         ��ʱ������us
*/
void Correct_DelayUs(uint32_t Time);
/*
*Parameter:Time
*					msʱ��(1800)
*Role     :
*         ��ʱ������ms
*/
void Correct_DelayMs(uint16_t Time);

#endif
