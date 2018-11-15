

#include "ssd2828.h"

void Delay10us(u16 time)
{
	Delay_10us(time);
	/*u16 i;
	while(time--){
		i=50;
		while(i--);
	}*/
}
void Delayms(u16 time)
{
	Delay_ms(time);
	/*
	u16 i=1200;
	while(time--)
		while(i--);*/
}

#define SPI_SDI_1     GPIO_SetBits(GPIOE, GPIO_Pin_2)
#define SPI_SDI_0     GPIO_ResetBits(GPIOE, GPIO_Pin_2) 
#define SPI_SCLK_1    GPIO_SetBits(GPIOE, GPIO_Pin_3)
#define SPI_SCLK_0    GPIO_ResetBits(GPIOE, GPIO_Pin_3)
#define SPI_SDO		  GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_1)  //??	 
#define SSD_RESET_1   GPIO_SetBits(GPIOE, GPIO_Pin_0);
#define SSD_RESET_0   GPIO_ResetBits(GPIOE, GPIO_Pin_0)	  //RESET PE0	 
#define SSD_SHUT_1    GPIO_SetBits(GPIOE, GPIO_Pin_5)
#define SSD_SHUT_0    GPIO_ResetBits(GPIOE, GPIO_Pin_5)   //SHUT  PE5

/*---------------------------LP or HS or Video------------------------------*/
#define LP 0
#define HS 1
#define VD 2
unsigned int mode = HS; 

unsigned char VCOM[3];
/*----------------------------------------------------------------------------*/

void SSD2828GPIOConfig(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE|RCC_APB2Periph_GPIOB, ENABLE );


	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_2|GPIO_Pin_3|	 //SDI,CS,RESET,SCLK
	                              GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6;	  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOE, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
  
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;                              //SDO
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOE, &GPIO_InitStructure);

//	SPIB_CS_1;
}

void W_C(unsigned char cmd)
{   
	unsigned char i;

//	SPI_CS_0;
	SPI_SDI_0; Delay10us(2);  				 
	SPI_SCLK_0;Delay10us(2);
    SPI_SCLK_1;Delay10us(2);
    
     for (i=0;i<8;i++)
     {
		if((cmd&0x80)==0x80)SPI_SDI_1;
		else  SPI_SDI_0;
		
		Delay10us(2);
		SPI_SCLK_0;
		Delay10us(2);
		SPI_SCLK_1;
		Delay10us(2);
		
		cmd=cmd<<1;
     }
 //    SPI_CS_1;   
	 Delay10us(0);
}

void W_D(unsigned char dat)
{   
	unsigned char i;
 //   SPI_CS_0;
    SPI_SDI_1;
	Delay10us(2);
     
	SPI_SCLK_0;
	Delay10us(2);
    SPI_SCLK_1;
	Delay10us(2);

	for(i=0;i<8;i++)
	{
		if((dat&0x80)==0x80)
		 	SPI_SDI_1;
		else
		 	SPI_SDI_0;
		
		Delay10us(2);	
		SPI_SCLK_0;
		Delay10us(2);
		SPI_SCLK_1;
		Delay10us(2);
		dat=dat<<1;
	}
 //   SPI_CS_1;	 
	Delay10us(2);   
}

