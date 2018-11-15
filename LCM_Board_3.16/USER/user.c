
#include "user.h"
#include "ssd2828.h"




unsigned int S90638_INIT_PCS=198-6;  //??????

extern void LCD_INIT(void);

unsigned char const  S90638_INIT_CODE[198-6][60]={ 
{0xFF,3,0x98,0x81,0x03},
{0x01,1,0x00},
{0x02,1,0x00},
{0x03,1,0x53},
{0x04,1,0x54},
{0x05,1,0x14},
{0x06,1,0x04},
{0x07,1,0x03},
{0x08,1,0x01},
{0x09,1,0x00},
{0x0a,1,0x64},
{0x0b,1,0x64},
{0x0c,1,0x00},
{0x0d,1,0x00},
{0x0e,1,0x00},
{0x0f,1,0x65},
{0x10,1,0x65},
{0x11,1,0x00},
{0x12,1,0x00},
{0x13,1,0x00},
{0x14,1,0x00},
{0x15,1,0x00},
{0x16,1,0x00},
{0x17,1,0x00},
{0x18,1,0x00},
{0x19,1,0x00},
{0x1a,1,0x00},
{0x1b,1,0x00},
{0x1c,1,0x00},
{0x1d,1,0x00},
{0x1e,1,0xC0},
{0x1f,1,0x80},
{0x20,1,0x03},
{0x21,1,0x08},
{0x22,1,0x00},
{0x23,1,0x00},
{0x24,1,0x00},
{0x25,1,0x00},
{0x26,1,0x00},
{0x27,1,0x00},
{0x28,1,0x55},
{0x29,1,0x04},
{0x2a,1,0x00},
{0x2b,1,0x00},
{0x2c,1,0x00},
{0x2d,1,0x00},
{0x2e,1,0x00},
{0x2f,1,0x00},
{0x30,1,0x00},
{0x31,1,0x00},
{0x32,1,0x00},
{0x33,1,0x00},
{0x34,1,0x03},
{0x35,1,0x00},
{0x36,1,0x05},
{0x37,1,0x00},
{0x38,1,0x01},
{0x39,1,0x00},
{0x3a,1,0x00},
{0x3b,1,0x00},
{0x3c,1,0x00},
{0x3d,1,0x00},
{0x3e,1,0x00},
{0x3f,1,0x00},
{0x40,1,0x00},
{0x41,1,0x00},
{0x42,1,0x00},
{0x43,1,0x00},
{0x44,1,0x00},
{0x50,1,0x01},
{0x51,1,0x23},
{0x52,1,0x45},
{0x53,1,0x67},
{0x54,1,0x89},
{0x55,1,0xab},
{0x56,1,0x01},
{0x57,1,0x23},
{0x58,1,0x45},
{0x59,1,0x67},
{0x5a,1,0x89},
{0x5b,1,0xab},
{0x5c,1,0xcd},
{0x5d,1,0xef},
{0x5e,1,0x01},
{0x5f,1,0x14},
{0x60,1,0x15},
{0x61,1,0x0C},
{0x62,1,0x0D},
{0x63,1,0x0E},
{0x64,1,0x0F},
{0x65,1,0x10},
{0x66,1,0x11},
{0x67,1,0x08},
{0x68,1,0x02},
{0x69,1,0x0A},
{0x6a,1,0x02},
{0x6b,1,0x02},
{0x6c,1,0x02},
{0x6d,1,0x02},
{0x6e,1,0x02},
{0x6f,1,0x02},
{0x70,1,0x02},
{0x71,1,0x02},
{0x72,1,0x06},
{0x73,1,0x02},
{0x74,1,0x02},
{0x75,1,0x14},
{0x76,1,0x15},
{0x77,1,0x0F},
{0x78,1,0x0E},
{0x79,1,0x0D},
{0x7a,1,0x0C},
{0x7b,1,0x11},
{0x7c,1,0x10},
{0x7d,1,0x06},
{0x7e,1,0x02},
{0x7f,1,0x0A},
{0x80,1,0x02},
{0x81,1,0x02},
{0x82,1,0x02},
{0x83,1,0x02},
{0x84,1,0x02},
{0x85,1,0x02},
{0x86,1,0x02},
{0x87,1,0x02},
{0x88,1,0x08},
{0x89,1,0x02},
{0x8A,1,0x02},
{0xFF,3,0x98,0x81,0x04},
{0x6C,1,0x15},
{0x6E,1,0x2F},
{0x6F,1,0x55},
{0x3A,1,0xA4},
{0x8D,1,0x1F},
{0x87,1,0xBA},
{0x26,1,0x76},
{0xB2,1,0xD1},
{0xFF,3,0x98,0x81,0x01},
{0x22,1,0x09},
{0x31,1,0x00},
{0x53,1,0x77},
{0x55,1,0x77},
{0x50,1,0xA6},
{0x51,1,0xA6},
{0x60,1,0x2B},
{0xA0,1,0x00},
{0xA1,1,0x0B},
{0xA2,1,0x2A},
{0xA3,1,0x14},
{0xA4,1,0x17},
{0xA5,1,0x2A},
{0xA6,1,0x1E},
{0xA7,1,0x20},
{0xA8,1,0x8C},
{0xA9,1,0x1C},
{0xAA,1,0x28},
{0xAB,1,0x78},
{0xAC,1,0x1A},
{0xAD,1,0x15},
{0xAE,1,0x4C},
{0xAF,1,0x20},
{0xB0,1,0x27},
{0xB1,1,0x52},
{0xB2,1,0x65},
{0xB3,1,0x3F},
{0xC0,1,0x00},
{0xC1,1,0x1B},
{0xC2,1,0x2A},
{0xC3,1,0x14},
{0xC4,1,0x17},
{0xC5,1,0x2A},
{0xC6,1,0x1E},
{0xC7,1,0x20},
{0xC8,1,0x8D},
{0xC9,1,0x1C},
{0xCA,1,0x28},
{0xCB,1,0x78},
{0xCC,1,0x1B},
{0xCD,1,0x15},
{0xCE,1,0x4C},
{0xCF,1,0x21},
{0xD0,1,0x27},
{0xD1,1,0x52},
{0xD2,1,0x65},
{0xD3,1,0x3F},
{0xFF,3,0x98,0x81,0x02},
{0x07,1,0xFF},
{0xFF,3,0x98,0x81,0x00},
{0x35,1,0x00},
{0x51,1,0xFF},
{0x53,1,0x24},
{0x55,1,0x00}};


