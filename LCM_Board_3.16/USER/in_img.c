
#include "in_img.h"
#include "stm32f10x.h"
#include "systick.h"	 
#include "lcd_drv.h"
#include "ssd2828.h"


void Img_CT(void)
{
	unsigned int h;
	unsigned int v1_2;
	unsigned int v1_4,h1_4;

	for(v1_4=0;v1_4<Lcd_LCDV/4;v1_4++)
	{
		for(h=0;h<Lcd_LCDH;h++)
		{ 
			LcdDrvWriteData(0x80);
			LcdDrvWriteData(0x80);
			LcdDrvWriteData(0x80); 
		}
	}

	for(v1_2=0;v1_2<Lcd_LCDV/4;v1_2++)
	{
		for(h1_4=0;h1_4<Lcd_LCDH/4;h1_4++)
		{
			LcdDrvWriteData(0x80);
			LcdDrvWriteData(0x80);
			LcdDrvWriteData(0x80); 

		} 

	    for(h1_4=0;h1_4<Lcd_LCDH/4;h1_4++)
		{   
			LcdDrvWriteData(0x00); 
			LcdDrvWriteData(0x00); 
			LcdDrvWriteData(0x00); 
			LcdDrvWriteData(0x00);
			LcdDrvWriteData(0x00); 
			LcdDrvWriteData(0x00);
		} 
	    for(h1_4=0;h1_4<Lcd_LCDH/4;h1_4++)
		{   
			LcdDrvWriteData(0x80);
			LcdDrvWriteData(0x80);
			LcdDrvWriteData(0x80); 
		} 
	}

	for(v1_2=0;v1_2<Lcd_LCDV/4;v1_2++)
	{
		for(h1_4=0;h1_4<Lcd_LCDH/4;h1_4++)
		{
			LcdDrvWriteData(0x80);
			LcdDrvWriteData(0x80);
			LcdDrvWriteData(0x80);
		} 

	    for(h1_4=0;h1_4<Lcd_LCDH/4;h1_4++)
		{   
			LcdDrvWriteData(0x00); 
			LcdDrvWriteData(0x00);
			LcdDrvWriteData(0x00); 
			LcdDrvWriteData(0x00);
			LcdDrvWriteData(0x00); 
			LcdDrvWriteData(0x00); 
		} 
	    for(h1_4=0;h1_4<Lcd_LCDH/4;h1_4++)
		{   
			LcdDrvWriteData(0x80);
			LcdDrvWriteData(0x80);
			LcdDrvWriteData(0x80); 
		} 
	}

	for(v1_4=0;v1_4<Lcd_LCDV/4;v1_4++)
	{
		for(h=0;h<Lcd_LCDH;h++)
		{ 
			LcdDrvWriteData(0x80);
			LcdDrvWriteData(0x80);
			LcdDrvWriteData(0x80);  

		}			
	}

}

void Flicker(void)
{
    unsigned int i, j;

	for(j=0;j<Lcd_LCDV;j++)
	{	
		for(i=0;i<Lcd_LCDH/2;i++)
		{
			LcdDrvWriteData(0x7f);LcdDrvWriteData(0x00);LcdDrvWriteData(0x7f);
			LcdDrvWriteData(0x00);LcdDrvWriteData(0x7f);LcdDrvWriteData(0x00);
		}
	}
}


void Img_Full(unsigned char r, unsigned char g, unsigned char b)
{
    unsigned int i, j;

	for(j=0;j<Lcd_LCDV;j++)
	{	
		for(i=0;i<Lcd_LCDH;i++)
		{
			LcdDrvWriteData(r);
			LcdDrvWriteData(g);
			LcdDrvWriteData(b);
		}
	}
}

