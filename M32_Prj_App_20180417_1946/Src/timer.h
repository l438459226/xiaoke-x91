#ifndef __TIMER_H
#define __TIMER_H

#include "BasicDataType.h"

#define T10MS                 (36000)           // 10ms 定时器设置
#define T20MS                 (72000)           // 20ms 定时器设置
#define T1MS                  (3600)            // 1ms 定时器设置
#define T250US                (900)             // 250us 定时器设置
#define T100US                (360)             // 100us 定时器设置
#define T10US                 (36)              // 100us 定时器设置

void NVIC_Configuration(void);
void Timer2_Configuration(void);
void Timer2_Enable(void);
void Timer3_Configuration(void);
void Timer3_Enable(void);
void TIM8_PWM_Configuration(UINT16 PwmFreqArr/*PWM频率=72MHz/(PwmFreqArr+1)*/, UINT8 PwmDuty/*占空比[0~100]*/);


extern UINT8 ConfigItem_Index;
extern UINT8 EncoderButton_Pressed;


#endif /* __TIMER_H */