#define nReportCnt 22
extern u8 Receive_Buffer[22];
extern u8 Transi_Buffer[22];
extern u8 USB_ReceiveFlg;
int usbnum=0;


BYTE buffer[10805]; // file copy buffer
BYTE buffer1[513];
char fb_buffer[256];
unsigned char lbuffer[64];

UINT uTimerH=0,uPreTimerH=0,uTimerL=0,uTimerPicH=0,uTimerPicL=0;
BYTE BurnStart=0,picDisBeforeBurn=0,u8PicIndex=0;

MISD_CardInfo SSDCardInfo;
MISD_Error SStatus = MISD_OK;

void LCD_SSD_SETT(void)
{
	
	Lcd_MODE = MIPI_SINGLE;   //
	Lcd_LCDH = 720;		  //???X?????
	Lcd_LCDV = 1280;	      //???Y?????
	Lcd_HBPD = 16;		      //??HBP
	Lcd_HFPD = 24; 
	Lcd_HSPW = 32;

	Lcd_VBPD = 8; 
	Lcd_VFPD = 8; 
	Lcd_VSPW = 16;  
	
	Lcd_fps = 60;
	Lcd_DCLK = (Lcd_fps * ((Lcd_LCDH + Lcd_HBPD + Lcd_HFPD + Lcd_HSPW) * (Lcd_LCDV + Lcd_VBPD + Lcd_VFPD + Lcd_VSPW)))/1000000;
	
	Dsi_LANE = 4;
  Dsi_mbps = 0;
	
	Lcd_DCLK_EDGE = DCLK_RISING_EDGE;         //???????		  
	Lcd_HSYNC_POLARITY = HSYNC_ACTIVE_LOW;    //HSYNC???????  
	Lcd_VSYNC_POLARITY = VSYNC_ACTIVE_LOW;    //VSYNC???????  
	Lcd_DE_POLARITY = DE_ACTIVE_HIGH;         //DE???????;	 	 	   
	LcdDrvInit();	
}

