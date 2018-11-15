/******************************* 广州天码电子 *********************************
 * 文件名   ：main.c        
 * 作者     ：天码电子
 * 版本     ：V01
 * 完成日期 ：2014-05-26 
 * 描述     ：实现在模组显示字符串
 * 函数列表 ：
               void ShowString(unsigned int x, 
			                   unsigned int y, 
							   unsigned int font, 
							   uint32_t color, 
							   uint32_t Bcolor, 
							   char* p);

 * 修改记录 ：|    作者    |   日期    |    版本    |    描述    | 				
*******************************************************************************/

#ifndef _SHOWTEXT_H_
#define _SHOWTEXT_H_

#include "stm32f10x.h"

//字体尺寸参数宏定义
#define FONT0816  0x01   //size: w=8, h=16
#define FONT1632  0X02   //size: w=16, h=32
#define FONT2448  0X03   //size: w=24, h=48
#define FONT3264  0X04   //size: w=32, h=64 
#define FONT4080  0X05   //size: w=40, h=80
#define FONT4896  0X06   //size: w=48, h=96

//色彩宏定义
#define NOCOLOR 0X1000000  //无色
#define RED    0XFF0000
#define GREEN  0X00FF00
#define BLUE   0X0000FF
#define YELLOW 0xFFFF00
 


/*
*函数名 : ShowString
*描述   : 显示一串字符，（注意 不会自动换行）
*参数   : x - 起始坐标水平方向值
		  y - 起始坐标垂直方向值
		  font - 字体尺寸参数 详见上面的字体尺寸参数宏定义
		  color - 字符颜色, 如：color=0xFF0000为纯红色, color=0x00ff00为纯绿色，无色赋值为color=NOCOLOR
		  Bcolor - 字符背景颜色，如：color=0xFF0000为纯红色, color=0x00ff00为纯绿色，无色赋值为color=NOCOLOR
		  *p - 指向字符串的指针
*返回   : 无
*/
void ShowString(unsigned int x, unsigned int y, unsigned int font, uint32_t color, uint32_t Bcolor, char* p);
void ShowCharc(unsigned int x, unsigned int y, unsigned int font, uint32_t color, uint32_t Bcolor, char a,char mode);
#endif

/******************************* 广州天码电子 *********************************/
