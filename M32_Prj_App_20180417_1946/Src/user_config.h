#ifndef __USER_CONFIG_H
#define __USER_CONFIG_H

#include "BasicDataType.h"

//--- MCU固件程序版本信息, 最高一个bit为1表示MCU32, 为0表示MCU8; ----------------------------------------------------------
#define EXTMCU_VERSION (0x80DD001) //--- 32bit

//--- 外部LCD接口板类型 ------------------------------------------------------------
// 1: 表示最初的双MIPI转接板; 
// 2: 表示在最初双MIPI转接板基础上加了上下电泄放电路的转接板; 
// 3: 表示eDP的转接板; 
// 4: 新的Dual-CommandMode转接板
#define LCD_DAUGHTER_BOARD_TYPE  (4)


typedef struct {
	UINT8 bLCDName[29]; //用于记录该MIPI-LCD的分辨率
	UINT8 bICName[29]; //用于记录该MIPI-LCD的分辨率
	UINT8 DUAL_MIPI_LCD; 			//--- 声明该LCD是否为双MIPI屏(单MIPI屏时主板会输出两路相同的单MIPI信号以同时驱动两个屏)
	UINT8 DUAL_MIPI_CHANNEL_SWAP; 	//--- 该双MIPI屏的两个通道的数据需要调换一下, 0不做调换, 1做调换
	UINT8 ODD_EVEN_nLEFT_RIGHT;     //---  声明该双MIPI屏是左右通道模式还是奇偶通道模式, 0表示左右通道(Left-Right Division), 1表示奇偶通道(Odd-Even Division)
	UINT16 PCLK_Freq; 	//PCLK Frequecy, 4~400的整数, 单位MHz
	UINT8 LANE_CNT;	// 4:4Lane, 8:8Lane, Others Reserved
	UINT8 V_DE;		// 1:DE 高电平有效, 0:DE 低电平有效
	UINT8 V_VS;		// 1:VS 高电平有效, 0:VS 低电平有效
	UINT8 V_HS; 	// 1:HS 高电平有效, 0:HS 低电平有效
	UINT8 Display_Mode; 	// 显示模式 0:Non burst mode with sync pulses  1:Non burst mode with sync events 2:Burst mode 3:Command mode
	UINT16 HACT_WIDTH;	//宽度
	UINT16 VACT_WIDTH;	//高度
	UINT16 HFP_WIDTH;	//宽前肩
	UINT16 HBP_WIDTH;	//宽后肩
	UINT16 HSW_WIDTH;	//宽同步
	UINT16 VFP_WIDTH;	//高前肩
	UINT16 VBP_WIDTH;	//高后肩
	UINT16 VSW_WIDTH; 	//高同步
	UINT16 VSP_mV;
	UINT16 VSN_mV;
	UINT16 VGH_mV;
	UINT16 VGL_mV;
	UINT16 SIZE_OF_SHOW_MODE; 	//显示的总画面个数
	UINT8  PicIndex1;
	UINT8  PicIndex2;
	void (*ptr_Initial_LCM)(void); //函数指针, 指向对应的初始化函数
} pMIPI_Para_Table;

extern const pMIPI_Para_Table *ptr_MIPI_TABLE[];
extern unsigned char MIPI_TABLE_LAST_INDEX;
extern UINT8 gMipiTableIndex;






#endif /* __USER_CONFIG_H */