void LCD_INITT(void)
{
		unsigned int  a,b;
		a=0;b=0;
		for(a=0;a<S90638_INIT_PCS;a++)	//??????	{0xFF,3,0x98,0x81,0x00},
		{
			GP_LP( S90638_INIT_CODE[a][1]+1);//	3 + 1

			W_D(S90638_INIT_CODE[a][0]);//	?	0xFF

			for(b=0;b<S90638_INIT_CODE[a][1];b++)
			W_D(S90638_INIT_CODE[a][b+2]);//??????
		}
}

void Usart_Init(u32 bound)
{
    GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure; 
	NVIC_InitTypeDef NVIC_InitStructure;	 

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA, ENABLE); 
 	USART_DeInit(USART1);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

	USART_InitStructure.USART_BaudRate = bound;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
 
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//?????3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//????3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ????
	NVIC_Init(&NVIC_InitStructure);

  USART_Init(USART1, &USART_InitStructure);
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE); 
	USART_Cmd(USART1, ENABLE);
}

/***********************************************************   
?????IO
***********************************************************/
void LCDGPIO_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);

	///////////先设置为输入/////////////////////////////////////////////
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|
	                              GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7; //注意PA5PA6PA7也是SPI接口         
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;  
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;            
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;  
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	//
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5;            
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;  
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_10|GPIO_Pin_11;  //注意PB10,PB11也是I2C接口          
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;  
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;            
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;  
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOD, &GPIO_InitStructure);

	//////////下面是用户用到的IO初始化///////////////////////////

	//LCD的RST ->PA2 PB0
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_7|GPIO_Pin_0|GPIO_Pin_3|GPIO_Pin_8;                    
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
  
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;                   
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;                   
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
 
	//LCD的BIST -> PA5
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;                   
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	//lcd_PWM

}

//LCM的复位键控制
void LCM_RST_1(void)
{   
    GPIO_SetBits(GPIOA, GPIO_Pin_1);  //PA1
	GPIO_SetBits(GPIOC, GPIO_Pin_5);  	//PC5
    GPIO_SetBits(GPIOA, GPIO_Pin_2);  //PA2
    GPIO_SetBits(GPIOB, GPIO_Pin_0);  //PB0

}

void LCM_RST_0(void)
{
	GPIO_ResetBits(GPIOA, GPIO_Pin_1); 	//PA1
	GPIO_ResetBits(GPIOC, GPIO_Pin_5);  //PC5
	GPIO_ResetBits(GPIOA, GPIO_Pin_2);	//PA2
  GPIO_ResetBits(GPIOB, GPIO_Pin_0);	//PB0

}


void POWER_ON(void)
{
	GPIO_SetBits(GPIOA, GPIO_Pin_7);  //PA7
}
void POWER_OFF(void)
{

	GPIO_ResetBits(GPIOA, GPIO_Pin_7); 	//PA7
}




//LCM BIST ???      
void LCM_BIST_1(void)
{
    GPIO_SetBits(GPIOA, GPIO_Pin_5);
}

void LCM_BIST_0(void)
{
    GPIO_ResetBits(GPIOA, GPIO_Pin_5);
}



void TIM3_Int_Init(u16 arr,u16 psc)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //????
	
	//???TIM3???
	TIM_TimeBaseStructure.TIM_Period = arr; //???????????????????????????	
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //??????TIMx???????????
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //??????:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM??????
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //??????????TIMx???????
 
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE ); //?????TIM3??,??????

	//?????NVIC??
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3??
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //?????0?
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //????3?
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ?????
	NVIC_Init(&NVIC_InitStructure);  //???NVIC???

	TIM_Cmd(TIM3, ENABLE);  //??TIMx					 
}

//???3??????
void TIM3_IRQHandler(void)   //TIM3??
{
	if(TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)  //??TIM3????????
	{
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );  //??TIMx?????? 
		if(uTimerL<4600){
			uTimerL++;
		}else{
			uTimerH++;
			uTimerL=0;
		}

		if(uTimerPicL<460){
			uTimerPicL++;
		}else{
			uTimerPicH++;
			uTimerPicL=0;
		}
	}
}
 
unsigned int ReadVCOM(void)
{
	unsigned int ret;

	SSD2828_IC1_CS_0();	//IC1?C73??   U5
	SSD2828_IC2_CS_1();	//IC2?????	 U6
	SSD2828LP();		
	Delay_ms(2);
	GP_LP(4);
	W_D(0xB9);
	W_D(0xFF);
	W_D(0x83);
	W_D(0x99);
	SSD2828_IC1_CS_0();
	SSD2828_IC2_CS_1();
//	SSD2828Video();	
	return ret;
}

