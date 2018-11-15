
#include "user.h"
#include "ssd2828.h"

#ifdef YT52F10A1

void LCD_SSD_SET(void)
{
	Lcd_MODE = MIPI_SINGLE;   //
	Lcd_LCDH = 720;		  //
	Lcd_LCDV = 1280;	     
	Lcd_HBPD = 16;		      
	Lcd_HFPD = 24; 
	Lcd_HSPW = 32;

	Lcd_VBPD = 8; 
	Lcd_VFPD = 8; 
	Lcd_VSPW = 16;  
	
	Lcd_fps = 60;
	Dsi_LANE = 4;
  	Dsi_mbps = 0;
	Lcd_DCLK = (Lcd_fps * ((Lcd_LCDH + Lcd_HBPD + Lcd_HFPD + Lcd_HSPW) * (Lcd_LCDV + Lcd_VBPD + Lcd_VFPD + Lcd_VSPW)))/1000000;

	Lcd_DCLK_EDGE = DCLK_RISING_EDGE;         //上升沿锁存数据	  
	Lcd_HSYNC_POLARITY = HSYNC_ACTIVE_LOW;    //HSYNC脉冲低电平有效  
	Lcd_VSYNC_POLARITY = VSYNC_ACTIVE_LOW;    //VSYNC脉冲低电平有效  
	Lcd_DE_POLARITY = DE_ACTIVE_HIGH;         //DE信号低电平有效;	 	   
	LcdDrvInit();	
}

