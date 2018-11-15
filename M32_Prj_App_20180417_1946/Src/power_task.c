#include "power_task.h"
#include "pport_spi.h"
#include "app.h"
#include "lcd_cfg.h"
#include "user_config.h"
#include "GPU_Cfg.h"
#include "vspn_ctrl.h"
//extern  void LCDsleepIn(void);





//关断电源板电源(下电), 控制电源下电顺序
void Power_Off() {
//	SPI_WriteCmd(0xB7);
//	SPI_WriteData(0x50);//10=TX_CLK 50=PCLK
//	SPI_WriteData(0x02);

//	SPI_WriteCmd(0xBD);
//	SPI_WriteData(0x00);
//	SPI_WriteData(0x00);

//  SSD2828_WritePackageSize(1);
//	SPI_WriteData(0x28);		   	  //SleepIn
//	Delay_ms(100);
//	SSD2828_WritePackageSize(1);
//	SPI_WriteData(0x10);		     //display OFF
//	Delay_ms(120);
	
//	Lcd_Reset(0); //LCD reset 拉低
	Delay_ms(20);
Lcd_ShowMode(4);
	Delay_ms(100);
	//LCDsleepIn();
		
	O_PWR_EN_VSN(0); // LCD_VSN下电
	Delay_ms(3);
	O_PWR_EN_VSP(0); // 子板上LCD_VSP下电
	Delay_ms(3);

	O_PWR_EN_LCDIOVCC(0); // 子板上LCD_1V8下电
	Delay_ms(10);
	
	
	O_PWR_EN_LCDVCC(0); // 子板上LCD_IOVCC下电
	Delay_ms(10);


	O_PWR_BL_PWM(0); //BL_PWM
	O_PWR_BL_EN(0); //BL_EN, LEDA背光对应的12V输入使能
	Delay_ms(500);

	
}

//打开电源板电源(上电), 控制电源上电顺序
void Power_On(void) {
	Reset(0);
	Delay_ms(50);
//Lcd_ShowMode(1);
	
	O_PWR_EN_LCDVCC(1);
	Delay_ms(1);
	
		O_PWR_EN_LCDIOVCC(1);
	Delay_ms(25);
	
		//reset_lcd();
	VSPN_SetVSNVoltage(ptr_MIPI_TABLE[gMipiTableIndex]->VSP_mV);
	VSPN_SetVSPVoltage(ptr_MIPI_TABLE[gMipiTableIndex]->VSN_mV);	
	VSPN_OutOn();
	
	O_PWR_EN_VSP(1);
	Delay_ms(3);
	
	O_PWR_EN_VSN(1);
	Delay_ms(3);
	
	
	Reset(1);
	Delay_ms(20);

	O_PWR_BL_PWM(1); //BL_PWM, 先暂时按100%来
	O_PWR_BL_EN(1); //BL_EN, LEDA背光对应的12V输入使能
	
	
  ptr_MIPI_TABLE[gMipiTableIndex]->ptr_Initial_LCM(); //写可以用或, 读得一个一个来	
Lcd_ShowMode(1);
}

