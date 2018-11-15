#include "pport_spi.h"
#include "lcd_cfg.h"
#include "user_config.h"
#include "GPU_Cfg.h"
#include "tools.h"
#include <stdio.h>


void Initial_LCM_1080x1920_KuPai_8750(void) {

Reset(0x00);  //复位
	delayms(200);
	Reset(0x01);
	delayms(200);
	printf("initial begin \n");



	
SPI_WriteCmd(0xb7);
SPI_WriteData(0x50);//  LP mode(DCS mode & HS clk disable) 
SPI_WriteData(0x00);    


SPI_WriteCmd(0xb8);
SPI_WriteData(0x00);
SPI_WriteData(0x00);   //VC(Virtual ChannelID) Control Register

SPI_WriteCmd(0xb9);
SPI_WriteData(0x00);//1=PLL disable
SPI_WriteData(0x00);
Delay(10);
//TX_CLK/MS should be between 5Mhz to100Mhz
SPI_WriteCmd(0xBA);
SPI_WriteData(0x14);
SPI_WriteData(0x42);
Delay(10);
SPI_WriteCmd(0xBB);
SPI_WriteData(0x03);
SPI_WriteData(0x00);
Delay(10);
SPI_WriteCmd(0xb9);
SPI_WriteData(0x01);//1=PLL disable
SPI_WriteData(0x00);
Delay(100);

SPI_WriteCmd(0xDE);
SPI_WriteData(0x00);
SPI_WriteData(0x00);  
Delay(10);

SPI_WriteCmd(0xc9);
SPI_WriteData(0x02);
SPI_WriteData(0x23);
Delay(100);

//////////////////Initial  CODE///////////////////////

		SSD2828_WritePackageSize(2);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
 
SSD2828_WritePackageSize(4);
SPI_WriteData(0xFF);
SPI_WriteData(0x19);
SPI_WriteData(0x11);
SPI_WriteData(0x01);
 
SSD2828_WritePackageSize(2);
SPI_WriteData(0x00);
SPI_WriteData(0x80);
 
SSD2828_WritePackageSize(3);
SPI_WriteData(0xFF);
SPI_WriteData(0x19);
SPI_WriteData(0x11);
 
SSD2828_WritePackageSize(2);
SPI_WriteData(0x00);
SPI_WriteData(0x93);
 
SSD2828_WritePackageSize(2);
SPI_WriteData(0xB3);
SPI_WriteData(0x06);
 
SSD2828_WritePackageSize(2);
SPI_WriteData(0x00);
SPI_WriteData(0xB0);
 
SSD2828_WritePackageSize(5);
SPI_WriteData(0xB3);
SPI_WriteData(0x04);
SPI_WriteData(0x38);
SPI_WriteData(0x08);
SPI_WriteData(0x70);
 
SSD2828_WritePackageSize(2);
SPI_WriteData(0x00);
SPI_WriteData(0x81);
 
SSD2828_WritePackageSize(4);
SPI_WriteData(0xC1);
SPI_WriteData(0xB0);
SPI_WriteData(0xC0);
SPI_WriteData(0xF0);
 
SSD2828_WritePackageSize(2);
SPI_WriteData(0x00);
SPI_WriteData(0x83);
 
SSD2828_WritePackageSize(3);
SPI_WriteData(0xC3);
SPI_WriteData(0x22);
SPI_WriteData(0x22);
 
SSD2828_WritePackageSize(2);
SPI_WriteData(0x00);
SPI_WriteData(0x90);
 
SSD2828_WritePackageSize(3);
SPI_WriteData(0xC3);
SPI_WriteData(0x20);
SPI_WriteData(0x20);
 
SSD2828_WritePackageSize(2);
SPI_WriteData(0x00);
SPI_WriteData(0x90);

SSD2828_WritePackageSize(6);
SPI_WriteData(0xC5);
SPI_WriteData(0x45);
SPI_WriteData(0xA0);
SPI_WriteData(0x33);
SPI_WriteData(0x65);
SPI_WriteData(0x80);
 
 
 
SSD2828_WritePackageSize(2);
SPI_WriteData(0x35); 
SPI_WriteData(0x00); 

 
SSD2828_WritePackageSize(1);
SPI_WriteData(0x11); 
  Delay(120);
SSD2828_WritePackageSize(1);
SPI_WriteData(0x29);
 Delay(50);

        



////////////////////Initial  CODE/////////////////////



//SSD2828_Initial
SPI_WriteCmd(0xb7);
SPI_WriteData(0x50);
SPI_WriteData(0x00);  
 
SPI_WriteCmd(0xb8);
SPI_WriteData(0x00);
SPI_WriteData(0x00);   

SPI_WriteCmd(0xb9);
SPI_WriteData(0x00);
SPI_WriteData(0x00);

SPI_WriteCmd(0xBA);
SPI_WriteData(0x5B);
SPI_WriteData(0xc2);

SPI_WriteCmd(0xBB);
SPI_WriteData(0x07);
SPI_WriteData(0x00);

SPI_WriteCmd(0xb9);
SPI_WriteData(0x01);
SPI_WriteData(0x00);

SPI_WriteCmd(0xc9);
SPI_WriteData(0x02);
SPI_WriteData(0x23); 
Delay(5);

SPI_WriteCmd(0xCA);
SPI_WriteData(0x01);
SPI_WriteData(0x23);

SPI_WriteCmd(0xCB); 
SPI_WriteData(0x10);
SPI_WriteData(0x05);

SPI_WriteCmd(0xCC); 
SPI_WriteData(0x05);
SPI_WriteData(0x10);
Delay(5);

SPI_WriteCmd(0xD0); 
SPI_WriteData(0x00);
SPI_WriteData(0x00);
Delay(5);


LoadLcdParameterConfig();   	

SPI_WriteCmd(0xb6);
SPI_WriteData(0x0B);
SPI_WriteData(0x00);


SPI_WriteCmd(0xDE);
SPI_WriteData(0x03);  //01 2LINE  02  3LINE  03 4LINE
SPI_WriteData(0x00);

SPI_WriteCmd(0xD6);
SPI_WriteData(0x05);
SPI_WriteData(0x00);

SPI_WriteCmd(0xB7);
SPI_WriteData(0x4B);
SPI_WriteData(0x02);Delay(100);

SPI_WriteCmd(0x2C);

}
void LCDsleepIn(void)
{
	
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

	//2BE0

	//MIPI lane configuration
	SPI_WriteCmd(0xDE);//通道数
	SPI_WriteData(0x03);//11=4LANE 10=3LANE 01=2LANE 00=1LANE
	SPI_WriteData(0x00);

	SPI_WriteCmd(0xD6);//  05=BGR  04=RGB
	SPI_WriteData(0x05);//D0=0=RGB 1:BGR D1=1=Most significant byte sent first
	SPI_WriteData(0x00);

	SSD2828_WritePackageSize(1);
	SPI_WriteData(0x28);		   	  //????
	Delay(200);
	
	

	SSD2828_WritePackageSize(1);
	SPI_WriteData(0x10);		     //display ON 		   
	Delay(120); 
	
	
	
	

	SPI_WriteCmd(0xB7);
	SPI_WriteData(0x4B);	//6B //4B
	SPI_WriteData(0x02);
	Delay(100);
	SPI_WriteCmd(0x2C);
		Reset(0x00);
}


