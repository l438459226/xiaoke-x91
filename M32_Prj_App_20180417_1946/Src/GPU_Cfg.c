#include <stdlib.h>
#include <stdio.h>
#include "GPU_Cfg.h"
#include "MCU_GPU_fsmc.h"
#include "pll_drp_func.h"
#include "pll_freq_def.h"
#include "tools.h"
#include "stm32f10x_gpio.h"
#include "DBG_uart.h"
#include "user_gpio_def.h"
#include "ExternalIntWithGPU.h"
#include "app.h"
#include "stm32f10x_rcc.h"
#include "timer.h"
#include "lcd240x320.h"
#include "BoardAndCoreInf.h"


UINT32 Get_GPU_DateTime(void) { //GPU DateTime, eg: 32'h2017_0813
	UINT32 Res32;
	UINT16 TmpVal;
	
	Res32 = 0;
	
	MCU_GPU__ADDR = MCU_CFG_GPU__GPU_DATE_TIME_ADDR0;
	TmpVal = MCU_GPU__DATA;
	Res32 = (UINT32)TmpVal;
	
	MCU_GPU__ADDR = MCU_CFG_GPU__GPU_DATE_TIME_ADDR1;
	TmpVal = MCU_GPU__DATA;
	Res32 |= (((UINT32)TmpVal) << 16);
	
	return Res32;
}
UINT32 Get_GPU_Version(void) { //GPU Version, eg: 32'h0000_0001
	UINT32 Res32;
	UINT16 TmpVal;
	
	Res32 = 0;
	
	MCU_GPU__ADDR = MCU_CFG_GPU__GPU_VERSION_ADDR0;
	TmpVal = MCU_GPU__DATA;
	Res32 = (UINT32)TmpVal;
	
	MCU_GPU__ADDR = MCU_CFG_GPU__GPU_VERSION_ADDR1;
	TmpVal = MCU_GPU__DATA;
	Res32 |= (((UINT32)TmpVal) << 16);
	
	return Res32;
}
UINT8 GPU_Connection_Check(void) { //为1表示GPU固件正常, 为0表示GPU固件异常(此时其余操作可能都会有异常)
	UINT16 Res;
	
	MCU_GPU__ADDR = MCU_CFG_GPU__CONNECTION_CHECK_ADDR;
	Res = MCU_GPU__DATA;
	
	return (Res == 0xA5C3);
}

UINT8 GPU_LogicWorkStatus(void) { //为1表示GPU逻辑工作正常, 否则异常
	UINT16 Res;
	
	MCU_GPU__ADDR = MCU_CFG_GPU__DDR_ACCESS_CTRL_REG_ADDR;
	Res = MCU_GPU__DATA;
	
	return ((Res & 0x8380) == 0x8380);
}



void GPU_set_PLL_factor(pPLL_FACTOR Val) {
	//----------- Reconfig pixel clock PLL
	gpu_reconfig_pll(Val.M, Val.N, Val.C);
}

