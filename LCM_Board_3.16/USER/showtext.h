/******************************* ����������� *********************************
 * �ļ���   ��main.c        
 * ����     ���������
 * �汾     ��V01
 * ������� ��2014-05-26 
 * ����     ��ʵ����ģ����ʾ�ַ���
 * �����б� ��
               void ShowString(unsigned int x, 
			                   unsigned int y, 
							   unsigned int font, 
							   uint32_t color, 
							   uint32_t Bcolor, 
							   char* p);

 * �޸ļ�¼ ��|    ����    |   ����    |    �汾    |    ����    | 				
*******************************************************************************/

#ifndef _SHOWTEXT_H_
#define _SHOWTEXT_H_

#include "stm32f10x.h"

//����ߴ�����궨��
#define FONT0816  0x01   //size: w=8, h=16
#define FONT1632  0X02   //size: w=16, h=32
#define FONT2448  0X03   //size: w=24, h=48
#define FONT3264  0X04   //size: w=32, h=64 
#define FONT4080  0X05   //size: w=40, h=80
#define FONT4896  0X06   //size: w=48, h=96

//ɫ�ʺ궨��
#define NOCOLOR 0X1000000  //��ɫ
#define RED    0XFF0000
#define GREEN  0X00FF00
#define BLUE   0X0000FF
#define YELLOW 0xFFFF00
 


/*
*������ : ShowString
*����   : ��ʾһ���ַ�����ע�� �����Զ����У�
*����   : x - ��ʼ����ˮƽ����ֵ
		  y - ��ʼ���괹ֱ����ֵ
		  font - ����ߴ���� ������������ߴ�����궨��
		  color - �ַ���ɫ, �磺color=0xFF0000Ϊ����ɫ, color=0x00ff00Ϊ����ɫ����ɫ��ֵΪcolor=NOCOLOR
		  Bcolor - �ַ�������ɫ���磺color=0xFF0000Ϊ����ɫ, color=0x00ff00Ϊ����ɫ����ɫ��ֵΪcolor=NOCOLOR
		  *p - ָ���ַ�����ָ��
*����   : ��
*/
void ShowString(unsigned int x, unsigned int y, unsigned int font, uint32_t color, uint32_t Bcolor, char* p);
void ShowCharc(unsigned int x, unsigned int y, unsigned int font, uint32_t color, uint32_t Bcolor, char a,char mode);
#endif

/******************************* ����������� *********************************/
