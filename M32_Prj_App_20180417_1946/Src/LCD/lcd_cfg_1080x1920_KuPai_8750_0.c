#include "pport_spi.h"
#include "lcd_cfg.h"
#include "user_config.h"
#include "GPU_Cfg.h"




void Initial_LCM_1080x1920_KuPai_8750_0(void) {

//Reset(0x00);  //复位
//	Delay(0x30);
//	Reset(0x01);
//	Delay(0x30);
//	printf("initial begin \n");

	//----------------------
	SPI_WriteCmd(0xb7);
	SPI_WriteData(0x50);//50=TX_CLK 70=PCLK
	SPI_WriteData(0x00);   //Configuration Register

	SPI_WriteCmd(0xb8);
	SPI_WriteData(0x00);
	SPI_WriteData(0x00);   //VC(Virtual ChannelID) Control Register

	SPI_WriteCmd(0xb9);
	SPI_WriteData(0x00);//1=PLL disable
	SPI_WriteData(0x00);
	Delay(50);

	//TX_CLK/MS should be between 5Mhz to100Mhz
	SPI_WriteCmd(0xBA);//PLL=(TX_CLK/MS)*NS 8228=480M 4428=240M  061E=120M 4214=240M 821E=360M 8219=300M
	SPI_WriteData(0x14);//D7-0=NS(0x01 : NS=1)
	SPI_WriteData(0x42);//D15-14=PLL范围 00=62.5-125 01=126-250 10=251-500 11=501-1000  DB12-8=MS(01:MS=1)
	Delay(50);

	SPI_WriteCmd(0xBB);//LP Clock Divider LP clock = 400MHz / LPD / 8 = 240 / 8 / 4 = 7.5MHz
	SPI_WriteData(0x03);//D5-0=LPD=0x1 – Divide by 2 //12
	SPI_WriteData(0x00);
	Delay(150);
	SPI_WriteCmd(0xb9);
	SPI_WriteData(0x01);//1=PLL disable
	SPI_WriteData(0x00);
	Delay(50);
	//MIPI lane configuration
	SPI_WriteCmd(0xDE);//通道数
	SPI_WriteData(0x00);//11=4LANE 10=3LANE 01=2LANE 00=1LANE
	SPI_WriteData(0x00);
	Delay(50);
	SPI_WriteCmd(0xc9);
	SPI_WriteData(0x02);
	SPI_WriteData(0x23);   //p1: HS-Data-zero  p2: HS-Data- prepare  --> 8031 issue
	Delay_ms(100);

	////////////////  //-----------------55P34OK-------------------- //////////////////////////////////////////////////////

	SPI_WriteCmd(0xB7);
	SPI_WriteData(0x10);//10=TX_CLK 30=PCLK
	SPI_WriteData(0x02);


	SPI_WriteCmd(0xBD);
	SPI_WriteData(0x00);
	SPI_WriteData(0x00);



SSD2828_WritePackageSize(2);SPI_WriteData(0xFF);SPI_WriteData(0x05);
SSD2828_WritePackageSize(2);SPI_WriteData(0xFB);SPI_WriteData(0x01);
SSD2828_WritePackageSize(2);SPI_WriteData(0xC5);SPI_WriteData(0x01);
Delay_ms(50);
SSD2828_WritePackageSize(2);SPI_WriteData(0xFF);SPI_WriteData(0xEE);
SSD2828_WritePackageSize(2);SPI_WriteData(0xFB);SPI_WriteData(0x01);
SSD2828_WritePackageSize(2);SPI_WriteData(0x1F);SPI_WriteData(0x45);
SSD2828_WritePackageSize(2);SPI_WriteData(0x24);SPI_WriteData(0x4F);
SSD2828_WritePackageSize(2);SPI_WriteData(0x38);SPI_WriteData(0xC8);
SSD2828_WritePackageSize(2);SPI_WriteData(0x39);SPI_WriteData(0x27);
SSD2828_WritePackageSize(2);SPI_WriteData(0x1E);SPI_WriteData(0x77);
SSD2828_WritePackageSize(2);SPI_WriteData(0x1D);SPI_WriteData(0x0F);
SSD2828_WritePackageSize(2);SPI_WriteData(0x7E);SPI_WriteData(0x71);
SSD2828_WritePackageSize(2);SPI_WriteData(0x7C);SPI_WriteData(0x03);
SSD2828_WritePackageSize(2);SPI_WriteData(0xFF);SPI_WriteData(0x01);
SSD2828_WritePackageSize(2);SPI_WriteData(0xFB);SPI_WriteData(0x01);
SSD2828_WritePackageSize(2);SPI_WriteData(0x00);SPI_WriteData(0x01);
SSD2828_WritePackageSize(2);SPI_WriteData(0x01);SPI_WriteData(0x55);
SSD2828_WritePackageSize(2);SPI_WriteData(0x02);SPI_WriteData(0x40);
SSD2828_WritePackageSize(2);SPI_WriteData(0x05);SPI_WriteData(0x40);
SSD2828_WritePackageSize(2);SPI_WriteData(0x06);SPI_WriteData(0x4A);
SSD2828_WritePackageSize(2);SPI_WriteData(0x07);SPI_WriteData(0x24);
SSD2828_WritePackageSize(2);SPI_WriteData(0x08);SPI_WriteData(0x0C);
SSD2828_WritePackageSize(2);SPI_WriteData(0x0B);SPI_WriteData(0x7D);
SSD2828_WritePackageSize(2);SPI_WriteData(0x0C);SPI_WriteData(0x7D);
SSD2828_WritePackageSize(2);SPI_WriteData(0x0E);SPI_WriteData(0xB0);
SSD2828_WritePackageSize(2);SPI_WriteData(0x0F);SPI_WriteData(0xAE);
SSD2828_WritePackageSize(2);SPI_WriteData(0x11);SPI_WriteData(0x10);
SSD2828_WritePackageSize(2);SPI_WriteData(0x12);SPI_WriteData(0x10);
SSD2828_WritePackageSize(2);SPI_WriteData(0x13);SPI_WriteData(0x03);
SSD2828_WritePackageSize(2);SPI_WriteData(0x14);SPI_WriteData(0x4A);
SSD2828_WritePackageSize(2);SPI_WriteData(0x15);SPI_WriteData(0x12);
SSD2828_WritePackageSize(2);SPI_WriteData(0x16);SPI_WriteData(0x12);
SSD2828_WritePackageSize(2);SPI_WriteData(0x18);SPI_WriteData(0x00);
SSD2828_WritePackageSize(2);SPI_WriteData(0x19);SPI_WriteData(0x77);
SSD2828_WritePackageSize(2);SPI_WriteData(0x1A);SPI_WriteData(0x55);
SSD2828_WritePackageSize(2);SPI_WriteData(0x1B);SPI_WriteData(0x13);
SSD2828_WritePackageSize(2);SPI_WriteData(0x1C);SPI_WriteData(0x00);
SSD2828_WritePackageSize(2);SPI_WriteData(0x1D);SPI_WriteData(0x00);
SSD2828_WritePackageSize(2);SPI_WriteData(0x1E);SPI_WriteData(0x13);
SSD2828_WritePackageSize(2);SPI_WriteData(0x1F);SPI_WriteData(0x00);
SSD2828_WritePackageSize(2);SPI_WriteData(0x23);SPI_WriteData(0x00);
SSD2828_WritePackageSize(2);SPI_WriteData(0x24);SPI_WriteData(0x00);
SSD2828_WritePackageSize(2);SPI_WriteData(0x25);SPI_WriteData(0x00);
SSD2828_WritePackageSize(2);SPI_WriteData(0x26);SPI_WriteData(0x00);
SSD2828_WritePackageSize(2);SPI_WriteData(0x27);SPI_WriteData(0x00);
SSD2828_WritePackageSize(2);SPI_WriteData(0x28);SPI_WriteData(0x00);
SSD2828_WritePackageSize(2);SPI_WriteData(0x35);SPI_WriteData(0x00);
SSD2828_WritePackageSize(2);SPI_WriteData(0x66);SPI_WriteData(0x00);
SSD2828_WritePackageSize(2);SPI_WriteData(0x58);SPI_WriteData(0x82);
SSD2828_WritePackageSize(2);SPI_WriteData(0x59);SPI_WriteData(0x02);
SSD2828_WritePackageSize(2);SPI_WriteData(0x5A);SPI_WriteData(0x02);
SSD2828_WritePackageSize(2);SPI_WriteData(0x5B);SPI_WriteData(0x02);
SSD2828_WritePackageSize(2);SPI_WriteData(0x5C);SPI_WriteData(0x82);
SSD2828_WritePackageSize(2);SPI_WriteData(0x5D);SPI_WriteData(0x82);
SSD2828_WritePackageSize(2);SPI_WriteData(0x5E);SPI_WriteData(0x02);
SSD2828_WritePackageSize(2);SPI_WriteData(0x5F);SPI_WriteData(0x02);
SSD2828_WritePackageSize(2);SPI_WriteData(0x72);SPI_WriteData(0x31);	
SSD2828_WritePackageSize(2);SPI_WriteData(0xFF);SPI_WriteData(0x05);
SSD2828_WritePackageSize(2);SPI_WriteData(0xFB);SPI_WriteData(0x01);
SSD2828_WritePackageSize(2);SPI_WriteData(0x00);SPI_WriteData(0x01);
SSD2828_WritePackageSize(2);SPI_WriteData(0x01);SPI_WriteData(0x0B);
SSD2828_WritePackageSize(2);SPI_WriteData(0x02);SPI_WriteData(0x0C);
SSD2828_WritePackageSize(2);SPI_WriteData(0x03);SPI_WriteData(0x09);
SSD2828_WritePackageSize(2);SPI_WriteData(0x04);SPI_WriteData(0x0A);
SSD2828_WritePackageSize(2);SPI_WriteData(0x05);SPI_WriteData(0x00);
SSD2828_WritePackageSize(2);SPI_WriteData(0x06);SPI_WriteData(0x0F);
SSD2828_WritePackageSize(2);SPI_WriteData(0x07);SPI_WriteData(0x10);
SSD2828_WritePackageSize(2);SPI_WriteData(0x08);SPI_WriteData(0x00);
SSD2828_WritePackageSize(2);SPI_WriteData(0x09);SPI_WriteData(0x00);
SSD2828_WritePackageSize(2);SPI_WriteData(0x0A);SPI_WriteData(0x00);
SSD2828_WritePackageSize(2);SPI_WriteData(0x0B);SPI_WriteData(0x00);
SSD2828_WritePackageSize(2);SPI_WriteData(0x0C);SPI_WriteData(0x00);
SSD2828_WritePackageSize(2);SPI_WriteData(0x0D);SPI_WriteData(0x13);
SSD2828_WritePackageSize(2);SPI_WriteData(0x0E);SPI_WriteData(0x15);
SSD2828_WritePackageSize(2);SPI_WriteData(0x0F);SPI_WriteData(0x17);
SSD2828_WritePackageSize(2);SPI_WriteData(0x10);SPI_WriteData(0x01);
SSD2828_WritePackageSize(2);SPI_WriteData(0x11);SPI_WriteData(0x0B);
SSD2828_WritePackageSize(2);SPI_WriteData(0x12);SPI_WriteData(0x0C);
SSD2828_WritePackageSize(2);SPI_WriteData(0x13);SPI_WriteData(0x09);
SSD2828_WritePackageSize(2);SPI_WriteData(0x14);SPI_WriteData(0x0A);
SSD2828_WritePackageSize(2);SPI_WriteData(0x15);SPI_WriteData(0x00);
SSD2828_WritePackageSize(2);SPI_WriteData(0x16);SPI_WriteData(0x0F);
SSD2828_WritePackageSize(2);SPI_WriteData(0x17);SPI_WriteData(0x10);
SSD2828_WritePackageSize(2);SPI_WriteData(0x18);SPI_WriteData(0x00);
SSD2828_WritePackageSize(2);SPI_WriteData(0x19);SPI_WriteData(0x00);
SSD2828_WritePackageSize(2);SPI_WriteData(0x1A);SPI_WriteData(0x00);
SSD2828_WritePackageSize(2);SPI_WriteData(0x1B);SPI_WriteData(0x00);
SSD2828_WritePackageSize(2);SPI_WriteData(0x1C);SPI_WriteData(0x00);
SSD2828_WritePackageSize(2);SPI_WriteData(0x1D);SPI_WriteData(0x13);
SSD2828_WritePackageSize(2);SPI_WriteData(0x1E);SPI_WriteData(0x15);
SSD2828_WritePackageSize(2);SPI_WriteData(0x1F);SPI_WriteData(0x17);
SSD2828_WritePackageSize(2);SPI_WriteData(0x20);SPI_WriteData(0x00);
SSD2828_WritePackageSize(2);SPI_WriteData(0x21);SPI_WriteData(0x03);
SSD2828_WritePackageSize(2);SPI_WriteData(0x22);SPI_WriteData(0x01);
SSD2828_WritePackageSize(2);SPI_WriteData(0x23);SPI_WriteData(0x40);
SSD2828_WritePackageSize(2);SPI_WriteData(0x24);SPI_WriteData(0x40);
SSD2828_WritePackageSize(2);SPI_WriteData(0x25);SPI_WriteData(0xED);
SSD2828_WritePackageSize(2);SPI_WriteData(0x29);SPI_WriteData(0x58);
SSD2828_WritePackageSize(2);SPI_WriteData(0x2A);SPI_WriteData(0x12);
SSD2828_WritePackageSize(2);SPI_WriteData(0x2B);SPI_WriteData(0x01);
SSD2828_WritePackageSize(2);SPI_WriteData(0x4B);SPI_WriteData(0x06);
SSD2828_WritePackageSize(2);SPI_WriteData(0x4C);SPI_WriteData(0x11);
SSD2828_WritePackageSize(2);SPI_WriteData(0x4D);SPI_WriteData(0x20);
SSD2828_WritePackageSize(2);SPI_WriteData(0x4E);SPI_WriteData(0x02);
SSD2828_WritePackageSize(2);SPI_WriteData(0x4F);SPI_WriteData(0x02);
SSD2828_WritePackageSize(2);SPI_WriteData(0x50);SPI_WriteData(0x20);
SSD2828_WritePackageSize(2);SPI_WriteData(0x51);SPI_WriteData(0x61);
SSD2828_WritePackageSize(2);SPI_WriteData(0x52);SPI_WriteData(0x01);
SSD2828_WritePackageSize(2);SPI_WriteData(0x53);SPI_WriteData(0x63);
SSD2828_WritePackageSize(2);SPI_WriteData(0x54);SPI_WriteData(0x77);
SSD2828_WritePackageSize(2);SPI_WriteData(0x55);SPI_WriteData(0xED);
SSD2828_WritePackageSize(2);SPI_WriteData(0x5B);SPI_WriteData(0x00);
SSD2828_WritePackageSize(2);SPI_WriteData(0x5C);SPI_WriteData(0x00);
SSD2828_WritePackageSize(2);SPI_WriteData(0x5D);SPI_WriteData(0x00);
SSD2828_WritePackageSize(2);SPI_WriteData(0x5E);SPI_WriteData(0x00);
SSD2828_WritePackageSize(2);SPI_WriteData(0x5F);SPI_WriteData(0x15);
SSD2828_WritePackageSize(2);SPI_WriteData(0x60);SPI_WriteData(0x75);
SSD2828_WritePackageSize(2);SPI_WriteData(0x61);SPI_WriteData(0x00);
SSD2828_WritePackageSize(2);SPI_WriteData(0x62);SPI_WriteData(0x00);
SSD2828_WritePackageSize(2);SPI_WriteData(0x63);SPI_WriteData(0x00);
SSD2828_WritePackageSize(2);SPI_WriteData(0x64);SPI_WriteData(0x00);
SSD2828_WritePackageSize(2);SPI_WriteData(0x65);SPI_WriteData(0x00);
SSD2828_WritePackageSize(2);SPI_WriteData(0x66);SPI_WriteData(0x00);
SSD2828_WritePackageSize(2);SPI_WriteData(0x67);SPI_WriteData(0x00);
SSD2828_WritePackageSize(2);SPI_WriteData(0x68);SPI_WriteData(0x04);
SSD2828_WritePackageSize(2);SPI_WriteData(0x69);SPI_WriteData(0x00);
SSD2828_WritePackageSize(2);SPI_WriteData(0x6A);SPI_WriteData(0x00);
SSD2828_WritePackageSize(2);SPI_WriteData(0x6C);SPI_WriteData(0x40);
SSD2828_WritePackageSize(2);SPI_WriteData(0x75);SPI_WriteData(0x01);
SSD2828_WritePackageSize(2);SPI_WriteData(0x76);SPI_WriteData(0x01);
SSD2828_WritePackageSize(2);SPI_WriteData(0x7A);SPI_WriteData(0x80);
SSD2828_WritePackageSize(2);SPI_WriteData(0x7B);SPI_WriteData(0xA3);
SSD2828_WritePackageSize(2);SPI_WriteData(0x7C);SPI_WriteData(0xD8);
SSD2828_WritePackageSize(2);SPI_WriteData(0x7D);SPI_WriteData(0x60);
SSD2828_WritePackageSize(2);SPI_WriteData(0x7F);SPI_WriteData(0x15);
SSD2828_WritePackageSize(2);SPI_WriteData(0x80);SPI_WriteData(0x81);
SSD2828_WritePackageSize(2);SPI_WriteData(0x83);SPI_WriteData(0x05);
SSD2828_WritePackageSize(2);SPI_WriteData(0x93);SPI_WriteData(0x08);
SSD2828_WritePackageSize(2);SPI_WriteData(0x94);SPI_WriteData(0x10);
SSD2828_WritePackageSize(2);SPI_WriteData(0x8A);SPI_WriteData(0x00);
SSD2828_WritePackageSize(2);SPI_WriteData(0x9B);SPI_WriteData(0x0F);
SSD2828_WritePackageSize(2);SPI_WriteData(0xEA);SPI_WriteData(0xFF);
SSD2828_WritePackageSize(2);SPI_WriteData(0xEC);SPI_WriteData(0x00);
SSD2828_WritePackageSize(2);SPI_WriteData(0xFF);SPI_WriteData(0x01);
SSD2828_WritePackageSize(2);SPI_WriteData(0xFB);SPI_WriteData(0x01);
SSD2828_WritePackageSize(2);SPI_WriteData(0x75);SPI_WriteData(0x00);
SSD2828_WritePackageSize(2);SPI_WriteData(0x76);SPI_WriteData(0x9D);
SSD2828_WritePackageSize(2);SPI_WriteData(0x77);SPI_WriteData(0x00);
SSD2828_WritePackageSize(2);SPI_WriteData(0x78);SPI_WriteData(0xA2);
SSD2828_WritePackageSize(2);SPI_WriteData(0x79);SPI_WriteData(0x00);
SSD2828_WritePackageSize(2);SPI_WriteData(0x7A);SPI_WriteData(0xB0);
SSD2828_WritePackageSize(2);SPI_WriteData(0x7B);SPI_WriteData(0x00);
SSD2828_WritePackageSize(2);SPI_WriteData(0x7C);SPI_WriteData(0xBD);
SSD2828_WritePackageSize(2);SPI_WriteData(0x7D);SPI_WriteData(0x00);
SSD2828_WritePackageSize(2);SPI_WriteData(0x7E);SPI_WriteData(0xC9);
SSD2828_WritePackageSize(2);SPI_WriteData(0x7F);SPI_WriteData(0x00);
SSD2828_WritePackageSize(2);SPI_WriteData(0x80);SPI_WriteData(0xD4);
SSD2828_WritePackageSize(2);SPI_WriteData(0x81);SPI_WriteData(0x00);
SSD2828_WritePackageSize(2);SPI_WriteData(0x82);SPI_WriteData(0xDF);
SSD2828_WritePackageSize(2);SPI_WriteData(0x83);SPI_WriteData(0x00);
SSD2828_WritePackageSize(2);SPI_WriteData(0x84);SPI_WriteData(0xE9);
SSD2828_WritePackageSize(2);SPI_WriteData(0x85);SPI_WriteData(0x00);
SSD2828_WritePackageSize(2);SPI_WriteData(0x86);SPI_WriteData(0xF2);
SSD2828_WritePackageSize(2);SPI_WriteData(0x87);SPI_WriteData(0x01);
SSD2828_WritePackageSize(2);SPI_WriteData(0x88);SPI_WriteData(0x17);
SSD2828_WritePackageSize(2);SPI_WriteData(0x89);SPI_WriteData(0x01);
SSD2828_WritePackageSize(2);SPI_WriteData(0x8A);SPI_WriteData(0x36);
SSD2828_WritePackageSize(2);SPI_WriteData(0x8B);SPI_WriteData(0x01);
SSD2828_WritePackageSize(2);SPI_WriteData(0x8C);SPI_WriteData(0x6B);
SSD2828_WritePackageSize(2);SPI_WriteData(0x8D);SPI_WriteData(0x01);
SSD2828_WritePackageSize(2);SPI_WriteData(0x8E);SPI_WriteData(0x98);
SSD2828_WritePackageSize(2);SPI_WriteData(0x8F);SPI_WriteData(0x01);
SSD2828_WritePackageSize(2);SPI_WriteData(0x90);SPI_WriteData(0xE0);
SSD2828_WritePackageSize(2);SPI_WriteData(0x91);SPI_WriteData(0x02);
SSD2828_WritePackageSize(2);SPI_WriteData(0x92);SPI_WriteData(0x19);
SSD2828_WritePackageSize(2);SPI_WriteData(0x93);SPI_WriteData(0x02);
SSD2828_WritePackageSize(2);SPI_WriteData(0x94);SPI_WriteData(0x1A);
SSD2828_WritePackageSize(2);SPI_WriteData(0x95);SPI_WriteData(0x02);
SSD2828_WritePackageSize(2);SPI_WriteData(0x96);SPI_WriteData(0x4E);
SSD2828_WritePackageSize(2);SPI_WriteData(0x97);SPI_WriteData(0x02);
SSD2828_WritePackageSize(2);SPI_WriteData(0x98);SPI_WriteData(0x85);
SSD2828_WritePackageSize(2);SPI_WriteData(0x99);SPI_WriteData(0x02);
SSD2828_WritePackageSize(2);SPI_WriteData(0x9A);SPI_WriteData(0xA9);
SSD2828_WritePackageSize(2);SPI_WriteData(0x9B);SPI_WriteData(0x02);
SSD2828_WritePackageSize(2);SPI_WriteData(0x9C);SPI_WriteData(0xD9);
SSD2828_WritePackageSize(2);SPI_WriteData(0x9D);SPI_WriteData(0x02);
SSD2828_WritePackageSize(2);SPI_WriteData(0x9E);SPI_WriteData(0xFB);
SSD2828_WritePackageSize(2);SPI_WriteData(0x9F);SPI_WriteData(0x03);
SSD2828_WritePackageSize(2);SPI_WriteData(0xA0);SPI_WriteData(0x28);
SSD2828_WritePackageSize(2);SPI_WriteData(0xA2);SPI_WriteData(0x03);
SSD2828_WritePackageSize(2);SPI_WriteData(0xA3);SPI_WriteData(0x35);
SSD2828_WritePackageSize(2);SPI_WriteData(0xA4);SPI_WriteData(0x03);
SSD2828_WritePackageSize(2);SPI_WriteData(0xA5);SPI_WriteData(0x44);
SSD2828_WritePackageSize(2);SPI_WriteData(0xA6);SPI_WriteData(0x03);
SSD2828_WritePackageSize(2);SPI_WriteData(0xA7);SPI_WriteData(0x54);
SSD2828_WritePackageSize(2);SPI_WriteData(0xA9);SPI_WriteData(0x03);
SSD2828_WritePackageSize(2);SPI_WriteData(0xAA);SPI_WriteData(0x67);
SSD2828_WritePackageSize(2);SPI_WriteData(0xAB);SPI_WriteData(0x03);
SSD2828_WritePackageSize(2);SPI_WriteData(0xAC);SPI_WriteData(0x7D);
SSD2828_WritePackageSize(2);SPI_WriteData(0xAD);SPI_WriteData(0x03);
SSD2828_WritePackageSize(2);SPI_WriteData(0xAE);SPI_WriteData(0x91);
SSD2828_WritePackageSize(2);SPI_WriteData(0xAF);SPI_WriteData(0x03);
SSD2828_WritePackageSize(2);SPI_WriteData(0xB0);SPI_WriteData(0xA7);
SSD2828_WritePackageSize(2);SPI_WriteData(0xB1);SPI_WriteData(0x03);
SSD2828_WritePackageSize(2);SPI_WriteData(0xB2);SPI_WriteData(0xCB);
SSD2828_WritePackageSize(2);SPI_WriteData(0xB3);SPI_WriteData(0x00);
SSD2828_WritePackageSize(2);SPI_WriteData(0xB4);SPI_WriteData(0x9D);
SSD2828_WritePackageSize(2);SPI_WriteData(0xB5);SPI_WriteData(0x00);
SSD2828_WritePackageSize(2);SPI_WriteData(0xB6);SPI_WriteData(0xA2);
SSD2828_WritePackageSize(2);SPI_WriteData(0xB7);SPI_WriteData(0x00);
SSD2828_WritePackageSize(2);SPI_WriteData(0xB8);SPI_WriteData(0xB0);
SSD2828_WritePackageSize(2);SPI_WriteData(0xB9);SPI_WriteData(0x00);
SSD2828_WritePackageSize(2);SPI_WriteData(0xBA);SPI_WriteData(0xBD);
SSD2828_WritePackageSize(2);SPI_WriteData(0xBB);SPI_WriteData(0x00);
SSD2828_WritePackageSize(2);SPI_WriteData(0xBC);SPI_WriteData(0xC9);
SSD2828_WritePackageSize(2);SPI_WriteData(0xBD);SPI_WriteData(0x00);
SSD2828_WritePackageSize(2);SPI_WriteData(0xBE);SPI_WriteData(0xD4);
SSD2828_WritePackageSize(2);SPI_WriteData(0xBF);SPI_WriteData(0x00);
SSD2828_WritePackageSize(2);SPI_WriteData(0xC0);SPI_WriteData(0xDF);
SSD2828_WritePackageSize(2);SPI_WriteData(0xC1);SPI_WriteData(0x00);
SSD2828_WritePackageSize(2);SPI_WriteData(0xC2);SPI_WriteData(0xE9);
SSD2828_WritePackageSize(2);SPI_WriteData(0xC3);SPI_WriteData(0x00);
SSD2828_WritePackageSize(2);SPI_WriteData(0xC4);SPI_WriteData(0xF2);
SSD2828_WritePackageSize(2);SPI_WriteData(0xC5);SPI_WriteData(0x01);
SSD2828_WritePackageSize(2);SPI_WriteData(0xC6);SPI_WriteData(0x17);
SSD2828_WritePackageSize(2);SPI_WriteData(0xC7);SPI_WriteData(0x01);
SSD2828_WritePackageSize(2);SPI_WriteData(0xC8);SPI_WriteData(0x36);
SSD2828_WritePackageSize(2);SPI_WriteData(0xC9);SPI_WriteData(0x01);
SSD2828_WritePackageSize(2);SPI_WriteData(0xCA);SPI_WriteData(0x6B);
SSD2828_WritePackageSize(2);SPI_WriteData(0xCB);SPI_WriteData(0x01);
SSD2828_WritePackageSize(2);SPI_WriteData(0xCC);SPI_WriteData(0x98);
SSD2828_WritePackageSize(2);SPI_WriteData(0xCD);SPI_WriteData(0x01);
SSD2828_WritePackageSize(2);SPI_WriteData(0xCE);SPI_WriteData(0xE0);
SSD2828_WritePackageSize(2);SPI_WriteData(0xCF);SPI_WriteData(0x02);
SSD2828_WritePackageSize(2);SPI_WriteData(0xD0);SPI_WriteData(0x19);
SSD2828_WritePackageSize(2);SPI_WriteData(0xD1);SPI_WriteData(0x02);
SSD2828_WritePackageSize(2);SPI_WriteData(0xD2);SPI_WriteData(0x1A);
SSD2828_WritePackageSize(2);SPI_WriteData(0xD3);SPI_WriteData(0x02);
SSD2828_WritePackageSize(2);SPI_WriteData(0xD4);SPI_WriteData(0x4E);
SSD2828_WritePackageSize(2);SPI_WriteData(0xD5);SPI_WriteData(0x02);
SSD2828_WritePackageSize(2);SPI_WriteData(0xD6);SPI_WriteData(0x85);
SSD2828_WritePackageSize(2);SPI_WriteData(0xD7);SPI_WriteData(0x02);
SSD2828_WritePackageSize(2);SPI_WriteData(0xD8);SPI_WriteData(0xA9);
SSD2828_WritePackageSize(2);SPI_WriteData(0xD9);SPI_WriteData(0x02);
SSD2828_WritePackageSize(2);SPI_WriteData(0xDA);SPI_WriteData(0xD9);
SSD2828_WritePackageSize(2);SPI_WriteData(0xDB);SPI_WriteData(0x02);
SSD2828_WritePackageSize(2);SPI_WriteData(0xDC);SPI_WriteData(0xFB);
SSD2828_WritePackageSize(2);SPI_WriteData(0xDD);SPI_WriteData(0x03);
SSD2828_WritePackageSize(2);SPI_WriteData(0xDE);SPI_WriteData(0x28);
SSD2828_WritePackageSize(2);SPI_WriteData(0xDF);SPI_WriteData(0x03);
SSD2828_WritePackageSize(2);SPI_WriteData(0xE0);SPI_WriteData(0x35);
SSD2828_WritePackageSize(2);SPI_WriteData(0xE1);SPI_WriteData(0x03);
SSD2828_WritePackageSize(2);SPI_WriteData(0xE2);SPI_WriteData(0x44);
SSD2828_WritePackageSize(2);SPI_WriteData(0xE3);SPI_WriteData(0x03);
SSD2828_WritePackageSize(2);SPI_WriteData(0xE4);SPI_WriteData(0x54);
SSD2828_WritePackageSize(2);SPI_WriteData(0xE5);SPI_WriteData(0x03);
SSD2828_WritePackageSize(2);SPI_WriteData(0xE6);SPI_WriteData(0x67);
SSD2828_WritePackageSize(2);SPI_WriteData(0xE7);SPI_WriteData(0x03);
SSD2828_WritePackageSize(2);SPI_WriteData(0xE8);SPI_WriteData(0x7D);
SSD2828_WritePackageSize(2);SPI_WriteData(0xE9);SPI_WriteData(0x03);
SSD2828_WritePackageSize(2);SPI_WriteData(0xEA);SPI_WriteData(0x91);
SSD2828_WritePackageSize(2);SPI_WriteData(0xEB);SPI_WriteData(0x03);
SSD2828_WritePackageSize(2);SPI_WriteData(0xEC);SPI_WriteData(0xA7);
SSD2828_WritePackageSize(2);SPI_WriteData(0xED);SPI_WriteData(0x03);
SSD2828_WritePackageSize(2);SPI_WriteData(0xEE);SPI_WriteData(0xCB);
SSD2828_WritePackageSize(2);SPI_WriteData(0xEF);SPI_WriteData(0x00);
SSD2828_WritePackageSize(2);SPI_WriteData(0xF0);SPI_WriteData(0x7D);
SSD2828_WritePackageSize(2);SPI_WriteData(0xF1);SPI_WriteData(0x00);
SSD2828_WritePackageSize(2);SPI_WriteData(0xF2);SPI_WriteData(0x81);
SSD2828_WritePackageSize(2);SPI_WriteData(0xF3);SPI_WriteData(0x00);
SSD2828_WritePackageSize(2);SPI_WriteData(0xF4);SPI_WriteData(0x94);
SSD2828_WritePackageSize(2);SPI_WriteData(0xF5);SPI_WriteData(0x00);
SSD2828_WritePackageSize(2);SPI_WriteData(0xF6);SPI_WriteData(0xA2);
SSD2828_WritePackageSize(2);SPI_WriteData(0xF7);SPI_WriteData(0x00);
SSD2828_WritePackageSize(2);SPI_WriteData(0xF8);SPI_WriteData(0xAF);
SSD2828_WritePackageSize(2);SPI_WriteData(0xF9);SPI_WriteData(0x00);
SSD2828_WritePackageSize(2);SPI_WriteData(0xFA);SPI_WriteData(0xBC);
SSD2828_WritePackageSize(2);SPI_WriteData(0xFF);SPI_WriteData(0x02);
SSD2828_WritePackageSize(2);SPI_WriteData(0xFB);SPI_WriteData(0x01);
SSD2828_WritePackageSize(2);SPI_WriteData(0x00);SPI_WriteData(0x00);
SSD2828_WritePackageSize(2);SPI_WriteData(0x01);SPI_WriteData(0xC8);
SSD2828_WritePackageSize(2);SPI_WriteData(0x02);SPI_WriteData(0x00);
SSD2828_WritePackageSize(2);SPI_WriteData(0x03);SPI_WriteData(0xD4);
SSD2828_WritePackageSize(2);SPI_WriteData(0x04);SPI_WriteData(0x00);
SSD2828_WritePackageSize(2);SPI_WriteData(0x05);SPI_WriteData(0xDF);
SSD2828_WritePackageSize(2);SPI_WriteData(0x06);SPI_WriteData(0x01);
SSD2828_WritePackageSize(2);SPI_WriteData(0x07);SPI_WriteData(0x06);
SSD2828_WritePackageSize(2);SPI_WriteData(0x08);SPI_WriteData(0x01);
SSD2828_WritePackageSize(2);SPI_WriteData(0x09);SPI_WriteData(0x28);
SSD2828_WritePackageSize(2);SPI_WriteData(0x0A);SPI_WriteData(0x01);
SSD2828_WritePackageSize(2);SPI_WriteData(0x0B);SPI_WriteData(0x61);
SSD2828_WritePackageSize(2);SPI_WriteData(0x0C);SPI_WriteData(0x01);
SSD2828_WritePackageSize(2);SPI_WriteData(0x0D);SPI_WriteData(0x8F);
SSD2828_WritePackageSize(2);SPI_WriteData(0x0E);SPI_WriteData(0x01);
SSD2828_WritePackageSize(2);SPI_WriteData(0x0F);SPI_WriteData(0xDA);
SSD2828_WritePackageSize(2);SPI_WriteData(0x10);SPI_WriteData(0x02);
SSD2828_WritePackageSize(2);SPI_WriteData(0x11);SPI_WriteData(0x15);
SSD2828_WritePackageSize(2);SPI_WriteData(0x12);SPI_WriteData(0x02);
SSD2828_WritePackageSize(2);SPI_WriteData(0x13);SPI_WriteData(0x17);
SSD2828_WritePackageSize(2);SPI_WriteData(0x14);SPI_WriteData(0x02);
SSD2828_WritePackageSize(2);SPI_WriteData(0x15);SPI_WriteData(0x4C);
SSD2828_WritePackageSize(2);SPI_WriteData(0x16);SPI_WriteData(0x02);
SSD2828_WritePackageSize(2);SPI_WriteData(0x17);SPI_WriteData(0x83);
SSD2828_WritePackageSize(2);SPI_WriteData(0x18);SPI_WriteData(0x02);
SSD2828_WritePackageSize(2);SPI_WriteData(0x19);SPI_WriteData(0xA7);
SSD2828_WritePackageSize(2);SPI_WriteData(0x1A);SPI_WriteData(0x02);
SSD2828_WritePackageSize(2);SPI_WriteData(0x1B);SPI_WriteData(0xD8);
SSD2828_WritePackageSize(2);SPI_WriteData(0x1C);SPI_WriteData(0x02);
SSD2828_WritePackageSize(2);SPI_WriteData(0x1D);SPI_WriteData(0xFA);
SSD2828_WritePackageSize(2);SPI_WriteData(0x1E);SPI_WriteData(0x03);
SSD2828_WritePackageSize(2);SPI_WriteData(0x1F);SPI_WriteData(0x27);
SSD2828_WritePackageSize(2);SPI_WriteData(0x20);SPI_WriteData(0x03);
SSD2828_WritePackageSize(2);SPI_WriteData(0x21);SPI_WriteData(0x35);
SSD2828_WritePackageSize(2);SPI_WriteData(0x22);SPI_WriteData(0x03);
SSD2828_WritePackageSize(2);SPI_WriteData(0x23);SPI_WriteData(0x44);
SSD2828_WritePackageSize(2);SPI_WriteData(0x24);SPI_WriteData(0x03);
SSD2828_WritePackageSize(2);SPI_WriteData(0x25);SPI_WriteData(0x55);
SSD2828_WritePackageSize(2);SPI_WriteData(0x26);SPI_WriteData(0x03);
SSD2828_WritePackageSize(2);SPI_WriteData(0x27);SPI_WriteData(0x67);
SSD2828_WritePackageSize(2);SPI_WriteData(0x28);SPI_WriteData(0x03);
SSD2828_WritePackageSize(2);SPI_WriteData(0x29);SPI_WriteData(0x7F);
SSD2828_WritePackageSize(2);SPI_WriteData(0x2A);SPI_WriteData(0x03);
SSD2828_WritePackageSize(2);SPI_WriteData(0x2B);SPI_WriteData(0x92);
SSD2828_WritePackageSize(2);SPI_WriteData(0x2D);SPI_WriteData(0x03);
SSD2828_WritePackageSize(2);SPI_WriteData(0x2F);SPI_WriteData(0xAA);
SSD2828_WritePackageSize(2);SPI_WriteData(0x30);SPI_WriteData(0x03);
SSD2828_WritePackageSize(2);SPI_WriteData(0x31);SPI_WriteData(0xCB);
SSD2828_WritePackageSize(2);SPI_WriteData(0x32);SPI_WriteData(0x00);
SSD2828_WritePackageSize(2);SPI_WriteData(0x33);SPI_WriteData(0x7D);
SSD2828_WritePackageSize(2);SPI_WriteData(0x34);SPI_WriteData(0x00);
SSD2828_WritePackageSize(2);SPI_WriteData(0x35);SPI_WriteData(0x81);
SSD2828_WritePackageSize(2);SPI_WriteData(0x36);SPI_WriteData(0x00);
SSD2828_WritePackageSize(2);SPI_WriteData(0x37);SPI_WriteData(0x94);
SSD2828_WritePackageSize(2);SPI_WriteData(0x38);SPI_WriteData(0x00);
SSD2828_WritePackageSize(2);SPI_WriteData(0x39);SPI_WriteData(0xA2);
SSD2828_WritePackageSize(2);SPI_WriteData(0x3A);SPI_WriteData(0x00);
SSD2828_WritePackageSize(2);SPI_WriteData(0x3B);SPI_WriteData(0xAF);
SSD2828_WritePackageSize(2);SPI_WriteData(0x3D);SPI_WriteData(0x00);
SSD2828_WritePackageSize(2);SPI_WriteData(0x3F);SPI_WriteData(0xBC);
SSD2828_WritePackageSize(2);SPI_WriteData(0x40);SPI_WriteData(0x00);
SSD2828_WritePackageSize(2);SPI_WriteData(0x41);SPI_WriteData(0xC8);
SSD2828_WritePackageSize(2);SPI_WriteData(0x42);SPI_WriteData(0x00);
SSD2828_WritePackageSize(2);SPI_WriteData(0x43);SPI_WriteData(0xD4);
SSD2828_WritePackageSize(2);SPI_WriteData(0x44);SPI_WriteData(0x00);
SSD2828_WritePackageSize(2);SPI_WriteData(0x45);SPI_WriteData(0xDF);
SSD2828_WritePackageSize(2);SPI_WriteData(0x46);SPI_WriteData(0x01);
SSD2828_WritePackageSize(2);SPI_WriteData(0x47);SPI_WriteData(0x06);
SSD2828_WritePackageSize(2);SPI_WriteData(0x48);SPI_WriteData(0x01);
SSD2828_WritePackageSize(2);SPI_WriteData(0x49);SPI_WriteData(0x28);
SSD2828_WritePackageSize(2);SPI_WriteData(0x4A);SPI_WriteData(0x01);
SSD2828_WritePackageSize(2);SPI_WriteData(0x4B);SPI_WriteData(0x61);
SSD2828_WritePackageSize(2);SPI_WriteData(0x4C);SPI_WriteData(0x01);
SSD2828_WritePackageSize(2);SPI_WriteData(0x4D);SPI_WriteData(0x8F);
SSD2828_WritePackageSize(2);SPI_WriteData(0x4E);SPI_WriteData(0x01);
SSD2828_WritePackageSize(2);SPI_WriteData(0x4F);SPI_WriteData(0xDA);
SSD2828_WritePackageSize(2);SPI_WriteData(0x50);SPI_WriteData(0x02);
SSD2828_WritePackageSize(2);SPI_WriteData(0x51);SPI_WriteData(0x15);
SSD2828_WritePackageSize(2);SPI_WriteData(0x52);SPI_WriteData(0x02);
SSD2828_WritePackageSize(2);SPI_WriteData(0x53);SPI_WriteData(0x17);
SSD2828_WritePackageSize(2);SPI_WriteData(0x54);SPI_WriteData(0x02);
SSD2828_WritePackageSize(2);SPI_WriteData(0x55);SPI_WriteData(0x4C);
SSD2828_WritePackageSize(2);SPI_WriteData(0x56);SPI_WriteData(0x02);
SSD2828_WritePackageSize(2);SPI_WriteData(0x58);SPI_WriteData(0x83);
SSD2828_WritePackageSize(2);SPI_WriteData(0x59);SPI_WriteData(0x02);
SSD2828_WritePackageSize(2);SPI_WriteData(0x5A);SPI_WriteData(0xA7);
SSD2828_WritePackageSize(2);SPI_WriteData(0x5B);SPI_WriteData(0x02);
SSD2828_WritePackageSize(2);SPI_WriteData(0x5C);SPI_WriteData(0xD8);
SSD2828_WritePackageSize(2);SPI_WriteData(0x5D);SPI_WriteData(0x02);
SSD2828_WritePackageSize(2);SPI_WriteData(0x5E);SPI_WriteData(0xFA);
SSD2828_WritePackageSize(2);SPI_WriteData(0x5F);SPI_WriteData(0x03);
SSD2828_WritePackageSize(2);SPI_WriteData(0x60);SPI_WriteData(0x27);
SSD2828_WritePackageSize(2);SPI_WriteData(0x61);SPI_WriteData(0x03);
SSD2828_WritePackageSize(2);SPI_WriteData(0x62);SPI_WriteData(0x35);
SSD2828_WritePackageSize(2);SPI_WriteData(0x63);SPI_WriteData(0x03);
SSD2828_WritePackageSize(2);SPI_WriteData(0x64);SPI_WriteData(0x44);
SSD2828_WritePackageSize(2);SPI_WriteData(0x65);SPI_WriteData(0x03);
SSD2828_WritePackageSize(2);SPI_WriteData(0x66);SPI_WriteData(0x55);
SSD2828_WritePackageSize(2);SPI_WriteData(0x67);SPI_WriteData(0x03);
SSD2828_WritePackageSize(2);SPI_WriteData(0x68);SPI_WriteData(0x67);
SSD2828_WritePackageSize(2);SPI_WriteData(0x69);SPI_WriteData(0x03);
SSD2828_WritePackageSize(2);SPI_WriteData(0x6A);SPI_WriteData(0x7F);
SSD2828_WritePackageSize(2);SPI_WriteData(0x6B);SPI_WriteData(0x03);
SSD2828_WritePackageSize(2);SPI_WriteData(0x6C);SPI_WriteData(0x92);
SSD2828_WritePackageSize(2);SPI_WriteData(0x6D);SPI_WriteData(0x03);
SSD2828_WritePackageSize(2);SPI_WriteData(0x6E);SPI_WriteData(0xAA);
SSD2828_WritePackageSize(2);SPI_WriteData(0x6F);SPI_WriteData(0x03);
SSD2828_WritePackageSize(2);SPI_WriteData(0x70);SPI_WriteData(0xCB);
SSD2828_WritePackageSize(2);SPI_WriteData(0x71);SPI_WriteData(0x00);
SSD2828_WritePackageSize(2);SPI_WriteData(0x72);SPI_WriteData(0x00);
SSD2828_WritePackageSize(2);SPI_WriteData(0x73);SPI_WriteData(0x00);
SSD2828_WritePackageSize(2);SPI_WriteData(0x74);SPI_WriteData(0x21);
SSD2828_WritePackageSize(2);SPI_WriteData(0x75);SPI_WriteData(0x00);
SSD2828_WritePackageSize(2);SPI_WriteData(0x76);SPI_WriteData(0x4C);
SSD2828_WritePackageSize(2);SPI_WriteData(0x77);SPI_WriteData(0x00);
SSD2828_WritePackageSize(2);SPI_WriteData(0x78);SPI_WriteData(0x6B);
SSD2828_WritePackageSize(2);SPI_WriteData(0x79);SPI_WriteData(0x00);
SSD2828_WritePackageSize(2);SPI_WriteData(0x7A);SPI_WriteData(0x85);
SSD2828_WritePackageSize(2);SPI_WriteData(0x7B);SPI_WriteData(0x00);
SSD2828_WritePackageSize(2);SPI_WriteData(0x7C);SPI_WriteData(0x9A);
SSD2828_WritePackageSize(2);SPI_WriteData(0x7D);SPI_WriteData(0x00);
SSD2828_WritePackageSize(2);SPI_WriteData(0x7E);SPI_WriteData(0xAD);
SSD2828_WritePackageSize(2);SPI_WriteData(0x7F);SPI_WriteData(0x00);
SSD2828_WritePackageSize(2);SPI_WriteData(0x80);SPI_WriteData(0xBE);
SSD2828_WritePackageSize(2);SPI_WriteData(0x81);SPI_WriteData(0x00);
SSD2828_WritePackageSize(2);SPI_WriteData(0x82);SPI_WriteData(0xCD);
SSD2828_WritePackageSize(2);SPI_WriteData(0x83);SPI_WriteData(0x01);
SSD2828_WritePackageSize(2);SPI_WriteData(0x84);SPI_WriteData(0x01);
SSD2828_WritePackageSize(2);SPI_WriteData(0x85);SPI_WriteData(0x01);
SSD2828_WritePackageSize(2);SPI_WriteData(0x86);SPI_WriteData(0x29);
SSD2828_WritePackageSize(2);SPI_WriteData(0x87);SPI_WriteData(0x01);
SSD2828_WritePackageSize(2);SPI_WriteData(0x88);SPI_WriteData(0x68);
SSD2828_WritePackageSize(2);SPI_WriteData(0x89);SPI_WriteData(0x01);
SSD2828_WritePackageSize(2);SPI_WriteData(0x8A);SPI_WriteData(0x98);
SSD2828_WritePackageSize(2);SPI_WriteData(0x8B);SPI_WriteData(0x01);
SSD2828_WritePackageSize(2);SPI_WriteData(0x8C);SPI_WriteData(0xE5);
SSD2828_WritePackageSize(2);SPI_WriteData(0x8D);SPI_WriteData(0x02);
SSD2828_WritePackageSize(2);SPI_WriteData(0x8E);SPI_WriteData(0x1E);
SSD2828_WritePackageSize(2);SPI_WriteData(0x8F);SPI_WriteData(0x02);
SSD2828_WritePackageSize(2);SPI_WriteData(0x90);SPI_WriteData(0x20);
SSD2828_WritePackageSize(2);SPI_WriteData(0x91);SPI_WriteData(0x02);
SSD2828_WritePackageSize(2);SPI_WriteData(0x92);SPI_WriteData(0x52);
SSD2828_WritePackageSize(2);SPI_WriteData(0x93);SPI_WriteData(0x02);
SSD2828_WritePackageSize(2);SPI_WriteData(0x94);SPI_WriteData(0x88);
SSD2828_WritePackageSize(2);SPI_WriteData(0x95);SPI_WriteData(0x02);
SSD2828_WritePackageSize(2);SPI_WriteData(0x96);SPI_WriteData(0xAA);
SSD2828_WritePackageSize(2);SPI_WriteData(0x97);SPI_WriteData(0x02);
SSD2828_WritePackageSize(2);SPI_WriteData(0x98);SPI_WriteData(0xD7);
SSD2828_WritePackageSize(2);SPI_WriteData(0x99);SPI_WriteData(0x02);
SSD2828_WritePackageSize(2);SPI_WriteData(0x9A);SPI_WriteData(0xF7);
SSD2828_WritePackageSize(2);SPI_WriteData(0x9B);SPI_WriteData(0x03);
SSD2828_WritePackageSize(2);SPI_WriteData(0x9C);SPI_WriteData(0x21);
SSD2828_WritePackageSize(2);SPI_WriteData(0x9D);SPI_WriteData(0x03);
SSD2828_WritePackageSize(2);SPI_WriteData(0x9E);SPI_WriteData(0x2E);
SSD2828_WritePackageSize(2);SPI_WriteData(0x9F);SPI_WriteData(0x03);
SSD2828_WritePackageSize(2);SPI_WriteData(0xA0);SPI_WriteData(0x3D);
SSD2828_WritePackageSize(2);SPI_WriteData(0xA2);SPI_WriteData(0x03);
SSD2828_WritePackageSize(2);SPI_WriteData(0xA3);SPI_WriteData(0x4C);
SSD2828_WritePackageSize(2);SPI_WriteData(0xA4);SPI_WriteData(0x03);
SSD2828_WritePackageSize(2);SPI_WriteData(0xA5);SPI_WriteData(0x5E);
SSD2828_WritePackageSize(2);SPI_WriteData(0xA6);SPI_WriteData(0x03);
SSD2828_WritePackageSize(2);SPI_WriteData(0xA7);SPI_WriteData(0x71);
SSD2828_WritePackageSize(2);SPI_WriteData(0xA9);SPI_WriteData(0x03);
SSD2828_WritePackageSize(2);SPI_WriteData(0xAA);SPI_WriteData(0x86);
SSD2828_WritePackageSize(2);SPI_WriteData(0xAB);SPI_WriteData(0x03);
SSD2828_WritePackageSize(2);SPI_WriteData(0xAC);SPI_WriteData(0x94);
SSD2828_WritePackageSize(2);SPI_WriteData(0xAD);SPI_WriteData(0x03);
SSD2828_WritePackageSize(2);SPI_WriteData(0xAE);SPI_WriteData(0xFA);
SSD2828_WritePackageSize(2);SPI_WriteData(0xAF);SPI_WriteData(0x00);
SSD2828_WritePackageSize(2);SPI_WriteData(0xB0);SPI_WriteData(0x00);
SSD2828_WritePackageSize(2);SPI_WriteData(0xB1);SPI_WriteData(0x00);
SSD2828_WritePackageSize(2);SPI_WriteData(0xB2);SPI_WriteData(0x21);
SSD2828_WritePackageSize(2);SPI_WriteData(0xB3);SPI_WriteData(0x00);
SSD2828_WritePackageSize(2);SPI_WriteData(0xB4);SPI_WriteData(0x4C);
SSD2828_WritePackageSize(2);SPI_WriteData(0xB5);SPI_WriteData(0x00);
SSD2828_WritePackageSize(2);SPI_WriteData(0xB6);SPI_WriteData(0x6B);
SSD2828_WritePackageSize(2);SPI_WriteData(0xB7);SPI_WriteData(0x00);
SSD2828_WritePackageSize(2);SPI_WriteData(0xB8);SPI_WriteData(0x85);
SSD2828_WritePackageSize(2);SPI_WriteData(0xB9);SPI_WriteData(0x00);
SSD2828_WritePackageSize(2);SPI_WriteData(0xBA);SPI_WriteData(0x9A);
SSD2828_WritePackageSize(2);SPI_WriteData(0xBB);SPI_WriteData(0x00);
SSD2828_WritePackageSize(2);SPI_WriteData(0xBC);SPI_WriteData(0xAD);
SSD2828_WritePackageSize(2);SPI_WriteData(0xBD);SPI_WriteData(0x00);
SSD2828_WritePackageSize(2);SPI_WriteData(0xBE);SPI_WriteData(0xBE);
SSD2828_WritePackageSize(2);SPI_WriteData(0xBF);SPI_WriteData(0x00);
SSD2828_WritePackageSize(2);SPI_WriteData(0xC0);SPI_WriteData(0xCD);
SSD2828_WritePackageSize(2);SPI_WriteData(0xC1);SPI_WriteData(0x01);
SSD2828_WritePackageSize(2);SPI_WriteData(0xC2);SPI_WriteData(0x01);
SSD2828_WritePackageSize(2);SPI_WriteData(0xC3);SPI_WriteData(0x01);
SSD2828_WritePackageSize(2);SPI_WriteData(0xC4);SPI_WriteData(0x29);
SSD2828_WritePackageSize(2);SPI_WriteData(0xC5);SPI_WriteData(0x01);
SSD2828_WritePackageSize(2);SPI_WriteData(0xC6);SPI_WriteData(0x68);
SSD2828_WritePackageSize(2);SPI_WriteData(0xC7);SPI_WriteData(0x01);
SSD2828_WritePackageSize(2);SPI_WriteData(0xC8);SPI_WriteData(0x98);
SSD2828_WritePackageSize(2);SPI_WriteData(0xC9);SPI_WriteData(0x01);
SSD2828_WritePackageSize(2);SPI_WriteData(0xCA);SPI_WriteData(0xE5);
SSD2828_WritePackageSize(2);SPI_WriteData(0xCB);SPI_WriteData(0x02);
SSD2828_WritePackageSize(2);SPI_WriteData(0xCC);SPI_WriteData(0x1E);
SSD2828_WritePackageSize(2);SPI_WriteData(0xCD);SPI_WriteData(0x02);
SSD2828_WritePackageSize(2);SPI_WriteData(0xCE);SPI_WriteData(0x20);
SSD2828_WritePackageSize(2);SPI_WriteData(0xCF);SPI_WriteData(0x02);
SSD2828_WritePackageSize(2);SPI_WriteData(0xD0);SPI_WriteData(0x52);
SSD2828_WritePackageSize(2);SPI_WriteData(0xD1);SPI_WriteData(0x02);
SSD2828_WritePackageSize(2);SPI_WriteData(0xD2);SPI_WriteData(0x88);
SSD2828_WritePackageSize(2);SPI_WriteData(0xD3);SPI_WriteData(0x02);
SSD2828_WritePackageSize(2);SPI_WriteData(0xD4);SPI_WriteData(0xAA);
SSD2828_WritePackageSize(2);SPI_WriteData(0xD5);SPI_WriteData(0x02);
SSD2828_WritePackageSize(2);SPI_WriteData(0xD6);SPI_WriteData(0xD7);
SSD2828_WritePackageSize(2);SPI_WriteData(0xD7);SPI_WriteData(0x02);
SSD2828_WritePackageSize(2);SPI_WriteData(0xD8);SPI_WriteData(0xF7);
SSD2828_WritePackageSize(2);SPI_WriteData(0xD9);SPI_WriteData(0x03);
SSD2828_WritePackageSize(2);SPI_WriteData(0xDA);SPI_WriteData(0x21);
SSD2828_WritePackageSize(2);SPI_WriteData(0xDB);SPI_WriteData(0x03);
SSD2828_WritePackageSize(2);SPI_WriteData(0xDC);SPI_WriteData(0x2E);
SSD2828_WritePackageSize(2);SPI_WriteData(0xDD);SPI_WriteData(0x03);
SSD2828_WritePackageSize(2);SPI_WriteData(0xDE);SPI_WriteData(0x3D);
SSD2828_WritePackageSize(2);SPI_WriteData(0xDF);SPI_WriteData(0x03);
SSD2828_WritePackageSize(2);SPI_WriteData(0xE0);SPI_WriteData(0x4C);
SSD2828_WritePackageSize(2);SPI_WriteData(0xE1);SPI_WriteData(0x03);
SSD2828_WritePackageSize(2);SPI_WriteData(0xE2);SPI_WriteData(0x5E);
SSD2828_WritePackageSize(2);SPI_WriteData(0xE3);SPI_WriteData(0x03);
SSD2828_WritePackageSize(2);SPI_WriteData(0xE4);SPI_WriteData(0x71);
SSD2828_WritePackageSize(2);SPI_WriteData(0xE5);SPI_WriteData(0x03);
SSD2828_WritePackageSize(2);SPI_WriteData(0xE6);SPI_WriteData(0x86);
SSD2828_WritePackageSize(2);SPI_WriteData(0xE7);SPI_WriteData(0x03);
SSD2828_WritePackageSize(2);SPI_WriteData(0xE8);SPI_WriteData(0x94);
SSD2828_WritePackageSize(2);SPI_WriteData(0xE9);SPI_WriteData(0x03);
SSD2828_WritePackageSize(2);SPI_WriteData(0xEA);SPI_WriteData(0xFA);
SSD2828_WritePackageSize(2);SPI_WriteData(0xFF);SPI_WriteData(0x01);
SSD2828_WritePackageSize(2);SPI_WriteData(0xFB);SPI_WriteData(0x01);
SSD2828_WritePackageSize(2);SPI_WriteData(0xFF);SPI_WriteData(0x02);
SSD2828_WritePackageSize(2);SPI_WriteData(0xFB);SPI_WriteData(0x01);
SSD2828_WritePackageSize(2);SPI_WriteData(0xFF);SPI_WriteData(0x04);
SSD2828_WritePackageSize(2);SPI_WriteData(0xFB);SPI_WriteData(0x01);
SSD2828_WritePackageSize(2);SPI_WriteData(0xFF);SPI_WriteData(0x00);
SSD2828_WritePackageSize(2);SPI_WriteData(0xD3);SPI_WriteData(0x05);
SSD2828_WritePackageSize(2);SPI_WriteData(0xD4);SPI_WriteData(0x04);		
 





	
	SSD2828_WritePackageSize(1);
	SPI_WriteData(0x11);		   	  //????
	Delay_ms(200);
	SSD2828_WritePackageSize(2);SPI_WriteData(0xFF);SPI_WriteData(0x00);
	SSD2828_WritePackageSize(2);SPI_WriteData(0x35);SPI_WriteData(0x00);

	SSD2828_WritePackageSize(1);
	SPI_WriteData(0x29);		     //display ON 		   
	Delay_ms(120); 
 
 
//----------------------------------

	SPI_WriteCmd(0xb7);
	SPI_WriteData(0x50);   //50
	SPI_WriteData(0x00);   //Configuration Register

	SPI_WriteCmd(0xb8);
	SPI_WriteData(0x00);
	SPI_WriteData(0x00);   //VC(Virtual ChannelID) Control Register

	SPI_WriteCmd(0xb9);
	SPI_WriteData(0x00);//1=PLL disable
	SPI_WriteData(0x00);

	SPI_WriteCmd(0xBA);
	SPI_WriteData(0x23); //	 24x35=840M
	SPI_WriteData(0xC0);//
				//c0,23
	SPI_WriteCmd(0xBB);//LP Clock Divider LP clock 
	SPI_WriteData(0x08);//840/8+1/8=12
	SPI_WriteData(0x00);

	SPI_WriteCmd(0xb9);
	SPI_WriteData(0x01);//1=PLL disable
	SPI_WriteData(0x00);

	SPI_WriteCmd(0xc9);
	SPI_WriteData(0x02);
	SPI_WriteData(0x23);   //p1: HS-Data-zero  p2: HS-Data- prepare  --> 8031 issue
	Delay_ms(5);

	SPI_WriteCmd(0xCA);
	SPI_WriteData(0x01);//CLK Prepare
	SPI_WriteData(0x23);//Clk Zero

	SPI_WriteCmd(0xCB); //local_write_reg(addr=0xCB,data=0x0510)
	SPI_WriteData(0x10); //Clk Post
	SPI_WriteData(0x05); //Clk Per

	SPI_WriteCmd(0xCC); //local_write_reg(addr=0xCC,data=0x100A)
	SPI_WriteData(0x05); //HS Trail
	SPI_WriteData(0x10); //Clk Trail
	Delay_ms(5);

	//SPI_WriteCmd(0xD0);//local_write_reg(addr=0xCC,data=0x100A)
	//SPI_WriteData(0x00);//HS Trail
	//SPI_WriteData(0x00);//Clk Trail
	//Delay(5);


	LoadLcdParameterConfig();

	SPI_WriteCmd(0xB6);//RGB CLK  16BPP=00 18BPP=01
	SPI_WriteData(0x0B);//D7=0 D6=0 D5=0  D1-0=11 – 24bpp//   03
	SPI_WriteData(0x00);//D15=VS D14=HS D13=CLK D12-9=NC D8=0=Video with blanking packet. 00-
	//2BE0

	//MIPI lane configuration
	SPI_WriteCmd(0xDE);//通道数
	SPI_WriteData(0x03);//11=4LANE 10=3LANE 01=2LANE 00=1LANE
	SPI_WriteData(0x00);

	SPI_WriteCmd(0xD6);//  05=BGR  04=RGB
	SPI_WriteData(0x05);//D0=0=RGB 1:BGR D1=1=Most significant byte sent first
	SPI_WriteData(0x00);

	SPI_WriteCmd(0xB7);
	SPI_WriteData(0x4B);	//6B //4B
	SPI_WriteData(0x02);
	Delay(100);
	SPI_WriteCmd(0x2C);

}



