#include "user_gpio_def.h"
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"











//240x320-LCD, ����CS, ����PIN���и�BottomBoard��MCU(LT32A01)����
//MCU_PB8  --- LCD_CS  == CS
//MCU_PB9  --- LCD_RST == RST
//MCU_PB13 --- LCD_WR == SDO
//MCU_PB14 --- LCD_RS == SCLK
//MCU_PB15 --- LCD_RD == SDI
//--- 3-Pin SPI 9bit mode
uint8_t I_LCD240x320_SDO(void) { //��������, LCD_WR
	//return GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_14);
	return GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_13);
}

void O_LCD240x320_SDI(uint8_t value) { //����, LCD_RD
	if(value == 0)
		GPIOB->BRR = GPIO_Pin_15;
		//GPIO_WriteBit(GPIOB, GPIO_Pin_15, Bit_RESET);
	else
		GPIOB->BSRR = GPIO_Pin_15;
		//GPIO_WriteBit(GPIOB, GPIO_Pin_15, Bit_SET);
}
void O_LCD240x320_SCK(uint8_t value) { //ʱ��, LCD_RS
	if(value == 0)
		//GPIOB->BRR = GPIO_Pin_13;
		GPIOB->BRR = GPIO_Pin_14;
	else
		//GPIOB->BSRR = GPIO_Pin_13;
		GPIOB->BSRR = GPIO_Pin_14;
}
void O_LCD240x320_REST(uint8_t value) { //��λ, LCD_RST
	if(value == 0)
		GPIOB->BRR = GPIO_Pin_9;
	else
		GPIOB->BSRR = GPIO_Pin_9;
}
void O_LCD240x320_CS(uint8_t value)  { //Ƭѡ, LCD_CS
	if(value == 0)
		GPIOB->BRR = GPIO_Pin_8;
	else
		GPIOB->BSRR = GPIO_Pin_8;
}



