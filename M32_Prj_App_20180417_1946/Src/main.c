#include <stdio.h>
#include <stdlib.h>
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "misc.h"
#include "stm32f10x_tim.h"

#include "pport_spi.h"
#include "lcd_cfg.h"
#include "redef_print.h"
#include "user_config.h"
#include "app.h"
#include "power_task.h"
#include "timer.h"
#include "tools.h"
#include "MCU_GPU_fsmc.h"
#include "GPU_Cfg.h"
#include "ExternalIntWithGPU.h"

#include "m25p80.h"
#include "lcd240x320.h"
#include "DBG_uart.h"
#include "GPU_SPI_Flash_CFG.h"
#include "i2c.h"
#include "BoardAndCoreInf.h"


UINT8 K3Pressed;
UINT8 ShowMode;
UINT8 AutoFlag;
UINT8 PowerStatus;

UINT8 gMipiTableIndex;
UINT8 gVersion[20] = "2017.1016.Ver-2";

UINT8 KeyPowerPressed;
UINT8 KeyUpPressed;
UINT8 KeyDownPressed;
UINT8 KeyAutoPressed;
UINT8 KeyOTPPressed;
UINT8 EBindingPinTrigger;

UINT8 SDCardLoaded;
UINT8 GPUAllReady;

void PowerOn_Process(void) {
	//�򿪵�Դ���Դ(�ϵ�), ���Ƶ�Դ�ϵ�˳��
  LCD_ShowString(10,10,"ON ",GREEN);
	Power_On();


	ShowMode = 1;
	PowerStatus = 1;
}
void PowerOff_Process(void) {
	ShowMode = 1;
	LCD_ShowString(10,10,"OFF",RED);
	//�ضϵ�Դ���Դ(�µ�), ���Ƶ�Դ�µ�˳��
	Power_Off();

	PowerStatus = 0;
}

void KeyUp_Process(void) { //ǰ/��һ������
	KeyUpPressed = 0;
	if(PowerStatus==0) return;
	AutoFlag = 0;
	LCD_ShowString(10,9,"UP  ",GREEN);	LCD_ShowString(10,2,"Manual Mode",GREEN);
	if(ShowMode == 1)
		ShowMode = ptr_MIPI_TABLE[gMipiTableIndex]->SIZE_OF_SHOW_MODE; //��ʾ���ܻ������
	else
		ShowMode -= 1;
	Lcd_ShowMode(ShowMode);
	
}
void KeyDown_Process(void) { //��/��һ������
	KeyDownPressed = 0;
	if(PowerStatus==0) return;
	AutoFlag = 0;
	LCD_ShowString(10,9,"NEXT",GREEN);	LCD_ShowString(10,2,"Manual Mode",GREEN);
	if(ShowMode == ptr_MIPI_TABLE[gMipiTableIndex]->SIZE_OF_SHOW_MODE) //��ʾ���ܻ������
		ShowMode = 1;
	else
		ShowMode += 1;
	Lcd_ShowMode(ShowMode);
	
}

void KeyAuto_Process(void) { //��/��һ������
	KeyAutoPressed = 0;
	//if(PowerStatus==0) return;
	 AutoFlag=!AutoFlag;
	if(AutoFlag)
	LCD_ShowString(10,2,"Auto Mode  ",GREEN);
	else
	LCD_ShowString(10,2,"Manual Mode",GREEN);
	
}

void KeyOTP_Process(void) { //��/��һ������
	KeyOTPPressed = 0;
	if(PowerStatus==0) return;
	LCD_ShowString(10,9,"OTP ",GREEN);
	



}

void SysInitErrorProcess(void) {
	LCD_ShowString(3,12,"System Startup Failed!",RED);
	while(1) { //
		//GPU SPI���ô���, GPU��������ҪSTM32��ϲ������, ����ϵͳ��ʼ����������������˲���ֱ��while(1); ��Ȼ�������޷�����GPU
		GPU_SPI_Config_Process();
		if(EBindingPinTrigger) {
			SPI_Flash_EncryptBinding_Process();
			EBindingPinTrigger = 0;
		}
	}
}