//?2828??? ???8bit??
void W_REG(unsigned char cmd,unsigned char dat1,unsigned char dat2)
{   
	unsigned char i;
//	SPI_CS_0;
	SPI_SDI_0;
	
	SPI_SCLK_0;SPI_SCLK_0;SPI_SCLK_0;
	SPI_SCLK_1;

	for(i=0;i<8;i++)
	{
		if((cmd&0x80)==0x80){SPI_SDI_1;	}
		else { SPI_SDI_0;}
		SPI_SCLK_0;	SPI_SCLK_0;SPI_SCLK_0;
		SPI_SCLK_1;
		cmd=cmd<<1;
	}
                 
    SPI_SDI_1;
	SPI_SCLK_0;SPI_SCLK_0;SPI_SCLK_0;
    SPI_SCLK_1;
	for (i=0;i<8;i++)
	{
		if((dat2&0x80)==0x80)	{SPI_SDI_1;}
		else	{ SPI_SDI_0; }
		
		SPI_SCLK_0;SPI_SCLK_0;SPI_SCLK_0;
		SPI_SCLK_1;
		
		dat2=dat2<<1;
	}


	SPI_SDI_1;
	SPI_SCLK_0;SPI_SCLK_0;SPI_SCLK_0;
	SPI_SCLK_1;

	for (i=0;i<8;i++)
	{
		if((dat1&0x80)==0x80)	{SPI_SDI_1;}
		else	{ SPI_SDI_0;}
		
		SPI_SCLK_0;SPI_SCLK_0;SPI_SCLK_0;
		SPI_SCLK_1;
		dat1=dat1<<1;
	}
//	SPI_CS_1;  
}
void Write_SSPI_REG(unsigned char cmd,unsigned short dat)
{
	W_REG(cmd,dat>>8,dat);
}
//----------------------------------------------------------------------------------

//DCS ??? ? 
//DT = 0x05, 0x15
//n - ????; 
void DCS_SP(unsigned char n)
{
	if(mode == LP)
	{	
		W_REG(0x00b7,0x02,0x50);	  //EOT Packet Enable,ECC CRC Check Enable, DCS, Short packer, LP
	}
	else if(mode == HS)
	{
		W_REG(0x00b7, 0x02, 0x50&0XEF|0X03); //EOT Packet Enable,ECC CRC Check Enable, DCS, Short packer, HS
	} 
	else if(mode == VD)
	{
		W_REG(0x00b7, 0x02|0x01, 0x50&0XEF|0X0B); //EOT Packet Enable,ECC CRC Check Disable, DCS, Short packer, HS Video
	}
	Delay10us(10);
	W_REG(0xbc,0x00,n);
	W_REG(0xbd,0x00,0x00);
	W_REG(0xbe,0x00,n);
    W_C(0xbf);
}


void DCS_LP(unsigned long n)
{
	if(mode == LP)
	{
		W_REG(0x00b7,0x06,0x50);  //EOT Packet Enable,ECC CRC Check Enable, DCS Long Write, LP
	}
	else if(mode == HS)
	{
		W_REG(0x00b7,0x06, 0x50&0XEF|0X03);  //EOT Packet Enable,ECC CRC Check Enable, DCS Long Write, HS
	}
	else if(mode == VD)
	{
		W_REG(0x00b7, 0x06|0x01, 0x50&0XEF|0X0B);  //EOT Packet Enable,ECC CRC Check Disable, DCS Long Write, HS Video
	}

	Delay10us(10);
	W_REG(0xbc,n>>8,n);
	W_REG(0xbd,n>>24,n>>16);
	W_REG(0xbe,0x0f,0xff);
    W_C(0xbf);
}


void GP_SP(unsigned char n)
{
  	

	if(mode == LP)
	{
		W_REG(0x00b7,0x02,0x10); //EOT Packet Enable,ECC CRC Check Enable, Generic Short Write, LP
	}
	else if(mode == HS)
	{
		W_REG(0x00b7,0x02,0x10&0XEF|0X03);  //EOT Packet Enable,ECC CRC Check Enable, Generic Short Write, HS
	}
	else if(mode == VD)
	{
		W_REG(0x00b7,0x02|0x01,0x10&0XEF|0X0B);  //EOT Packet Enable,ECC CRC Check Disable, Generic Short Write, HS Video
	}

	Delay10us(10);
	W_REG(0xbc,0x00,n);
	W_REG(0xbd,0x00,0x00);
	W_REG(0xbe,0x00,n);
    W_C(0xbf);
}


