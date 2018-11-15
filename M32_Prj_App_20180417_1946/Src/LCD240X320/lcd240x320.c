#include "tools.h"
#include "font.h"
#include "lcd240x320.h"
//#include "bsp_timer.h"
#include "user_gpio_def.h"

#define   LCD_DAT_OUT   GPIOB->CRH=(GPIOB->CRH&(~(0x000000FF<<20)))|0x00000038<<20 //输出模式
#define   LCD_DAT_IN    GPIOB->CRH=(GPIOB->CRH&(~(0x000000FF<<20)))|0x00000083<<20 //输入模式

u16 BACK_COLOR, POINT_COLOR;   //背景色，画笔色
u8 SysStatus; //All-bits==0: OK(正常); bit0==1: Error(2828 id error); bit1==1: BigCurrent(大电流); bit2~7: reserved

void LCD_Write(unsigned char val){

if(val & 0x80)GPIOB->BSRR = GPIO_Pin_15;
	else GPIOB->BRR = GPIO_Pin_15;
	GPIOB->BRR = GPIO_Pin_14; GPIOB->BSRR = GPIO_Pin_14;  //bit7
	
		if(val & 0x40)GPIOB->BSRR = GPIO_Pin_15;
	else GPIOB->BRR = GPIO_Pin_15;
	GPIOB->BRR = GPIO_Pin_14; GPIOB->BSRR = GPIO_Pin_14;  //bit6
	
		if(val & 0x20)GPIOB->BSRR = GPIO_Pin_15;
	else GPIOB->BRR = GPIO_Pin_15;
	GPIOB->BRR = GPIO_Pin_14; GPIOB->BSRR = GPIO_Pin_14;  //bit5
	
		if(val & 0x10)GPIOB->BSRR = GPIO_Pin_15;
	else GPIOB->BRR = GPIO_Pin_15;
	GPIOB->BRR = GPIO_Pin_14; GPIOB->BSRR = GPIO_Pin_14;  //bit4
	
		if(val & 0x08)GPIOB->BSRR = GPIO_Pin_15;
	else GPIOB->BRR = GPIO_Pin_15;
	GPIOB->BRR = GPIO_Pin_14; GPIOB->BSRR = GPIO_Pin_14;  //bit3
	
		if(val & 0x04)GPIOB->BSRR = GPIO_Pin_15;
	else GPIOB->BRR = GPIO_Pin_15;
	GPIOB->BRR = GPIO_Pin_14; GPIOB->BSRR = GPIO_Pin_14;  //bit2
	
		if(val & 0x02)GPIOB->BSRR = GPIO_Pin_15;
	else GPIOB->BRR = GPIO_Pin_15;
	GPIOB->BRR = GPIO_Pin_14; GPIOB->BSRR = GPIO_Pin_14;  //bit1
	
		if(val & 0x01)GPIOB->BSRR = GPIO_Pin_15;
	else GPIOB->BRR = GPIO_Pin_15;
	GPIOB->BRR = GPIO_Pin_14; GPIOB->BSRR = GPIO_Pin_14;  //bit0

}

void LCD_CtrlWrite(unsigned char val) {
//	char i;
	LCD_DAT_OUT;
	O_LCD240x320_SCK(0);
	O_LCD240x320_CS(0);
	O_LCD240x320_SDI(0);
	O_LCD240x320_SCK(0);
	O_LCD240x320_SCK(1);        
  LCD_Write(val);   
	O_LCD240x320_CS(1);
	LCD_DAT_IN;
}

void LCD_DataWrite(unsigned char val) {
//	char i;
	LCD_DAT_OUT;
	O_LCD240x320_SCK(0);
	O_LCD240x320_CS(0);
	O_LCD240x320_SDI(1);
	O_LCD240x320_SCK(0);
	O_LCD240x320_SCK(1);      
  LCD_Write(val);
	O_LCD240x320_CS(1);
	LCD_DAT_IN;
}

