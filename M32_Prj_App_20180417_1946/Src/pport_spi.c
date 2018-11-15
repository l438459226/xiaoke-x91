#include "pport_spi.h"
#include "tools.h"
#include "user_config.h"
#include "GPU_Cfg.h"







void init_spi(void) {
	O_SSD2828_SPI_CS(1);
	O_SSD2828_SPI_CLK(0);
	O_SSD2828_SPI_SDI(1);
}

void reset_lcd(void) {
	//RESET   = 1;
//	O_TEST1_TP_RESET(1);
	O_SSD2828_RESET(1);
	
	delayms(5);
	
	//RESET   = 0;
//	O_TEST1_TP_RESET(0);
	O_SSD2828_RESET(0);
	
	delayms(10);
	
	//RESET   = 1;
//	O_TEST1_TP_RESET(1);
	O_SSD2828_RESET(1);
	
	delayms(35);
}



void Delay_ms(unsigned int ms) {
	delayms(ms);
}




void SPI_3W_SET_Cmd(unsigned int Sdata) { //设备ID发送函数
	unsigned char i;
	
	O_SSD2828_SPI_CS(0);
	O_SSD2828_SPI_SDI(0);
	O_SSD2828_SPI_CLK(0); //上升沿发送数据
	O_SSD2828_SPI_CLK(1);
	
	for(i=8; i>0; i--) {
		if(Sdata&0x80) //判断高位是否为1
			O_SSD2828_SPI_SDI(1);
		else
			O_SSD2828_SPI_SDI(0);
		O_SSD2828_SPI_CLK(0); //上升沿发送数据
		O_SSD2828_SPI_CLK(1);
		Sdata <<= 1;
	}
	O_SSD2828_SPI_CLK(0);
	O_SSD2828_SPI_CS(1);
}

void SPI_3W_SET_PAs(unsigned int Sdata) { //设备地址数据发送函数
	unsigned char i;
	
	O_SSD2828_SPI_CS(0);
	O_SSD2828_SPI_SDI(1);
	O_SSD2828_SPI_CLK(0); //上升沿发送数据
	O_SSD2828_SPI_CLK(1);
	
	for(i=8; i>0; i--) {
		if(Sdata&0x80) //判断高位是否为1
			O_SSD2828_SPI_SDI(1);
		else
			O_SSD2828_SPI_SDI(0);
		O_SSD2828_SPI_CLK(0); //上升沿发送数据
		O_SSD2828_SPI_CLK(1);
		Sdata <<= 1;
	}
	O_SSD2828_SPI_CLK(0);
	O_SSD2828_SPI_CS(1);
}

unsigned char SPI_ReadData(void) {	 
	unsigned char i;
	UINT8 Value = 0;
	
	O_SSD2828_SPI_CS(0);
	O_SSD2828_SPI_CLK(0);
	
	for(i=0; i<8; i++) {
		O_SSD2828_SPI_CLK(0); //上升沿发送数据
		O_SSD2828_SPI_CLK(1);
		Value <<= 1;
		if(1 == I_SSD2828_SPI_SDO())
			Value |= 0x01;
	}
	O_SSD2828_SPI_CS(1);
	
	return Value;
}

void SPI_WriteData(unsigned char value) {
	SPI_3W_SET_PAs(value);
}

void SPI_WriteCmd(unsigned char value) {
	SPI_3W_SET_Cmd(value);
}

void SPI_2828_WrReg(unsigned char c,unsigned char PAs_L, unsigned char PAs_H) {
	SPI_WriteCmd(c);//SPI_3W_SET_Cmd(c);
	SPI_WriteData(PAs_L);//SPI_3W_SET_PAs(PAs_L);
	SPI_WriteData(PAs_H);//SPI_3W_SET_PAs(PAs_H);
}