void GP_LP(unsigned long n)
{
  	if(mode == LP)
	{	
		W_REG(0x00b7,0x06,0x10); //EOT Packet Enable,ECC CRC Check Enable, Generic Long Write, LP; 
	}
	else if(mode == HS)
	{
		W_REG(0x00b7,0x06,0x10&0XEF|0X03); //EOT Packet Enable,ECC CRC Check Enable, Generic Long Write, HS;
	}
	else if(mode == VD)
	{
		W_REG(0x00b7,0x06|0X01,0x10&0XEF|0X0B);//EOT Packet Enable,ECC CRC Check Disable, Generic Long Write, HS Video
	}
	
	Delay10us(10);
	W_REG(0xbc,n>>8,n);
	W_REG(0xbd,n>>24,n>>16);
	W_REG(0xbe,0x0f,0xff);
  W_C(0xbf);
}


uint8_t SSD2828Read()
{
	unsigned int i;
	uint8_t tmp = 0;
//	SPI_CS_0;
    Delay10us(1);
    for(i = 0; i < 8; i++)
	{
		SPI_SCLK_0;
		Delay10us(1);
    	SPI_SCLK_1;
		Delay10us(1);
        tmp <<= 1;
		if(SPI_SDO) tmp |= 0x01;
	}
	


	return tmp;
}


uint16_t SSD2828ReadReg(uint8_t reg)
{
    uint16_t tmp;
	uint8_t data_l, data_h;
	W_REG(0xd4,0x00,0xfa); //Set read command "FA" for 3 wire 8bit
	W_C(reg);	//????????
    W_C(0xfa);	//???

	data_l = SSD2828Read();
	data_h = SSD2828Read();

	tmp = data_h;
	tmp <<= 8;
	tmp |= data_l;
	
	return tmp;	
}			   

unsigned int DCS_R(uint8_t adr, uint16_t l, uint8_t *p)
{
	uint16_t state;
	unsigned int i;
	unsigned int timeout_cnt=0;

	do
	{
		if(mode == LP)
		{
			W_REG(0x00b7,0x03,0xc2);		//LP DCS read
		}
		else if(mode == HS)
		{
			W_REG(0x00b7,0x03,0xc2&(0XEF|0X03));
		}
		else if(mode == VD)
		{
			W_REG(0x00b7,0x03,0xc2&(0XEF|0X0B));
		}
	  W_REG(0x00b7,0x03,0xc2&(0XEF|0X0B));
		W_REG(0x00bb,0x00,8);			//PL clock
		W_REG(0x00c1,l>>8,l);		//Maximum Return Size
		W_REG(0x00c0,0x00,0x01);		//??SSD2828?????
		W_REG(0x00BC,0x00,0x01);
		W_REG(0x00BF,0x00,adr);	   //??????????
		Delay10us(800);					   //????????
		state = SSD2828ReadReg(0xc6);		//? ssd2828 ??????
		
		if(state & 0x01){break;}     //??? ????
		else if(++timeout_cnt > 10){return MIPI_READ_FAIL;}		//?? ???
	}while(1);	

	W_C(0xff);			   //?2828?0XFF???,?????????,?????LCM????????0XFF
	for(i = 0; i < l;)
	{
		W_C(0xfa);			   //???
		VCOM[i]=*p++ = SSD2828Read();
		if(++i >= l){SSD2828Read(); break;}
		VCOM[i]=*p++ = SSD2828Read();
		++i;
	}
	return MIPI_READ_SUCCEED;
}
  