void LCD_WR_DATA8(char da) //发送数据-8位参数
{
    //O_LCD_DC(1);
	//LCD_Writ_Bus(da);
	
	LCD_DataWrite(da);
}
 void LCD_WR_DATA(int da)
{
    //O_LCD_DC(1);
	//LCD_Writ_Bus(da>>8);
	//LCD_Writ_Bus(da);
	
	LCD_DataWrite(da>>8);
	LCD_DataWrite(da);
}
void LCD_WR_REG(char da)	 
{
    //O_LCD_DC(0);
	//LCD_Writ_Bus(da);
	
	LCD_CtrlWrite(da);
}
 void LCD_WR_REG_DATA(int reg,int da)
{
    LCD_WR_REG(reg);
	LCD_WR_DATA(da);
}
void Address_set(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2)
{  
   LCD_WR_REG(0x2a);
   LCD_WR_DATA8(x1>>8);
   LCD_WR_DATA8(x1);
   LCD_WR_DATA8(x2>>8);
   LCD_WR_DATA8(x2);
  
   LCD_WR_REG(0x2b);
   LCD_WR_DATA8(y1>>8);
   LCD_WR_DATA8(y1);
   LCD_WR_DATA8(y2>>8);
   LCD_WR_DATA8(y2);

   LCD_WR_REG(0x2C);

}
void Lcd240x320_Init(void)
{   BACK_COLOR=BLACK;//BLACK;
    POINT_COLOR=WHITE;//RED;//WHITE; 

	O_LCD240x320_CS(1);
	
	O_LCD240x320_REST(1);
	delayms(20);
	O_LCD240x320_REST(0);
	delayms(50);
	O_LCD240x320_REST(1);
	delayms(50);

LCD_CtrlWrite(0x01);// Software Reset 
        delayms(20); 
 
        LCD_CtrlWrite(0x11);//Sleep Out 
        delayms(20); 
 //************* Start Initial Sequence **********//
LCD_CtrlWrite(0xCF);
LCD_DataWrite(0x00);
LCD_DataWrite(0x99);
LCD_DataWrite(0X30);


LCD_CtrlWrite(0xED);
LCD_DataWrite(0x67);
LCD_DataWrite(0x03);
LCD_DataWrite(0X12);
LCD_DataWrite(0X81);


LCD_CtrlWrite(0xE8);
LCD_DataWrite(0x85);
LCD_DataWrite(0x01);
LCD_DataWrite(0x78);


LCD_CtrlWrite(0xCB);
LCD_DataWrite(0x39);
LCD_DataWrite(0x2C);
LCD_DataWrite(0x00);
LCD_DataWrite(0x34);
LCD_DataWrite(0x02);


LCD_CtrlWrite(0xF7);


LCD_DataWrite(0x20);


LCD_CtrlWrite(0xEA);
LCD_DataWrite(0x00);
LCD_DataWrite(0x00);


LCD_CtrlWrite(0xC0);
LCD_DataWrite(0x25);


LCD_CtrlWrite(0xC1);
LCD_DataWrite(0x10);


LCD_CtrlWrite(0xC5);
LCD_DataWrite(0x40);
LCD_DataWrite(0x3F);

LCD_CtrlWrite(0xC7);
LCD_DataWrite(0xB0);

LCD_CtrlWrite(0xB6); // Display Function Control
LCD_DataWrite(0x0A);
LCD_DataWrite(0x82);

LCD_CtrlWrite(0x36);
LCD_DataWrite(0x48);

LCD_CtrlWrite(0x3A);
LCD_DataWrite(0x55);


LCD_CtrlWrite(0xF2);
LCD_DataWrite(0x00);


LCD_CtrlWrite(0x26);
LCD_DataWrite(0x01);

//Set Gamma
LCD_CtrlWrite(0xE0);
LCD_DataWrite(0x0F);
LCD_DataWrite(0x27);
LCD_DataWrite(0x23);
LCD_DataWrite(0x0B);
LCD_DataWrite(0x0F);
LCD_DataWrite(0x05);
LCD_DataWrite(0x54);
LCD_DataWrite(0x74);
LCD_DataWrite(0x45);
LCD_DataWrite(0x0A);
LCD_DataWrite(0x17);
LCD_DataWrite(0x0A);
LCD_DataWrite(0x1C);
LCD_DataWrite(0x0E);
LCD_DataWrite(0x08);


LCD_CtrlWrite(0XE1);
LCD_DataWrite(0x08);
LCD_DataWrite(0x1A);
LCD_DataWrite(0x1E);
LCD_DataWrite(0x03);
LCD_DataWrite(0x0F);
LCD_DataWrite(0x05);
LCD_DataWrite(0x2E);
LCD_DataWrite(0x25);
LCD_DataWrite(0x3B);
LCD_DataWrite(0x01);
LCD_DataWrite(0x06);
LCD_DataWrite(0x05);
LCD_DataWrite(0x25);
LCD_DataWrite(0x33);
LCD_DataWrite(0x0F);
LCD_Clear(BACK_COLOR);

//delayms(100);
LCD_CtrlWrite(0x29);//display on 
}
//清屏函数
//Color:要清屏的填充色
void LCD_Clear(u16 Color)
{
	u8 VH,VL;
	u16 i,j;
	VH=Color>>8;
	VL=Color;	
	Address_set(0,0,LCD_W-1,LCD_H-1);
    for(i=0;i<LCD_W;i++) {
		for (j=0;j<LCD_H;j++) {
			LCD_WR_DATA8(VH);
			LCD_WR_DATA8(VL);
		}
	}
}
void LCD_Logo_Disp(void) {
	u32 i;
	
	Address_set(0,0,LCD_W-1,LCD_H-1);
	
//	//240 * 114
//    for(i=0;i<LCD_W*84;i++) {
//		LCD_WR_DATA(BACK_COLOR);
//	}
//	//240 * 94
//	for(i=0;i<LCD_W*94;i++) {
//		LCD_WR_DATA(Logo_TST[i]==0xffff?BACK_COLOR:Logo_TST[i]);
//	}
//	//240 * 112
//	for(i=0;i<LCD_W*142;i++) {
//		LCD_WR_DATA(BACK_COLOR);
//	}
	
	//240 * 103
    for(i=0;i<LCD_W*68;i++) {
		LCD_WR_DATA(BACK_COLOR);
	}
	//240 * 105
	for(i=0;i<LCD_W*105;i++) {
		LCD_WR_DATA(Logo_TST[i]);
	}
	//240 * 112
	for(i=0;i<LCD_W*147;i++) {
		LCD_WR_DATA(BACK_COLOR);
	}
}