//FONT2448
int printfk(uint32_t x,uint32_t y,u8 font,uint32_t color,uint32_t bcolor,char mode,const char *fmt, ...)
{//x ? y?
	
	int i;
	uint32_t size;
	int len;
	
	__va_list ap;	
	size = 16*font;

	x = (x*size)>>1;	//x ????
	y = y*size;		//y ????
	printf("  x:%d y:%d   ",x,y);
	va_start(ap, fmt);
	len = vsprintf((char*)fb_buffer,fmt,ap);
	va_end(ap);
	printf("fb_buffer:%s  len:%d  ",fb_buffer,len);
	
	for (i = 0; i < strlen((char*)fb_buffer); i++)
	{
		if(x >= Lcd_LCDH){x=0; y += size;}	//Lcd_LCDH
    if(y >= Lcd_LCDV)	{y = y%Lcd_LCDV;};	//??  ShowString(16, 48, FONT2448, RED, 0x000000, str);
//static void ShowChar(unsigned int x, unsigned int y, unsigned int font, uint32_t color, uint32_t Bcolor, char a)		
		printf("  x:%d y:%d   ",x,y);
		ShowCharc(x,y,font,color,bcolor,fb_buffer[i],mode);
		x += size/2;
	}
	return len;
}

void USB_SendString(u8 *str)
{
     u8 ii=0;  
		 usbnum++;
     while(*str)
     {
         Transi_Buffer[ii++]=*(str++);
         if (ii == nReportCnt) break;
     }
     UserToPMABufferCopy(Transi_Buffer, ENDP2_TXADDR, nReportCnt);//Transi_Buffer[22];
     SetEPTxValid(ENDP2);
}

extern void Delay10us(u16 time);
u8 TBuffer[22];
int hid_printf(const char *fmt, ...)
{
	int i,j=0;
	int len;
	//char *fbp;
	
	__va_list ap;	

	va_start(ap, fmt);
	len = vsprintf((char*)fb_buffer,fmt,ap);
	va_end(ap);
	printf("fb_buffer:%s  len:%d  ",fb_buffer,len);
	j=0;
	for (i = 0; i < strlen((char*)fb_buffer); i++)
	{
		Transi_Buffer[j++] =	fb_buffer[i];
		if((((j)%22)==0)||((i+1)==strlen((char*)fb_buffer))){
			UserToPMABufferCopy(Transi_Buffer, ENDP2_TXADDR, nReportCnt);//Transi_Buffer[22];
			printf("\r\nTBuffer:%s\r\n",Transi_Buffer);
			SetEPTxValid(ENDP2);
			Delay10us(10000);
			j=0;
		}
	}
	return len;
}

//设置USB 连接/断线
//enable:0,断开
//       1,允许连接	   
void usb_port_set(u8 enable)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	  	 
	if(enable)_SetCNTR(_GetCNTR()&(~(1<<1)));//退出断电模式
	else
	{	  
		_SetCNTR(_GetCNTR()|(1<<1));  // 断电模式
		GPIOA->CRH&=0XFFF00FFF;
		GPIOA->CRH|=0X00033000;
		   		  
	}
}  	

void InitMipi_PanelInit(void)
{	
	SSD2828Init();	//
  	SSD2828_IC1_CS_0();	//IC1靠C73位置   U5	  0为选中IC  1为不选中
	SSD2828_IC2_CS_0();	//IC2靠按键位置	 U6
	
	SSD_LANE(Dsi_LANE,Dsi_mbps);//

	SSD2828LP();
	LCD_INIT();

	SSD2828_IC2_CS_1();//不选IC2
	DCS_Short_Read_NP(0x09, 1, lbuffer);//GP_R
	printf(" ID:0x%X ",lbuffer[0]);

	DCS_Short_Write_NP(0x11);
	Delay_ms(150);
	DCS_Short_Write_NP(0x29);
	Delay_ms(50);
/*
	GP_SP(1);
	W_D(0x11);		   	  //DCS_Short_Write_NP(0x11);
	Delay_ms(120);	
	GP_SP(1);
	W_D(0x29);		     //DCS_Short_Write_NP(0x29); display ON 		   
	Delay_ms(50); 		
*/
	SSD_MODE(0,1);
}



