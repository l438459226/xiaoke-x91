

#ifndef _SSD2828_H_
#define _SSD2828_H_

#include "stm32f10x.h"
#include "SysTick.h"
#include "lcd_drv.h"

///////////////////////////////////////////////////////////////////////////////
#define MIPI_READ_FAIL 0X01	          //讀失敗 是通信失敗
#define MIPI_READ_SUCCEED 0X00		  //讀成功 是通信成功，並不能說明讀出來的值就是對的值
							  
///////////////////////////////////////////////////////////////////////////////

void SSD2828_RST_H(void);
void SSD2828_RST_L(void);

void SSD2828_IC1_CS_0(void);
void SSD2828_IC1_CS_1(void);
void SSD2828_IC2_CS_0(void);
void SSD2828_IC2_CS_1(void);
void SSD2828Init(void);
void SSD2828Video(void);
void SSD2828LP(void);
void SSD2828_STOP(void);
void SSD2828_STOP_1(void);

void GP_LP(unsigned long n); 
void GP_SP(unsigned char n); 
void DCS_LP(unsigned long n);
void DCS_SP(unsigned char n);
unsigned int DCS_R(uint8_t adr, uint16_t l, uint8_t *p);
unsigned int GP_R(uint8_t adr, uint16_t l, uint8_t *p);


void W_D(unsigned char dat);
void W_C(unsigned char cmd);
void W_REG(unsigned char cmd,unsigned char dat1,unsigned char dat2);
void Write_SSPI_REG(unsigned char cmd,unsigned short dat);


void WR_DT29(unsigned long n); 
void WR_DT03_13_23(unsigned char n);
void WR_DT39(unsigned long n); 
void WR_DT05_15(unsigned char n);
unsigned int RD_DT06(uint8_t adr, uint16_t l, uint8_t *p); 
unsigned int RD_DT14(uint8_t adr, uint16_t l, uint8_t *p); 


uint16_t SSD2828ReadReg(uint8_t reg);
u16 ssd_rdata(u8 reg);
void ssd_wdata(u8 reg,u16 parmer);
void Generic_Short_Write_NP(u8 Generic);
void Generic_Short_Write_1P(u8 Generic,u8 Parma);	
void Generic_Long_Write_2P(u8 Generic,u8 Parma1,u8 Parma2);
void Generic_Long_Write_3P(u8 Generic,u8 Parma1,u8 Parma2,u8 Parma3);
void Generic_Long_Write_4P(u8 Generic,u8 Parma1,u8 Parma2,u8 Parma3,u8 Parma4);
void Generic_Long_Write_5P(u8 Generic,u8 Parma1,u8 Parma2,u8 Parma3,u8 Parma4,u8 Parma5);
void Generic_Long_Write_6P(u8 Generic,u8 Parma1,u8 Parma2,u8 Parma3,u8 Parma4,u8 Parma5,u8 Parma6);
void Generic_Long_Write_7P(u8 Generic,u8 Parma1,u8 Parma2,u8 Parma3,u8 Parma4,u8 Parma5,u8 Parma6,u8 Parma7);
void Generic_Long_Write_FIFO(u16 num,u8 *Parma);
u32 Generic_Short_Read_NP(u16 reg, u8 cnt, u8 *Parma);

void DCS_Short_Write_NP(u8 Generic);
void DCS_Short_Write_1P(u8 Generic,u8 Parma);	
void DCS_Long_Write_2P(u8 Generic,u8 Parma1,u8 Parma2);
void DCS_Long_Write_3P(u8 Generic,u8 Parma1,u8 Parma2,u8 Parma3);
void DCS_Long_Write_4P(u8 Generic,u8 Parma1,u8 Parma2,u8 Parma3,u8 Parma4);
void DCS_Long_Write_5P(u8 Generic,u8 Parma1,u8 Parma2,u8 Parma3,u8 Parma4,u8 Parma5);
void DCS_Long_Write_6P(u8 Generic,u8 Parma1,u8 Parma2,u8 Parma3,u8 Parma4,u8 Parma5,u8 Parma6);
void DCS_Long_Write_7P(u8 Generic,u8 Parma1,u8 Parma2,u8 Parma3,u8 Parma4,u8 Parma5,u8 Parma6,u8 Parma7);
void DCS_Long_Write_FIFO(u16 num,u8 *Parma);
u32 DCS_Short_Read_NP(u16 reg, u8 cnt, u8 *Parma);




#endif


