#ifndef __PPORT_SPI_H
#define __PPORT_SPI_H


#include "BasicDataType.h"
#include "user_gpio_def.h"


void init_spi(void);
void reset_lcd(void);
void Delay_ms(unsigned int ms);
void SPI_3W_SET_Cmd(unsigned int Sdata);
void SPI_3W_SET_PAs(unsigned int Sdata);
unsigned char SPI_ReadData(void);
void SPI_WriteData(unsigned char value);
void SPI_WriteCmd(unsigned char value);
void SPI_2828_WrReg(unsigned char c,unsigned char PAs_L, unsigned char PAs_H);
void GP_COMMAD_PA(unsigned int num);

void Reset(unsigned char Val);
void Lcd_Reset(unsigned char Val);
void Delay(unsigned int x);
void SSD2828_RegConfig(unsigned char address,unsigned char lbyte,unsigned char hbyte);
void SSD2828_WritePackageSize(unsigned char num);
unsigned char Ssd2828_ID_OK_check(void);
unsigned char Ssd2828_ID_OK_check_CmdMode(void);
void LoadLcdParameterConfig(void);
void LoadLcdParameterConfig_CmdMode(void);
void SSD2828WriteReg(unsigned char c,  unsigned char PAs_H, unsigned char PAs_L);

#endif /* __PPORT_SPI_H */