void Img_Chcker58()
{
	unsigned int i;
	unsigned int y;

//	for(j=0;j<4;j++)
	{
		for(y=0;y<Lcd_LCDV*1/8;y++)
		{
			for(i=0	;i<Lcd_LCDH/5;	i++){LcdDrvWriteData(0x00);LcdDrvWriteData(0x00);LcdDrvWriteData(0x00);}
			for(	;i<Lcd_LCDH*2/5;i++){LcdDrvWriteData(0xff);LcdDrvWriteData(0xff);LcdDrvWriteData(0xff);}
			for(	;i<Lcd_LCDH*3/5;i++){LcdDrvWriteData(0x00);LcdDrvWriteData(0x00);LcdDrvWriteData(0x00);}
			for(	;i<Lcd_LCDH*4/5;i++){LcdDrvWriteData(0xff);LcdDrvWriteData(0xff);LcdDrvWriteData(0xff);}
			for(	;i<Lcd_LCDH;	i++){LcdDrvWriteData(0x00);LcdDrvWriteData(0x00);LcdDrvWriteData(0x00);}
		}

		for(   ;y<Lcd_LCDV*2/8;y++)
		{
			for(i=0	;i<Lcd_LCDH/5;	i++){LcdDrvWriteData(0xff);LcdDrvWriteData(0xff);LcdDrvWriteData(0xff);}
			for(	;i<Lcd_LCDH*2/5;i++){LcdDrvWriteData(0x00);LcdDrvWriteData(0x00);LcdDrvWriteData(0x00);}
			for(	;i<Lcd_LCDH*3/5;i++){LcdDrvWriteData(0xff);LcdDrvWriteData(0xff);LcdDrvWriteData(0xff);}
			for(	;i<Lcd_LCDH*4/5;i++){LcdDrvWriteData(0x00);LcdDrvWriteData(0x00);LcdDrvWriteData(0x00);}
			for(	;i<Lcd_LCDH;	i++){LcdDrvWriteData(0xff);	LcdDrvWriteData(0xff);LcdDrvWriteData(0xff);}
		}

		for( ;y<Lcd_LCDV*3/8;y++)
		{
			for(i=0	;i<Lcd_LCDH/5;	i++){LcdDrvWriteData(0x00);LcdDrvWriteData(0x00);LcdDrvWriteData(0x00);}
			for(	;i<Lcd_LCDH*2/5;i++){LcdDrvWriteData(0xff);LcdDrvWriteData(0xff);LcdDrvWriteData(0xff);}
			for(	;i<Lcd_LCDH*3/5;i++){LcdDrvWriteData(0x00);LcdDrvWriteData(0x00);LcdDrvWriteData(0x00);}
			for(	;i<Lcd_LCDH*4/5;i++){LcdDrvWriteData(0xff);LcdDrvWriteData(0xff);LcdDrvWriteData(0xff);}
			for(	;i<Lcd_LCDH;	i++){LcdDrvWriteData(0x00);LcdDrvWriteData(0x00);LcdDrvWriteData(0x00);}
		}

		for(   ;y<Lcd_LCDV*4/8;y++)
		{
			for(i=0	;i<Lcd_LCDH/5;	i++){LcdDrvWriteData(0xff);LcdDrvWriteData(0xff);LcdDrvWriteData(0xff);}
			for(	;i<Lcd_LCDH*2/5;i++){LcdDrvWriteData(0x00);LcdDrvWriteData(0x00);LcdDrvWriteData(0x00);}
			for(	;i<Lcd_LCDH*3/5;i++){LcdDrvWriteData(0xff);LcdDrvWriteData(0xff);LcdDrvWriteData(0xff);}
			for(	;i<Lcd_LCDH*4/5;i++){LcdDrvWriteData(0x00);LcdDrvWriteData(0x00);LcdDrvWriteData(0x00);}
			for(	;i<Lcd_LCDH;	i++){LcdDrvWriteData(0xff);	LcdDrvWriteData(0xff);LcdDrvWriteData(0xff);}
		}

		for( ;y<Lcd_LCDV*5/8;y++)
		{
			for(i=0	;i<Lcd_LCDH/5;	i++){LcdDrvWriteData(0x00);LcdDrvWriteData(0x00);LcdDrvWriteData(0x00);}
			for(	;i<Lcd_LCDH*2/5;i++){LcdDrvWriteData(0xff);LcdDrvWriteData(0xff);LcdDrvWriteData(0xff);}
			for(	;i<Lcd_LCDH*3/5;i++){LcdDrvWriteData(0x00);LcdDrvWriteData(0x00);LcdDrvWriteData(0x00);}
			for(	;i<Lcd_LCDH*4/5;i++){LcdDrvWriteData(0xff);LcdDrvWriteData(0xff);LcdDrvWriteData(0xff);}
			for(	;i<Lcd_LCDH;	i++){LcdDrvWriteData(0x00);LcdDrvWriteData(0x00);LcdDrvWriteData(0x00);}
		}

		for(   ;y<Lcd_LCDV*6/8;y++)
		{
			for(i=0	;i<Lcd_LCDH/5;	i++){LcdDrvWriteData(0xff);LcdDrvWriteData(0xff);LcdDrvWriteData(0xff);}
			for(	;i<Lcd_LCDH*2/5;i++){LcdDrvWriteData(0x00);LcdDrvWriteData(0x00);LcdDrvWriteData(0x00);}
			for(	;i<Lcd_LCDH*3/5;i++){LcdDrvWriteData(0xff);LcdDrvWriteData(0xff);LcdDrvWriteData(0xff);}
			for(	;i<Lcd_LCDH*4/5;i++){LcdDrvWriteData(0x00);LcdDrvWriteData(0x00);LcdDrvWriteData(0x00);}
			for(	;i<Lcd_LCDH;	i++){LcdDrvWriteData(0xff);	LcdDrvWriteData(0xff);LcdDrvWriteData(0xff);}
		}

		for(   ;y<Lcd_LCDV*7/8;y++)
		{
			for(i=0	;i<Lcd_LCDH/5;	i++){LcdDrvWriteData(0x00);LcdDrvWriteData(0x00);LcdDrvWriteData(0x00);}
			for(	;i<Lcd_LCDH*2/5;i++){LcdDrvWriteData(0xff);LcdDrvWriteData(0xff);LcdDrvWriteData(0xff);}
			for(	;i<Lcd_LCDH*3/5;i++){LcdDrvWriteData(0x00);LcdDrvWriteData(0x00);LcdDrvWriteData(0x00);}
			for(	;i<Lcd_LCDH*4/5;i++){LcdDrvWriteData(0xff);LcdDrvWriteData(0xff);LcdDrvWriteData(0xff);}
			for(	;i<Lcd_LCDH;	i++){LcdDrvWriteData(0x00);LcdDrvWriteData(0x00);LcdDrvWriteData(0x00);}
		}

		for(   ;y<Lcd_LCDV*8/8;y++)
		{
			for(i=0	;i<Lcd_LCDH/5;	i++){LcdDrvWriteData(0xff);LcdDrvWriteData(0xff);LcdDrvWriteData(0xff);}
			for(	;i<Lcd_LCDH*2/5;i++){LcdDrvWriteData(0x00);LcdDrvWriteData(0x00);LcdDrvWriteData(0x00);}
			for(	;i<Lcd_LCDH*3/5;i++){LcdDrvWriteData(0xff);LcdDrvWriteData(0xff);LcdDrvWriteData(0xff);}
			for(	;i<Lcd_LCDH*4/5;i++){LcdDrvWriteData(0x00);LcdDrvWriteData(0x00);LcdDrvWriteData(0x00);}
			for(	;i<Lcd_LCDH;	i++){LcdDrvWriteData(0xff);	LcdDrvWriteData(0xff);LcdDrvWriteData(0xff);}
		}
	}
}