void Gpu_DisplayCfg(void) {
	UINT16 value;
	UINT16 DE_VS_HS_POLARITY;
	UINT16 DUALMIPI_CHANNEL_CFG;
	
//    #define V_DE_BITMASK 0x8000 /* bit[15], bit:0默认高电平有效 */
//    #define V_VS_BITMASK 0x4000 /* bit[14], bit:0默认高电平有效 */
//    #define V_HS_BITMASK 0x2000 /* bit[13], bit:0默认高电平有效 */
	DE_VS_HS_POLARITY = (((UINT16)(!ptr_MIPI_TABLE[gMipiTableIndex]->V_DE) << 15) | ((UINT16)(!ptr_MIPI_TABLE[gMipiTableIndex]->V_VS) << 14) | ((UINT16)(!ptr_MIPI_TABLE[gMipiTableIndex]->V_HS) << 13));
	DUALMIPI_CHANNEL_CFG = (((UINT16)ptr_MIPI_TABLE[gMipiTableIndex]->DUAL_MIPI_LCD) << 15) | (((UINT16)ptr_MIPI_TABLE[gMipiTableIndex]->DUAL_MIPI_CHANNEL_SWAP) << 14) | (((UINT16)ptr_MIPI_TABLE[gMipiTableIndex]->ODD_EVEN_nLEFT_RIGHT) << 13);
	
	//PLL
	GPU_set_PLL_factor(gPLL_FACTOR_Table[ptr_MIPI_TABLE[gMipiTableIndex]->PCLK_Freq]);
	
	//V-FP/BP/SW
	MCU_GPU__ADDR = MCU_CFG_GPU__PARAM_VFP_ADDR;
	MCU_GPU__DATA = ptr_MIPI_TABLE[gMipiTableIndex]->VFP_WIDTH;
	MCU_GPU__ADDR = MCU_CFG_GPU__PARAM_VBP_ADDR;
	MCU_GPU__DATA = ptr_MIPI_TABLE[gMipiTableIndex]->VBP_WIDTH;
	MCU_GPU__ADDR = MCU_CFG_GPU__PARAM_VSW_ADDR;
	MCU_GPU__DATA = (ptr_MIPI_TABLE[gMipiTableIndex]->VSW_WIDTH & 0x1FFF) | DUALMIPI_CHANNEL_CFG; //{ChannelTwoSame, ChannelSwap, DualMipi_EO_nLR, VSW[12:0]}
	
	//H-FP/BP/SW
	MCU_GPU__ADDR = MCU_CFG_GPU__PARAM_HFP_ADDR;
	MCU_GPU__DATA = ptr_MIPI_TABLE[gMipiTableIndex]->HFP_WIDTH;
	MCU_GPU__ADDR = MCU_CFG_GPU__PARAM_HBP_ADDR;
	MCU_GPU__DATA = ptr_MIPI_TABLE[gMipiTableIndex]->HBP_WIDTH;
	MCU_GPU__ADDR = MCU_CFG_GPU__PARAM_HSW_ADDR;
	MCU_GPU__DATA = ptr_MIPI_TABLE[gMipiTableIndex]->HSW_WIDTH;
	
	//VACT
	MCU_GPU__ADDR = MCU_CFG_GPU__PARAM_VACT_ADDR;
	MCU_GPU__DATA = (ptr_MIPI_TABLE[gMipiTableIndex]->VACT_WIDTH & 0x1FFF) | DE_VS_HS_POLARITY; //DE_INV=0; VS_INV=1; HS_INV=1;
	
	//HACT
	MCU_GPU__ADDR = MCU_CFG_GPU__PARAM_HACT_ADDR;
	value = ptr_MIPI_TABLE[gMipiTableIndex]->HACT_WIDTH & 0x1FFF;
	MCU_GPU__DATA = value;
	delayus(10);
	MCU_GPU__DATA = value|0x2000;//Cancel reset
}



//显示纯色, 三个输入参数分别对应RGB888中的R,G,B;
void Lcd_ShowPureColor(UINT8 pure_R, UINT8 pure_G, UINT8 pure_B) {
	MCU_GPU__ADDR = MCU_CFG_GPU__PURECOLOR_ADDR0;
	MCU_GPU__DATA = ((UINT16)pure_G << 8) | (UINT16)pure_B;
	
	MCU_GPU__ADDR = MCU_CFG_GPU__PURECOLOR_ADDR1;
	MCU_GPU__DATA = 0x0100 | ((UINT16)pure_R);
}