//画点
//PixelColor:此点的颜色
void LCD_DrawPoint(u16 x, u16 y, u16 PixelColor)
{
	Address_set(x,y,x,y);//设置光标位置 
	LCD_WR_DATA(PixelColor); 	    
} 	 
//画一个大点
//PixelColor:此点的颜色
void LCD_DrawPoint_big(u16 x,u16 y, u16 PixelColor)
{
	LCD_Fill(x-1,y-1,x+1,y+1,PixelColor);
} 
//在指定区域内填充指定颜色
//区域大小:
//  (xend-xsta)*(yend-ysta)
void LCD_Fill(u16 xsta,u16 ysta,u16 xend,u16 yend,u16 color)
{          
	u16 i,j; 
	Address_set(xsta,ysta,xend,yend);      //设置光标位置 
	for(i=ysta;i<=yend;i++)
	{													   	 	
		for(j=xsta;j<=xend;j++)LCD_WR_DATA(color);//设置光标位置 	    
	} 					  	    
}  
//画线
//x1,y1:起点坐标
//x2,y2:终点坐标  
void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2, u16 PixelColor)
{
	u16 t; 
	int xerr=0,yerr=0,delta_x,delta_y,distance; 
	int incx,incy,uRow,uCol; 

	delta_x=x2-x1; //计算坐标增量 
	delta_y=y2-y1; 
	uRow=x1; 
	uCol=y1; 
	if(delta_x>0)incx=1; //设置单步方向 
	else if(delta_x==0)incx=0;//垂直线 
	else {incx=-1;delta_x=-delta_x;} 
	if(delta_y>0)incy=1; 
	else if(delta_y==0)incy=0;//水平线 
	else{incy=-1;delta_y=-delta_y;} 
	if( delta_x>delta_y)distance=delta_x; //选取基本增量坐标轴 
	else distance=delta_y; 
	for(t=0;t<=distance+1;t++ )//画线输出 
	{  
		LCD_DrawPoint(uRow, uCol, PixelColor);//画点 
		xerr+=delta_x ; 
		yerr+=delta_y ; 
		if(xerr>distance) 
		{ 
			xerr-=distance; 
			uRow+=incx; 
		} 
		if(yerr>distance) 
		{ 
			yerr-=distance; 
			uCol+=incy; 
		} 
	}  
}    
//画矩形
void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2, u16 PixelColor)
{
	LCD_DrawLine(x1,y1,x2,y1, PixelColor);
	LCD_DrawLine(x1,y1,x1,y2, PixelColor);
	LCD_DrawLine(x1,y2,x2,y2, PixelColor);
	LCD_DrawLine(x2,y1,x2,y2, PixelColor);
}
//在指定位置画一个指定大小的圆
//(x,y):中心点
//r    :半径
void Draw_Circle(u16 x0, u16 y0, u8 r, u16 PixelColor)
{
	int a,b;
	int di;
	a=0;b=r;	  
	di=3-(r<<1);             //判断下个点位置的标志
	while(a<=b)
	{
		LCD_DrawPoint(x0-b, y0-a, PixelColor);             //3           
		LCD_DrawPoint(x0+b, y0-a, PixelColor);             //0           
		LCD_DrawPoint(x0-a, y0+b, PixelColor);             //1       
		LCD_DrawPoint(x0-b, y0-a, PixelColor);             //7           
		LCD_DrawPoint(x0-a, y0-b, PixelColor);             //2             
		LCD_DrawPoint(x0+b, y0+a, PixelColor);             //4               
		LCD_DrawPoint(x0+a, y0-b, PixelColor);             //5
		LCD_DrawPoint(x0+a, y0+b, PixelColor);             //6 
		LCD_DrawPoint(x0-b, y0+a, PixelColor);             
		a++;
		//使用Bresenham算法画圆     
		if(di<0)di +=4*a+6;	  
		else
		{
			di+=10+4*(a-b);   
			b--;
		} 
		LCD_DrawPoint(x0+a, y0+b, PixelColor);
	}
} 
//在指定位置显示一个字符

