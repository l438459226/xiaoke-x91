#include <stdio.h>
#include "app.h"
#include "pport_spi.h"
#include "user_config.h"
#include "user_gpio_def.h"
#include "tools.h"
#include "GPU_Cfg.h"
#include "lcd240x320.h"

extern UINT8 P0_SampleValue;
extern UINT8 KeyPowerPressed;
extern UINT8 KeyUpPressed;
extern UINT8 KeyDownPressed;
extern UINT8 ShowMode;

//��ʼ��IO����ǿ��
void Init_IO(void) {
	

	
	init_spi();
}

extern void ShowChar(void);

void Lcd_ShowMode(UINT8 ShowId) {
	UINT32 TmpData;
	UINT32 TmpD[2];
	
	
	switch(ShowId) {
		case 1: 	op_PatternPureColorThroughDDR(0xff, 0x00, 0x00);                LCD_ShowString(10,11,"Red                  ",GREEN);break; //(R,G,B)��
		case 2: 	op_PatternPureColorThroughDDR(0x00, 0xff, 0x00);                LCD_ShowString(10,11,"Green                ",GREEN);break; //(R,G,B)��
		case 3: 	op_PatternPureColorThroughDDR(0x00, 0x00, 0xff);                LCD_ShowString(10,11,"Blue                 ",GREEN);break; //(R,G,B)��
		case 4: 	op_PatternPureColorThroughDDR(0x00, 0x00, 0x00);                LCD_ShowString(10,11,"Black                ",GREEN);break; //(R,G,B)��
		case 5: 	op_PatternPureColorThroughDDR(0xff, 0xff, 0xff);                LCD_ShowString(10,11,"White                ",GREEN);break; //(R,G,B)��
		case 6: 	op_PatternPureColorThroughDDR(0x80, 0x80, 0x80);                LCD_ShowString(10,11,"Gray128              ",GREEN);break; //(R,G,B)��
		case 7:  	op_PatternColorOutline(255,255,255);                LCD_ShowString(10,11,"Frame                ",GREEN);break;
		case 8: 	op_PatternGrayScaleH(0, 255);                        LCD_ShowString(10,11,"Gray_H Level 255     ",GREEN);break;
		case 9: 	op_PatternGrayScaleH(1, 255);                        LCD_ShowString(10,11,"Gray_H Level 255 INV ",GREEN);break;
		case 10: 	op_PatternGrayScaleH(0, 127);                        LCD_ShowString(10,11,"Gray_H Level 127     ",GREEN);break;
		case 11: 	op_PatternGrayScaleH(1, 127);                        LCD_ShowString(10,11,"Gray_H Level 127 INV ",GREEN);break;
		case 12: 	op_PatternGrayScaleV(0, 255);                        LCD_ShowString(10,11,"Gray_V Level 255     ",GREEN);break;
		case 13: 	op_PatternGrayScaleV(1, 255);                        LCD_ShowString(10,11,"Gray_V Level 255 INV ",GREEN);break;
		case 14: 	op_PatternGrayScaleV(0, 127);                        LCD_ShowString(10,11,"Gray_V Level 127     ",GREEN);break;
		case 15: 	op_PatternGrayScaleV(1, 127);                        LCD_ShowString(10,11,"Gray_V Level 127 INV ",GREEN);break;
		case 16:  op_Pattern8ColorBarH_BBRGWCYM();                     LCD_ShowString(10,11,"Color Table_H        ",GREEN);break;
		case 17:  op_Pattern8ColorBarV_BBRGWCYM();                     LCD_ShowString(10,11,"Color Table_V        ",GREEN);break;
		case 18:  op_PatternCrosstalk_BlackWhite(0);                   LCD_ShowString(10,11,"Cross Talk WG        ",GREEN);break;
		case 19:  op_PatternCrosstalk_BlackWhite(1);                   LCD_ShowString(10,11,"Cross Talk BG        ",GREEN);break;
		case 20:  op_PatternChecker_BlackWhite(0, 9, 13);              LCD_ShowString(10,11,"9*13_WB              ",GREEN);break;
		case 21:  op_PatternChecker_BlackWhite(1, 9, 13);              LCD_ShowString(10,11,"9*13_BW              ",GREEN);break;
		case 22:  op_PatternFlickerOneDot(127,0,127, 0,127,0);         LCD_ShowString(10,11,"Flicker 1dot 127     ",GREEN);break;
		case 23:  op_PatternFlickerColumnInversion(127,0,127, 0,127,0);LCD_ShowString(10,11,"Flicker col 127      ",GREEN);break;
		case 24:  op_Pattern4ColorBarGrayScaleV(0, 255);               LCD_ShowString(10,11,"Color Level_V 255    ",GREEN);break;
		case 25:  op_Pattern4ColorBarGrayScaleV(1, 255);               LCD_ShowString(10,11,"Color Level_V 255 INV",GREEN);break;
		case 26:  op_Pattern4ColorBarGrayScaleH(0, 255);               LCD_ShowString(10,11,"Color Level_H 255    ",GREEN);break;
		case 27:  op_Pattern4ColorBarGrayScaleH(1, 255);               LCD_ShowString(10,11,"Color Level_H 255 INV",GREEN);break;
		case 28:   DisplayBMP(1);                                      LCD_ShowString(10,11,"PIC 1                ",GREEN);break;
		case 29:   DisplayBMP(2);                                      LCD_ShowString(10,11,"PIC 2                ",GREEN);break;
		case 30:  DisplayBMP(3);                                       LCD_ShowString(10,11,"PIC 3                ",GREEN);break;
		case 31:  DisplayBMP(4);                                       LCD_ShowString(10,11,"PIC 4                ",GREEN);break;		
		case 32:  DisplayBMP(5);                                       LCD_ShowString(10,11,"PIC 5                ",GREEN);break;
		case 33:  DisplayBMP(6);                                       LCD_ShowString(10,11,"PIC 6                ",GREEN);break;
		case 34:  DisplayBMP(7);                                       LCD_ShowString(10,11,"PIC 7                ",GREEN);break;
//		case 35:  DisplayBMP(8);                                       LCD_ShowString(10,11,"PIC 8                ",GREEN);break;
//		case 36:  DisplayBMP(9);                                       LCD_ShowString(10,11,"PIC 9                ",GREEN);break;
//		case 37:  DisplayBMP(10);                                      LCD_ShowString(10,11,"PIC 10               ",GREEN);break;
		default: break;
	}
	
//	TestDrawPixelDotLine();
	
	//��������������β ��Command Modeˢ��һ��֡����Ĳ���
	TmpData = 0x0001;
	CommandMode_Write( 0xC0, &TmpData, 1);

	//2A��2B, Restart from (0,0) "origin of coordinates"
	//2A����
	TmpData = 0x0743;
	CommandMode_Write( 0xB7, &TmpData, 1);
	TmpData = 0x0005;
	CommandMode_Write( 0xBC, &TmpData, 1);
	TmpData = 0x0000;
	CommandMode_Write( 0xBD, &TmpData, 1);
	TmpD[0] = 0x00002A;
	TmpD[1] = 0x003704;
	CommandMode_Write( 0xBF, TmpD, 2);
	
	//2B����
	TmpData = 0x0743;
	CommandMode_Write( 0xB7, &TmpData, 1);
	TmpData = 0x0005;
	CommandMode_Write( 0xBC, &TmpData, 1);
	TmpData = 0x0000;
	CommandMode_Write( 0xBD, &TmpData, 1);
	TmpD[0] = 0x00002B;
	TmpD[1] = 0x007F07;
	CommandMode_Write( 0xBF, TmpD, 2);
	
	
	//����������GPUҪд�����ݿ�Ĵ�С
	TmpData = 0x0743;
	CommandMode_Write( 0xB7, &TmpData, 1);
	TmpData = 0xEC00;
	CommandMode_Write( 0xBC, &TmpData, 1);
	TmpData = 0x005E;
	CommandMode_Write( 0xBD, &TmpData, 1);
	CommandMode_Write( 0xBF, &TmpData, 0);
	
	CommandMode_GPUWholeFrame_FastWrite(0x2C);
	
	
//	//��DDR��һ֡�������滭�Խ���
//	TestDrawPixelDotLine();
//	
//	//��DDR�ж������128x128С����, ���Խ�����ʾ����
//	TestCommandModeDrawRectangleFromDDR();
}


//void Delay_ms_with_KeyScan(UINT16 ms) {
//	while(ms--) {
//		//Delay_ms(1);
//		//ShortDelay(40);
//		delayms(1);
//		
//		if((P0_SampleValue & 0x1F) != 0x1F) {
//			return; //if any KEY pressed, then break the loop
//		}
//	}
//}

//void Delay_ms_Only_PowerKeyScan(UINT16 ms) {
//	while(ms--) {
//		//Delay_ms(1);
//		//ShortDelay(40);
//		delayms(1);
//		
//		if(I_KEY_POWER() == 0) {
//			return; //if Power KEY pressed, then break the loop
//		}
//	}
//}