void DisplayON_PanelInit(void)
{				
	GPIO_ResetBits(GPIOA, GPIO_Pin_1);   //BL控制 PA1

	GPIO_SetBits(GPIOA, GPIO_Pin_0);   //PA0  控制2.85V,VCI-2.85,IOVCC-1.8V AVDD,AVEE
	//GPIO_SetBits(GPIOA, GPIO_Pin_2);	//OTP 电压控制
	GPIO_SetBits(GPIOA, GPIO_Pin_3);	 //SSD2828 3.3V 1.2V
	Delay_ms(50);
	SSD2828_STOP_1();	//SSD2828 所有I/O置高
	Delay_ms(10);

	GPIO_SetBits(GPIOA, GPIO_Pin_8);	 //LCM RESET	PA8
	Delay_ms(50);
	GPIO_ResetBits(GPIOA, GPIO_Pin_8);	 //LCM RESET
	Delay_ms(20);
	GPIO_SetBits(GPIOA, GPIO_Pin_8);	 //LCM RESET
	Delay_ms(50); 
																						
	InitMipi_PanelInit();     //MIPI初始化	 LCM初始化
	LcdDrv_RGB_ON();    			//开启RGB时序

	GPIO_SetBits(GPIOA, GPIO_Pin_1);   //BL 开
}


/*-------------------------------------------------------*/
void exit_sleep(void)
{
  	//---tft init------------
	DCS_SP(1);
	W_D(0x11);				  //SWREST
	Delay_ms(15);
}

void sleep(void)
{
  	//---tft init------------
	//SSD2828LP();
  DCS_SP(1);
	W_D(0x28);				  //SWREST
	Delay_ms(15);
	DCS_SP(1);
	W_D(0x10);				  //SWREST
	Delay_ms(120);
}

void DisplayOFF()
{	
		sleep();
		LcdDrv_RGB_OFF();

		Delay_ms(5);
		SSD2828_STOP_1();	//SSD2828 ??I/O??
		Delay_ms(5);

		GPIO_ResetBits(GPIOA, GPIO_Pin_8);	 //LCM RESET   
		GPIO_ResetBits(GPIOA, GPIO_Pin_0);   //PA0  ??2.85V,VCI2.85,IOVCC1.8V AVDD,AVEE
		GPIO_ResetBits(GPIOA, GPIO_Pin_3);	 //SSD2828 3.3V 1.2V
		Delay_ms(5);
		SSD2828_STOP_1();	//SSD2828 ??I/O??
		Delay_ms(5);		
		GPIO_ResetBits(GPIOA, GPIO_Pin_1);   //BL ??	   
		SSD2828_STOP();	//SSD2828 ??I/O??	
		Delay_ms(5);											    
}

void InitMipi_PanelInitr(void)
{
	SSD2828Init();
	SSD2828LP();
  SSD2828_IC1_CS_0();	//IC1?C73??   U5
	SSD2828_IC2_CS_0();	//IC2?????	 U6
	
	
	Write_SSPI_REG(0xB9, 0x0000);
	Write_SSPI_REG(0xB7, 0x0150);
	Write_SSPI_REG(0xB8, 0x0000);

	Write_SSPI_REG(0xBA, 0x8337);
	Write_SSPI_REG(0xBB, 0x0005);
	Write_SSPI_REG(0xBC, 0x0001);


	Write_SSPI_REG(0xC6, 0xCF86);
	Write_SSPI_REG(0xC9, 0x1307);
	Write_SSPI_REG(0xCA, 0x2204);
	Write_SSPI_REG(0xCB, 0x083D);
	Write_SSPI_REG(0xCC, 0x090C);
	Write_SSPI_REG(0xCD, 0x2CC4);

	Write_SSPI_REG(0xD5, 0x30C0);
	Write_SSPI_REG(0xDE, 0x0003);
	Write_SSPI_REG(0xB9, 0x0001);
	
	LCD_INIT();
	GP_SP(1);
	W_D(0x11);		   	  //????
	Delay_ms(120);	
	GP_SP(1);
	W_D(0x29);		     //display ON 		   
	Delay_ms(50); 			//lcd driver ic   lcm_9881c
	
	W_REG(0x00d6,0x00,0x05);
	Write_SSPI_REG(0xB7, 0x0159);
	W_REG(0x00b1,Lcd_VSPW, Lcd_HSPW);
	W_REG(0x00b2, Lcd_VBPD, Lcd_HBPD);
	W_REG(0x00b3,Lcd_VFPD, Lcd_HFPD);
	W_REG(0xb4,(Lcd_LCDH >> 8) & 0xff, Lcd_LCDH & 0xff);	
	W_REG(0xb5,(Lcd_LCDV >> 8) & 0xff, Lcd_LCDV & 0xff);
	
	Write_SSPI_REG(0xB6, 0x00D3);			//non burst sync event, 24bpp

	SSD2828_IC1_CS_1();	//IC1?????
	SSD2828_IC2_CS_1();	//IC2?C73??	
}