unsigned int GP_R(uint8_t adr, uint16_t l, uint8_t *p)
{
	uint16_t state;
	unsigned int i;
	unsigned int timeout_cnt=0;

	do
	{
		if(mode == LP)
		{
			W_REG(0x00b7,0x03,0x82);		//LP generic read
		}
		else if(mode == HS)
		{
			W_REG(0x00b7,0x03,0x82&0XEF|0X03);
		}
		else if(mode == VD)
		{
			W_REG(0x00b7,0x03,0x82&0XEF|0X0B);
		}

		W_REG(0x00bb,0x00,8);			//PL clock
		W_REG(0x00c1,l>>8,l);		//Maximum Return Size
		W_REG(0x00c0,0x00,0x01);		//??SSD2828?????
		W_REG(0x00BC,0x00,1);		 // *???? 
		W_REG(0x00BF,0x00,adr);	   //??????????
		Delayms(10);					   //????????
		state = SSD2828ReadReg(0xc6);		//? ssd2828 ??????

		if(state & 0x01){break;}     //??? ????
		else if(++timeout_cnt > 10){return MIPI_READ_FAIL;}		//?? ???
	}while(1);	//ssd2828????? ?????

	W_C(0xff);			   //?2828?0XFF???,?????????,?????LCM????????0XFF
	for(i = 0; i < l;)
	{
		W_C(0xfa);			   //???
		*p++ = SSD2828Read();
		if(++i >= l){SSD2828Read(); break;}
		*p++ = SSD2828Read();
		++i;
	}

	return MIPI_READ_SUCCEED;
}



void SSD2828LP()
{
	mode = LP;
}

void SSD2828Video()
{
	mode = VD;	   
	W_REG(0x00b7,0x01,0x59);//?? video,24b,Short  TCLK?????	
	W_REG(0x00b9,0x00,0x00); //?pLL

	W_REG(0x00b1,Lcd_VSPW, Lcd_HSPW);
	W_REG(0x00b2, Lcd_VBPD, Lcd_HBPD);
	W_REG(0x00b3,Lcd_VFPD, Lcd_HFPD);




	W_REG(0xb4,(Lcd_LCDH >> 8) & 0xff, Lcd_LCDH & 0xff);	
	W_REG(0xb5,(Lcd_LCDV >> 8) & 0xff, Lcd_LCDV & 0xff);
//	W_REG(0x00b6,0x00,0x0B);	//24bpp burst mode
	//W_REG(0x00b6,0x00, 0x07);	//24bpp Non burst mode with sync events	
    W_REG(0x00b6,0x00, 0xd3);	//24bpp Non burst mode PCLK???????	

//	W_REG(0xbb,0x00,6);			// LP Mode CLK =PLL /(LPD+1)/8 = x MHz
//	W_REG(0x00b9,0x00,0x00); //?pLL
	W_REG(0x00c9,0x13,0x07);
	W_REG(0x00ca,0x22,0x04);
	W_REG(0x00cb,0x08,0x3d);
	W_REG(0x00cc,0x09,0x0c);
	W_REG(0x00cd,0x2c,0xc4);

	W_REG(0x00de,0x00,0x02);//4 lane mode
//	W_REG(0x00de,0x00,0x01);//2 lane mode
//	W_REG(0x00d6,0x00,0x04); ////??RGB???? ???????????????????
	W_REG(0x00d5,0x30,0xc0);
	W_REG(0x00d6,0x00,0x05);//??RGB???? ???????????????????
	W_REG(0x00c4,0x00,0x01); //Automatically perform BTA after the next write packe
	//W_REG(0x00e9,0xff2f); //
	W_REG(0x00eb,0x80,0x00);

	Delayms(5);

	//W_REG(0x00ba,0x80, 37);  // PLL= fIN X NS = xMHz	   251 ~ 500
	W_REG(0x00ba,0xc0, 38);//34  // PLL= fIN X NS = xMHz	   501 ~ 1000
//	W_REG(0x00ba,0xc2, 65);  // PLL= fIN/2 X NS = xMHz	   501 ~ 1000
	W_REG(0x00bb,0x00,0x05);//Clock Control Register 0/1 ;LP Clock Divider
	W_REG(0x00b8,0x00,0x00); //
	//W_REG(0x00b7,0x03,0x0B);//  TCLK?????
	W_REG(0x00b7,0x03,0x0B);//  //?? video,24b, Short Packet, PCLK?????

	W_REG(0x00b9,0x00,0x01); //?PLL
	Delayms(50);
}