void start_pet(){
	int i=0;
	UINT32 Tmp32D;
	UINT32 Tmp32V;
	Sys_Beep(100);
	LCD_Logo_Disp();
	LCD_ShowString(0,0,"Shen Zhen XK-Image CO.LTD",POINT_COLOR);
	LCD_ShowString(5,12,"System Starting...",POINT_COLOR);
	Disp_Frame(18,238,204,8,0xffff);
	for(i=0;i<201;i++){
		Disp_Window(20,240,i,4,0xFFFF);
		Delay(5);
		
		if(i==60){
			VSPN_I2C_Init();
			reset_lcd();
			CommandMode_Init();
			//if(Ssd2828_ID_OK_check()==1){
			if(Ssd2828_ID_OK_check_CmdMode() == 1) {
				LCD_ShowString(0,16,"MIPI Staus OK!",GREEN);   
			}else{
				Disp_Window(20,240,i,4,0xF800);
				LCD_ShowString(0,16,"MIPI NG!",RED); 
				//LCD_ShowString(3,12,"System Startup Failed!",RED);		
				SysInitErrorProcess();//while(1);
			}

		}
		if(i==100){
			GPUAllReady = 0;
			if(0 == I_GPU_StartUpBoot_Done()) { //GPU�޹̼�, ��Ҫ����GPU�̼�
				LCD_ShowString(0,17,"No GPU, Please Download!",RED);
				SysInitErrorProcess();
			}
			else if(0 == GPU_Connection_Check()) { //GPU�̼�����, �������ش��˹̼�
				LCD_ShowString(0,17,"GPU Ver ERR, Pls Updated!",RED);
				SysInitErrorProcess();
			}
			else if(0 == GPU_LogicWorkStatus()) { //GPUδ����, ��ʱ���İ����½�(6��������Ա��Ǹ�)LED�Ʋ�����, ���ǻ�ʺ�����˸�򼱴���˸״̬
				UINT16 Res;
				MCU_GPU__ADDR = MCU_CFG_GPU__DDR_ACCESS_CTRL_REG_ADDR;
				Res = MCU_GPU__DATA;
				if((Res & 0x8300) != 0x8300)
					LCD_ShowString(0,17,"GPU not Activated!",RED);
				else {
					MCU_GPU__ADDR = MCU_CFG_GPU__PURECOLOR_ADDR0;
					MCU_GPU__DATA = 0xA5C3;
					Res = MCU_GPU__DATA;
					if(Res != 0xA5C3) {
						LCD_ShowString(0,17,"MCU-GPU FSMC Connect ERR!",RED);
					}
					else {
						MCU_GPU__ADDR = MCU_CFG_GPU__PURECOLOR_ADDR0;
						MCU_GPU__DATA = 0x5A3C;
						Res = MCU_GPU__DATA;
						if(Res != 0x5A3C) {
							LCD_ShowString(0,17,"MCU-GPU FSMC Connect ERR!",RED);
						}
						else {
							LCD_ShowString(0,17,"GPU DDR Calib Fail!",RED);
						}
					}
				}
				SysInitErrorProcess();
			}
			else { //�ɹ�����GPU, ��ʱ���İ����½�LED�ƻᴦ��Ϩ��״̬
				GPUAllReady = 1;
				Tmp32D = Get_GPU_DateTime();
				Tmp32V = Get_GPU_Version();
				LCD_ShowString(0,17,"GPU ver:",GREEN); DispHexChar(8*8,17*16,Tmp32V,8,GREEN);
				
				Gpu_DisplayCfg();  //GPU ��������
			}
		}
		if(i==140){
			if(GPUAllReady) { //ֻ��GPU�ɹ����غ�, ���ܽ��к�������
				if(SD_IP_Card_Init()==1){
					SDCardLoaded = 0;
					//Disp_Window(20,240,i,4,0xF800);
					LCD_ShowString(0,18,"SD Init NG, or No Card!",RED);
					//LCD_ShowString(3,12,"System Startup Failed!",RED);
					SysInitErrorProcess(); //while(1);
				}else{
					SDCardLoaded = 1; //��ʾ SD������/��ʼ�� �ɹ�
					LCD_ShowString(0,18,"SD Card Init OK!",GREEN); 
				}
			}
		}
		if(i==180){
			if(SDCardLoaded) { //ֻ��SD�����سɹ�����ִ�����º���
				ExtractBPB_Param();
				FindALLBMP_Entry();
			}
		}
	}
}