void InitMipi_PanelInitTTTT(void)
{ 
	SSD2828Init();
	SSD2828LP();

	SSD2828_IC1_CS_0();	
	SSD2828_IC2_CS_0();		
		
  GP_SP(1);
	W_D(0x11);		   	  //????
	Delay_ms(120);	
	
	GP_SP(1);
	W_D(0x29);		     //display ON 		   
	Delay_ms(50); 
	//LCD_INIT();
  SSD2828Video();	 
	SSD2828_IC1_CS_1();	//IC1?????
	SSD2828_IC2_CS_1();	//IC2?C73??	
}

/*******************************************************************************
*??? : OutPutSdCardFile
*??   : ?SD?????????lcd??
*??   : file_name - ???????
*??   : ?
********************************************************************************/
void OutPutSdCardFileRollingover(char* file_name)
{ 
	FATFS fs;  
	FIL fsrc;      // file objects
	UINT br;         // File R/W count
	unsigned int  a,R,G,B;
	FRESULT res;
	unsigned int Data_Offset;
	unsigned int porter;
//	unsigned char *lp;
	int ll;
//	unsigned int i;
	BITMAPINFO *bmphead;
 	disk_initialize(0);
    
	f_mount(0, &fs);  // ???0??fs

	res = f_open(&fsrc, file_name, FA_OPEN_EXISTING | FA_READ);	//??????
	if(res != 0)	printf("f_open wanning or error!\r\n");
	br=1;

  res = f_read(&fsrc, buffer, 0x36, &br); //???????
	bmphead = (BITMAPINFO *)buffer;
	printf(" %s ",file_name);//bmphead->bmiHeader.biSize
	printf("Type:%X  Size:%d \r\n",bmphead->bmfHeader.bfType,bmphead->bmfHeader.bfSize);
	printf("biWidth:%d biHeight:%d  biBitCount:%d \r\n",bmphead->bmiHeader.biWidth,bmphead->bmiHeader.biHeight,bmphead->bmiHeader.biBitCount);
	printf("OffBits:%d biYPelsPerMeter:%X biXPelsPerMeter:%X \r\n",bmphead->bmfHeader.bfOffBits,bmphead->bmiHeader.biYPelsPerMeter,bmphead->bmiHeader.biXPelsPerMeter);
	printf("biSize:%d  biClrUsed:%X ",bmphead->bmiHeader.biSize,bmphead->bmiHeader.biClrUsed);
	printf("biClrImportant:%X biCompression:%X \r\n\r\n",bmphead->bmiHeader.biClrImportant,bmphead->bmiHeader.biCompression);
  Data_Offset = bmphead->bmfHeader.bfOffBits;//+ buffer[11]<<8+ buffer[12]<<16+ buffer[13]<<24;
	
	if(bmphead->bmfHeader.bfType != 0x4D42) return ;//??? MB
	if(Data_Offset !=54 ) return ;

	if((fsrc.fsize-54)%3 ==0)	porter = fsrc.fsize;//?????3???
	else porter = fsrc.fsize-((fsrc.fsize-54)%3);
	for (;;) 
	{
		if((porter)>=10800)	{
			porter = porter - 10800;
			res = f_lseek(&fsrc, porter);
			res = f_read(&fsrc, buffer, 10800, &br);
			ll = 10800;
		}
		else {
			ll = porter-Data_Offset;
			if(ll<=0) return ;
			res = f_lseek(&fsrc, Data_Offset);
			res = f_read(&fsrc, buffer, porter-Data_Offset, &br);
			porter = 0;
		}
		 for(;;)
			{
				if(ll>(Lcd_LCDH*3)){		//size
					ll -= (Lcd_LCDH*3);	
					for(a = 0; a <(Lcd_LCDH*3); )
					{
						B=(uint8_t)( buffer[ll+a]);a++;		  	//BRG?RGB			
						G=(uint8_t)( buffer[ll+a]);a++;	
						R=(uint8_t)( buffer[ll+a]);a++;	
					
						LcdDrvWriteData(R);	LcdDrvWriteData(G);LcdDrvWriteData(B);
					}	
				}else if((ll<=(Lcd_LCDH*3))&&(ll>0)){
					for(a = 0; a <ll; )
					{
						B=(uint8_t)( buffer[a]);a++;		  	//BRG?RGB			
						G=(uint8_t)( buffer[a]);a++;	
						R=(uint8_t)( buffer[a]);a++;	
						LcdDrvWriteData(R);	LcdDrvWriteData(G);LcdDrvWriteData(B);
					}	
					break;
				}else if(ll<=0){printf("lll:%d",ll);break;}
			}
			if (porter == 0) break;   
	}
	f_close(&fsrc);   		    	
}

