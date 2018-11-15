
#include "showtext.h" 
#include "ascii.h"
#include "lcd_drv.h"
#include "systick.h"

void delay(unsigned int i)
{
	while(i--);
}

static void ShowChar(unsigned int x, unsigned int y, unsigned int font, uint32_t color, uint32_t Bcolor, char a)
{
    unsigned int i,j;
	unsigned int wc, hc, xp;
	const unsigned char *p;

	p=ascii_char[(unsigned char)(a)];

	for(i = 0; i < 16; i++)
	{       
		for(hc = 0; hc < font; hc++)
		{
			Delay_10us(1);
			LcdDrvGotoXy(x, y);
			xp = x;
			a = *p;
		    for(j = 0; j < 8; j++)
			{
				for(wc = 0; wc < font; wc++)
				{
					++xp;
					if(a & 0x80)
					{
						if(color <= 0xffffff){LcdDrvWriteRgb(color);}	//0x00FF
						else {Delay_10us(0);LcdDrvGotoXy(xp, y);Delay_10us(0);}
					}
					else
					{
						if(Bcolor <= 0xffffff){LcdDrvWriteRgb(Bcolor);}
						else {Delay_10us(0);LcdDrvGotoXy(xp, y);Delay_10us(0);}
					}
				}
				a<<=1;
			}
			++y;
		}

		++p;
	}
}


void ShowCharc(unsigned int x, unsigned int y, unsigned int font, uint32_t color, uint32_t Bcolor, char a,char mode)
{
    unsigned int i,j;
	unsigned int wc, hc, xp;
	const unsigned char *p;

	p=ascii_char[(unsigned char)(a)];

	for(i = 0; i < 16; i++)
	{       
		for(hc = 0; hc < font; hc++)
		{
			Delay_10us(1);
			LcdDrvGotoXy(x, y);
			xp = x;
			a = *p;
		    for(j = 0; j < 8; j++)
			{
				for(wc = 0; wc < font; wc++)
				{
					++xp;
					if(a & 0x80)
					{
						if(color <= 0xffffff){LcdDrvWriteRgb(color);}
						else {Delay_10us(0);LcdDrvGotoXy(xp, y);Delay_10us(0);}
					}
					else	//mode
					{
						if(mode){	//1²»µþ¼Ó	
							if(Bcolor <= 0xffffff){LcdDrvWriteRgb(Bcolor);}
							else {Delay_10us(0);LcdDrvGotoXy(xp, y);Delay_10us(0);}
						}else{							
							{Delay_10us(0);LcdDrvGotoXy(xp, y);Delay_10us(0);}
						}
					}
				}
				a<<=1;
			}
			++y;
		}
		++p;
	}
}
void ShowString(unsigned int x, unsigned int y, unsigned int font, uint32_t color, uint32_t Bcolor, char* p)
{
	char a;
	Delay_ms(5);
	while((a=*p++)!=0){ShowChar(x, y, font, color, Bcolor, a); x += 8*font;}
}