void Img_Box(void)
{
	unsigned int x,y;
	for(y = 0; y < Lcd_LCDV; y++)
	{
		for(x = 0; x < Lcd_LCDH; x++)
		{
			if((y == 0) || (y == Lcd_LCDV - 1))
			{
				LcdDrvWriteData(0xff);LcdDrvWriteData(0xFF);LcdDrvWriteData(0xFF);	
			}

		 	else	if(x == 0)
			{
				LcdDrvWriteData(0xff);LcdDrvWriteData(0x00);LcdDrvWriteData(0x00);	
			}

		   	else	if(x == (Lcd_LCDH - 1))
			{
				LcdDrvWriteData(0x00);LcdDrvWriteData(0x00);LcdDrvWriteData(0xFF);	
			}

			else
			{
				LcdDrvWriteData(0x00);	LcdDrvWriteData(0x00);LcdDrvWriteData(0x00);
			}
		
		}
	}
}

void Img_Gray256_H(void)
{
	unsigned int x, y;
	unsigned int lcd_h;
	unsigned char w;
	lcd_h =  Lcd_LCDH - 1;

	for(y = 0; y <Lcd_LCDV; y++)
	{
		for(x = 0; x < Lcd_LCDH; x++)
		{ 
			w=(x*255)/(lcd_h); 
			LcdDrvWriteData(w);
			LcdDrvWriteData(w);
			LcdDrvWriteData(w);
        }
	}	
}

void Img_RED256_H(void)
{
	unsigned int x, y;
	unsigned int lcd_h;
	unsigned char w;
	lcd_h =  Lcd_LCDH - 1;

	for(y = 0; y <Lcd_LCDV; y++)
	{
		for(x = 0; x < Lcd_LCDH; x++)
		{ 
			w=(x*255)/(lcd_h); 
			LcdDrvWriteData(w);
			LcdDrvWriteData(0);
			LcdDrvWriteData(0);
        }
	}	
}

void Img_GREEN256_H(void)
{
	unsigned int x, y;
	unsigned int lcd_h;
	unsigned char w;
	lcd_h =  Lcd_LCDH - 1;

	for(y = 0; y <Lcd_LCDV; y++)
	{
		for(x = 0; x < Lcd_LCDH; x++)
		{ 
			w=(x*255)/(lcd_h); 
			LcdDrvWriteData(0);
			LcdDrvWriteData(w);
			LcdDrvWriteData(0);
        }
	}	
}