void SSD2828WriteReg(unsigned char c,  unsigned char PAs_H, unsigned char PAs_L) {
	SPI_WriteCmd(c);//SPI_3W_SET_Cmd(c);
	SPI_WriteData(PAs_L);//SPI_3W_SET_PAs(PAs_L);
	SPI_WriteData(PAs_H);//SPI_3W_SET_PAs(PAs_H);	
}

//2014-08-29 去掉bd be
void GP_COMMAD_PA(unsigned int num) {
	//SPI_CS = 1;
	SPI_WriteCmd(0xbc);
	SPI_WriteData(num&0xff);	
	SPI_WriteData((num>>8)&0xff);	
	SPI_WriteCmd(0xbf);
      //   	SPI_2825_WrReg(0xbc, num);
	    //	Write_com(0x00bd);
			//SPI_2825_WrReg(0xbe, num);
      //  	Write_com(0x00bf);
      //  SPI_CS = 1;
	//SPI_CS = 1;
}

void Reset(unsigned char Val) {
	//O_TEST1_TP_RESET(Val); //LCD Reset
O_SSD2828_RESET(Val);	
}
void Lcd_Reset(unsigned char Val) {
//	O_TEST1_TP_RESET(Val); //LCD Reset
}
	
void Delay(unsigned int x) {
	Delay_ms( x );
	//delayus(x);
}

void SSD2828_RegConfig(unsigned char address,unsigned char lbyte,unsigned char hbyte) {
	SPI_2828_WrReg(address,lbyte, hbyte);
}


void SSD2828_WritePackageSize(unsigned char num) {
  GP_COMMAD_PA(num);
}

unsigned char Ssd2828_ID_OK_check(void) {
	unsigned char ErrCnt = 0;
	unsigned char DeviceID, DeviceID2;
	while(ErrCnt<200) {
		SPI_WriteCmd(0xB0);SPI_WriteCmd(0xFA);
		DeviceID = SPI_ReadData();
		DeviceID2 = SPI_ReadData();
		if((DeviceID==0x28)&& (DeviceID2==0x28)) {
			return 1;
		}
		ErrCnt++;
	}
	return 0;
}

unsigned char Ssd2828_ID_OK_check_CmdMode(void) {
	UINT8 ErrCnt = 0;
	UINT32 DeviceID;
	
	while(ErrCnt < 200) {
		CommandMode_Read(0xB0, &DeviceID, 1); //MCU接口读SSD2828寄存器不需要发0xFA命令
		if(DeviceID == 0x2828)
			return 1;
		ErrCnt++;
	}
	return 0;
}