//num:要显示的字符:" "--->"~"
//mode:叠加方式(1)还是非叠加方式(0)
//在指定位置显示一个字符

//num:要显示的字符:" "--->"~"

//mode:叠加方式(1)还是非叠加方式(0)
void LCD_ShowChar(u16 x,u16 y,u8 num,u8 mode,u16 FrontColor)
{
    u8 temp;
    u8 pos,t;
	u16 x0=x;
	u16 PixelColor;
	
	x = x + 4;
	y = y + 4;
	
    if(x>LCD_W-8||y>LCD_H-16)return;	    
	//设置窗口		   
	num=num-' ';//得到偏移后的值
	Address_set(x,y,x+8-1,y+16-1);      //设置光标位置 
	if(!mode) //非叠加方式
	{
		for(pos=0;pos<16;pos++)
		{ 
			temp=asc2_1608[(u16)num*16+pos];		 //调用1608字体
			for(t=0;t<8;t++)
		    {
					if(temp&0x01)
						PixelColor = FrontColor;
					else
						PixelColor = BACK_COLOR;
					LCD_WR_DATA(PixelColor);	
					temp>>=1; 
					x++;
		    }
			x=x0;
			y++;
		}	
	}else//叠加方式
	{
		PixelColor = FrontColor;
		for(pos=0;pos<16;pos++)
		{
		    temp=asc2_1608[(u16)num*16+pos];		 //调用1608字体
			for(t=0;t<8;t++)
		    {                 
		        if(temp&0x01)
					LCD_DrawPoint(x+t, y+pos, PixelColor);//画一个点     
		        temp>>=1; 
		    }
		}
	} 	   	 	  
}