void SSD2828_STOP(void)
{

	SSD2828GPIOConfig();
	SSD_SHUT_0;
    SSD_RESET_0;
	SSD2828_IC1_CS_0();
	SSD2828_IC2_CS_0(); 
   	SPI_SDI_0;
	SPI_SCLK_0;	 
 }


 void SSD2828_STOP_1(void)
{

	SSD2828GPIOConfig();
	SSD_SHUT_1;
    SSD_RESET_1;
	SSD2828_IC1_CS_1();
	SSD2828_IC2_CS_1(); 
   	SPI_SDI_1;
	SPI_SCLK_1;	 
}

void SSD2828Init(void)
{
	SSD2828GPIOConfig();
	
	SSD_SHUT_1;
    SSD_RESET_1;
	SSD2828_IC1_CS_1();
	SSD2828_IC2_CS_1(); 
   	SPI_SDI_1;
	SPI_SCLK_1;	

	SSD_SHUT_0;

    SSD_RESET_1;	//LCM SSD2828 RESET PIN
	Delayms(50);
    SSD_RESET_0;
	Delayms(50);
	SSD_RESET_1;
	Delayms(50);

}

void SSD2828_RST_H(void)
{
	SSD_RESET_1;
}

void SSD2828_RST_L(void)
{
	SSD_RESET_0;
}

//??2828 IC1
void SSD2828_IC1_CS_0(void)
{
	GPIO_ResetBits(GPIOE, GPIO_Pin_6);
}	  

void SSD2828_IC1_CS_1(void)
{
	GPIO_SetBits(GPIOE, GPIO_Pin_6);
}

void SSD2828_IC2_CS_0(void) 
{
	GPIO_ResetBits(GPIOB, GPIO_Pin_5);
}

void SSD2828_IC2_CS_1(void) 
{
	GPIO_SetBits(GPIOB, GPIO_Pin_5);
}


void WR_DT29(unsigned long n) {GP_LP(n);}
void WR_DT03_13_23(unsigned char n) {GP_SP(n);}   
void WR_DT39(unsigned long n) {DCS_LP(n);}
void WR_DT05_15(unsigned char n) {DCS_SP(n);}
unsigned int RD_DT06(uint8_t adr, uint16_t l, uint8_t *p) {return DCS_R(adr, l, p);}
unsigned int RD_DT14(uint8_t adr, uint16_t l, uint8_t *p) {return GP_R(adr, l, p);}

//SSD2828ReadReg(uint8_t reg)
u16 ssd_rdata(u8 reg)
{
	return SSD2828ReadReg(reg);
}

void ssd_wdata(u8 reg,u16 parmer)
{
	Write_SSPI_REG(reg,parmer);
}

void Generic_Short_Write_NP(u8 Generic)	
{
	GP_SP(1);
	W_D(Generic);
}
void Generic_Short_Write_1P(u8 Generic,u8 Parma)	
{
	GP_LP(2);
	W_D(Generic);
	W_D(Parma);
}
void Generic_Long_Write_2P(u8 Generic,u8 Parma1,u8 Parma2)
{
	GP_LP(3);
	W_D(Generic);
	W_D(Parma1);
	W_D(Parma2);
}