void Img_BLUE256_H(void)
{
	unsigned int x, y;
	unsigned int lcd_h;
	unsigned char w;
	lcd_h =  Lcd_LCDH - 1;

	for(y = 0; y <Lcd_LCDV; y++)
	{
		for(x = 0; x < Lcd_LCDH; x++)
		{ 
			w=(x*255)/(lcd_h); 
			LcdDrvWriteData(0);
			LcdDrvWriteData(0);
			LcdDrvWriteData(w);
        }
	}	
}

void Img_Gray256_V(void)
{
	unsigned int x, y;
	unsigned int lcd_y;
	unsigned char w;
	lcd_y =  Lcd_LCDV - 1;

	for(y = 0; y <Lcd_LCDV; y++)
	{	
		w=(y*255)/(lcd_y);
		for(x = 0; x < Lcd_LCDH; x++)
		{ 
			 
			LcdDrvWriteData(w);
			LcdDrvWriteData(w);
			LcdDrvWriteData(w);
        }
	}	
}

                                                                                                                                                                                                    



void Img_Gray32_H(void)
{
    unsigned int i, j;

	for(j=0;j<Lcd_LCDV;j++)
	{	
		for(i=0;i<Lcd_LCDH / 32;i++){ LcdDrvWriteData(0xff);LcdDrvWriteData(0xff);LcdDrvWriteData(0xff);}	
		for(;i<Lcd_LCDH *2/ 32;i++){ LcdDrvWriteData(0xf8);LcdDrvWriteData(0xf8);LcdDrvWriteData(0xf8);}
		for(;i<Lcd_LCDH *3/ 32;i++){ LcdDrvWriteData(0xf1);LcdDrvWriteData(0xf1);LcdDrvWriteData(0xf1);}
		for(;i<Lcd_LCDH *4/ 32;i++){ LcdDrvWriteData(0xea);LcdDrvWriteData(0xea);LcdDrvWriteData(0xea);}
		for(;i<Lcd_LCDH *5/ 32;i++){ LcdDrvWriteData(0xe3);LcdDrvWriteData(0xe3);LcdDrvWriteData(0xe3);}
		for(;i<Lcd_LCDH *6/ 32;i++){ LcdDrvWriteData(0xdc);LcdDrvWriteData(0xdc);LcdDrvWriteData(0xdc);}
		for(;i<Lcd_LCDH *7/ 32;i++){ LcdDrvWriteData(0xd5);LcdDrvWriteData(0xd5);LcdDrvWriteData(0xd5);}
		for(;i<Lcd_LCDH *8/ 32;i++){ LcdDrvWriteData(0xce);LcdDrvWriteData(0xce);LcdDrvWriteData(0xce);}
		for(;i<Lcd_LCDH *9/ 32;i++){ LcdDrvWriteData(0xc7);LcdDrvWriteData(0xc7);LcdDrvWriteData(0xc7);}
		for(;i<Lcd_LCDH *10/ 32;i++){ LcdDrvWriteData(0xc0);LcdDrvWriteData(0xc0);LcdDrvWriteData(0xc0);}
		for(;i<Lcd_LCDH *11/ 32;i++){ LcdDrvWriteData(0xb9);LcdDrvWriteData(0xb9);LcdDrvWriteData(0xb9);}
		for(;i<Lcd_LCDH *12/ 32;i++){ LcdDrvWriteData(0xb2);LcdDrvWriteData(0xb2);LcdDrvWriteData(0xb2);}
		for(;i<Lcd_LCDH *13/ 32;i++){ LcdDrvWriteData(0xab);LcdDrvWriteData(0xab);LcdDrvWriteData(0xab);}
		for(;i<Lcd_LCDH *14/ 32;i++){ LcdDrvWriteData(0xa4);LcdDrvWriteData(0xa4);LcdDrvWriteData(0xa4);}
		for(;i<Lcd_LCDH *15/ 32;i++){ LcdDrvWriteData(0x9d);LcdDrvWriteData(0x9d);LcdDrvWriteData(0x9d);}
		for(;i<Lcd_LCDH *16/ 32;i++){ LcdDrvWriteData(0x96);LcdDrvWriteData(0x96);LcdDrvWriteData(0x96);}
		for(;i<Lcd_LCDH *17/ 32;i++){ LcdDrvWriteData(0x8f);LcdDrvWriteData(0x8f);LcdDrvWriteData(0x8f);}
		for(;i<Lcd_LCDH *18/ 32;i++){ LcdDrvWriteData(0x88);LcdDrvWriteData(0x88);LcdDrvWriteData(0x88);}
		for(;i<Lcd_LCDH *19/ 32;i++){ LcdDrvWriteData(0x81);LcdDrvWriteData(0x81);LcdDrvWriteData(0x81);}
		for(;i<Lcd_LCDH *20/ 32;i++){ LcdDrvWriteData(0x7a);LcdDrvWriteData(0x7a);LcdDrvWriteData(0x7a);}
		for(;i<Lcd_LCDH *21/ 32;i++){ LcdDrvWriteData(0x73);LcdDrvWriteData(0x73);LcdDrvWriteData(0x73);}
		for(;i<Lcd_LCDH *22/ 32;i++){ LcdDrvWriteData(0x6c);LcdDrvWriteData(0x6c);LcdDrvWriteData(0x6c);}
		for(;i<Lcd_LCDH *23/ 32;i++){ LcdDrvWriteData(0x65);LcdDrvWriteData(0x65);LcdDrvWriteData(0x65);}
		for(;i<Lcd_LCDH *24/ 32;i++){ LcdDrvWriteData(0x5e);LcdDrvWriteData(0x5e);LcdDrvWriteData(0x5e);}
		for(;i<Lcd_LCDH *25/ 32;i++){ LcdDrvWriteData(0x57);LcdDrvWriteData(0x57);LcdDrvWriteData(0x57);}
		for(;i<Lcd_LCDH *26/ 32;i++){ LcdDrvWriteData(0x50);LcdDrvWriteData(0x50);LcdDrvWriteData(0x50);}
		for(;i<Lcd_LCDH *27/ 32;i++){ LcdDrvWriteData(0x49);LcdDrvWriteData(0x49);LcdDrvWriteData(0x49);}
		for(;i<Lcd_LCDH *28/ 32;i++){ LcdDrvWriteData(0x42);LcdDrvWriteData(0x42);LcdDrvWriteData(0x42);}
		for(;i<Lcd_LCDH *29/ 32;i++){ LcdDrvWriteData(0x3b);LcdDrvWriteData(0x3b);LcdDrvWriteData(0x3b);}
		for(;i<Lcd_LCDH *30/ 32;i++){ LcdDrvWriteData(0x34);LcdDrvWriteData(0x34);LcdDrvWriteData(0x34);}
		for(;i<Lcd_LCDH *31/ 32;i++){ LcdDrvWriteData(0x2d);LcdDrvWriteData(0x2d);LcdDrvWriteData(0x2d);}
		for(;i<Lcd_LCDH *32/ 32;i++){ LcdDrvWriteData(0x26);LcdDrvWriteData(0x26);LcdDrvWriteData(0x26);}
		
	}
}


