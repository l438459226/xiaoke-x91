/******************************* ����������� *********************************
 * �ļ���   ��systick.c        
 * ����     ���������
 * �汾     ��V02
 * ������� ��2014-09-11
 * ����     ��Tick�r犵đ���
 * �޸ļ�¼ ��|    ����    |   ����    |    �汾    |    ����    |
 				 ��a���	2014-09-11				  ���Ӝy���r�g�ăɂ�����				
*******************************************************************************/

#ifndef __SYSTICK_H
#define __SYSTICK_H

#include "stm32f10x.h"
#include "delay.h"
/*---------���΄�݆ԃ�r�g���x--------------------*/
#define MAX_TASK 	 4          //������������
extern __IO unsigned int task_time_ms[MAX_TASK];  

#define u16 unsigned short
#define u8 unsigned char

/*-----------------------------------------------*/

//�r�g���Is
extern __IO unsigned int _1ms_ok;
extern __IO unsigned int _20ms_ok;

//��ʼ��TICK
void SysTick_Init(void);

//�ӕr����
//void Delay_10us(__IO u32 nTime);
//void Delay_ms(u32 t);

//�ɂ��y���r�g�ĺ���
//unsigned int MeasureTimeStart(void);
//unsigned int GetMeasureTime(unsigned int ts);


#endif

/******************************* ����������� *********************************/
