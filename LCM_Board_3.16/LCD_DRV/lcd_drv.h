

#ifndef _LCD_DRV_H_
#define _LCD_DRV_H_

#include "stm32f10x.h"


#define DCLK_FALLING_EDGE 0	 //lcd在DCLK的下降沿锁存数据
#define DCLK_RISING_EDGE  1	 //lcd在DCLK的上升沿锁存数据
#define HSYNC_ACTIVE_LOW  0  //hsync脉冲低电平有效
#define HSYNC_ACTIVE_HIGH 1  //hsync脉冲高电平有效
#define VSYNC_ACTIVE_LOW  0  //vsync脉冲低电平有效
#define VSYNC_ACTIVE_HIGH 1  //vsync脉冲高电平有效
#define DE_ACTIVE_LOW     1  //DE低电平有效
#define DE_ACTIVE_HIGH    0  //DE高电平有效


#define MIPI_SINGLE 0X00	  //包含1,2,3,4LANE的接口
#define MIPI_DOUBLE 0X01      //即8LANE	MIPI接口



extern unsigned int Lcd_DCLK;	  //DCLK频率设置 单位为MHz 最大值150MH左右
extern unsigned int Lcd_LCDH;	  //分辨率.宽
extern unsigned int Lcd_LCDV;	  //分辨率.高
extern unsigned int Lcd_HBPD;
extern unsigned int Lcd_HFPD;
extern unsigned int Lcd_HSPW;
extern unsigned int Lcd_VBPD;
extern unsigned int Lcd_VFPD;
extern unsigned int Lcd_VSPW;
extern unsigned int Lcd_DCLK_EDGE;		//lcd锁存数据时的DCLK边沿	 请用上面的宏定义来赋值
extern unsigned int Lcd_HSYNC_POLARITY;  //HSYNC脉冲极性			  	 请用上面的宏定义来赋值
extern unsigned int Lcd_VSYNC_POLARITY;  //VSYNC脉冲极性			  	 请用上面的宏定义来赋值
extern unsigned int Lcd_DE_POLARITY;	 //DE信号有效电平			 请用上面的宏定义来赋值

extern unsigned int Lcd_MODE;  //接口方式 MIPI_8LANE 或 MIPI_4LANE	 请用上面的宏定义来赋值
                               //1,2,3,4LANE的都赋值为MIPI_4LANE


/*---------------------------------------------------------------------*/
extern unsigned int MCU_Tsu;
extern void LcdDrvInit(void);						 //初始化程序，记得先给全局变量赋值
extern void LcdDrvWriteData(uint8_t data); //LcdDrvWriteData
extern void LcdDrv_RGB_ON(void);	 				 
extern void LcdDrv_RGB_OFF(void); 
extern void LcdDrvGotoXy(unsigned int x,unsigned int y);  //设置lcd坐标
extern void LcdDrvWriteRgb(unsigned int color);           //
extern void LcdDrvSetFrame(unsigned int frame);
extern void LcdDrvDisplayFrame(unsigned int frame);
#endif 