//GPIO
void O_PWR_EN_VSN(UINT8 Val) {
	MCU_GPU__ADDR = MCU_CFG_GPU__GPIO_Output_ADDR0;
	if(Val == 0)
		MCU_GPU__DATA = 0x0100;
	else
		MCU_GPU__DATA = 0x0101;
}
void O_PWR_EN_VSP(UINT8 Val) {
	MCU_GPU__ADDR = MCU_CFG_GPU__GPIO_Output_ADDR0;
	if(Val == 0)
		MCU_GPU__DATA = 0x0200;
	else
		MCU_GPU__DATA = 0x0202;
}
void O_PWR_BL_EN(UINT8 Val) {
	MCU_GPU__ADDR = MCU_CFG_GPU__GPIO_Output_ADDR0;
	if(Val == 0)
		MCU_GPU__DATA = 0x0400;
	else
		MCU_GPU__DATA = 0x0404;
}
void O_PWR_BLK_SET_GPA23(UINT8 Val) {
	MCU_GPU__ADDR = MCU_CFG_GPU__GPIO_Output_ADDR0;
	if(Val == 0)
		MCU_GPU__DATA = 0x0800;
	else
		MCU_GPU__DATA = 0x0808;
}
void O_PWR_BLK_SET_GPA24(UINT8 Val) {
	MCU_GPU__ADDR = MCU_CFG_GPU__GPIO_Output_ADDR0;
	if(Val == 0)
		MCU_GPU__DATA = 0x1000;
	else
		MCU_GPU__DATA = 0x1010;
}
void O_PWR_BLK_SET_GPE14(UINT8 Val) {
	MCU_GPU__ADDR = MCU_CFG_GPU__GPIO_Output_ADDR0;
	if(Val == 0)
		MCU_GPU__DATA = 0x2000;
	else
		MCU_GPU__DATA = 0x2020;
}
void O_PWR_BLK_SET_GPE15(UINT8 Val) {
	MCU_GPU__ADDR = MCU_CFG_GPU__GPIO_Output_ADDR0;
	if(Val == 0)
		MCU_GPU__DATA = 0x4000;
	else
		MCU_GPU__DATA = 0x4040;
}
void O_PWR_BLK_SET_GPM0(UINT8 Val) {
	MCU_GPU__ADDR = MCU_CFG_GPU__GPIO_Output_ADDR0;
	if(Val == 0)
		MCU_GPU__DATA = 0x8000;
	else
		MCU_GPU__DATA = 0x8080;
}
void O_EN_RES(UINT8 Val) {
	MCU_GPU__ADDR = MCU_CFG_GPU__GPIO_Output_ADDR1;
	if(Val == 0)
		MCU_GPU__DATA = 0x0100;
	else
		MCU_GPU__DATA = 0x0101;
}
void O_LCM_TP_RES(UINT8 Val) { //GPU里该寄存器上电默认为0
	MCU_GPU__ADDR = MCU_CFG_GPU__GPIO_Output_ADDR1;
	if(Val == 0)
		MCU_GPU__DATA = 0x0200;
	else
		MCU_GPU__DATA = 0x0202;
}

UINT8 I_LCM_INT(void) {
	UINT16 Res;
	
	MCU_GPU__ADDR = MCU_CFG_GPU__GPIO_Input_ADDR0;
	Res = MCU_GPU__DATA;
	
	return ((Res & 0x0001) == 0x0001); 
}



//--- Command Mode Related function
void O_CommandMode_SSD2828_IF_SEL(UINT8 Val) { //T850/T750底板上叫GPJ8_LCM_TP_RES, 对应T850核心板CON4的GPU_BK0_GPIO89_P/LCM_TP_RES
	//SSD2828 CommandMode的IF_SEL脚默认下拉, 0: RGB+SPI, 1: MCU-interface
	O_LCM_TP_RES(Val);
}

void CM_GPU_CommandModeEnable(UINT8 Val) {
	MCU_GPU__ADDR = MCU_CFG_GPU__COMMANDMODE_ENABLE;
	if(Val)
		MCU_GPU__DATA = 0x01; //选择CommandMode, RGB/VS/DE/PCLK会变成MCU-typeB接口
	else
		MCU_GPU__DATA = 0x00; //选择VideoMode(GPU固件上电默认为VideoMode)
}
void CM_GPU_CommandMode_Control(UINT16 Val) {
	MCU_GPU__ADDR = MCU_CFG_GPU__COMMANDMODE_CONTROL;
	MCU_GPU__DATA = Val;
}
UINT16 CM_GPU_CommandMode_ReadControl(void) {
	UINT16 Res16;
	MCU_GPU__ADDR = MCU_CFG_GPU__COMMANDMODE_CONTROL;
	Res16 = MCU_GPU__DATA;
	
	return Res16;
}
void CM_GPU_CommandMode_WriteData(UINT32 Val) {
	MCU_GPU__ADDR = MCU_CFG_GPU__COMMANDMODE_W_DATA | ((Val >> 16) & 0x000000FF); // [23:16]
	MCU_GPU__DATA = (UINT16)Val; //[15:0]
}
void CM_GPU_CommandMode_WriteRectanglePixelTotalNumber(UINT32 Val) { //[21:0]
	MCU_GPU__ADDR = MCU_CFG_GPU__COMMANDMODE_RECT_PIXELNUM | ((Val >> 16) & 0x0000003F); // [21:16]
	MCU_GPU__DATA = (UINT16)Val; //[15:0]
}
UINT32 CM_GPU_CommandMode_ReadData(void) { //读数据前要保证ReadReq已经置1, 读完之后要将ReadReq置0; (ReadReq用于切换24bit Data线的输入输出方向切换)
	UINT16 Res16;
	UINT32 Res32;
	
	MCU_GPU__ADDR = MCU_CFG_GPU__COMMANDMODE_R_DATAH;
	Res16 = MCU_GPU__DATA;
	Res32 = Res16 & 0x00FF; //[23:16]
	Res32 <<= 16;
	MCU_GPU__ADDR = MCU_CFG_GPU__COMMANDMODE_R_DATAL;
	Res16 = MCU_GPU__DATA; //[15:0]
	Res32 |= (UINT32)Res16;
	
	return Res32;
}


