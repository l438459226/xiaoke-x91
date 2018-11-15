#ifndef __LCD240x320_H
#define __LCD240x320_H		

#include "BasicDataType.h"
#include "stm32f10x.h"

//����LCD�ĳߴ�	
#define LCD_W 240
#define LCD_H 320



extern  u16 BACK_COLOR, POINT_COLOR;   //����ɫ������ɫ
extern  u8 SysStatus;

#define SYS_STATUS_2828ERR    (0x01)
#define SYS_STATUS_BIGCURRENT (0x02)

void Lcd240x320_Init(void); 
void LCD_Clear(u16 Color);
void LCD_Logo_Disp(void);

void Address_set(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2);
void LCD_WR_DATA8(char da);
void LCD_WR_DATA(int da);
void LCD_WR_REG(char da);

void LCD_DrawPoint(u16 x, u16 y, u16 PixelColor);//����
void LCD_DrawPoint_big(u16 x,u16 y, u16 PixelColor);//��һ�����
u16  LCD_ReadPoint(u16 x,u16 y); //����
void Draw_Circle(u16 x0, u16 y0, u8 r, u16 PixelColor);
void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2, u16 PixelColor);
void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2, u16 PixelColor);		   
void LCD_Fill(u16 xsta,u16 ysta,u16 xend,u16 yend,u16 color);
void LCD_ShowChar(u16 x,u16 y,u8 num,u8 mode,u16 FrontColor);//��ʾһ���ַ�

void LCD_ShowHanziChar(u16 x,u16 y,u8 num,u8 mode, u16 FrontColor, u16 BackColor);
void LCD_ShowHanzi24x24Char(u16 x,u16 y,u8 num,u8 mode, u16 FrontColor, u16 BackColor);
void DISP_WINDOWS(U16 xS,U16 yS,U16 xE,U16 yE);
void Disp_Window(unsigned short x,unsigned short y, unsigned short width,unsigned short high,unsigned short cc);
void Disp_Frame(unsigned short x,unsigned short y, unsigned short width,unsigned short high,unsigned short cc);
void DispNumber(int x,int y,int value,U16 len,U16 cValue);
void DispHexChar(int x,int y,int value,U16 len,U16 cValue);

void LCD_ShowNum(u16 x,u16 y,u32 num,u8 len);//��ʾ����
void LCD_Show2Num(u16 x,u16 y,u16 num,u8 len);//��ʾ2������
void LCD_ShowString(u16 x,u16 y,const char *p,u16 FrontColor);		 //��ʾһ���ַ���,16����




//������ɫ
#define WHITE         	 0xFFFF
#define BLACK         	 0x0000	  
#define BLUE         	 0x001F  
#define BRED             0XF81F
#define GRED 			 0XFFE0
#define GBLUE			 0X07FF
#define RED           	 0xF800
#define MAGENTA       	 0xF81F
#define GREEN         	 0x07E0
#define CYAN          	 0x7FFF
#define YELLOW        	 0xFFE0
#define BROWN 			 0XBC40 //��ɫ
#define BRRED 			 0XFC07 //�غ�ɫ
#define GRAY  			 0X8430 //��ɫ
//GUI��ɫ

#define DARKBLUE      	 0X01CF	//����ɫ
#define LIGHTBLUE      	 0X7D7C	//ǳ��ɫ  
#define GRAYBLUE       	 0X5458 //����ɫ
//������ɫΪPANEL����ɫ 
 
#define LIGHTGREEN     	 0X841F //ǳ��ɫ
#define LGRAY 			 0XC618 //ǳ��ɫ(PANNEL),���屳��ɫ

#define LGRAYBLUE        0XA651 //ǳ����ɫ(�м����ɫ)
#define LBBLUE           0X2B12 //ǳ����ɫ(ѡ����Ŀ�ķ�ɫ)


					  		 
#endif  
	 
	 



