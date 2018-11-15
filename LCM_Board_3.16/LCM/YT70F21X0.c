

#include "user.h"
#include "ssd2828.h"

#ifdef YT70F21X0

void LCD_SSD_SET(void)
{
	
	Lcd_MODE = MIPI_SINGLE;   //
	Lcd_LCDH = 1200;		  //
	Lcd_LCDV = 1920;	      //
	Lcd_HBPD = 16;		      //HBP
	Lcd_HFPD = 24; 
	Lcd_HSPW = 32;

	Lcd_VBPD = 8; 
	Lcd_VFPD = 8; 
	Lcd_VSPW = 16;  
	
	Lcd_fps = 55;
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
	DCS_Short_Write_NP(0x29);
	Delay_ms(120);
	DCS_Short_Write_NP(0x11);
	Delay_ms(100);
}

#endif

