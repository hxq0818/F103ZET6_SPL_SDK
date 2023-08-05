#ifndef _SysTick_H
#define _SysTick_H

#include "system.h"

/*
*Parameter:SysClk
*					系统时钟频率，即AHB预分频后的时钟
*Role     :
*         精确延时初始化
*/
void SysTick_Init(u8 SYSCLK);
/*
*Parameter:Time
*					us时间(1800,000)
*Role     :
*         延时参数个us
*/
void Correct_DelayUs(uint32_t Time);
/*
*Parameter:Time
*					ms时间(1800)
*Role     :
*         延时参数个ms
*/
void Correct_DelayMs(uint16_t Time);

#endif
