#ifndef __TIMER_H
#define __TIMER_H

#include "BasicDataType.h"

#define T10MS                 (36000)           // 10ms ��ʱ������
#define T20MS                 (72000)           // 20ms ��ʱ������
#define T1MS                  (3600)            // 1ms ��ʱ������
#define T250US                (900)             // 250us ��ʱ������
#define T100US                (360)             // 100us ��ʱ������
#define T10US                 (36)              // 100us ��ʱ������

void NVIC_Configuration(void);
void Timer2_Configuration(void);
void Timer2_Enable(void);
void Timer3_Configuration(void);
void Timer3_Enable(void);
void TIM8_PWM_Configuration(UINT16 PwmFreqArr/*PWMƵ��=72MHz/(PwmFreqArr+1)*/, UINT8 PwmDuty/*ռ�ձ�[0~100]*/);


extern UINT8 ConfigItem_Index;
extern UINT8 EncoderButton_Pressed;


#endif /* __TIMER_H */