void Generic_Long_Write_3P(u8 Generic,u8 Parma1,u8 Parma2,u8 Parma3)
{
	GP_LP(4);
	W_D(Generic);
	W_D(Parma1);
	W_D(Parma2);
	W_D(Parma3);
}
void Generic_Long_Write_4P(u8 Generic,u8 Parma1,u8 Parma2,u8 Parma3,u8 Parma4)
{
	GP_LP(5);
	W_D(Generic);
	W_D(Parma1);
	W_D(Parma2);
	W_D(Parma3);
	W_D(Parma4);
}
void Generic_Long_Write_5P(u8 Generic,u8 Parma1,u8 Parma2,u8 Parma3,u8 Parma4,u8 Parma5)
{
	GP_LP(6);
	W_D(Generic);
	W_D(Parma1);
	W_D(Parma2);
	W_D(Parma3);
	W_D(Parma4);
	W_D(Parma5);
}
void Generic_Long_Write_6P(u8 Generic,u8 Parma1,u8 Parma2,u8 Parma3,u8 Parma4,u8 Parma5,u8 Parma6)
{
	GP_LP(7);
	W_D(Generic);
	W_D(Parma1);
	W_D(Parma2);
	W_D(Parma3);
	W_D(Parma4);
	W_D(Parma5);
	W_D(Parma6);
}
void Generic_Long_Write_7P(u8 Generic,u8 Parma1,u8 Parma2,u8 Parma3,u8 Parma4,u8 Parma5,u8 Parma6,u8 Parma7)
{
	GP_LP(8);
	W_D(Generic);
	W_D(Parma1);
	W_D(Parma2);
	W_D(Parma3);
	W_D(Parma4);
	W_D(Parma5);
	W_D(Parma6);
	W_D(Parma7);
}

void Generic_Long_Write_FIFO(u16 num,u8 *Parma)
{
	u16 i;
	GP_LP(num);
	for(i=0;i<num;i++){
		W_D(Parma[i]);
	}
}

void DCS_Short_Write_NP(u8 Generic)	
{
	DCS_SP(1);
	W_D(Generic);
}
void DCS_Short_Write_1P(u8 Generic,u8 Parma)	
{
	DCS_LP(2);
	W_D(Generic);
	W_D(Parma);
}
void DCS_Long_Write_2P(u8 Generic,u8 Parma1,u8 Parma2)
{
	DCS_LP(3);
	W_D(Generic);
	W_D(Parma1);
	W_D(Parma2);
}

void DCS_Long_Write_3P(u8 Generic,u8 Parma1,u8 Parma2,u8 Parma3)
{
	DCS_LP(4);
	W_D(Generic);
	W_D(Parma1);
	W_D(Parma2);
	W_D(Parma3);
}
void DCS_Long_Write_4P(u8 Generic,u8 Parma1,u8 Parma2,u8 Parma3,u8 Parma4)
{
	DCS_LP(5);
	W_D(Generic);
	W_D(Parma1);
	W_D(Parma2);
	W_D(Parma3);
	W_D(Parma4);
}
void DCS_Long_Write_5P(u8 Generic,u8 Parma1,u8 Parma2,u8 Parma3,u8 Parma4,u8 Parma5)
{
	DCS_LP(6);
	W_D(Generic);
	W_D(Parma1);
	W_D(Parma2);
	W_D(Parma3);
	W_D(Parma4);
	W_D(Parma5);
}
void DCS_Long_Write_6P(u8 Generic,u8 Parma1,u8 Parma2,u8 Parma3,u8 Parma4,u8 Parma5,u8 Parma6)
{
	DCS_LP(7);
	W_D(Generic);
	W_D(Parma1);
	W_D(Parma2);
	W_D(Parma3);
	W_D(Parma4);
	W_D(Parma5);
	W_D(Parma6);
}
void DCS_Long_Write_7P(u8 Generic,u8 Parma1,u8 Parma2,u8 Parma3,u8 Parma4,u8 Parma5,u8 Parma6,u8 Parma7)
{
	DCS_LP(8);
	W_D(Generic);
	W_D(Parma1);
	W_D(Parma2);
	W_D(Parma3);
	W_D(Parma4);
	W_D(Parma5);
	W_D(Parma6);
	W_D(Parma7);
}
void DCS_Long_Write_FIFO(u16 num,u8 *Parma)
{
	u16 i;
	DCS_LP(num);
	for(i=0;i<num;i++){
		W_D(Parma[i]);
	}
}

u32 Generic_Short_Read_NP(u16 reg, u8 cnt, u8 *Parma)
{
	return GP_R(reg,cnt,Parma);
}
u32 DCS_Short_Read_NP(u16 reg, u8 cnt, u8 *Parma)
{
	return DCS_R(reg,cnt,Parma);
}








