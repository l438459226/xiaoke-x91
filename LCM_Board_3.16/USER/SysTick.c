/******************************* 广州天码电子 *********************************
 * 文件名   ：systick.c        
 * 作者     ：天码电子
 * 版本     ：V02
 * 完成日期 ：2014-09-11
 * 描述     ：Tick時鐘的應用
 * 修改记录 ：|    作者    |   日期    |    版本    |    描述    |
 				 天碼電子	2014-09-11				  增加測量時間的兩個函數				
*******************************************************************************/

#include "SysTick.h"

static __IO u32 TimingDelay;
static u32 SysTick_10usCon;
static uint32_t _1ms_cnt;
static uint32_t _20ms_cnt;
__IO unsigned int _1ms_ok = 0;
__IO unsigned int _20ms_ok = 0;

__IO unsigned int task_time_ms[MAX_TASK]; 

#define SystemFrequency  72000000
/********************************************************************************
*函數名：SysTick_Init
*描述  ：啟動系統Tick時鐘
*参数  ：无
*返回  ：無
********************************************************************************/
void SysTick_Init(void)
{
	/* SystemFrequency / 1000    1ms中断一次
	 * SystemFrequency / 100000	 10us中断一次
	 * SystemFrequency / 1000000 1us中断一次
	 */
	if (SysTick_Config(SystemFrequency / 100000))
    { 
        /* Capture error */ 
        while (1);
    }
}

/********************************************************************************
*函數名：Delay_10us
*描述  ：10us延時程序
*参数  ：nTime：延時時間 單位10us
*返回  ：無
********************************************************************************/
void Delay_10uss(__IO u32 nTime)
{ 
  TimingDelay = nTime;

  while(TimingDelay != 0);
}

/********************************************************************************
*函數名：Delay_ms
*描述  ：ms延時程序
*参数  ：t：延時時間 單位ms
*返回  ：無
********************************************************************************/
void Delay_mss(u32 t)
{
	TimingDelay = t * 100;
	while(TimingDelay != 0);		
}

/********************************************************************************
*函數名：TimingDelay_Decrement
*描述  ：Tick時鐘的中斷函數，在SysTick_Handler()调用
*参数  ：無
*返回  ：無
********************************************************************************/ 
void TimingDelay_Decrement(void)
{
	unsigned int i;
	
	if(TimingDelay != 0x00)
	{ 
		TimingDelay--;
	}
	SysTick_10usCon++;

  	if(++_1ms_cnt >= 100)
	{
		_1ms_cnt = 0;
		_1ms_ok = 1;

		//多任務任務時間計時
		for(i = 0; i < MAX_TASK; i++)
		{
			if(task_time_ms[i] > 0)
			{
				task_time_ms[i]--;
			}
		}
	}

	if(++_20ms_cnt >= 2000)
	{
		_20ms_cnt = 0;
		_20ms_ok = 1;
	}

}


/********************************************************************************
*函數名：MeasureTimeStart
*描述  ：獲取初始時間，開始測量時間
*参数  ：無
*返回  ：當前時間計算值 SysTick_10usCon
********************************************************************************/
unsigned int MeasureTimeStart(void)
{
	return SysTick_10usCon;
}

/**
返回测量值
參數：ts是初試時間，函數要根據這個初始時間來計算時間差
**/
/********************************************************************************
*函數名：GetMeasureTime
*描述  ：獲取 調用MeasureTimeStart()時到現在時間長度 
*参数  ：ts-是初試時間，就是調用MeasureTimeStart()函數時的返回值。
            本函數要根據這個初始時間來計算時間差
*返回  ：調用MeasureTimeStart()時到現在時間長度 
********************************************************************************/
unsigned int GetMeasureTime(unsigned int ts)
{
	u32 tmp;
	tmp = SysTick_10usCon;
    if(tmp < ts)
	{
		tmp = 0xffffffff - ts + tmp;
	}
	else
	{
		tmp = tmp - ts;
	}
	return tmp;
}