void LCD_ShowHanziChar(u16 x,u16 y,u8 num,u8 mode, u16 FrontColor, u16 BackColor)
{
    u8 temp;
    u8 pos,t;
	u16 x0=x;
	u16 PixelColor;
	
	x = x + 4;
	y = y + 4;
		
    if(x>LCD_W-16||y>LCD_H-16)return;	    
	//设置窗口		   
	//num=num-' ';//得到偏移后的值
	Address_set(x,y,x+16-1,y+16-1);      //设置光标位置 
	if(!mode) //非叠加方式
	{
		for(pos=0;pos<16;pos++) {
			
			temp=Hanzi[(u16)num*32+pos*2];		 //调用汉字字体, 汉字每个字16x16占32个字节
			for(t=0;t<8;t++) {
				if(temp&0x80)
					PixelColor = FrontColor;
				else
					PixelColor = BackColor;
				LCD_WR_DATA(PixelColor);	
				temp<<=1; 
				x++;
		  }
			temp=Hanzi[(u16)num*32+pos*2+1];		 //调用汉字字体
			for(t=8;t<16;t++) {
				if(temp&0x80)
					PixelColor = FrontColor;
				else
					PixelColor = BackColor;
				LCD_WR_DATA(PixelColor);	
				temp<<=1; 
				x++;
		  }
			x=x0;
			y++;
		}	
	}else//叠加方式
	{
		PixelColor = FrontColor;
		for(pos=0;pos<16;pos++)
		{
		  temp=Hanzi[(u16)num*32+pos*2];		 //调用汉字字体
			for(t=0;t<8;t++) {                 
				if(temp&0x80)
					LCD_DrawPoint(x+t, y+pos, PixelColor);//画一个点     
				temp<<=1; 
			}
			temp=Hanzi[(u16)num*32+pos*2+1];		 //调用1608字体
			for(t=8;t<16;t++) {                 
				if(temp&0x80)
					LCD_DrawPoint(x+t, y+pos, PixelColor);//画一个点     
				temp<<=1; 
			}
		}
	}
}

void LCD_ShowHanzi24x24Char(u16 x,u16 y,u8 num,u8 mode, u16 FrontColor, u16 BackColor)
{
    u8 temp;
    u8 pos,t,i;
	u16 x0=x;
	u16 PixelColor;  
	
	x = x + 4;
	    
    if(x>LCD_W-24||y>LCD_H-24)return;	    
	//设置窗口		   
	//num=num-' ';//得到偏移后的值
	Address_set(x,y,x+24-1,y+24-1);      //设置光标位置 
	if(!mode) //非叠加方式
	{
		for(pos=0;pos<24;pos++) {
			
			for(i=0; i<3; i++) {
				temp=HanziBig[(u16)num*32 + pos*2 + i];		 //调用汉字字体, 汉字每个字24x24占24*3个字节
				for(t=i*8;t<(i+1)*8;t++) {
					if(temp&0x80)
						PixelColor = FrontColor;
					else
						PixelColor = BackColor;
					LCD_WR_DATA(PixelColor);	
					temp<<=1; 
					x++;
				}
			}
			x=x0;
			y++;
		}	
	}else//叠加方式
	{
		PixelColor = FrontColor;
		for(pos=0;pos<16;pos++)
		{
			for(i=0; i<3; i++) {
				temp=HanziBig[(u16)num*32+pos*2+i];		 //调用汉字字体
				for(t=i*8;t<(i+1)*8;t++) {
					if(temp&0x80)
						LCD_DrawPoint(x+t, y+pos, PixelColor);//画一个点     
					temp<<=1; 
				}
			}
		}
	}
}

//m^n函数
u32 mypow(u8 m,u8 n)
{
	u32 result=1;	 
	while(n--)result*=m;    
	return result;
}			 
//显示2个数字
//x,y :起点坐标	 
//len :数字的位数
//color:颜色
//num:数值(0~4294967295);	
void LCD_ShowNum(u16 x,u16 y,u32 num,u8 len)
{         	
	u8 t,temp;
	u8 enshow=0;
	num=(u16)num;
	for(t=0;t<len;t++)
	{
		temp=(num/mypow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				LCD_ShowChar(x+8*t,y,' ',0, POINT_COLOR);
				continue;
			}else enshow=1; 
		 	 
		}
	 	LCD_ShowChar(x+8*t,y,temp+48,0, POINT_COLOR); 
	}
} 
void DispNumber(int x,int y,int value,U16 len,U16 cValue)
{
	int  k;
	int  xx,yy;
	int  id;
	//int  tValue;
	char pStr[16];

	if(len>16) len = 16;

	for(k=0;k<len;k++)
	{
		pStr[len-1-k] = value%10+0x30;
		value = value/10;
	}

	if(len<1) return ;
	id = 0;
	xx = x;
	yy = y;
	while(1)
	{
		
		if((xx+8)>240)
		{
			yy += 16;
			xx = x;
		}
		LCD_ShowChar(xx,yy,pStr[id++],0,cValue);
		if(id>=len) break;
		xx +=8;	
	}
}

