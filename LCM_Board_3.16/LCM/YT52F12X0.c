
#include "user.h"
#include "ssd2828.h"

#ifdef YT52F12X0

void LCD_SSD_SET(void)
{
	Lcd_MODE = MIPI_SINGLE;   //
	Lcd_LCDH = 720;		  //???X?????
	Lcd_LCDV = 1280;	      //???Y?????
	Lcd_HBPD = 16;		      //??HBP
	Lcd_HFPD = 24; 
	Lcd_HSPW = 32;

	Lcd_VBPD = 8; 
	Lcd_VFPD = 8; 
	Lcd_VSPW = 16;  
	
	Lcd_fps = 60;
	Lcd_DCLK = (Lcd_fps * ((Lcd_LCDH + Lcd_HBPD + Lcd_HFPD + Lcd_HSPW) * (Lcd_LCDV + Lcd_VBPD + Lcd_VFPD + Lcd_VSPW)))/1000000;
	
	Dsi_LANE = 4;
  Dsi_mbps = 0;
	
	Lcd_DCLK_EDGE = DCLK_RISING_EDGE;         //???????		  
	Lcd_HSYNC_POLARITY = HSYNC_ACTIVE_LOW;    //HSYNC???????  
	Lcd_VSYNC_POLARITY = VSYNC_ACTIVE_LOW;    //VSYNC???????  
	Lcd_DE_POLARITY = DE_ACTIVE_HIGH;         //DE???????;	 	 	   
	LcdDrvInit();	
}

void LCD_INIT(void)
{
	/*

Generic_Long_Write_5P(0xF0,0x55,0xAA,0x52,0x08,0x00);
Generic_Long_Write_3P(0xE1,0x11,0x10,0x11);
Generic_Long_Write_4P(0xB0,0x14,0x1E,0x30,0x20);//V H porch

Generic_Short_Write_1P(0xBA,0x03);
Generic_Short_Write_1P(0xB6,0x04);//
Generic_Long_Write_4P(0xB7,0x04,0x04,0x06,0x04);//STV
Generic_Long_Write_2P(0xB8,0x02,0x00);
Generic_Short_Write_1P(0xBB,0x44);
Generic_Long_Write_FIFO(10,B4);
Generic_Long_Write_FIFO(10,B5);



Generic_Long_Write_FIFO(11,C0);
Generic_Long_Write_FIFO(11,C1);
Generic_Long_Write_FIFO(11,C2);
Generic_Long_Write_FIFO(11,C3);

Generic_Long_Write_FIFO(13,C6);
Generic_Long_Write_FIFO(13,C7);
Generic_Long_Write_FIFO(10,CC);
Generic_Long_Write_FIFO(13,CD);



Generic_Long_Write_5P(0xF0,0x55,0xAA,0x52,0x08,0x01);
Generic_Short_Write_1P(0xB6,0x2D);
Generic_Short_Write_1P(0xBB,0x2E);
Generic_Long_Write_2P(0xC3,0x11,0x0A);

Generic_Long_Write_6P(0xD1,0x1F,0x2F,0x3F,0x4F,0x4F,0x9F);
Generic_Long_Write_FIFO(11,D2);
Generic_Long_Write_3P(0xD3,0x01,0x00,0x50);
Generic_Short_Write_1P(0xBE,0x1C);




Generic_Long_Write_5P(0xF0,0x55,0xAA,0x52,0x08,0x02);

Generic_Long_Write_6P(0xE0,0x00,0xF0,0x00,0xCE,0x01,0x09);
//Generic_Long_Write_6P(0xE0,0xAA,0xA0,0xAA,0xC8,0xA1,0xA9);
Generic_Long_Write_FIFO(16,E1);
Generic_Long_Write_FIFO(16,E2);
Generic_Long_Write_5P(0xE3,0xFA,0xF7,0xFE,0x04,0x09);
Generic_Long_Write_FIFO(16,E4);
Generic_Long_Write_FIFO(16,E5);
Generic_Long_Write_5P(0xE6,0xFF,0x07,0x0D,0x14,0x19);
Generic_Long_Write_FIFO(16,E7);
Generic_Long_Write_FIFO(16,E8);
Generic_Long_Write_5P(0xE9,0xFF,0x96,0x9D,0xA6,0xAC);


*/

//Generic_Long_Write_5P(0xF0,0x55,0xAA,0x52,0x08,0x02);

//Generic_Short_Write_1P(0xC9,0x1D);
/*
	Generic_Long_Write_5P(0xF0,0x55,0xAA,0x52,0x08,0x01);
	DCS_Short_Read_NP(0xEF, 3, BUFFER+0);	
*/


	Generic_Long_Write_5P(0xF0,0x55,0xAA,0x52,0x08,0x02);
	Generic_Short_Write_1P(0xC9,0x1D);
	Generic_Long_Write_5P(0xF0,0x55,0xAA,0x52,0x08,0x00);
}

#endif