void Img_Gray32_V(void)
{
    unsigned int i, j;

	for(j=0;j<Lcd_LCDH;j++)
	{	
		for(i=0;i<Lcd_LCDV / 32;i++){LcdDrvWriteData(0xff);LcdDrvWriteData(0xff);LcdDrvWriteData(0xff);}
		
		}

			for(j=0;j<Lcd_LCDH;j++)
	{	
		for(i=Lcd_LCDV / 32;i<Lcd_LCDV *2/ 32;i++){LcdDrvWriteData(0xf7);LcdDrvWriteData(0xf7);LcdDrvWriteData(0xf7);}
		
		}

			for(j=0;j<Lcd_LCDH;j++)
	{	
		for(i=Lcd_LCDV *2/ 32;i<Lcd_LCDV *3/ 32;i++){LcdDrvWriteData(0xef);LcdDrvWriteData(0xef);LcdDrvWriteData(0xef);}
		
		}

			for(j=0;j<Lcd_LCDH;j++)
	{	
		for(i=Lcd_LCDV *3/ 32;i<Lcd_LCDV *4/ 32;i++){LcdDrvWriteData(0xe7);LcdDrvWriteData(0xe7);LcdDrvWriteData(0xe7);}
		
		}		
					
			for(j=0;j<Lcd_LCDH;j++)
	{	
		for(i=Lcd_LCDV *4/ 32;i<Lcd_LCDV *5/ 32;i++){ LcdDrvWriteData(0xdf);LcdDrvWriteData(0xdf);LcdDrvWriteData(0xdf);}
		
		}
					for(j=0;j<Lcd_LCDH;j++)
	{	
		for(i=Lcd_LCDV *5/ 32;i<Lcd_LCDV *6/ 32;i++){ LcdDrvWriteData(0xd7);LcdDrvWriteData(0xd7);LcdDrvWriteData(0xd7);}
		
		}
					for(j=0;j<Lcd_LCDH;j++)
	{	
		for(i=Lcd_LCDV *6/ 32;i<Lcd_LCDV *7/ 32;i++){ LcdDrvWriteData(0xcf);LcdDrvWriteData(0xcf);LcdDrvWriteData(0xcf);}
		
		}
					for(j=0;j<Lcd_LCDH;j++)
	{	
		for(i=Lcd_LCDV *7/ 32;i<Lcd_LCDV *8/ 32;i++){ LcdDrvWriteData(0xc7);LcdDrvWriteData(0xc7);LcdDrvWriteData(0xc7);}
		
		}
					for(j=0;j<Lcd_LCDH;j++)
	{	
		for(i=Lcd_LCDV *8/ 32;i<Lcd_LCDV *9/ 32;i++){ LcdDrvWriteData(0xbf);LcdDrvWriteData(0xbf);LcdDrvWriteData(0xbf);}
		
		}
					for(j=0;j<Lcd_LCDH;j++)
	{	
		for(i=Lcd_LCDV *9/ 32;i<Lcd_LCDV *10/ 32;i++){ LcdDrvWriteData(0xb7);LcdDrvWriteData(0xb7);LcdDrvWriteData(0xb7);}
		
		}
					for(j=0;j<Lcd_LCDH;j++)
	{	
		for(i=Lcd_LCDV *10/ 32;i<Lcd_LCDV *11/ 32;i++){ LcdDrvWriteData(0xaf);LcdDrvWriteData(0xaf);LcdDrvWriteData(0xaf);}
		
		}
					for(j=0;j<Lcd_LCDH;j++)
	{	
		for(i=Lcd_LCDV *11/ 32;i<Lcd_LCDV *12/ 32;i++) { LcdDrvWriteData(0xa7);LcdDrvWriteData(0xa7);LcdDrvWriteData(0xa7);}
		
		}
					for(j=0;j<Lcd_LCDH;j++)
	{	
		for(i=Lcd_LCDV *12/ 32;i<Lcd_LCDV *13/ 32;i++) { LcdDrvWriteData(0x9f);LcdDrvWriteData(0x9f);LcdDrvWriteData(0x9f);}
		
		}
					for(j=0;j<Lcd_LCDH;j++)
	{	
		for(i=Lcd_LCDV *13/ 32;i<Lcd_LCDV *14/ 32;i++)	{ LcdDrvWriteData(0x97);LcdDrvWriteData(0x97);LcdDrvWriteData(0x97);}
		
		}
					for(j=0;j<Lcd_LCDH;j++)
	{	
		for(i=Lcd_LCDV *14/ 32;i<Lcd_LCDV *15/ 32;i++) { LcdDrvWriteData(0x8f);LcdDrvWriteData(0x8f);LcdDrvWriteData(0x8f);}
		
		}
					for(j=0;j<Lcd_LCDH;j++)
	{	
		for(i=Lcd_LCDV *15/ 32;i<Lcd_LCDV *16/ 32;i++){ LcdDrvWriteData(0x87);LcdDrvWriteData(0x87);LcdDrvWriteData(0x87);}
		
		}
					for(j=0;j<Lcd_LCDH;j++)
	{	
		for(i=Lcd_LCDV *16/ 32;i<Lcd_LCDV *17/ 32;i++){ LcdDrvWriteData(0x7f);LcdDrvWriteData(0x7f);LcdDrvWriteData(0x7f);}
		
		}
					for(j=0;j<Lcd_LCDH;j++)
	{	
		for(i=Lcd_LCDV *17/ 32;i<Lcd_LCDV *18/ 32;i++) { LcdDrvWriteData(0x77);LcdDrvWriteData(0x77);LcdDrvWriteData(0x77);}
		
		}
					for(j=0;j<Lcd_LCDH;j++)
	{	
		for(i=Lcd_LCDV *18/ 32;i<Lcd_LCDV *19/ 32;i++) { LcdDrvWriteData(0x6f);LcdDrvWriteData(0x6f);LcdDrvWriteData(0x6f);}
		
		}
					for(j=0;j<Lcd_LCDH;j++)
	{	
		for(i=Lcd_LCDV *19/ 32;i<Lcd_LCDV *20/ 32;i++) { LcdDrvWriteData(0x67);LcdDrvWriteData(0x67);LcdDrvWriteData(0x67);}
		
		}
					for(j=0;j<Lcd_LCDH;j++)
	{	
		for(i=Lcd_LCDV *20/ 32;i<Lcd_LCDV *21/ 32;i++) { LcdDrvWriteData(0x5f);LcdDrvWriteData(0x5f);LcdDrvWriteData(0x5f);}
		
		}
					for(j=0;j<Lcd_LCDH;j++)
	{	
		for(i=Lcd_LCDV *21/ 32;i<Lcd_LCDV *22/ 32;i++){ LcdDrvWriteData(0x57);LcdDrvWriteData(0x57);LcdDrvWriteData(0x57);}
		
		}
					for(j=0;j<Lcd_LCDH;j++)
	{	
		for(i=Lcd_LCDV *22/ 32;i<Lcd_LCDV *23/ 32;i++) { LcdDrvWriteData(0x4f);LcdDrvWriteData(0x4f);LcdDrvWriteData(0x4f);}
		
		}
					for(j=0;j<Lcd_LCDH;j++)
	{	
		for(i=Lcd_LCDV *23/ 32;i<Lcd_LCDV *24/ 32;i++){ LcdDrvWriteData(0x47);LcdDrvWriteData(0x47);LcdDrvWriteData(0x47);}
		
		}
					for(j=0;j<Lcd_LCDH;j++)
	{	
		for(i=Lcd_LCDV *24/ 32;i<Lcd_LCDV *25/ 32;i++){ LcdDrvWriteData(0x3f);LcdDrvWriteData(0x3f);LcdDrvWriteData(0x3f);}
		
		}
					for(j=0;j<Lcd_LCDH;j++)
	{	
		for(i=Lcd_LCDV *25/ 32;i<Lcd_LCDV *26/ 32;i++){ LcdDrvWriteData(0x37);LcdDrvWriteData(0x37);LcdDrvWriteData(0x37);}
		
		}
					for(j=0;j<Lcd_LCDH;j++)
	{	
		for(i=Lcd_LCDV *26/ 32;i<Lcd_LCDV *27/ 32;i++){ LcdDrvWriteData(0x2f);LcdDrvWriteData(0x2f);LcdDrvWriteData(0x2f);}
		
		}
					for(j=0;j<Lcd_LCDH;j++)
	{	
		for(i=Lcd_LCDV *27/ 32;i<Lcd_LCDV *28/ 32;i++) { LcdDrvWriteData(0x27);LcdDrvWriteData(0x27);LcdDrvWriteData(0x27);}
		
		}
					for(j=0;j<Lcd_LCDH;j++)
	{	
		for(i=Lcd_LCDV *28/ 32;i<Lcd_LCDV *29/ 32;i++){ LcdDrvWriteData(0x1f);LcdDrvWriteData(0x1f);LcdDrvWriteData(0x1f);}
		
		}
					for(j=0;j<Lcd_LCDH;j++)
	{	
		for(i=Lcd_LCDV *29/ 32;i<Lcd_LCDV *30/ 32;i++){ LcdDrvWriteData(0x17);LcdDrvWriteData(0x17);LcdDrvWriteData(0x17);}
		
		}
					for(j=0;j<Lcd_LCDH;j++)
	{	
		for(i=Lcd_LCDV *30/ 32;i<Lcd_LCDV *31/ 32;i++){ LcdDrvWriteData(0x0f);LcdDrvWriteData(0x0f);LcdDrvWriteData(0x0f);}
		
		}
					for(j=0;j<Lcd_LCDH;j++)
	{	
		for(i=Lcd_LCDV *31/ 32;i<Lcd_LCDV *32/ 32;i++){ LcdDrvWriteData(0x08);LcdDrvWriteData(0x08);LcdDrvWriteData(0x08);}
		
		}
				


	}