void DispHexChar(int x,int y,int value,U16 len,U16 cValue)
{
	int  k;
	int  xx,yy;
	int  id;
	char tCH;
	char pStr[16];

	if(len>16) len = 16;

	for(k=0;k<8;k++)
	{
		tCH = (value>>(k*4))&0x0F;
		if(tCH<10)  
			pStr[k] = tCH+0x30;
		else  pStr[k] = tCH-10+'A';
	}

	if(len<1) return ;
	if(len>8) len = 8;
	id = 0;
	xx = x;
	yy = y;
	
	while(1)
	{
		
		if((xx+8)>240)
		{
			yy += 16;
			xx = x;
		}
    LCD_ShowChar(xx,yy,pStr[len-1-id],0, cValue);
		
		id++;
		if(id>=len) break;
		xx +=8;	
	}
}
//显示2个数字
//x,y:起点坐标
//num:数值(0~99);	 
void LCD_Show2Num(u16 x,u16 y,u16 num,u8 len)
{         	
	u8 t,temp;						   
	for(t=0;t<len;t++)
	{
		temp=(num/mypow(10,len-t-1))%10;
	 	LCD_ShowChar(x+8*t,y,temp+'0',0, POINT_COLOR); 
	}
} 
//显示字符串
//x,y:起点坐标  
//*p:字符串起始地址
//用16字体
void LCD_ShowString(u16 x,u16 y,const char *p, u16 FrontColor)
{  
UINT8 x1=x,y1=y;	
    while(*p!='\0')
    {       
        if((x1*8)>(LCD_W-12)){x1=x;y1+=1;}
        if((y1*16)>(LCD_H-20)){y1=x1=0;}
        LCD_ShowChar(x1*8,y1*16,*p,0, FrontColor);
        //x+=8;
        x1++;
        p++;
    }  
}



void DISP_WINDOWS(U16 xS,U16 yS,U16 xE,U16 yE)  
{ 
      //xS = xS+0x02;
	xE = xS+xE;
	//yS = yS+0x01;
	yE = yS+yE;
 
      LCD_CtrlWrite (0x2a);                         
      LCD_DataWrite( xS>>8); 
      LCD_DataWrite( xS&0xFF);                 
      LCD_DataWrite( xE>>8); 
      LCD_DataWrite( xE&0xFF);                   
   
      LCD_CtrlWrite (0x2b); 
      LCD_DataWrite( yS>>8);             
      LCD_DataWrite( yS&0xFF);                 
      LCD_DataWrite( yE>>8);             
      LCD_DataWrite( yE&0xFF);                     
 
      LCD_CtrlWrite (0x2C);                                        //Memory write   
} 

void Disp_Window(unsigned short x,unsigned short y, unsigned short width,unsigned short high,unsigned short cc)
{
      unsigned int i,j;
      
      DISP_WINDOWS(x,y,width-1,high-1);
      
      for(i=0;i<high;i++)
      {
            for(j=0;j<width;j++)
            {
                  LCD_DataWrite(cc>>8);
                  LCD_DataWrite(cc);
            }
      }
}

void Disp_Frame(unsigned short x,unsigned short y, unsigned short width,unsigned short high,unsigned short cc)
{
      U32 i,j;
      
      DISP_WINDOWS(x,y,width-1,high-1);
      
      for(j=0;j<width;j++)
      {
            LCD_DataWrite(cc>>8);
            LCD_DataWrite(cc);
      }
      
      for(i=1;i<high-1;i++)
      {
            LCD_DataWrite(cc>>8);
            LCD_DataWrite(cc);
            for(j=1;j<width-1;j++)
            {
                  LCD_DataWrite(BACK_COLOR>>8);
                  LCD_DataWrite(BACK_COLOR);
            }
            LCD_DataWrite(cc>>8);
            LCD_DataWrite(cc);
            
      }
      
      for(j=0;j<width;j++)
      {
            LCD_DataWrite(cc>>8);
            LCD_DataWrite(cc);
      }
}