void OutPutSdCardFileOverturn(char* file_name)
{ 
	FATFS fs;  
	FIL fsrc;      // file objects
	UINT br;         // File R/W count
	unsigned int  a,R,G,B;
	FRESULT res;
	unsigned int Data_Offset;
	unsigned int porter;
//	unsigned char *lp;
	int ll;
//	unsigned int i;
	BITMAPINFO *bmphead;
 	disk_initialize(0);
    
	f_mount(0, &fs);  // ???0??fs

	res = f_open(&fsrc, file_name, FA_OPEN_EXISTING | FA_READ);	//??????
	if(res != 0)	printf("f_open wanning or error!\r\n");
	br=1;

  res = f_read(&fsrc, buffer, 0x36, &br); //???????
	bmphead = (BITMAPINFO *)buffer;
	printf(" %s ",file_name);//bmphead->bmiHeader.biSize
	printf("Type:%X  Size:%d \r\n",bmphead->bmfHeader.bfType,bmphead->bmfHeader.bfSize);
	printf("biWidth:%d biHeight:%d  biBitCount:%d \r\n",bmphead->bmiHeader.biWidth,bmphead->bmiHeader.biHeight,bmphead->bmiHeader.biBitCount);
	printf("OffBits:%d biYPelsPerMeter:%X biXPelsPerMeter:%X \r\n",bmphead->bmfHeader.bfOffBits,bmphead->bmiHeader.biYPelsPerMeter,bmphead->bmiHeader.biXPelsPerMeter);
	printf("biSize:%d  biClrUsed:%X ",bmphead->bmiHeader.biSize,bmphead->bmiHeader.biClrUsed);
	printf("biClrImportant:%X biCompression:%X \r\n\r\n",bmphead->bmiHeader.biClrImportant,bmphead->bmiHeader.biCompression);
  Data_Offset = bmphead->bmfHeader.bfOffBits;//+ buffer[11]<<8+ buffer[12]<<16+ buffer[13]<<24;
	
	if(bmphead->bmfHeader.bfType != 0x4D42) return ;//??? MB
	if(Data_Offset != 54 ) return ;

	if((fsrc.fsize-54)%3 ==0)	porter = fsrc.fsize;//?????3???
	else porter = fsrc.fsize-((fsrc.fsize-54)%3);
	for (;;) 
	{
		if((porter)>=10800)	{
			porter = porter - 10800;
			res = f_lseek(&fsrc, porter);
			res = f_read(&fsrc, buffer, 10800, &br);
			ll = 10800;
		}
		else {
			ll = porter-Data_Offset;
			if(ll<=0) return ;
			res = f_lseek(&fsrc, Data_Offset);
			res = f_read(&fsrc, buffer, porter-Data_Offset, &br);
			porter = 0;
		}
			
		for(a = 10799;; )
			{
				R=(uint8_t)( buffer[a--]);if(a==0) break;	  	//BRG?RGB			
				G=(uint8_t)( buffer[a--]);if(a==0) break;
				B=(uint8_t)( buffer[a--]);if(a==0) break;
				LcdDrvWriteData(R);	LcdDrvWriteData(G);LcdDrvWriteData(B);
			}	
			R=(uint8_t)( buffer[2]);	  	//BRG?RGB		
			G=(uint8_t)( buffer[1]);	
			B=(uint8_t)( buffer[0]);	
			LcdDrvWriteData(R);	LcdDrvWriteData(G);LcdDrvWriteData(B);
			if (porter == 0) break;   // error or eof
	}
	f_close(&fsrc);   		    	
}