//SPI Flash, M25P80, GPU-Config-Data
//PA0,PA1 keep dis-connect, input-floating;
//PA2 --- GPU_StartUpBoot_Done, input, GPU PowerOn/Reset Start-up Boot status, input-floating
//PA3 --- GPU_StartUpBoot_ResetN, output, Low Active, when Program SPI Flash(M25P80), Keep this pin active untill program flash done
//PA4 --- MCU_SPI_NSS
//PA5 --- MCU_SPI_SCK
//PA6 --- MCU_SPI_MISO
//PA7 --- MCU_SPI_MOSI
//when config GPU-SPI-Flash, enable output of CS/SCK/MOSI, otherwise keep input-floating
uint8_t I_GPU_StartUpBoot_Done(void) { //GPU Start-up Boot finish/done
	return GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_2);
}
void O_GPU_StartUpBoot_ResetN(uint8_t value) { //GPU_StartUpBoot_ResetN
	if(value == 0)
		GPIO_WriteBit(GPIOA, GPIO_Pin_3, Bit_RESET);
	else
		GPIO_WriteBit(GPIOA, GPIO_Pin_3, Bit_SET);
}
void O_M25P80_SPI_CSN(uint8_t value) { //MCU_SPI_NSS
	if(value == 0)
		GPIO_WriteBit(GPIOA, GPIO_Pin_4, Bit_RESET);
	else
		GPIO_WriteBit(GPIOA, GPIO_Pin_4, Bit_SET);
}
void O_M25P80_SPI_CLK(uint8_t value) { //MCU_SPI_SCK
	if(value == 0)
		GPIO_WriteBit(GPIOA, GPIO_Pin_5, Bit_RESET);
	else
		GPIO_WriteBit(GPIOA, GPIO_Pin_5, Bit_SET);
}
void O_M25P80_SPI_MOSI(uint8_t value) { //MCU_SPI_MOSI
	if(value == 0)
		GPIO_WriteBit(GPIOA, GPIO_Pin_7, Bit_RESET);
	else
		GPIO_WriteBit(GPIOA, GPIO_Pin_7, Bit_SET);
}
uint8_t I_M25P80_SPI_MISO(void) { //MCU_SPI_MISO
	return GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_6);
}
//���ﲻ�����ó�OpenDrain, ��Ϊ������10K��������, ��STM32��IO��Rpd=40K, OpenDrain�Ļ���ѹ������
void EnableGPU_SPI_FLASH_OutputDriving(void) { //Enable Output Push-Pull
	GPIO_InitTypeDef GPIO_InitStructure;
	//Output GPIOA
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	//Output GPIOA
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}
void DisableGPU_SPI_FLASH_OutputDriving(void) { //Keep Input Floating
	GPIO_InitTypeDef GPIO_InitStructure;
	//Input GPIOA
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void EnableEBindingPin_OutputDriving(uint16_t GPIO_PinX) { //Keep Output Push-Pull
	GPIO_InitTypeDef GPIO_InitStructure;
	//Output GPIOA
	GPIO_InitStructure.GPIO_Pin = GPIO_PinX;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}
void DisableEBindingPin_OutputDriving(uint16_t GPIO_PinX) { //Keep Input PullUp
	GPIO_InitTypeDef GPIO_InitStructure;
	//Input GPIOA
	GPIO_InitStructure.GPIO_Pin = GPIO_PinX; //GPIO_Pin_13 | GPIO_Pin_14;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}



//AD�������
//ARM_AIN0 		--- MCU_PC0, BottomBoard�е�12V_IN�������, ʹ��IN193����, ʵ�ʺ��ӵĲ�������0.1R(1206,F3), ����ܵ����Ƿ����쳣
//ARM_AIN6 		--- MCU_PC1, BottomBoard�е�N_IOVCC�������, ʹ��IN193����, ʵ�ʺ��ӵĲ�������0.0R(1206,F7)
//ARM_AIN7 		--- MCU_PC2, BottomBoard�е�N_VCC�������, ʹ��IN193����, ʵ�ʺ��ӵĲ�������0.0R(1206,F9)
//ARM_AIN8 		--- MCU_PC3, BottomBoard�е�VSP_5V6�������, ʹ��IN193����, ʵ�ʺ��ӵĲ�������0.1R(1206,F10)
//ARM_AIN9 		--- MCU_PC4, BottomBoard�е�VSN_5V6�������, ʹ��IN193����, ʵ�ʺ��ӵĲ�������0.1R(1206,F11)
//TP_INT_ADC 	--- MCU_PC5, ---







//����5��PIN��������BottomBoard��J14, ���ӵ�2828ת���Ϲ�2828��STM32ͨ��ʹ��
//EINT11_2828RESET 	--- MCU_PE6, 2828��λ
//SPICS 	--- MCU_PB12, LCD_SPI_CS
//SPISCK 	--- MCU_PB13, LCD_SPI_SCL
//SPISDO 	--- MCU_PB14, LCD_SPI_SDO
//SPISDI 	--- MCU_PB15, LCD_SPI_SDA
void O_SSD2828_RESET(uint8_t value) { //EINT11_2828RESET
	if(value == 0)
		GPIO_WriteBit(GPIOE, GPIO_Pin_6, Bit_RESET);
	else
		GPIO_WriteBit(GPIOE, GPIO_Pin_6, Bit_SET);
}
void O_SSD2828_SPI_CS(uint8_t value) { //SPICS
	if(value == 0)
		GPIO_WriteBit(GPIOB, GPIO_Pin_12, Bit_RESET);
	else
		GPIO_WriteBit(GPIOB, GPIO_Pin_12, Bit_SET);
}
void O_SSD2828_SPI_CLK(uint8_t value) { //SPISCK
	if(value == 0)
		GPIO_WriteBit(GPIOB, GPIO_Pin_13, Bit_RESET);
	else
		GPIO_WriteBit(GPIOB, GPIO_Pin_13, Bit_SET);
}
void O_SSD2828_SPI_SDI(uint8_t value) { //SPISDI, ��ͨ2828��"SDI"����
	if(value == 0)
		GPIO_WriteBit(GPIOB, GPIO_Pin_15, Bit_RESET);
	else
		GPIO_WriteBit(GPIOB, GPIO_Pin_15, Bit_SET);
}
uint8_t I_SSD2828_SPI_SDO(void) { //SPISDO, ��ͨ2828��"SDO"����
	return GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_14);
}

//����2��PIN��������BottomBoard��J14, ���ӵ�2828ת���Ϲ�������IICͨ��ʹ��
//GPG4_TP_SCL 	--- MCU_PB6
//GPG5_TP_SDA  	--- MCU_PB7
uint8_t GPG_TP_I2C_SCL(uint8_t value) { //GPG4_TP_SCL
	if(value == 0)
		GPIO_WriteBit(GPIOB, GPIO_Pin_6, Bit_RESET);
	else
		GPIO_WriteBit(GPIOB, GPIO_Pin_6, Bit_SET);
	
	return GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_6);
}
uint8_t GPG_TP_I2C_SDA(uint8_t value) { //GPG5_TP_SDA
	if(value == 0)
		GPIO_WriteBit(GPIOB, GPIO_Pin_7, Bit_RESET);
	else
		GPIO_WriteBit(GPIOB, GPIO_Pin_7, Bit_SET);

	return GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_7);
}






