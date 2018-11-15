/******************************* 广州天码电子 *********************************
 * 文件名   ：systick.c        
 * 作者     ：天码电子
 * 版本     ：V02
 * 完成日期 ：2014-09-11
 * 描述     ：Tick時鐘的應用
 * 修改记录 ：|    作者    |   日期    |    版本    |    描述    |
 				 天碼電子	2014-09-11				  增加測量時間的兩個函數				
*******************************************************************************/

#ifndef __SYSTICK_H
#define __SYSTICK_H

#include "stm32f10x.h"
#include "delay.h"
/*---------多任務輪詢時間定義--------------------*/
#define MAX_TASK 	 4          //定义任务数量
extern __IO unsigned int task_time_ms[MAX_TASK];  

#define u16 unsigned short
#define u8 unsigned char

/*-----------------------------------------------*/

//時間標誌s
extern __IO unsigned int _1ms_ok;
extern __IO unsigned int _20ms_ok;

//初始化TICK
void SysTick_Init(void);

//延時函數
//void Delay_10us(__IO u32 nTime);
//void Delay_ms(u32 t);

//兩個測量時間的函數
//unsigned int MeasureTimeStart(void);
//unsigned int GetMeasureTime(unsigned int ts);


#endif

/******************************* 广州天码电子 *********************************/