void LoadLcdParameterConfig(void) {
		UINT8 mode=0;
		if(ptr_MIPI_TABLE[gMipiTableIndex]->Display_Mode==0){
				SPI_2828_WrReg(0xB1, ptr_MIPI_TABLE[gMipiTableIndex]->HSW_WIDTH, ptr_MIPI_TABLE[gMipiTableIndex]->VSW_WIDTH); 	  //H V  //HSA/VSA
			SPI_2828_WrReg(0xB2, ptr_MIPI_TABLE[gMipiTableIndex]->HBP_WIDTH, ptr_MIPI_TABLE[gMipiTableIndex]->VBP_WIDTH); 	  //H V  //HBP/VBP   //

		}else if(ptr_MIPI_TABLE[gMipiTableIndex]->Display_Mode<=2&&ptr_MIPI_TABLE[gMipiTableIndex]->Display_Mode>0){
		 SPI_2828_WrReg(0xB2, ptr_MIPI_TABLE[gMipiTableIndex]->HBP_WIDTH+ptr_MIPI_TABLE[gMipiTableIndex]->HSW_WIDTH, ptr_MIPI_TABLE[gMipiTableIndex]->VBP_WIDTH+ptr_MIPI_TABLE[gMipiTableIndex]->VSW_WIDTH); 	  //H V  //HBP/VBP   //07  0B 用此
		}
	//SPI_2828_WrReg(0xB2, (ptr_MIPI_TABLE[gMipiTableIndex]->HBP_WIDTH), (ptr_MIPI_TABLE[gMipiTableIndex]->VBP_WIDTH)); 	  //H V  //HBP/VBP  //03用此
    SPI_2828_WrReg(0xB3, ptr_MIPI_TABLE[gMipiTableIndex]->HFP_WIDTH, ptr_MIPI_TABLE[gMipiTableIndex]->VFP_WIDTH);  	  //H V  //HFP/VFP
    SPI_2828_WrReg(0xB4, ((UINT8)ptr_MIPI_TABLE[gMipiTableIndex]->HACT_WIDTH), ((UINT8)(ptr_MIPI_TABLE[gMipiTableIndex]->HACT_WIDTH>>8))); //800	H
    SPI_2828_WrReg(0xB5, ((UINT8)ptr_MIPI_TABLE[gMipiTableIndex]->VACT_WIDTH), ((UINT8)(ptr_MIPI_TABLE[gMipiTableIndex]->VACT_WIDTH>>8))); //2560 V
		mode = ptr_MIPI_TABLE[gMipiTableIndex]->Display_Mode;
		mode = mode ==0?0x03:(mode==1?0x07:0x0b);
		SPI_WriteCmd(0xB6);//RGB CLK  16BPP=00 18BPP=01
		SPI_WriteData(mode);//D7=0 D6=0 D5=0  D1-0=11 – 24bpp//   03
		SPI_WriteData(0x00);//D15=VS D14=HS D13=CLK D12-9=NC D8=0=Video with blanking packet. 00-
}
void LoadLcdParameterConfig_CmdMode(void) {
	UINT32 TmpDat;
	UINT8 mode=0;
	
	if(ptr_MIPI_TABLE[gMipiTableIndex]->Display_Mode==0){
		TmpDat = (ptr_MIPI_TABLE[gMipiTableIndex]->VSW_WIDTH << 8) | (ptr_MIPI_TABLE[gMipiTableIndex]->HSW_WIDTH & 0x00FF);
		CommandMode_Write(0xB1, &TmpDat, 1);//HSA/VSA

		TmpDat = (ptr_MIPI_TABLE[gMipiTableIndex]->VBP_WIDTH << 8) | (ptr_MIPI_TABLE[gMipiTableIndex]->HBP_WIDTH & 0x00FF);
		CommandMode_Write(0xB2, &TmpDat, 1);//H V  //HBP/VBP   //

	}else if(ptr_MIPI_TABLE[gMipiTableIndex]->Display_Mode<=2&&ptr_MIPI_TABLE[gMipiTableIndex]->Display_Mode>0){
		TmpDat = ptr_MIPI_TABLE[gMipiTableIndex]->HBP_WIDTH+ptr_MIPI_TABLE[gMipiTableIndex]->HSW_WIDTH;
		TmpDat &= 0x00FF;
		TmpDat |= (ptr_MIPI_TABLE[gMipiTableIndex]->VBP_WIDTH<<8)+(ptr_MIPI_TABLE[gMipiTableIndex]->VSW_WIDTH<<8);
		CommandMode_Write(0xB2, &TmpDat, 1);
	}
	
	TmpDat = (ptr_MIPI_TABLE[gMipiTableIndex]->VFP_WIDTH << 8) | (ptr_MIPI_TABLE[gMipiTableIndex]->HFP_WIDTH & 0x00FF);
	CommandMode_Write(0xB3, &TmpDat, 1);
	
	TmpDat = ptr_MIPI_TABLE[gMipiTableIndex]->HACT_WIDTH;
	CommandMode_Write(0xB4, &TmpDat, 1);
	
	TmpDat = ptr_MIPI_TABLE[gMipiTableIndex]->VACT_WIDTH;
	CommandMode_Write(0xB5, &TmpDat, 1);
	
	mode = ptr_MIPI_TABLE[gMipiTableIndex]->Display_Mode;
	mode = mode ==0?0x03:(mode==1?0x07:0x0b);
	TmpDat = mode;
	CommandMode_Write(0xB6, &TmpDat, 1);
}