//IO_TEST1_TP_RESET --- MCU_PE1, ������BottomBoard��J14, 
//IO_TEST0 			--- MCU_PE3, IO���Ե�, ����Ϊ��PIN������
//BLK_SET_GPJ2 		--- MCU_PE0
//EN_LCDIOVCC 		--- MCU_PE2
//EN_MTP 			--- MCU_PE4
//EN_LCDVCC 		--- MCU_PE5
//BL_PWM_GPB0 		--- MCU_PB0
void O_PWR_EN_LCDIOVCC(uint8_t value) { //EN_LCDIOVCC
	if(value == 0)
		GPIO_WriteBit(GPIOE, GPIO_Pin_2, Bit_RESET);
	else
		GPIO_WriteBit(GPIOE, GPIO_Pin_2, Bit_SET);
}
void O_PWR_EN_LCDVCC(uint8_t value) { //EN_LCDVCC
	if(value == 0)
		GPIO_WriteBit(GPIOE, GPIO_Pin_5, Bit_RESET);
	else
		GPIO_WriteBit(GPIOE, GPIO_Pin_5, Bit_SET);
}
void O_PWR_EN_MTP(uint8_t value) { //EN_MTP
	if(value == 0)
		GPIO_WriteBit(GPIOE, GPIO_Pin_4, Bit_RESET);
	else
		GPIO_WriteBit(GPIOE, GPIO_Pin_4, Bit_SET);
}
void O_PWR_BLK_SET_LEDK5(uint8_t value) { //BLK_SET_GPJ2
	if(value == 0)
		GPIO_WriteBit(GPIOE, GPIO_Pin_0, Bit_RESET);
	else
		GPIO_WriteBit(GPIOE, GPIO_Pin_0, Bit_SET);
}
void O_TEST1_TP_RESET(uint8_t value) { //IO_TEST1_TP_RESET
	if(value == 0)
		GPIO_WriteBit(GPIOE, GPIO_Pin_1, Bit_RESET);
	else
		GPIO_WriteBit(GPIOE, GPIO_Pin_1, Bit_SET);
}
void O_PWR_BL_PWM(uint8_t value) { //BL_PWM_GPB0
	if(value == 0)
		GPIO_WriteBit(GPIOB, GPIO_Pin_0, Bit_RESET);
	else
		GPIO_WriteBit(GPIOB, GPIO_Pin_0, Bit_SET);
}





//comunication with LT32A01 on BottomBoard, ��ЩPIN����LCD240x320���õ�
//SPISS0 	--- MCU_PD3
//SPICLK0 	--- MCU_PB13
//SPIMISO0 	--- MCU_PB14
//SPIMOSI0 	--- MCU_PB15








//Iphone LCM SPI(J2 of BottomBoard)
//LCM_SPI_CS 	--- MCU_PA15
//LCM_SPI_CLK 	--- MCU_PB3
//LCM_SPI_MOSI 	--- MCU_PB5
//LCM_SPI_MISO  --- MCU_BP4


//Ŀǰ������PIN����BottomBoard�������յ�
//GPB1_LED0 --- MCU_PB1
//GPC_LED1  --- MCU_PB2


//XUODM 	--- MCU_PA11, ����IO��:USBDM
//XUODP 	--- MCU_PA12, ����IO��:USBDP

//XUTXD0 	--- MCU_PA9, ����IO��USART1_TX,���ع̼���, ͬʱ����׼��ӡ�ն����
//XURXD0 	--- MCU_PA10, ����IO��USART1_RX

//XUTXD1 	--- MCU_PB10, ����IO��USART3_TX
//XURXD1 	--- MCU_PB11, ����IO��USART3_RX