void Img_RED256_V(void)
{
	unsigned int x, y;
	unsigned int lcd_y;
	unsigned char w;
	lcd_y =  Lcd_LCDV - 1;

	for(y = 0; y <Lcd_LCDV; y++)
	{	
		w=(y*255)/(lcd_y);
		for(x = 0; x < Lcd_LCDH; x++)
		{ 
			 
			LcdDrvWriteData(w);
			LcdDrvWriteData(0);
			LcdDrvWriteData(0);
        }
	}	
}

void Img_GREEN256_V(void)
{
	unsigned int x, y;
	unsigned int lcd_y;
	unsigned char w;
	lcd_y =  Lcd_LCDV - 1;

	for(y = 0; y <Lcd_LCDV; y++)
	{	
		w=(y*255)/(lcd_y);
		for(x = 0; x < Lcd_LCDH; x++)
		{ 
			 
			LcdDrvWriteData(0);
			LcdDrvWriteData(w);
			LcdDrvWriteData(0);
        }
	}	
}

void Img_BLUE256_V(void)
{
	unsigned int x, y;
	unsigned int lcd_y;
	unsigned char w;
	lcd_y =  Lcd_LCDV - 1;

	for(y = 0; y <Lcd_LCDV; y++)
	{	
		w=(y*255)/(lcd_y);
		for(x = 0; x < Lcd_LCDH; x++)
		{ 
			 
			LcdDrvWriteData(0);
			LcdDrvWriteData(0);
			LcdDrvWriteData(w);
        }
	}	
}

