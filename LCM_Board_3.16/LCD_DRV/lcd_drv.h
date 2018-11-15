

#ifndef _LCD_DRV_H_
#define _LCD_DRV_H_

#include "stm32f10x.h"


#define DCLK_FALLING_EDGE 0	 //lcd��DCLK���½�����������
#define DCLK_RISING_EDGE  1	 //lcd��DCLK����������������
#define HSYNC_ACTIVE_LOW  0  //hsync����͵�ƽ��Ч
#define HSYNC_ACTIVE_HIGH 1  //hsync����ߵ�ƽ��Ч
#define VSYNC_ACTIVE_LOW  0  //vsync����͵�ƽ��Ч
#define VSYNC_ACTIVE_HIGH 1  //vsync����ߵ�ƽ��Ч
#define DE_ACTIVE_LOW     1  //DE�͵�ƽ��Ч
#define DE_ACTIVE_HIGH    0  //DE�ߵ�ƽ��Ч


#define MIPI_SINGLE 0X00	  //����1,2,3,4LANE�Ľӿ�
#define MIPI_DOUBLE 0X01      //��8LANE	MIPI�ӿ�



extern unsigned int Lcd_DCLK;	  //DCLKƵ������ ��λΪMHz ���ֵ150MH����
extern unsigned int Lcd_LCDH;	  //�ֱ���.��
extern unsigned int Lcd_LCDV;	  //�ֱ���.��
extern unsigned int Lcd_HBPD;
extern unsigned int Lcd_HFPD;
extern unsigned int Lcd_HSPW;
extern unsigned int Lcd_VBPD;
extern unsigned int Lcd_VFPD;
extern unsigned int Lcd_VSPW;
extern unsigned int Lcd_DCLK_EDGE;		//lcd��������ʱ��DCLK����	 ��������ĺ궨������ֵ
extern unsigned int Lcd_HSYNC_POLARITY;  //HSYNC���弫��			  	 ��������ĺ궨������ֵ
extern unsigned int Lcd_VSYNC_POLARITY;  //VSYNC���弫��			  	 ��������ĺ궨������ֵ
extern unsigned int Lcd_DE_POLARITY;	 //DE�ź���Ч��ƽ			 ��������ĺ궨������ֵ

extern unsigned int Lcd_MODE;  //�ӿڷ�ʽ MIPI_8LANE �� MIPI_4LANE	 ��������ĺ궨������ֵ
                               //1,2,3,4LANE�Ķ���ֵΪMIPI_4LANE


/*---------------------------------------------------------------------*/
extern unsigned int MCU_Tsu;
extern void LcdDrvInit(void);						 //��ʼ�����򣬼ǵ��ȸ�ȫ�ֱ�����ֵ
extern void LcdDrvWriteData(uint8_t data); //LcdDrvWriteData
extern void LcdDrv_RGB_ON(void);	 				 
extern void LcdDrv_RGB_OFF(void); 
extern void LcdDrvGotoXy(unsigned int x,unsigned int y);  //����lcd����
extern void LcdDrvWriteRgb(unsigned int color);           //
extern void LcdDrvSetFrame(unsigned int frame);
extern void LcdDrvDisplayFrame(unsigned int frame);
#endif 

