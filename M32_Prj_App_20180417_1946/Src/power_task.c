#include "power_task.h"
#include "pport_spi.h"
#include "app.h"
#include "lcd_cfg.h"
#include "user_config.h"
#include "GPU_Cfg.h"
#include "vspn_ctrl.h"
//extern  void LCDsleepIn(void);





//�ضϵ�Դ���Դ(�µ�), ���Ƶ�Դ�µ�˳��
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
	
//	Lcd_Reset(0); //LCD reset ����
	Delay_ms(20);
Lcd_ShowMode(4);
	Delay_ms(100);
	//LCDsleepIn();
		
	O_PWR_EN_VSN(0); // LCD_VSN�µ�
	Delay_ms(3);
	O_PWR_EN_VSP(0); // �Ӱ���LCD_VSP�µ�
	Delay_ms(3);

	O_PWR_EN_LCDIOVCC(0); // �Ӱ���LCD_1V8�µ�
	Delay_ms(10);
	
	
	O_PWR_EN_LCDVCC(0); // �Ӱ���LCD_IOVCC�µ�
	Delay_ms(10);


	O_PWR_BL_PWM(0); //BL_PWM
	O_PWR_BL_EN(0); //BL_EN, LEDA�����Ӧ��12V����ʹ��
	Delay_ms(500);

	
}

//�򿪵�Դ���Դ(�ϵ�), ���Ƶ�Դ�ϵ�˳��
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

	O_PWR_BL_PWM(1); //BL_PWM, ����ʱ��100%��
	O_PWR_BL_EN(1); //BL_EN, LEDA�����Ӧ��12V����ʹ��
	
	
  ptr_MIPI_TABLE[gMipiTableIndex]->ptr_Initial_LCM(); //д�����û�, ����һ��һ����	
Lcd_ShowMode(1);
}