//CommandMode MCU-interface的操作分为三部分: WriteCommand, WriteData, ReadData;
void CommandMode_Init(void) {
	O_CommandMode_SSD2828_IF_SEL(1); //选择MCU-interface, 同时硬件上通过上下拉电阻将CommandMode转板的PS[4:0]配置成5'b10001(24bit MCU TypeB, and 3wire 8bit SPI);
	
	//GPU-CommandMode-Select, and init value of RDX, WRX, DCX
	CM_GPU_CommandModeEnable(1);
	CM_GPU_CommandMode_Control(CM_GPU_CONTROL__READREQ_0 | CM_GPU_CONTROL__WRX_1 | CM_GPU_CONTROL__RDX_1 | CM_GPU_CONTROL__DCX_0 | CM_GPU_CONTROL__RGB0_BGR1_ORDER_1 | CM_GPU_CONTROL__LINERD_ENABLE_0);
	
	O_SSD2828_SPI_CS(1); //将CSX0置1, 该引脚接到了STM32上
	
	//硬复位, 以进入MCU-interface
	O_SSD2828_RESET(0);
	delayms(15);
	O_SSD2828_RESET(1);
	delayms(15);
}
void CommandMode_Read(UINT32 Cmd, UINT32 *RData, INT16 RdCnt) {
	//先变DCX
	CM_GPU_CommandMode_Control(CM_GPU_CONTROL__READREQ_0 | CM_GPU_CONTROL__WRX_1 | CM_GPU_CONTROL__RDX_1 | CM_GPU_CONTROL__DCX_0);
	//再CSX0
	O_SSD2828_SPI_CS(0);
	//然后DATA 和 WRX, 写Command
	CM_GPU_CommandMode_WriteData(Cmd);
	CM_GPU_CommandMode_Control(CM_GPU_CONTROL__WRX_0);
	CM_GPU_CommandMode_Control(CM_GPU_CONTROL__WRX_1);
	//切换DATA方向, 切换DCX
	CM_GPU_CommandMode_Control(CM_GPU_CONTROL__READREQ_1 | CM_GPU_CONTROL__DCX_1);
	
	while(RdCnt > 0) {
		//RDX下降沿
		CM_GPU_CommandMode_Control(CM_GPU_CONTROL__RDX_0);
		//tACC = (5.3+4T) ns, 其中T是PLL输出的clock的周期
		delayus(1); //wait enough time
		//读数据
		*RData++ = CM_GPU_CommandMode_ReadData();
		//RDX上升沿
		CM_GPU_CommandMode_Control(CM_GPU_CONTROL__RDX_1);
		
		--RdCnt;
	}
	
	//将方向切换回来
	CM_GPU_CommandMode_Control(CM_GPU_CONTROL__READREQ_0);
	//将CSX0拉起来
	O_SSD2828_SPI_CS(1);
}
void CommandMode_Write(UINT32 Cmd, UINT32 *WData, INT16 WrCnt) {
	//先变DCX
	CM_GPU_CommandMode_Control(CM_GPU_CONTROL__READREQ_0 | CM_GPU_CONTROL__WRX_1 | CM_GPU_CONTROL__RDX_1 | CM_GPU_CONTROL__DCX_0);
	//再CSX0
	O_SSD2828_SPI_CS(0);
	//然后DATA 和 WRX, 写Command
	CM_GPU_CommandMode_WriteData(Cmd);
	CM_GPU_CommandMode_Control(CM_GPU_CONTROL__WRX_0);
	CM_GPU_CommandMode_Control(CM_GPU_CONTROL__WRX_1);
	//切换DCX
	CM_GPU_CommandMode_Control(CM_GPU_CONTROL__DCX_1);
	
	while(WrCnt > 0) {
		//写数据
		CM_GPU_CommandMode_WriteData(*WData++);
		//WRX下降沿
		CM_GPU_CommandMode_Control(CM_GPU_CONTROL__WRX_0);
		//WRX上升沿
		CM_GPU_CommandMode_Control(CM_GPU_CONTROL__WRX_1);
		
		--WrCnt;
	}
	
	//将CSX0拉起来
	O_SSD2828_SPI_CS(1);
}
void CommandMode_GPUWholeFrame_FastWrite(UINT32 Cmd) {
	UINT16 Res16;
	UINT16 TimeOut;
	
	//先变DCX
	CM_GPU_CommandMode_Control(CM_GPU_CONTROL__READREQ_0 | CM_GPU_CONTROL__WRX_1 | CM_GPU_CONTROL__RDX_1 | CM_GPU_CONTROL__DCX_0);
	//再CSX0
	O_SSD2828_SPI_CS(0);
	//然后DATA 和 WRX, 写Command
	CM_GPU_CommandMode_WriteData(Cmd);
	CM_GPU_CommandMode_Control(CM_GPU_CONTROL__WRX_0);
	CM_GPU_CommandMode_Control(CM_GPU_CONTROL__WRX_1);
	//切换DCX, 并请求GPU 整帧数据写出
	CM_GPU_CommandMode_Control(CM_GPU_CONTROL__DCX_1 | CM_GPU_CONTROL__WHOLEFRAME_1);
	
	TimeOut = 0;
	do {
		delayms(2); //wait 2ms
		
		Res16 = CM_GPU_CommandMode_ReadControl();
		Res16 &= 0x0020; //check if bit of WholeFramePeriod be auto cleared
		
		++TimeOut;
	}
	while(Res16 || (TimeOut > 250)); //如果大于500ms, 则超时退出
	
	//将CSX0拉起来
	O_SSD2828_SPI_CS(1);
}
void CommandMode_GPURectanglePureColor_FastWrite(UINT32 PureColorRGB, UINT32 PixelTotalNumberInRegion, UINT32 Cmd) {
	UINT16 Res16;
	UINT16 TimeOut;
	
	//先变DCX
	CM_GPU_CommandMode_Control(CM_GPU_CONTROL__READREQ_0 | CM_GPU_CONTROL__WRX_1 | CM_GPU_CONTROL__RDX_1 | CM_GPU_CONTROL__DCX_0);
	//再CSX0
	O_SSD2828_SPI_CS(0);
	//然后DATA 和 WRX, 写Command
	CM_GPU_CommandMode_WriteData(Cmd);
	CM_GPU_CommandMode_Control(CM_GPU_CONTROL__WRX_0);
	CM_GPU_CommandMode_Control(CM_GPU_CONTROL__WRX_1);
	//切换DCX, 并请求GPU 整帧数据写出
	CM_GPU_CommandMode_Control(CM_GPU_CONTROL__DCX_1);
	
	CM_GPU_CommandMode_WriteRectanglePixelTotalNumber(PixelTotalNumberInRegion);
	CM_GPU_CommandMode_WriteData(PureColorRGB); //{8'h0, R[7:0], G[7:0], B[7:0]}
	CM_GPU_CommandMode_Control(CM_GPU_CONTROL__RECTANGLEPURECOLOR_1);

	TimeOut = 0;
	do {
		delayus(1); //wait 1us
		
		Res16 = CM_GPU_CommandMode_ReadControl();
		Res16 &= 0x0010; //check if bit of RectanglePureColorPeriod be auto cleared
		
		++TimeOut;
	}
	while(Res16 || (TimeOut > 60000)); //如果大于60ms, 则超时退出
	
	//将CSX0拉起来
	O_SSD2828_SPI_CS(1);
}
void CommandMode_GPURectangleReadOutFromDDR(UINT32 Cmd, UINT16 ddr_current_display_region_addr,
	UINT16 LinePixel_RowAddrStart, UINT16 Row_Num,
	UINT16 LinePixel_ColumnAddrStart, UINT16 ColumnPixel_Num/*Should be multiply of 4 pixels*/)
{
	//--- 函数变量声明
	UINT16 value;
	UINT16 res;
	UINT16 tmpRowAddr, tmpColumnAddr;
	
	
	if((ColumnPixel_Num < 4) || (ColumnPixel_Num > 256)) //Column Pixel Number should be at least 4 pixels, and multiply of 4 pixels; and should be no more than 256 pixels
		return ;
	
	//先变DCX
	CM_GPU_CommandMode_Control(CM_GPU_CONTROL__READREQ_0 | CM_GPU_CONTROL__WRX_1 | CM_GPU_CONTROL__RDX_1 | CM_GPU_CONTROL__DCX_0);
	//再CSX0
	O_SSD2828_SPI_CS(0);
	//然后DATA 和 WRX, 写Command
	CM_GPU_CommandMode_WriteData(Cmd);
	CM_GPU_CommandMode_Control(CM_GPU_CONTROL__WRX_0);
	CM_GPU_CommandMode_Control(CM_GPU_CONTROL__WRX_1);
	//切换DCX, 并请求GPU 将对应矩形框的数据从DDR中读出并写出到IO端口, WHOLEFRAME控制位也需为1
	CM_GPU_CommandMode_Control(CM_GPU_CONTROL__DCX_1 | CM_GPU_CONTROL__LINERD_ENABLE_1 | CM_GPU_CONTROL__WHOLEFRAME_1);
	
	//
	for(tmpRowAddr=LinePixel_RowAddrStart; tmpRowAddr<(LinePixel_RowAddrStart+Row_Num); tmpRowAddr++) {
		tmpColumnAddr = LinePixel_ColumnAddrStart & 0x0FFF; //[11:0], max:4095
		if(ddr_current_display_region_addr == 0) { //process with ddr-byte-addr[26], 写到当前显示的Frame区域
			value = (tmpRowAddr>>2) & 0x03ff;
		}
		else {
			value = (tmpRowAddr>>2) | 0x0400;
		}
		value = value | 0x4000; //bit[14]为1表示下面的burst传输是读DDR
		MCU_GPU__ADDR = MCU_CFG_GPU__DDR_ACCESS_BYTE_ADDR1;
		MCU_GPU__DATA = value;
		
		value = tmpRowAddr<<14;
		MCU_GPU__ADDR = MCU_CFG_GPU__DDR_ACCESS_BYTE_ADDR0;
		MCU_GPU__DATA = value | (tmpColumnAddr<<2); //[13:0]-->[13:2](Column,4095Max) [1:0](Pixel,32bit), GPU会自动根据[3:2]做mask处理

		value = (ColumnPixel_Num>>2) - 1; //右移2位表示以4Pixel为单位
		MCU_GPU__ADDR = MCU_CFG_GPU__DDR_ACCESS_CTRL_REG_ADDR;
		MCU_GPU__DATA = (value&0x3f) | 0x0040; //0x007f;//start_enable:1, burst length:63, that is 64 of 128bits
			
		//-----wait transfer done
		res = 0x40;
		while(res) {
			res = MCU_GPU__DATA;
			res = res & 0x40;
		}
		delayus(10); //延时以保证SSD2828能有足够空余时间把数据发出去
	}

	delayus(1);
	CM_GPU_CommandMode_Control(CM_GPU_CONTROL__LINERD_ENABLE_0 | CM_GPU_CONTROL__WHOLEFRAME_0);
	
	//将CSX0拉起来
	O_SSD2828_SPI_CS(1);
}


