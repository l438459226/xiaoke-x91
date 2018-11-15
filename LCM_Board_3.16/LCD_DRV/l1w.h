

#ifndef _L1W_H_
#define _L1W_H_

#include "stm32f10x.h"

//GetFlickerValue�ķ���ֵ���x
#define FV_OLD		0x00	//�@ȡ��ֵ���fֵ���ϴ��ѫ@ȡ�^
#define FV_NEW 		0X01 	//�@ȡ��ֵ����ֵ
#define FV_ERROR	0xFF	//�@ȡ�e�`��������ͨӍ�e�`

//LOGS�ı�������������ֵ�궨�x
#define LGS_FAIL 	0XFF    //��������ʧ��
#define LGS_FULFIL	0X00	//�����������

//LOGS�ı��@ʾ���wɫ�ʺ궨��
#define LGST_RED    	0XF800
#define LGST_GREEN  	0X07E0
#define LGST_BLUE   	0X001F
#define LGST_WHITE      0XFFFF


///////////////////////////////////////////////

/*
*��������L1WInit
*����  ��L1WͨӍ��ʼ��
*����  ����
*����  ���o
*/
extern void L1WInit(void);

/*
*��������L1WGetFlickerValue
*����  ����ȡFlickerֵ��
         ע�⣺��ȡ����Flickerֵ��ǰ100ms��ֵ�����@��ֵ��F����ǰ100ms����˸��r��
		       �K�Ǯ�ǰ����˸��r

*����  ��flicker_pct - ����flicker �ٷֱ�ֵ�ı�����ַ.
             *flicker_pctֵ�Ć�λ��0.1%���� *flicker_pct=100������ʾ=10.0%.
	     flicer_db - ����flicker ��λ��dB��ֵ�ı�����ַ��
		     *flicker_db ֵ�Ć�λ��0.1dB���� *flicker_db= -100������ʾ=-10.0dB��
		 ע�⣺�@�ɂ�������ʾ����ǰ100ms��Flickerֵ��

*����  ��״ֵ̬��
         =FV_OLD����ȡ��ֵ�Ǿ�ֵ���ϴ��ѻ�ȡ��
		 =FV_NEW����ȡ��ֵ����ֵ ��ע�⣬��ʹ����ֵҲ��ǰ100ms��fliker��r��
		 =FV_ERROR����ȡ�e�`��������ͨӍ�e�`

*����  ��
		unsigned int flicker_tcp;
		int flicker_db;   //�@�����з������ͱ���
		if(FV_NEW == L1WGetFlickerValue(&flicker_tcp, &flicker_db)) //�������������ĵ�ַ;
		{										                   //�Է���ֵ�ж�flickerֵ�Ƿ�����ֵ
			...... //�û�����
		}
*/
extern unsigned int L1WGetFlickerValue(unsigned int *flicker_pct, int *flicker_db);

/*
*��������L1WLogsDisplayString
*����  ����LOGS�ı�����ʾһ���ַ���LOGS�ı������ʾ16�С�3�� ��16*3=48���ַ���
*����  ��x�������ֵ꣬��0~15
         y�������ֵ꣬��0~2
		 color��������ɫ����ʽRGB565����������ĺ궨�x
		        =LGST_RED   -> ���w��tɫ
				=LGST_GREEN -> ���w��Gɫ
				=LGST_BLUE  -> ���w���{ɫ
				=LGST_WHITE -> ���w���ɫ
		 str��ָ��Ҫ�@ʾ���ַ�����ַ
*����  �����ص��Ǻ���������B
		 =LGS_FAIL����������ʧ��������ͨѶʧ��
		 =LGS_FULFIL�������������
*/
extern unsigned int L1WLogsDisplayString(unsigned int x, unsigned int y, uint16_t color, char *str);

/*
*��������L1WLogsClear
*����  �����LOGS�ı�����ʾ���ַ�
*����  ����
*����  �����ص��Ǻ���������B
		 =LGS_FAIL����������ʧ��������ͨѶʧ��
		 =LGS_FULFIL�������������
*/
extern unsigned int L1WLogsClear(void);

#endif

