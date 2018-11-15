
#ifndef __USER_H
#define __USER_H

#include "stm32f10x.h"
#include <string.h>
#include "lcd_drv.h"
#include "systick.h"
#include "power_ctrl.h"
#include "lcd_drv.h"
#include "ssd2828.h"
#include "in_img.h"
#include "key.h"
#include "sdcard.h"
#include "ff.h"
#include "diskio.h"	  
#include "l1w.h"	
#include "stm32f10x_usart.h"
#include "stdio.h"	 			 
#include "showtext.h"	
#include "gxnussd2828.h"
#include "string.h"
#include "bmp.h"
#include "stdarg.h"
#include "bsp_usart1.h"
#include "bsp_sdio_sdcard.h"

#include "hw_config.h" 
#include "usb_lib.h"
#include "usb_pwr.h"
#include "gxnu.h"
//#include "user.h"
#include "delay.h"

//#define YT70F21X0
#define YT52F10A1
//#define YT52F12X0

extern UINT uTimerH,uPreTimerH,uTimerL,uTimerPicH,uTimerPicL;
extern BYTE BurnStart,picDisBeforeBurn,u8PicIndex;
extern BYTE buffer1[513];

extern void LCD_SSD_SET(void);
void LCD_INIT(void);
void SDcard_init(void);
void usb_hid_mass_init(void);
int hid_printf(const char *fmt, ...);

void Usart_Init(u32 bound);
void LCDGPIO_Configuration(void);	//void GPIO_Configuration(void);
void LCM_RST_1(void);
void LCM_RST_0(void);
void POWER_ON(void);
void POWER_OFF(void);
void LCM_BIST_1(void);
void LCM_BIST_0(void);
void TIM3_Int_Init(u16 arr,u16 psc);
void TIM3_IRQHandler(void);
unsigned int ReadVCOM(void);
int printfk(uint32_t x,uint32_t y,u8 font,uint32_t color,uint32_t bcolor,char mode,const char *fmt, ...);
void USB_SendString(u8 *str);
void usb_port_set(u8 enable);
void InitMipi_PanelInit(void);
void DisplayON_PanelInit(void);
void exit_sleep(void);
void sleep(void);
void DisplayOFF(void);
void InitMipi_PanelInitr(void);
void InitMipi_PanelInitr(void);
void InitMipi_PanelInitTTTT(void);
void OutPutSdCardFileRollingover(char* file_name);
void OutPutSdCardFileOverturn(char* file_name);
void OutPutSdCardFile(char* file_name);



#endif




