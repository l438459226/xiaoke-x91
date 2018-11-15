/******************************* ����������� *********************************
 * �ļ���   ��power_ctrl.h        
 * ����     ���������
 * �汾     ��V02
 * ������� ��2014-05-26
 * ����     ����ͨ��늉�������O��
 * �����б�	��	
			  	void PwrCtrlInit(void);
				void PwrVDD1(unsigned int mv);
				void PwrVDD2(unsigned int mv);
				void PwrVDD3(unsigned int mv);
				void PwrVDD4(unsigned int mv);
				void PwrVDD5(unsigned int mv);
				void PwrVDD6(unsigned int mv);
	
				void PwrVDD_5V_ON(void);	  //��ͨ����SSD2828���Դ
				void PwrVDD_5V_OFF(void);
				
				void PwrVLED1(unsigned int ma);
				void PwrVLED2(unsigned int ma);
				void PwrVLED3(unsigned int ma);
				void PwrVLED4(unsigned int ma);
				void PwrVLED5(unsigned int ma);
				void PwrVLED6(unsigned int ma);
				void PwrVLED7(unsigned int ma);
				void PwrVLED8(unsigned int ma);
				void PwrVLED_ON(void);		   //����ͨ���O������� Ҫ�{�ô˺����������ͨ�
				void PwrVLED_OFF(void);

				uint8_t ReadDialSwitch(void);

 * �޸ļ�¼ ��|    ����    |   ����    |    �汾    |    ����    |	
 				�������	2014-05-26      V02		  ���Ӷ����뿪��		
*******************************************************************************/

#ifndef _POWER_CTRL_
#define _POWER_CTRL_

#include "stm32f10x.h"

/*
*������ : PowerCtrlInit
*����   : ��Դ���Ƴ�ʼ��
*����   : ��
*����   : ��
*/
extern void PwrCtrlInit(void);

/*
*������ : PwrVDD1
*����   : ����VDD1�ĵ�ѹ, 늉����O�ù���0~5V
*����   : mv -��ѹֵ ��λmV
*����   : ��
*/
extern void PwrVDD1(unsigned int mv);

/*
*������ : PwrVDD2
*����   : ����VDD2�ĵ�ѹ, 늉����O�ù���0~5V
*����   : mv -��ѹֵ ��λmV
*����   : ��
*/
extern void PwrVDD2(unsigned int mv);

/*
*������ : PwrVDD3
*����   : ����VDD3�ĵ�ѹ, 늉����O�ù���0~10V
*����   : mv -��ѹֵ ��λmV
*����   : ��
*/
extern void PwrVDD3(unsigned int mv);

/*
*������ : PwrVDD4
*����   : ����VDD4�ĵ�ѹ��늉����O�ù���0~10V
*����   : mv -��ѹֵ ��λmV
*����   : ��
*/
extern void PwrVDD4(unsigned int mv);

/*
*������ : PwrVDD5
*����   : ����VDD5�ĵ�ѹ����ͨ��ݔ������ؓ늉���늉����O�ù���0 ~ -10V
*����   : mv -��ѹֵ ��λ(-mV),�����������ͣ�ݔ������ؓ늉�
*����   : ��
*/
extern void PwrVDD5(unsigned int mv);

/*
*������ : PwrVDD6
*����   : ����VDD6�ĵ�ѹ��늉����O�ù���0~10V
*����   : mv -��ѹֵ ��λmV
*����   : ��
*/
extern void PwrVDD6(unsigned int mv);

/*
*������ : PwrVDD5V_ON
*����   : ����VDD5V��Դ����ͨ��Ҳ��SSD2828���Դ
*����   : ��
*����   : ��
*/
extern void PwrVDD_5V_ON(void);

/*
*������ : PwrVDD5V_OFF
*����   : �ر�VDD5V��Դ����ͨ��Ҳ��SSD2828���Դ
*����   : ��
*����   : ��
**/
extern void PwrVDD_5V_OFF(void);

/*
*������ : PwrVLED1
*����   : ����VLED1����ͨ�����������O���������0~100mA
*����   : ma -����ֵ ��λ mA
*����   : ��
*/
extern void PwrVLED1(unsigned int ma);

/*
*������ : PwrVLED2
*����   : ����VLED2����ͨ�����������O���������0~100mA
*����   : ma -����ֵ ��λ mA
*����   : ��
*/
extern void PwrVLED2(unsigned int ma);

/*
*������ : PwrVLED3
*����   : ����VLED3����ͨ�����������O���������0~100mA
*����   : ma -����ֵ ��λ mA
*����   : ��
*/
extern void PwrVLED3(unsigned int ma);

/*
*������ : PwrVLED4
*����   : ����VLED4����ͨ�����������O���������0~100mA
*����   : ma -����ֵ ��λ mA
*����   : ��
*/
extern void PwrVLED4(unsigned int ma);

/*
*������ : PwrVLED5
*����   : ����VLED5����ͨ�����������O���������0~100mA
*����   : ma -����ֵ ��λ mA
*����   : ��
*/
extern void PwrVLED5(unsigned int ma);

/*
*������ : PwrVLED6
*����   : ����VLED6����ͨ�����������O���������0~100mA
*����   : ma -����ֵ ��λ mA
*����   : ��
*/
extern void PwrVLED6(unsigned int ma);

/*
*������ : PwrVLED7
*����   : ����VLED7����ͨ�����������O���������0~100mA
*����   : ma -����ֵ ��λ mA
*����   : ��
*/
extern void PwrVLED7(unsigned int ma);

/*
*������ : PwrVLED8
*����   : ����VLED8����ͨ�����������O���������0~100mA
*����   : ma -����ֵ ��λ mA
*����   : ��
*/
extern void PwrVLED8(unsigned int ma);

/*
*������ : PwrVLED_ON
*����   : ���������Դ������ͨ���O�������Ҫ�{�ô˺����u�����ͨ�
*����   : ��
*����   : ��
*����   : �ⲿ����
*/
extern void PwrVLED_ON(void);

/*
*������ : PwrVDD5V_OFF
*����   : �ر�VDD5V��Դ
*����   : ��
*����   : ��
*/
extern void PwrVLED_OFF(void);


////////////////////////////////////���뿪��////////////////////////////////////

#define DSW1_ON 0X01
#define DSW2_ON	0x02
#define DSW3_ON 0x04
#define DSW4_ON 0x08
#define DSW_NULL 0X00

/*
*������ : ReadDialSwitch
*����   : �����뿪��
*����   : ��
*����   : ���뿪��״̬��������ĺ궨��
*/
extern uint8_t ReadDialSwitch(void);

#endif

/******************************* ����������� *********************************/