void LCD_INIT(void)
{
	Generic_Long_Write_3P(0xFF,0x98,0x81,0x03);

	//GIP_1
	Generic_Short_Write_1P(0x01,0x00);
	Generic_Short_Write_1P(0x02,0x00);
	Generic_Short_Write_1P(0x03,0x53);
	Generic_Short_Write_1P(0x04,0x54);
	Generic_Short_Write_1P(0x05,0x14);
	Generic_Short_Write_1P(0x06,0x04);
	Generic_Short_Write_1P(0x07,0x03);
	Generic_Short_Write_1P(0x08,0x01);
	Generic_Short_Write_1P(0x09,0x00);
	Generic_Short_Write_1P(0x0a,0x64);
	Generic_Short_Write_1P(0x0b,0x64);
	Generic_Short_Write_1P(0x0c,0x00);
	Generic_Short_Write_1P(0x0d,0x00);
	Generic_Short_Write_1P(0x0e,0x00);
	Generic_Short_Write_1P(0x0f,0x65);
	Generic_Short_Write_1P(0x10,0x65);
	Generic_Short_Write_1P(0x11,0x00);
	Generic_Short_Write_1P(0x12,0x00);
	Generic_Short_Write_1P(0x13,0x00);
	Generic_Short_Write_1P(0x14,0x00);
	Generic_Short_Write_1P(0x15,0x00);
	Generic_Short_Write_1P(0x16,0x00);
	Generic_Short_Write_1P(0x17,0x00);
	Generic_Short_Write_1P(0x18,0x00);
	Generic_Short_Write_1P(0x19,0x00);
	Generic_Short_Write_1P(0x1a,0x00);
	Generic_Short_Write_1P(0x1b,0x00);
	Generic_Short_Write_1P(0x1c,0x00);
	Generic_Short_Write_1P(0x1d,0x00);
	Generic_Short_Write_1P(0x1e,0xC0);
	Generic_Short_Write_1P(0x1f,0x80);
	Generic_Short_Write_1P(0x20,0x03);
	Generic_Short_Write_1P(0x21,0x08);
	Generic_Short_Write_1P(0x22,0x00);
	Generic_Short_Write_1P(0x23,0x00);
	Generic_Short_Write_1P(0x24,0x00);
	Generic_Short_Write_1P(0x25,0x00);
	Generic_Short_Write_1P(0x26,0x00);
	Generic_Short_Write_1P(0x27,0x00);
	Generic_Short_Write_1P(0x28,0x55);
	Generic_Short_Write_1P(0x29,0x04);
	Generic_Short_Write_1P(0x2a,0x00);
	Generic_Short_Write_1P(0x2b,0x00);
	Generic_Short_Write_1P(0x2c,0x00);
	Generic_Short_Write_1P(0x2d,0x00);
	Generic_Short_Write_1P(0x2e,0x00);
	Generic_Short_Write_1P(0x2f,0x00);
	Generic_Short_Write_1P(0x30,0x00);
	Generic_Short_Write_1P(0x31,0x00);
	Generic_Short_Write_1P(0x32,0x00);
	Generic_Short_Write_1P(0x33,0x00);
	Generic_Short_Write_1P(0x34,0x03);
	Generic_Short_Write_1P(0x35,0x00);
	Generic_Short_Write_1P(0x36,0x05);
	Generic_Short_Write_1P(0x37,0x00);
	Generic_Short_Write_1P(0x38,0x01);//3c
	Generic_Short_Write_1P(0x39,0x00);
	Generic_Short_Write_1P(0x3a,0x00);
	Generic_Short_Write_1P(0x3b,0x00);
	Generic_Short_Write_1P(0x3c,0x00);
	Generic_Short_Write_1P(0x3d,0x00);
	Generic_Short_Write_1P(0x3e,0x00);
	Generic_Short_Write_1P(0x3f,0x00);
	Generic_Short_Write_1P(0x40,0x00);
	Generic_Short_Write_1P(0x41,0x00);
	Generic_Short_Write_1P(0x42,0x00);
	Generic_Short_Write_1P(0x43,0x00);
	Generic_Short_Write_1P(0x44,0x00);

	//GIP_2
	Generic_Short_Write_1P(0x50,0x01);
	Generic_Short_Write_1P(0x51,0x23);
	Generic_Short_Write_1P(0x52,0x45);
	Generic_Short_Write_1P(0x53,0x67);
	Generic_Short_Write_1P(0x54,0x89);
	Generic_Short_Write_1P(0x55,0xab);
	Generic_Short_Write_1P(0x56,0x01);
	Generic_Short_Write_1P(0x57,0x23);
	Generic_Short_Write_1P(0x58,0x45);
	Generic_Short_Write_1P(0x59,0x67);
	Generic_Short_Write_1P(0x5a,0x89);
	Generic_Short_Write_1P(0x5b,0xab);
	Generic_Short_Write_1P(0x5c,0xcd);
	Generic_Short_Write_1P(0x5d,0xef);

	//GIP_3
	Generic_Short_Write_1P(0x5e,0x01);
	Generic_Short_Write_1P(0x5f,0x14);
	Generic_Short_Write_1P(0x60,0x15);
	Generic_Short_Write_1P(0x61,0x0C);
	Generic_Short_Write_1P(0x62,0x0D);
	Generic_Short_Write_1P(0x63,0x0E);
	Generic_Short_Write_1P(0x64,0x0F);
	Generic_Short_Write_1P(0x65,0x10);
	Generic_Short_Write_1P(0x66,0x11);
	Generic_Short_Write_1P(0x67,0x08);
	Generic_Short_Write_1P(0x68,0x02);
	Generic_Short_Write_1P(0x69,0x0A);
	Generic_Short_Write_1P(0x6a,0x02);
	Generic_Short_Write_1P(0x6b,0x02);
	Generic_Short_Write_1P(0x6c,0x02);
	Generic_Short_Write_1P(0x6d,0x02);
	Generic_Short_Write_1P(0x6e,0x02);
	Generic_Short_Write_1P(0x6f,0x02);
	Generic_Short_Write_1P(0x70,0x02);
	Generic_Short_Write_1P(0x71,0x02);
	Generic_Short_Write_1P(0x72,0x06);
	Generic_Short_Write_1P(0x73,0x02);
	Generic_Short_Write_1P(0x74,0x02);

	Generic_Short_Write_1P(0x75,0x14);
	Generic_Short_Write_1P(0x76,0x15);
	Generic_Short_Write_1P(0x77,0x0F);
	Generic_Short_Write_1P(0x78,0x0E);
	Generic_Short_Write_1P(0x79,0x0D);
	Generic_Short_Write_1P(0x7a,0x0C);
	Generic_Short_Write_1P(0x7b,0x11);
	Generic_Short_Write_1P(0x7c,0x10);
	Generic_Short_Write_1P(0x7d,0x06);
	Generic_Short_Write_1P(0x7e,0x02);
	Generic_Short_Write_1P(0x7f,0x0A);
	Generic_Short_Write_1P(0x80,0x02);
	Generic_Short_Write_1P(0x81,0x02);
	Generic_Short_Write_1P(0x82,0x02);
	Generic_Short_Write_1P(0x83,0x02);
	Generic_Short_Write_1P(0x84,0x02);
	Generic_Short_Write_1P(0x85,0x02);
	Generic_Short_Write_1P(0x86,0x02);
	Generic_Short_Write_1P(0x87,0x02);
	Generic_Short_Write_1P(0x88,0x08);
	Generic_Short_Write_1P(0x89,0x02);
	Generic_Short_Write_1P(0x8A,0x02);

	//CMD_Page 4
	Generic_Long_Write_3P(0xFF,0x98,0x81,0x04);
	Generic_Short_Write_1P(0x6C,0x15);                //Set VCORE voltage =1.5V
	Generic_Short_Write_1P(0x6E,0x2F);                //di_pwr_reg=0 for power mode 2A //VGH clamp 18V
	Generic_Short_Write_1P(0x6F,0x55);                // reg vcl + pumping ratio VGH=4x VGL=-2.5x
	Generic_Short_Write_1P(0x3A,0xA4);                //POWER SAVING
	Generic_Short_Write_1P(0x8D,0x1F);               //VGL clamp -10V
	Generic_Short_Write_1P(0x87,0xBA);               //ESD
	Generic_Short_Write_1P(0x26,0x76);
	Generic_Short_Write_1P(0xB2,0xD1);

	//CMD_Page 1
	Generic_Long_Write_3P(0xFF,0x98,0x81,0x01);
	Generic_Short_Write_1P(0x22,0x09);               //BGR, SS
	Generic_Short_Write_1P(0x31,0x00);               //column inversion
	Generic_Short_Write_1P(0x53,0x77);               //VCOM1
	Generic_Short_Write_1P(0x55,0x77);               //VCOM2
	Generic_Short_Write_1P(0x50,0xA6);               // VREG1OUT=4.7V
	Generic_Short_Write_1P(0x51,0xA6);               // VREG2OUT=-4.7V
	Generic_Short_Write_1P(0x60,0x2B);               //SDT

	Generic_Short_Write_1P(0xA0,0x00);               //VP255 Gamma P
	Generic_Short_Write_1P(0xA1,0x0B);               //VP251
	Generic_Short_Write_1P(0xA2,0x2A);               //VP247
	Generic_Short_Write_1P(0xA3,0x14);               //VP243
	Generic_Short_Write_1P(0xA4,0x17);               //VP239
	Generic_Short_Write_1P(0xA5,0x2A);               //VP231
	Generic_Short_Write_1P(0xA6,0x1E);               //VP219
	Generic_Short_Write_1P(0xA7,0x20);               //VP203
	Generic_Short_Write_1P(0xA8,0x8C);               //VP175
	Generic_Short_Write_1P(0xA9,0x1C);               //VP144
	Generic_Short_Write_1P(0xAA,0x28);               //VP111
	Generic_Short_Write_1P(0xAB,0x78);               //VP80
	Generic_Short_Write_1P(0xAC,0x1A);               //VP52
	Generic_Short_Write_1P(0xAD,0x15);               //VP36
	Generic_Short_Write_1P(0xAE,0x4C);               //VP24
	Generic_Short_Write_1P(0xAF,0x20);               //VP16
	Generic_Short_Write_1P(0xB0,0x27);               //VP12
	Generic_Short_Write_1P(0xB1,0x52);               //VP8
	Generic_Short_Write_1P(0xB2,0x65);               //VP4
	Generic_Short_Write_1P(0xB3,0x3F);               //VP0

	Generic_Short_Write_1P(0xC0,0x00);               //VN255 GAMMA N
	Generic_Short_Write_1P(0xC1,0x1B);               //VN251
	Generic_Short_Write_1P(0xC2,0x2A);               //VN247
	Generic_Short_Write_1P(0xC3,0x14);               //VN243
	Generic_Short_Write_1P(0xC4,0x17);               //VN239
	Generic_Short_Write_1P(0xC5,0x2A);               //VN231
	Generic_Short_Write_1P(0xC6,0x1E);               //VN219
	Generic_Short_Write_1P(0xC7,0x20);               //VN203
	Generic_Short_Write_1P(0xC8,0x8D);               //VN175
	Generic_Short_Write_1P(0xC9,0x1C);               //VN144
	Generic_Short_Write_1P(0xCA,0x28);               //VN111
	Generic_Short_Write_1P(0xCB,0x78);               //VN80
	Generic_Short_Write_1P(0xCC,0x1B);               //VN52
	Generic_Short_Write_1P(0xCD,0x15);               //VN36
	Generic_Short_Write_1P(0xCE,0x4C);               //VN24
	Generic_Short_Write_1P(0xCF,0x21);               //VN16
	Generic_Short_Write_1P(0xD0,0x27);               //VN12
	Generic_Short_Write_1P(0xD1,0x52);               //VN8
	Generic_Short_Write_1P(0xD2,0x65);               //VN4
	Generic_Short_Write_1P(0xD3,0x3F);               //VN0


  	Generic_Long_Write_3P(0xFF,0x98,0x81,0x02);
	Generic_Short_Write_1P(0x07,0xFF);

	Generic_Long_Write_3P(0xFF,0x98,0x81,0x00);

	Generic_Short_Write_1P(0x35,0x00);
   	Generic_Short_Write_1P(0x51,0xFF);   //CABC
	Generic_Short_Write_1P(0x53,0x24);
	Generic_Short_Write_1P(0x55,0x00);

}

#endif
