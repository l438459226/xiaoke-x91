/******************************* ����������� *********************************
 * �ļ���   ��systick.c        
 * ����     ���������
 * �汾     ��V02
 * ������� ��2014-09-11
 * ����     ��Tick�r犵đ���
 * �޸ļ�¼ ��|    ����    |   ����    |    �汾    |    ����    |
 				 ��a���	2014-09-11				  ���Ӝy���r�g�ăɂ�����				
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
*��������SysTick_Init
*����  ������ϵ�yTick�r�
*����  ����
*����  ���o
********************************************************************************/
void SysTick_Init(void)
{
	/* SystemFrequency / 1000    1ms�ж�һ��
	 * SystemFrequency / 100000	 10us�ж�һ��
	 * SystemFrequency / 1000000 1us�ж�һ��
	 */
	if (SysTick_Config(SystemFrequency / 100000))
    { 
        /* Capture error */ 
        while (1);
    }
}

/********************************************************************************
*��������Delay_10us
*����  ��10us�ӕr����
*����  ��nTime���ӕr�r�g ��λ10us
*����  ���o
********************************************************************************/
void Delay_10uss(__IO u32 nTime)
{ 
  TimingDelay = nTime;

  while(TimingDelay != 0);
}

/********************************************************************************
*��������Delay_ms
*����  ��ms�ӕr����
*����  ��t���ӕr�r�g ��λms
*����  ���o
********************************************************************************/
void Delay_mss(u32 t)
{
	TimingDelay = t * 100;
	while(TimingDelay != 0);		
}

/********************************************************************************
*��������TimingDelay_Decrement
*����  ��Tick�r犵��Дຯ������SysTick_Handler()����
*����  ���o
*����  ���o
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

		//���΄��΄Օr�gӋ�r
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
*��������MeasureTimeStart
*����  ���@ȡ��ʼ�r�g���_ʼ�y���r�g
*����  ���o
*����  ����ǰ�r�gӋ��ֵ SysTick_10usCon
********************************************************************************/
unsigned int MeasureTimeStart(void)
{
	return SysTick_10usCon;
}

/**
���ز���ֵ
������ts�ǳ�ԇ�r�g������Ҫ�����@����ʼ�r�g��Ӌ��r�g��
**/
/********************************************************************************
*��������GetMeasureTime
*����  ���@ȡ �{��MeasureTimeStart()�r���F�ڕr�g�L�� 
*����  ��ts-�ǳ�ԇ�r�g�������{��MeasureTimeStart()�����r�ķ���ֵ��
            ������Ҫ�����@����ʼ�r�g��Ӌ��r�g��
*����  ���{��MeasureTimeStart()�r���F�ڕr�g�L�� 
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