//SD Card SDIO Interface, only connect to GPU, keep disconnect with STM32, so these pins keep input-floating
//XEINT6_SD0_NWP 	--- MCU_PD3
//XMMC0CDN 			--- MCU_PD6
//XMMCCLK0 			--- MCU_PC12, ����IO��SDIO_CK
//XMMCCMD0 			--- MCU_PD2, ����IO��SDIO_CMD
//XMMC0DATA0 		--- MCU_PC8, ����IO��SDIO_D0
//XMMC0DATA1 		--- MCU_PC9, ����IO��SDIO_D1
//XMMC0DATA2 		--- MCU_PC10, ����IO��SDIO_D2
//XMMC0DATA3 		--- MCU_PC11, ����IO��SDIO_D3





//--- ���� ------------------------------------------------------
//USER_K1_GPF0 	--- MCU_PA8
//USER_K2_GPF1 	--- MCU_PC13
//USER_K3_GPF2 	--- MCU_PC6
//USER_K4_GPF3 	--- MCU_PC14
//USER_K5_GPF4 	--- MCU_PC7
//USER_K6_GPF5 	--- MCU_PC15
uint8_t I_USER_K1_AUTO(void) { //USER_K1_GPF0, �Զ�/�ֶ�, �ֶ�ѡ��
	return GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_8);
}
uint8_t I_USER_K2_POWER(void) { //USER_K2_GPF1, ON/OFF
	return GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_13);
}
uint8_t I_USER_K3_NEXT(void) { //USER_K3_GPF2, �Զ�ʶ��,�·�
	return GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_6);
}
uint8_t I_USER_K4_UP(void) { //USER_K4_GPF3, �ֶ�ȷ��, �Ϸ�
	return GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_14);
}
uint8_t I_USER_K5(void) { //---
	return GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_7);
}
uint8_t I_USER_K6_MODE(void) { //USER_K6_GPF5, ��������
	return GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_15);
}













void RCC_Configuration(void) {
	//ʹ��GPIOA/B/C/D/E, ADC1, AFIOʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOE | RCC_APB2Periph_ADC1 | RCC_APB2Periph_AFIO, ENABLE); 
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_FSMC, ENABLE); //ʹ��FSMC
	RCC_ADCCLKConfig(RCC_PCLK2_Div8);//����ADCʱ��=PCLK2 1/8 = 9MHz, ADC���Ƶ�ʲ��ܳ���14MHz
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE); //ʹ��USART1ʱ��
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE); //ʹ��USART3ʱ��
}

void GPIO_Configuration(void) {
	GPIO_InitTypeDef GPIO_InitStructure;
	
	//RCC(Periph Clock) enable, Clock configuration should be prior to GPIO Setting
	RCC_Configuration();
	
	//Change the maping of specified pins(JTAG: JTDI,JTDO,JNTRST) as GPIO
	//GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE); //SWJ enable, JTAG disable
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE); //Full SWJ Disabled (JTAG-DP + SW-DP), ʹ��SWD������PIN�����İ弤����
	
	//--- GPIOA ----------------------------------------------------------------------------------------------------
	//Input GPIOA, --- GPU_StartUpBoot_ResetN and MCU_SPI_* �������ó���������
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	//Input, USART1-RX
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_13 | GPIO_Pin_14;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	//Alternate-function Output GPIOA, USART1-TX
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	
	//--- GPIOB ----------------------------------------------------------------------------------------------------
	//Output GPIOB
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	//Alternate-function Output, TIM8_CH2N
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	//OpenDrain Output GPIOB
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	//Input
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_14;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	//Input, USART3-RX
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	//Alternate-function Output GPIOA, USART3-TX
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	
	//--- GPIOC ----------------------------------------------------------------------------------------------------
	//Analog Input
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	//Input,
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	//Input PullUP, ����PC8/9/10/11/12��SDIO�ӿ�,��Ҫ���մ���
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9  | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	

	
	//--- GPIOD ----------------------------------------------------------------------------------------------------
	//Alternate-function Output GPIOD, FSMC, WR,RD,DB[3:0],DB[15:13], A[18:16]
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	//Input Floating
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	//Input PullUP
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	//Input pull-down, (NE1,�������ж�����, ������FSMC���NE1)
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_Init(GPIOD, &GPIO_InitStructure);

	
	//--- GPIOE ----------------------------------------------------------------------------------------------------
	//Alternate-function Output GPIOE, FSMC, DB[12:4]
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	//Output GPIOE
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOE, &GPIO_InitStructure);

}



