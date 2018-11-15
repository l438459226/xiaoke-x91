#include "pport_spi.h"
#include "lcd_cfg.h"
#include "user_config.h"
#include "GPU_Cfg.h"
#include <stdio.h>

void Initial_LCM_1080x1920_Moto_CommandMode(void) {
	UINT32 TmpData;
	UINT32 WArray[12];
	
	Reset(0);
	Delay(30);
	Reset(1);
	Delay(30);

	
//	TmpData = 0x0350;
//	CommandMode_Write( 0xB7, &TmpData, 1);

	
	
	TmpData = 0x0000;
	CommandMode_Write( 0xB8, &TmpData, 1);
	
	
	TmpData = 0x0000;
	CommandMode_Write( 0xB9, &TmpData, 1);// PLL OFF

	TmpData = 0xC127;
	CommandMode_Write( 0xBA, &TmpData, 1);// PLL Output
	
	TmpData = 0x000a;
	CommandMode_Write( 0xBB, &TmpData, 1);// LP Clock = PLL Output/8/x
	
	TmpData = 0x0001;
	CommandMode_Write( 0xB9, &TmpData, 1);// PLL ON
		
	
	//---
	TmpData = 0x2302;
	CommandMode_Write( 0xC9, &TmpData, 1); //p1: HS-Data-zero  p2: HS-Data- prepare  --> 8031 issue
	
	TmpData = 0x3C01;
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

		
	TmpData = 0x0001;
	CommandMode_Write( 0xC0, &TmpData, 1);
	
	Delay(100);
	
	
	
	TmpData = 0x0302; //--- Generic Short Write
	CommandMode_Write( 0xB7, &TmpData, 1);

	TmpData = 0x0002; //Write number/count
	CommandMode_Write( 0xBC, &TmpData, 1);
	TmpData = 0x0000;
	CommandMode_Write( 0xBD, &TmpData, 1);
	TmpData = 0x0004B0;
	CommandMode_Write( 0xBF, &TmpData, 1);

	TmpData = 0x0002; //Write number/count
	CommandMode_Write( 0xBC, &TmpData, 1);
	TmpData = 0x0000;
	CommandMode_Write( 0xBD, &TmpData, 1);
	TmpData = 0x0001D6;
	CommandMode_Write( 0xBF, &TmpData, 1);


	TmpData = 0x0702; //--- Generic Long Write
	CommandMode_Write( 0xB7, &TmpData, 1);

	TmpData = 0x0006; //Write number/count
	CommandMode_Write( 0xBC, &TmpData, 1);
	TmpData = 0x0000;
	CommandMode_Write( 0xBD, &TmpData, 1);
	WArray[0] = 0x1004B3;
	WArray[1] = 0x000000;
	CommandMode_Write( 0xBF, WArray, 2);

	TmpData = 0x0003; //Write number/count
	CommandMode_Write( 0xBC, &TmpData, 1);
	TmpData = 0x0000;
	CommandMode_Write( 0xBD, &TmpData, 1);
	WArray[0] = 0x000CB4;
	CommandMode_Write( 0xBF, WArray, 1);

	TmpData = 0x0004; //Write number/count
	CommandMode_Write( 0xBC, &TmpData, 1);
	TmpData = 0x0000;
	CommandMode_Write( 0xBD, &TmpData, 1);
	WArray[0] = 0xD33BB6;
	WArray[1] = 0x000000;
	CommandMode_Write( 0xBF, WArray, 2);

	TmpData = 0x0007; //Write number/count
	CommandMode_Write( 0xBC, &TmpData, 1);
	TmpData = 0x0000;
	CommandMode_Write( 0xBD, &TmpData, 1);
	WArray[0] = 0x9007B8;
	WArray[1] = 0x1E101E;
	WArray[2] = 0x000032;
	CommandMode_Write( 0xBF, WArray, 3);

	TmpData = 0x0007; //Write number/count
	CommandMode_Write( 0xBC, &TmpData, 1);
	TmpData = 0x0000;
	CommandMode_Write( 0xBD, &TmpData, 1);
	WArray[0] = 0x8207B9;
	WArray[1] = 0x3C103C;
	WArray[2] = 0x000087;
	CommandMode_Write( 0xBF, WArray, 3);

	TmpData = 0x0007; //Write number/count
	CommandMode_Write( 0xBC, &TmpData, 1);
	TmpData = 0x0000;
	CommandMode_Write( 0xBD, &TmpData, 1);
	WArray[0] = 0x7807BA;
	WArray[1] = 0x641064;
	WArray[2] = 0x0000B4;
	CommandMode_Write( 0xBF, WArray, 3);



	TmpData = 0x0302; //--- Generic Short Write
	CommandMode_Write( 0xB7, &TmpData, 1);

	TmpData = 0x0002; //Write number/count
	CommandMode_Write( 0xBC, &TmpData, 1);
	TmpData = 0x0000;
	CommandMode_Write( 0xBD, &TmpData, 1);
	TmpData = 0x0000C0;
	CommandMode_Write( 0xBF, &TmpData, 1);




	TmpData = 0x0702; //--- Generic Long Write
	CommandMode_Write( 0xB7, &TmpData, 1);

	TmpData = 0x0020; //Write number/count
	CommandMode_Write( 0xBC, &TmpData, 1);
	TmpData = 0x0000;
	CommandMode_Write( 0xBD, &TmpData, 1);
	WArray[0]  = 0x0080C1;
	WArray[1]  = 0xBFFF01;
	WArray[2]  = 0xFFE51A;
	WArray[3]  = 0xC59BE7;
	WArray[4]  = 0x8D739A;
	WArray[5]  = 0xCFF32D;
	WArray[6]  = 0x5443FF;
	WArray[7]  = 0x003FF0;
	WArray[8]  = 0x004000;
	WArray[9]  = 0x0801E2;
	WArray[10] = 0x000100;
	CommandMode_Write( 0xBF, WArray, 11);
	
	TmpData = 0x000B; //Write number/count
	CommandMode_Write( 0xBC, &TmpData, 1);
	TmpData = 0x0000;
	CommandMode_Write( 0xBD, &TmpData, 1);
	WArray[0]  = 0xF701C2;
	WArray[1]  = 0x630480;
	WArray[2]  = 0x006000;
	WArray[3]  = 0x003001;
	CommandMode_Write( 0xBF, WArray, 4);
	
	TmpData = 0x0007; //Write number/count
	CommandMode_Write( 0xBC, &TmpData, 1);
	TmpData = 0x0000;
	CommandMode_Write( 0xBD, &TmpData, 1);
	WArray[0]  = 0x0155C3;
	WArray[1]  = 0x000100;
	WArray[2]  = 0x000000;
	CommandMode_Write( 0xBF, WArray, 3);
	
	TmpData = 0x0012; //Write number/count
	CommandMode_Write( 0xBC, &TmpData, 1);
	TmpData = 0x0000;
	CommandMode_Write( 0xBD, &TmpData, 1);
	WArray[0]  = 0x0070C4;
	WArray[1]  = 0x000000;
	WArray[2]  = 0x000000;
	WArray[3]  = 0x010200;
	WArray[4]  = 0x010500;
	WArray[5]  = 0x000000;
	CommandMode_Write( 0xBF, WArray, 6);
	
	TmpData = 0x000F; //Write number/count
	CommandMode_Write( 0xBC, &TmpData, 1);
	TmpData = 0x0000;
	CommandMode_Write( 0xBD, &TmpData, 1);
	WArray[0]  = 0x075BC6;
	WArray[1]  = 0x500750;
	WArray[2]  = 0x010E01;
	WArray[3]  = 0x020102;
	WArray[4]  = 0x071509;
	CommandMode_Write( 0xBF, WArray, 5);
	
	TmpData = 0x001F; //Write number/count
	CommandMode_Write( 0xBC, &TmpData, 1);
	TmpData = 0x0000;
	CommandMode_Write( 0xBD, &TmpData, 1);
	WArray[0]  = 0x0F01C7;
	WArray[1]  = 0x312217;
	WArray[2]  = 0x54473F;
	WArray[3]  = 0x493D36;
	WArray[4]  = 0x6B6357;
	WArray[5]  = 0x0F017F;
	WArray[6]  = 0x312217;
	WArray[7]  = 0x54473F;
	WArray[8]  = 0x493D36;
	WArray[9]  = 0x6B6357;
	WArray[10] = 0x00007F;
	CommandMode_Write( 0xBF, WArray, 11);
	
	TmpData = 0x0014; //Write number/count
	CommandMode_Write( 0xBC, &TmpData, 1);
	TmpData = 0x0000;
	CommandMode_Write( 0xBD, &TmpData, 1);
	WArray[0]  = 0x0001C8;
	WArray[1]  = 0xFB01FC;
	WArray[2]  = 0x0000F4;
	WArray[3]  = 0xFD04FA;
	WArray[4]  = 0x0000FC;
	WArray[5]  = 0xFDFAFD;
	WArray[6]  = 0x0000B7;
	CommandMode_Write( 0xBF, WArray, 7);
	
	TmpData = 0x0009; //Write number/count
	CommandMode_Write( 0xBC, &TmpData, 1);
	TmpData = 0x0000;
	CommandMode_Write( 0xBD, &TmpData, 1);
	WArray[0]  = 0x681CC9;
	WArray[1]  = 0x4C681C;
	WArray[2]  = 0x00C44C;
	CommandMode_Write( 0xBF, WArray, 3);
	
	TmpData = 0x000A; //Write number/count
	CommandMode_Write( 0xBC, &TmpData, 1);
	TmpData = 0x0000;
	CommandMode_Write( 0xBD, &TmpData, 1);
	WArray[0]  = 0xF53CCB;
	WArray[1]  = 0x000F2B;
	WArray[2]  = 0x000000;
	WArray[3]  = 0x000000;
	CommandMode_Write( 0xBF, WArray, 4);
	
	


	TmpData = 0x0302; //--- Generic Short Write
	CommandMode_Write( 0xB7, &TmpData, 1);

	TmpData = 0x0002; //Write number/count
	CommandMode_Write( 0xBC, &TmpData, 1);
	TmpData = 0x0000;
	CommandMode_Write( 0xBD, &TmpData, 1);
	TmpData = 0x0004CC;
	CommandMode_Write( 0xBF, &TmpData, 1);




	TmpData = 0x0702; //--- Generic Long Write
	CommandMode_Write( 0xB7, &TmpData, 1);

	TmpData = 0x0011; //Write number/count
	CommandMode_Write( 0xBC, &TmpData, 1);
	TmpData = 0x0000;
	CommandMode_Write( 0xBD, &TmpData, 1);
	WArray[0]  = 0xD01101;
	WArray[1]  = 0x910B99;
	WArray[2]  = 0x141400;
	WArray[3]  = 0x000019;
	WArray[4]  = 0x990000;
	WArray[5]  = 0x000000;
	CommandMode_Write( 0xBF, WArray, 6);
	
	TmpData = 0x001D; //Write number/count
	CommandMode_Write( 0xBC, &TmpData, 1);
	TmpData = 0x0000;
	CommandMode_Write( 0xBD, &TmpData, 1);
	WArray[0]  = 0xD31B3B;
	WArray[1]  = 0xBBADA5;
	WArray[2]  = 0x333333;
	WArray[3]  = 0x0080AF;
	WArray[4]  = 0xA54B4B;
	WArray[5]  = 0x333333;
	WArray[6]  = 0xF7F20F;
	WArray[7]  = 0x7D7CFF;
	WArray[8]  = 0x0F9900;
	WArray[9]  = 0xFFFF00;
	CommandMode_Write( 0xBF, WArray, 10);
	
	TmpData = 0x0004; //Write number/count
	CommandMode_Write( 0xBC, &TmpData, 1);
	TmpData = 0x0000;
	CommandMode_Write( 0xBD, &TmpData, 1);
	WArray[0]  = 0x3357D4;
	WArray[1]  = 0x000001;
	CommandMode_Write( 0xBF, WArray, 2);
	
	TmpData = 0x0021; //Write number/count
	CommandMode_Write( 0xBC, &TmpData, 1);
	TmpData = 0x0000;
	CommandMode_Write( 0xBD, &TmpData, 1);
	WArray[0]  = 0xFF04D7;
	WArray[1]  = 0x475523;
	WArray[2]  = 0x78FE1E;
	WArray[3]  = 0xA819F0;
	WArray[4]  = 0x3E380F;
	WArray[5]  = 0x0F1C60;
	WArray[6]  = 0xE3C78F;
	WArray[7]  = 0x20E199;
	WArray[8]  = 0x000000;
	WArray[9]  = 0xEBF000;
	WArray[10] = 0x071839;
	CommandMode_Write( 0xBF, WArray, 11);
	
	
	
	

	TmpData = 0x0302; //--- Generic Short Write
	CommandMode_Write( 0xB7, &TmpData, 1);

	TmpData = 0x0002; //Write number/count
	CommandMode_Write( 0xBC, &TmpData, 1);
	TmpData = 0x0000;
	CommandMode_Write( 0xBD, &TmpData, 1);
	TmpData = 0x000FE7;
	CommandMode_Write( 0xBF, &TmpData, 1);

	TmpData = 0x0002; //Write number/count
	CommandMode_Write( 0xBC, &TmpData, 1);
	TmpData = 0x0000;
	CommandMode_Write( 0xBD, &TmpData, 1);
	TmpData = 0x008051;
	CommandMode_Write( 0xBF, &TmpData, 1);

	TmpData = 0x0002; //Write number/count
	CommandMode_Write( 0xBC, &TmpData, 1);
	TmpData = 0x0000;
	CommandMode_Write( 0xBD, &TmpData, 1);
	TmpData = 0x002C53;
	CommandMode_Write( 0xBF, &TmpData, 1);

	TmpData = 0x0002; //Write number/count
	CommandMode_Write( 0xBC, &TmpData, 1);
	TmpData = 0x0000;
	CommandMode_Write( 0xBD, &TmpData, 1);
	TmpData = 0x000255;
	CommandMode_Write( 0xBF, &TmpData, 1);
	
	TmpData = 0x0002; //Write number/count
	CommandMode_Write( 0xBC, &TmpData, 1);
	TmpData = 0x0000;
	CommandMode_Write( 0xBD, &TmpData, 1);
	TmpData = 0x000035;
	CommandMode_Write( 0xBF, &TmpData, 1);

	
	
	
	
	
	
	
	
	
	
	

	TmpData = 0x0342; //--- DCS Short Write
	CommandMode_Write( 0xB7, &TmpData, 1);

	TmpData = 0x0001;
	CommandMode_Write( 0xBC, &TmpData, 1);
	TmpData = 0x0000;
	CommandMode_Write( 0xBD, &TmpData, 1);
	TmpData = 0x0029;
	CommandMode_Write( 0xBF, &TmpData, 1);
    Delay(100);

	TmpData = 0x0001;
	CommandMode_Write( 0xBC, &TmpData, 1);
	TmpData = 0x0000;
	CommandMode_Write( 0xBD, &TmpData, 1);
	TmpData = 0x0011;
	CommandMode_Write( 0xBF, &TmpData, 1);
    Delay(30);


	
	TmpData = 1620; //PST(Packet Size Threshold), must be in multiple of 3 bytes, and less than 4096Bytes
	CommandMode_Write( 0xBE, &TmpData, 1);
	

	CommandMode_Read(0xBE, &TmpData, 1); 
	printf("\r\nInit1: 0x%04X;\r\n", TmpData);

	
	TmpData = 0x0743;
	CommandMode_Write( 0xB7, &TmpData, 1);
	

	TmpData = 1620; //PST(Packet Size Threshold), must be in multiple of 3 bytes, and less than 4096Bytes
	CommandMode_Write( 0xBE, &TmpData, 1);
	
	TmpData = 0x0000;
	CommandMode_Write( 0x2C, &TmpData, 0);
	
	CommandMode_Read(0xBE, &TmpData, 1); 
	printf("\r\nInit2: 0x%04X;\r\n", TmpData);
	
//	TmpData = 0x0001;
//	CommandMode_Write( 0xC0, &TmpData, 1);
}