void Img_ColorBar(void)
{
    unsigned int i, j;

	for(j=0;j<Lcd_LCDV;j++)
	{	
		for(i=0;i<Lcd_LCDH / 8;i++){ LcdDrvWriteData(0xff);LcdDrvWriteData(0xff);LcdDrvWriteData(0xff);}	
		for(;i<Lcd_LCDH *2/ 8;i++){ LcdDrvWriteData(0xff);LcdDrvWriteData(0xff);LcdDrvWriteData(0x00);}
		for(;i<Lcd_LCDH *3/ 8;i++){ LcdDrvWriteData(0x00);LcdDrvWriteData(0xff);LcdDrvWriteData(0xff);}
		for(;i<Lcd_LCDH *4/ 8;i++){ LcdDrvWriteData(0x00);LcdDrvWriteData(0xff);LcdDrvWriteData(0x00);}
		for(;i<Lcd_LCDH *5/ 8;i++){ LcdDrvWriteData(0xff);LcdDrvWriteData(0x00);LcdDrvWriteData(0xff);}
		for(;i<Lcd_LCDH *6/ 8;i++){ LcdDrvWriteData(0xff);LcdDrvWriteData(0x00);LcdDrvWriteData(0x00);}
		for(;i<Lcd_LCDH *7/ 8;i++){ LcdDrvWriteData(0x00);LcdDrvWriteData(0x00);LcdDrvWriteData(0xff);}
		for(;i<Lcd_LCDH *8/ 8;i++){ LcdDrvWriteData(0x00);LcdDrvWriteData(0x00);LcdDrvWriteData(0x00);}	
	}
}