////////////////////////////////////////////////////////////////////////////////////////////



u32 CURR_ARRAY[100],CURR_INDEX=0,CURR_DELAY;
void Show_Curr(void){
	int j,k,sum=0;
	
	if(CURR_INDEX>=100){
		for(j=0;j<100;j++){	
			for(k=0;k<100;k++){
				if(CURR_ARRAY[k]>CURR_ARRAY[j]){
					sum = CURR_ARRAY[k];
					CURR_ARRAY[k] =CURR_ARRAY[j];
					CURR_ARRAY[j] =sum;
				 }
			 }
		 }
		sum =0;
		for(j=30;j<70;j++){
			sum+=CURR_ARRAY[j];
			//printf("curr[%d]=%d\n",j,CURR_ARRAY[j]);
		}
		sum/=40;
		LCD_ShowString(14,13,"mA      ",0x07e0);DispNumber(10*8,13*16,(int)((double)sum*0.3486),4,0x07e0);
		CURR_INDEX =0;
		CURR_DELAY=0;
	}else{
		if(CURR_DELAY/5==1){
			CURR_ARRAY[CURR_INDEX] = Get_Sys_Curr();
			if( CURR_ARRAY[CURR_INDEX]>0)CURR_INDEX++;
			CURR_DELAY=0;
		}else{
			CURR_DELAY++;
		}
	}

}

