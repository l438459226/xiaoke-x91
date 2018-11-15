#include "pport_spi.h"
#include "lcd_cfg.h"
#include "user_config.h"
#include "GPU_Cfg.h"


void Initial_LCM_1080x1920_OppoR9_Oled(void) {
	UINT32 TmpData;
	
	Reset(0);
	Delay(30);
	Reset(1);
	Delay(50);
	
	TmpData = 0x0001;
	CommandMode_Write( 0xC0, &TmpData, 1);
	
	TmpData = 0x0350;
	CommandMode_Write( 0xB7, &TmpData, 1);

	TmpData = 0x0000;
	CommandMode_Write( 0xB8, &TmpData, 1);
	
	
	
	TmpData = 0x0000;
	CommandMode_Write( 0xB9, &TmpData, 1);// PLL OFF

	TmpData = 0xC027;
	CommandMode_Write( 0xBA, &TmpData, 1);// PLL Output
	
	TmpData = 0x000F;
	CommandMode_Write( 0xBB, &TmpData, 1);// LP Clock = PLL Output/8/x
	
	TmpData = 0x0001;
	CommandMode_Write( 0xB9, &TmpData, 1);// PLL ON
		
	
	//---
	TmpData = 0x2302;
	CommandMode_Write( 0xC9, &TmpData, 1); //p1: HS-Data-zero  p2: HS-Data- prepare  --> 8031 issue
	
	TmpData = 0x2301;
	CommandMode_Write( 0xCA, &TmpData, 1);//CLK Prepare, Clk Zero
	
	TmpData = 0x0510;
	CommandMode_Write( 0xCB, &TmpData, 1);//Clk Post,Clk Per
	
	TmpData = 0x1005;
	CommandMode_Write( 0xCC, &TmpData, 1);//HS Trail,Clk Trail

	
	
	//RGB parameter
	LoadLcdParameterConfig_CmdMode();

	TmpData = 0x0003;//4 lane mode
	CommandMode_Write( 0xDE, &TmpData, 1);
	
	TmpData = 0x74A0; //Driving Strength
	CommandMode_Write( 0xD9, &TmpData, 1);

	
	
	TmpData = 0x0342;
	CommandMode_Write( 0xB7, &TmpData, 1);

	



	Delay(100);

	
	TmpData = 0x0001;
	CommandMode_Write( 0xBC, &TmpData, 1);
	TmpData = 0x0000;
	CommandMode_Write( 0xBD, &TmpData, 1);
	TmpData = 0x0011;
	CommandMode_Write( 0xBF, &TmpData, 1);
    Delay(120);


	TmpData = 0x0001;
	CommandMode_Write( 0xBC, &TmpData, 1);
	TmpData = 0x0000;
	CommandMode_Write( 0xBD, &TmpData, 1);
	TmpData = 0x0029;
	CommandMode_Write( 0xBF, &TmpData, 1);
    Delay(30);


	TmpData = ptr_MIPI_TABLE[gMipiTableIndex]->HACT_WIDTH * 3; //PST(Packet Size Threshold), must be in multiple of 3 bytes, and less than 4096Bytes
	if(TmpData > 8192)
		TmpData >>= 2;
	else if(TmpData > 4096)
		TmpData >>= 1;
	CommandMode_Write( 0xBE, &TmpData, 1);
	
}