void OutPutSdCardFile(char* file_name)
{ 
	FATFS fs;  
	FIL fsrc;      // file objects
	UINT br;         // File R/W count
	unsigned int  a,R,G,B;
	FRESULT res;
	unsigned int Data_Offset;
	BITMAPINFO *bmphead;
	
 	disk_initialize(0);
    
	res = f_mount(0, &fs);  // ???0??fs
	printf("\r\n f_mount res:%d",res);
	res = f_open(&fsrc, file_name, FA_OPEN_EXISTING | FA_READ);	//??????
	printf("\r\n f_open res:%d",res);
	br=1;

  	res = f_read(&fsrc, buffer, 0x36, &br); //???????
	printf("\r\n f_read res:%d",res);
  	bmphead = (BITMAPINFO *)buffer;
	printf("\r\nfile_name:%s ",file_name);//bmphead->bmiHeader.biSize
	printf("Type:%X  Size:%d \r\n",bmphead->bmfHeader.bfType,bmphead->bmfHeader.bfSize);
	printf("biWidth:%d biHeight:%d  biBitCount:%d \r\n",bmphead->bmiHeader.biWidth,bmphead->bmiHeader.biHeight,bmphead->bmiHeader.biBitCount);
	printf("OffBits:%d biYPelsPerMeter:%X biXPelsPerMeter:%X \r\n",bmphead->bmfHeader.bfOffBits,bmphead->bmiHeader.biYPelsPerMeter,bmphead->bmiHeader.biXPelsPerMeter);
	printf("biSize:%d  biClrUsed:%X ",bmphead->bmiHeader.biSize,bmphead->bmiHeader.biClrUsed);
	printf("biClrImportant:%X biCompression:%X \r\n\r\n",bmphead->bmiHeader.biClrImportant,bmphead->bmiHeader.biCompression);
  Data_Offset = bmphead->bmfHeader.bfOffBits;//+ buffer[11]<<8+ buffer[12]<<16+ buffer[13]<<24;
	res = f_lseek(&fsrc, Data_Offset);//??????????????
	for (;;) 
	{
		res = f_read(&fsrc, buffer, 10239, &br);
    	for(a = 0; a <10239; )
		{
			B=(uint8_t)( buffer[a]);a++;	  	//BRG?RGB		
			G=(uint8_t)( buffer[a]);a++;	
			R=(uint8_t)( buffer[a]);a++;	
			LcdDrvWriteData(R);	LcdDrvWriteData(G);LcdDrvWriteData(B);
		}		 
		if (res || br == 0) break;   // error or eof
	}
	f_close(&fsrc);   		    	
}

void usb_hid_mass_init(void)
{
	//Delay_ms(200);		//?????????
	//usb_port_set(0);
	//Delay_ms(500);
	usb_port_set(1);
	
	/*配置USB中断(包括SDIO中断)*/
	USB_Interrupts_Config();
	/*设置USB时钟为48M*/
	Set_USBClock();
	/*USB初始化*/
 	USB_Init();
	Delay_ms(200);	
}

void SDcard_init(void)
{
	SStatus = MISD_Init();																				      
	if (SStatus == MISD_OK)//----------------- Read CSD/CID MSD registers ------------------
		SStatus = MISD_GetCardInfo(&SSDCardInfo);
	
	if (SStatus == MISD_OK)//----------------- Select Card --------------------------------
		SStatus = MISD_SelectDeselect((u32) (SSDCardInfo.RCA << 16));
	
	if (SStatus == MISD_OK)
		//SStatus = MISD_EnableWideBusOperation(SDIO_BusWide_4b);
					   
	if (SStatus == MISD_OK)	
		SStatus = MISD_SetDeviceMode(MISD_INTERRUPT_MODE);
	MISD_ReadBlock(0, (u32 *)buffer1,1);	
}