void Img_ColorBar_V(void)
{
   unsigned int i, j;

	for(j=0;j<Lcd_LCDH;j++)
	{	
		for(i=0;i<Lcd_LCDV / 3;i++){LcdDrvWriteData(0xff);LcdDrvWriteData(0x00);LcdDrvWriteData(0x00);}
		
		}

			for(j=0;j<Lcd_LCDH;j++)
	{	
		for(i=Lcd_LCDV / 3;i<Lcd_LCDV *2/ 3;i++){ LcdDrvWriteData(0x00);LcdDrvWriteData(0xff);LcdDrvWriteData(0x00);}
		
		}

			for(j=0;j<Lcd_LCDH;j++)
	{	
		for(i=Lcd_LCDV *2/ 3;i<Lcd_LCDV *3/ 3;i++){ LcdDrvWriteData(0x00);LcdDrvWriteData(0x00);LcdDrvWriteData(0xff);}
		
		}


}



void two_windows(void)
{
    unsigned int i, j;

	for(j=0;j<128;j++){for(i=0;i<Lcd_LCDH;i++){ LcdDrvWriteData(127);LcdDrvWriteData(127);LcdDrvWriteData(127);} }

	for(j=0;j<384;j++)
	   {
	    for(i=0;i<108;i++){ LcdDrvWriteData(127);LcdDrvWriteData(127);LcdDrvWriteData(127);}
    	for(i=0;i<216;i++){ LcdDrvWriteData(0);LcdDrvWriteData(0);LcdDrvWriteData(0);}
	 	for(i=0;i<396;i++){ LcdDrvWriteData(127);LcdDrvWriteData(127);LcdDrvWriteData(127);}
	 	}

	for(j=0;j<256;j++){for(i=0;i<Lcd_LCDH;i++){ LcdDrvWriteData(127);LcdDrvWriteData(127);LcdDrvWriteData(127);} }

	for(j=0;j<384;j++)
	   {
	    for(i=0;i<396;i++){ LcdDrvWriteData(127);LcdDrvWriteData(127);LcdDrvWriteData(127);}
		for(i=0;i<216;i++){ LcdDrvWriteData(0xff);LcdDrvWriteData(0xff);LcdDrvWriteData(0xff);}
		for(i=0;i<108;i++){ LcdDrvWriteData(127);LcdDrvWriteData(127);LcdDrvWriteData(127);}
		}	
				
	for(j=0;j<128;j++){for(i=0;i<Lcd_LCDH;i++){ LcdDrvWriteData(127);LcdDrvWriteData(127);LcdDrvWriteData(127);} }
}

void MAX_Current(void)
{
    unsigned int i, j;

	for(j=0;j<Lcd_LCDV/2;j++)
	{	
		for(i=0;i<Lcd_LCDH/2;i++)
		{
			LcdDrvWriteData(0xff);LcdDrvWriteData(0x00);LcdDrvWriteData(0xff);
			LcdDrvWriteData(0x00);LcdDrvWriteData(0xff);LcdDrvWriteData(0x00);
		 }
	   for(i=0;i<Lcd_LCDH/2;i++)
		{
			LcdDrvWriteData(0x00);LcdDrvWriteData(0xff);LcdDrvWriteData(0x00);
			LcdDrvWriteData(0xff);LcdDrvWriteData(0x00);LcdDrvWriteData(0xff);
			
		 }
	}
}