u32 DEV_ID=85012345;
void pat1(){
	DEV_ID=Arm_Get_Current(0x81,0x4a);
	Disp_Frame(0,0,240,320,0xffff);
	LCD_ShowString(7,0,"X91 TEST BOX ",POINT_COLOR);
	LCD_ShowString(0,2,"PAT STAU:",POINT_COLOR);
	LCD_ShowString(0,4,"LCM Name:",POINT_COLOR);LCD_ShowString(0,5,(const char *)ptr_MIPI_TABLE[gMipiTableIndex]->bLCDName,GREEN);
	LCD_ShowString(0,8,"IC  Name:",POINT_COLOR);LCD_ShowString(10,8,(const char *)ptr_MIPI_TABLE[gMipiTableIndex]->bICName,GREEN);
	LCD_ShowString(0,9,"KEY STAU:",POINT_COLOR);
	LCD_ShowString(0,10,"PWR STAU:",POINT_COLOR);
	LCD_ShowString(0,11,"PAT Name:",POINT_COLOR);
	LCD_ShowString(0,13,"SYS Curr:",POINT_COLOR);
	LCD_ShowString(0,18,"DEV ID:",POINT_COLOR);DispNumber(7*8,18*16,DEV_ID,8,GRAY);LCD_ShowString(18,18,__DATE__,BLUE);
}

int main (void) {
	
	  /*!< At this stage the microcontroller clock setting is already configured, 
       this is done through SystemInit() function which is called from startup
       file (startup_stm32f10x_xx.s) before to branch to application main.
       To reconfigure the default setting of SystemInit() function, refer to
       system_stm32f10x.c file
     */
       
	//��ʼ���ڲ�����
	ShowMode = 1;
	AutoFlag = 0;
	K3Pressed = 0;
	EBindingPinTrigger = 0;
	SDCardLoaded = 0;
	GPUAllReady = 0;
	
	GPU_Int_Pending = 0;
	PowerStatus = 0;
	gMipiTableIndex = 0;
	srand((int)__TIME__&rand());
	//��ʼ��ʹ�õ���GPIO�ķ���: Output/Input, ��IO����ģʽ
  	Init_System();
	
	
//	Power_Off();
	Lcd240x320_Init();   //MCU-TFT(240x320) ��ʼ��
	//LCD_Clear(BACK_COLOR); //����, ---�����Logoͼ����Ҫ��ʾ�Ļ�, ����������滻��
	
		
	TIM8_PWM_Configuration(36000-1, 100);
	Timer2_Enable(); //����start_pet()ǰ��
	Timer3_Enable();

	//printf("\r\n..1..\r\n");
	
	//Gpu_DisplayCfg();
	





	start_pet();
	//�򿪵�Դ���Դ(�ϵ�), ���Ƶ�Դ�ϵ�˳��
	//Power_On();
//	PowerStatus = 1;
//	printf("\r\nPower ON\r\n\r\n");


	//��λLCD������оƬ
	//reset_lcd();
	delayms(1000);
	ShowMode = 1;
	pat1();
	
	while(1) {
		

	 	Show_Curr();
		if(AutoFlag&&PowerStatus) {
			if(ShowMode == ptr_MIPI_TABLE[gMipiTableIndex]->SIZE_OF_SHOW_MODE) //��ʾ���ܻ������
				ShowMode = 1;
			else
				ShowMode += 1;
			Lcd_ShowMode(ShowMode);
			delayms(1000);
		}
	
		if(KeyUpPressed == 1) { //�㴥����, ����ʱΪ�ߵ�ƽ, ����ʱΪ�͵�ƽ
			printf("\r\nUP\r\n");
			KeyUp_Process();
		}
		else if(KeyDownPressed == 1) { //�㴥����, ����ʱΪ�ߵ�ƽ, ����ʱΪ�͵�ƽ
			printf("\r\nDOWN\r\n");
			KeyDown_Process();
		}
		if(KeyPowerPressed == 1) {
			if(PowerStatus) {
				PowerOff_Process();
				printf("\r\nPower OFF\r\n\r\n");
			}
			else {
				PowerOn_Process();
				printf("\r\nPower ON\r\n\r\n");
			}
			KeyPowerPressed = 0;
		}
		if(KeyAutoPressed==1){
		 KeyAuto_Process();
		}
		if(KeyOTPPressed==1){
		 KeyOTP_Process();
		}
		
		//GPU SPI���ô���
		GPU_SPI_Config_Process();
		if(EBindingPinTrigger) {
			SPI_Flash_EncryptBinding_Process();
			EBindingPinTrigger = 0;
		}
	}
}

