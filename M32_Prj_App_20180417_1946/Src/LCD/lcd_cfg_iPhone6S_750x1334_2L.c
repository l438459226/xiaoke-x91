#include "pport_spi.h"
#include "lcd_cfg.h"
#include "user_config.h"
#include "GPU_Cfg.h"
#include "tools.h"



void Initial_LCM_iPhone6S_750x1334_2L(void){

Reset(0x00);  //¸´Î»
	delayms(200);
	Reset(0x01);
	delayms(200);
	//printf("initial begin \n");

	//----------------------
	SPI_WriteCmd(0xB7);
	SPI_WriteData(0x50);
	SPI_WriteData(0x02);

	SPI_WriteCmd(0xB8);
	SPI_WriteData(0x00);
	SPI_WriteData(0x00);

	SPI_WriteCmd(0xB9);				// PLL OFF
	SPI_WriteData(0x00);
	SPI_WriteData(0x00);

	SPI_WriteCmd(0xBA);				// PLL Output
	//SPI_WriteData(0x2C);
    SPI_WriteData(0x2E);
	SPI_WriteData(0xC0);

	SPI_WriteCmd(0xBB);				// LP Clock = PLL Output/8/x
	SPI_WriteData(0x20);
	SPI_WriteData(0x00);

	SPI_WriteCmd(0xB9);				// PLL ON
	SPI_WriteData(0x01);
	SPI_WriteData(0x00);

	SPI_WriteCmd(0xC9);
	SPI_WriteData(0x02);
	SPI_WriteData(0x23);   //p1: HS-Data-zero  p2: HS-Data- prepare  --> 8031 issue

	SPI_WriteCmd(0xCA);
	SPI_WriteData(0x01);//CLK Prepare
	SPI_WriteData(0x23);//Clk Zero

	SPI_WriteCmd(0xCB); //local_write_reg(addr=0xCB,data=0x0510)
	SPI_WriteData(0x10); //Clk Post
	SPI_WriteData(0x05); //Clk Per

	SPI_WriteCmd(0xCC); //local_write_reg(addr=0xCC,data=0x100A)
	SPI_WriteData(0x05); //HS Trail
	SPI_WriteData(0x10); //Clk Trail

	//RGB parameter
	LoadLcdParameterConfig();

	SPI_WriteCmd(0xB6);
	SPI_WriteData(0x23);
	SPI_WriteData(0x00);

	SPI_WriteCmd(0xDE);
	SPI_WriteData(0x01); //6s-2lane  6-3lane
	SPI_WriteData(0x00);

//	SPI_WriteCmd(0xD6);
//	SPI_WriteData(0x04);
//	SPI_WriteData(0x00);

	SPI_WriteCmd(0xD9);
	SPI_WriteData(0xA0);
	SPI_WriteData(0x74);
	//SPI_WriteData(0x70);

	SPI_WriteCmd(0xB7);
	SPI_WriteData(0x50);
	SPI_WriteData(0x02);

	SSD2828_WritePackageSize(1);
	SPI_WriteData(0x11);
	Delay(150);

	SSD2828_WritePackageSize(1);
	SPI_WriteData(0x29);
	Delay(100);

	SPI_WriteCmd(0xB7);
	SPI_WriteData(0x4B);
	SPI_WriteData(0x02);
	Delay(10);

	//printf("\r\n11,29 display \r\n");


}


