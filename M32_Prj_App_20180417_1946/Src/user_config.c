#include "user_config.h"
#include "lcd_cfg.h"

//CommandMode的PCLK_Freq的值不能超过SSD2828 PLL时钟的1/8, 否则SSD2828会处理不过来
const pMIPI_Para_Table PARA_MIPI_MOTOCM_1080x1920_A = {
	"Moto_1080x1920_CommandM ", //UINT8 bLCDName[30];
	"XXXX   ", //UINT8 bICName[30];
	0, 		//UINT8 DUAL_MIPI_LCD; 			//--- 声明该LCD是否为双MIPI屏(单MIPI屏时主板会输出两路相同的单MIPI信号以同时驱动两个屏)
	0, 		//UINT8 DUAL_MIPI_CHANNEL_SWAP; //--- 该双MIPI屏的两个通道的数据需要调换一下, 0不做调换, 1做调换
	0, 		//UINT8 ODD_EVEN_nLEFT_RIGHT;   //---  声明该双MIPI屏是左右通道模式还是奇偶通道模式, 0表示左右通道(Left-Right Division), 1表示奇偶通道(Odd-Even Division)
	100, 	//UINT16 PCLK_Freq; //PCLK Frequecy, 4~400的整数, 单位MHz
	4, 		//UINT8 LANE_CNT;	// 1:1Lane, 2:2Lane, 4:4Lane, Others Reserved
	1, 		//UINT8 V_DE;		// 1:DE 高电平有效, 0:DE 低电平有效
	0, 		//UINT8 V_VS;		// 1:VS 高电平有效, 0:VS 低电平有效
	0, 		//UINT8 V_HS; 		// 1:HS 高电平有效, 0:HS 低电平有效
	
	3,   //UINT8 Display_Mode; // 显示模式 0:Non burst mode with sync pulses  1:Non burst mode with sync events 2:Burst mode 3:Command mode

	1080, 	//UINT16 HACT_WIDTH;//宽度
	1920, 	//UINT16 VACT_WIDTH;//高度
	180, 	//UINT16 HFP_WIDTH;	//宽前肩
	180, 	//UINT16 HBP_WIDTH;	//宽后肩
	120, 	//UINT16 HSW_WIDTH;	//宽同步
	10, 	//UINT16 VFP_WIDTH;	//高前肩
	10, 		//UINT16 VBP_WIDTH;	//高后肩
	6, 		//UINT16 VSW_WIDTH; //高同步
	
	5500, 		//UINT16 VSP_mV;
	5500, 		//UINT16 VSN_mV;
	0, 		//UINT16 VGH_mV;
	0, 		//UINT16 VGL_mV;
	34, 	//UINT16 SIZE_OF_SHOW_MODE; 	//显示的总画面个数
	1, 		//UINT8  PicIndex1;
	2, 		//UINT8  PicIndex2;
	Initial_LCM_1080x1920_OppoR9_Oled
};



const pMIPI_Para_Table PARA_MIPI_TIANJI2_1080x1920_A = {
	"TianJi2_1080x1920_VideoM ", //UINT8 bLCDName[30];
	"XXXX   ", //UINT8 bICName[30];
	0, 		//UINT8 DUAL_MIPI_LCD; 			//--- 声明该LCD是否为双MIPI屏(单MIPI屏时主板会输出两路相同的单MIPI信号以同时驱动两个屏)
	0, 		//UINT8 DUAL_MIPI_CHANNEL_SWAP; //--- 该双MIPI屏的两个通道的数据需要调换一下, 0不做调换, 1做调换
	0, 		//UINT8 ODD_EVEN_nLEFT_RIGHT;   //---  声明该双MIPI屏是左右通道模式还是奇偶通道模式, 0表示左右通道(Left-Right Division), 1表示奇偶通道(Odd-Even Division)
	133, 	//UINT16 PCLK_Freq; //PCLK Frequecy, 4~400的整数, 单位MHz
	4, 		//UINT8 LANE_CNT;	// 1:1Lane, 2:2Lane, 4:4Lane, Others Reserved
	1, 		//UINT8 V_DE;		// 1:DE 高电平有效, 0:DE 低电平有效
	0, 		//UINT8 V_VS;		// 1:VS 高电平有效, 0:VS 低电平有效
	0, 		//UINT8 V_HS; 		// 1:HS 高电平有效, 0:HS 低电平有效
	
	0,   //UINT8 Display_Mode; // 显示模式 0:Non burst mode with sync pulses  1:Non burst mode with sync events 2:Burst mode 3:Command mode

	1080, 	//UINT16 HACT_WIDTH;//宽度
	1920, 	//UINT16 VACT_WIDTH;//高度
	20, 	//UINT16 HFP_WIDTH;	//宽前肩
	22, 	//UINT16 HBP_WIDTH;	//宽后肩
	10, 	//UINT16 HSW_WIDTH;	//宽同步
	20, 	//UINT16 VFP_WIDTH;	//高前肩
	1, 		//UINT16 VBP_WIDTH;	//高后肩
	6, 		//UINT16 VSW_WIDTH; //高同步
	
	5500, 		//UINT16 VSP_mV;
	5500, 		//UINT16 VSN_mV;
	0, 		//UINT16 VGH_mV;
	0, 		//UINT16 VGL_mV;
	34, 	//UINT16 SIZE_OF_SHOW_MODE; 	//显示的总画面个数
	1, 		//UINT8  PicIndex1;
	2, 		//UINT8  PicIndex2;
	Initial_LCM_1080x1920_TianJi2
};


//-----------------------------------------------------------------------------------
// 屏参数配置表汇总, 增加一款MIPI屏的".c"文件之后, 要把对应的结构体常量加到该指针数组里(加的时候可以不管先后顺序)
const pMIPI_Para_Table *ptr_MIPI_TABLE[] = {
	&PARA_MIPI_MOTOCM_1080x1920_A
	//&PARA_MIPI_TIANJI2_1080x1920_A
};
unsigned char MIPI_TABLE_LAST_INDEX = ((sizeof(ptr_MIPI_TABLE)/sizeof(const pMIPI_Para_Table *)) - 1); //自动计算ptr_EDP_TABLE表中对应屏参配置的个数



