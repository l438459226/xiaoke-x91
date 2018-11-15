#include "LED_I2C.h"
#include "user_config.h"
#include "tools.h"
#include "user_gpio_def.h"
#include <stdio.h>

/*
函数：I2C_Delay()
功能：延时，模拟I2C总线专用
*/
void LED_I2C_Delay()
{
	delayus(5);
}


/*
函数：I2C_Init()
功能：I2C总线初始化，使总线处于空闲状态
说明：在main()函数的开始处，通常应当要执行一次本函数
*/
void LED_I2C_Init(void)
{
	
	LED_I2C_SDA(1);
	LED_I2C_SCL(1);
}


/*
函数：I2C_Start()
功能：产生I2C总线的起始状态
说明：
    SCL处于高电平期间，当SDA出现下降沿时启动I2C总线
    不论SDA和SCL处于什么电平状态，本函数总能正确产生起始状态
    本函数也可以用来产生重复起始状态
    本函数执行后，I2C总线处于忙状态
*/
void LED_I2C_Start(void)
{
	LED_I2C_SDA(1);
	LED_I2C_Delay();
	LED_I2C_SCL(1);
	LED_I2C_Delay();
	LED_I2C_SDA(0);
	LED_I2C_Delay();
	LED_I2C_SCL(0);
	LED_I2C_Delay();
}


/*
函数：I2C_Write()
功能：向I2C总线写1个字节的数据
参数：
    dat：要写到总线上的数据
*/
void LED_I2C_Write(unsigned char dat)
{
    unsigned char t = 8;
  
	do
	{
		LED_I2C_SDA((dat & 0x80));
		dat <<= 1;
		LED_I2C_Delay();
		LED_I2C_SCL(1);
		LED_I2C_Delay();
		LED_I2C_SCL(0);
	} while ( --t != 0 );
	
}


/*
函数：I2C_Read()
功能：从从机读取1个字节的数据
返回：读取的一个字节数据
*/
unsigned char LED_I2C_Read(void)
{
    unsigned char dat;
    unsigned char t = 8;

	
	LED_I2C_SDA(1);    //在读取数据之前，要把SDA拉高
	do
	{
		LED_I2C_SCL(1);
		LED_I2C_Delay();
		dat <<= 1;
		if ( LED_I2C_SDA(1) ) dat |= 0x01;
		LED_I2C_SCL(0);
		LED_I2C_Delay();
	} while ( --t != 0 );

		
    return dat;
}


/*
函数：I2C_GetAck()
功能：读取从机应答位
返回：
    0：从机应答
    1：从机非应答
说明：
    从机在收到每个字节的数据后，要产生应答位
    从机在收到最后1个字节的数据后，一般要产生非应答位
*/
unsigned char LED_I2C_GetAck(void)
{
    unsigned char ack;
	
	delayus(300); //------------------

	LED_I2C_Delay();
	LED_I2C_SDA(1);
	LED_I2C_Delay();
	LED_I2C_SCL(1);
	LED_I2C_Delay();LED_I2C_Delay();LED_I2C_Delay();
	ack = LED_I2C_SDA(1);
	LED_I2C_SCL(0);
	LED_I2C_Delay();
	
    return ack;
}


/*
函数：I2C_PutAck()
功能：主机产生应答位或非应答位
参数：
    ack=0：主机产生应答位
    ack=1：主机产生非应答位
说明：
    主机在接收完每一个字节的数据后，都应当产生应答位
    主机在接收完最后一个字节的数据后，应当产生非应答位
*/
void LED_I2C_PutAck(unsigned char ack)
{
	LED_I2C_SDA(ack);
	LED_I2C_Delay();
	LED_I2C_SCL(1);
	LED_I2C_Delay();
	LED_I2C_SCL(0);
	LED_I2C_Delay();
}


/*
函数：I2C_Stop()
功能：产生I2C总线的停止状态
说明：
    SCL处于高电平期间，当SDA出现上升沿时停止I2C总线
    不论SDA和SCL处于什么电平状态，本函数总能正确产生停止状态
    本函数执行后，I2C总线处于空闲状态
*/
void LED_I2C_Stop(void)
{
    unsigned int t = LED_I2C_STOP_WAIT_VALUE;
	
	LED_I2C_SDA(0);
	LED_I2C_Delay();
	LED_I2C_SCL(1);
	LED_I2C_Delay();
	LED_I2C_SDA(1);
	LED_I2C_Delay();
	while ( --t != 0 );     //在下一次产生Start之前，要加一定的延时
}




/*
函数：I2C_Puts()
功能：I2C总线综合发送函数，向从机发送多个字节的数据
参数：
    SlaveAddr：从机地址（7位纯地址，不含读写位）
    SubAddr：从机的子地址
    SubMod：子地址模式，0－无子地址，1－单字节子地址，2－双字节子地址
    *dat：要发送的数据
    Size：数据的字节数
返回：
    0：发送成功
    1：在发送过程中出现异常
说明：
    本函数能够很好地适应所有常见的I2C器件，不论其是否有子地址
    当从机没有子地址时，参数SubAddr任意，而SubMod应当为0
*/
unsigned char LED_I2C_Puts
(
    unsigned char SlaveAddr,
    unsigned int SubAddr,
    unsigned char SubMod,
    unsigned char *dat,
    unsigned int Size
)
{
//定义临时变量
    unsigned char i;
    char a[3];
//检查长度
    if ( Size == 0 ) return 0;
//准备从机地址
    a[0] = (SlaveAddr << 1);
//检查子地址模式
    if ( SubMod > 2 ) SubMod = 2;
//确定子地址
    switch ( SubMod )
    {
    case 0:
        break;
    case 1:
        a[1] = (char)(SubAddr);
        break;
    case 2:
        a[1] = (char)(SubAddr >> 8);
        a[2] = (char)(SubAddr);
        break;
    default:
        break;
    }
//发送从机地址，接着发送子地址（如果有子地址的话）
    SubMod++;
    LED_I2C_Start();
    for ( i=0; i<SubMod; i++ ) {
		LED_I2C_Write(a[i]);
        if ( LED_I2C_GetAck() ) {
            LED_I2C_Stop();
            return 1;
        }
    }
//发送数据
    do
    {
        LED_I2C_Write(*dat++);
        if ( LED_I2C_GetAck() ) break;
    } while ( --Size != 0 );
//发送完毕，停止I2C总线，并返回结果
    LED_I2C_Stop();
    if ( Size == 0 ) {
        return 0;
    }
    else {
        //return 1;
		return 2;
    }
}


/*
函数：I2C_Gets()
功能：I2C总线综合接收函数，从从机接收多个字节的数据
参数：
    SlaveAddr：从机地址（7位纯地址，不含读写位）
    SubAddr：从机的子地址
    SubMod：子地址模式，0－无子地址，1－单字节子地址，2－双字节子地址
    *dat：保存接收到的数据
    Size：数据的字节数
返回：
    0：接收成功
    1：在接收过程中出现异常
说明：
    本函数能够很好地适应所有常见的I2C器件，不论其是否有子地址
    当从机没有子地址时，参数SubAddr任意，而SubMod应当为0
*/
unsigned char LED_I2C_Gets
(
    unsigned char SlaveAddr,
    unsigned int SubAddr,
    unsigned char SubMod,
    unsigned char *dat,
    unsigned int Size
)
{
//定义临时变量
    unsigned char i;
    char a[3];
//检查长度
    if ( Size == 0 ) return 3;
//准备从机地址
    a[0] = (SlaveAddr << 1);
//检查子地址模式
    if ( SubMod > 2 ) SubMod = 2;
//如果是有子地址的从机，则要先发送从机地址和子地址
    if ( SubMod != 0 )
    {
    //确定子地址
        if ( SubMod == 1 )
        {
            a[1] = (char)(SubAddr);
        }
        else
        {
            a[1] = (char)(SubAddr >> 8);
            a[2] = (char)(SubAddr);
        }
    //发送从机地址，接着发送子地址
        SubMod++;
        LED_I2C_Start();
        for ( i=0; i<SubMod; i++ )
        {
            LED_I2C_Write(a[i]);
            if ( LED_I2C_GetAck() )
            {
                LED_I2C_Stop();
                return 4;
            }
        }
    }
//这里的I2C_Start()对于有子地址的从机是重复起始状态
//对于无子地址的从机则是正常的起始状态
    LED_I2C_Start();
//发送从机地址
    LED_I2C_Write(a[0]+1);
    if ( LED_I2C_GetAck() )
    {
        LED_I2C_Stop();
        return 5;
    }
//接收数据
    for (;;)
    {
        *dat++ = LED_I2C_Read();
        if ( --Size == 0 )
        {
            LED_I2C_PutAck(1);
            break;
        }
        LED_I2C_PutAck(0);
    }
//接收完毕，停止I2C总线，并返回结果
    LED_I2C_Stop();
    return 0;
}


#define BRIGHTNESS_8  0x00
#define BRIGHTNESS_1  0x10
#define BRIGHTNESS_2  0x20
#define BRIGHTNESS_3  0x30
#define BRIGHTNESS_4  0x40
#define BRIGHTNESS_5  0x50
#define BRIGHTNESS_6  0x60
#define BRIGHTNESS_7  0x70

#define SEGMENT_7     0x08
#define SEGMENT_8     0x00

//------ LED Control ---------------------------------------------------------------------------
void LED_Control_Init(void) {
	UINT8 Res;
	UINT8 tAddr, tData;
	
	//Command1, 数据命令:48H
	//Command2, 开显示, 显示亮度级
	tAddr = 0x48;
	tData = BRIGHTNESS_4 | SEGMENT_8 | 0x01; //开显示
	Res = LED_I2C_Puts (
		tAddr>>1,	//unsigned char SlaveAddr,
		0, 			//unsigned int SubAddr,
		0, 			//unsigned char SubMod,
		&tData, 	//unsigned char *dat,
		1 			//unsigned int Size
	);
	if(Res != 0)
		printf("\r\nRes:%02X\r\n", Res);
}

UINT8 LED_Convert[22] = { //0~9,  A,b,C,d,E,F,  灭, U,H,L,P,-,
	0x3F, //0
	0x06, //1
	0x5B, //2
	0x4F, //3
	0x66, //4
	0x6D, //5
	0x7D, //6
	0x07, //7
	0x7F, //8
	0x6F, //9
	0x77, //A
	0x7C, //b
	0x39, //C
	0x5E, //d
	0x79, //E
	0x71, //F
	0x00, //灭---
	0x3E, //U ---
	0x76, //H ---
	0x38, //L ---
	0x73, //P ---
	0x40, //- ---
};

void LED_BasicShow(UINT8 Num0, UINT8 Num1, UINT8 Num2, UINT8 Num3, UINT8 Dot) { //Dot, bit[3:0]对应LED0,LED1,LED2,LED3
	UINT8 Res;
	UINT8 tAddr, tData;
	UINT8 tDot;
	
	//显存地址
	//显示数据
	tDot = ((Dot & 0x08) == 0x08) ? 0x80 : 0x00;
	tAddr = 0x68;
	tData = Num0 | tDot;
	Res = LED_I2C_Puts (
		tAddr>>1,	//unsigned char SlaveAddr,
		0, 			//unsigned int SubAddr,
		0, 			//unsigned char SubMod,
		&tData, 	//unsigned char *dat,
		1 			//unsigned int Size
	);
	if(Res != 0)
		printf("\r\nRes:%02X\r\n", Res);
	
	//显存地址
	//显示数据
	tDot = ((Dot & 0x04) == 0x04) ? 0x80 : 0x00;
	tAddr = 0x6A;
	tData = Num1 | tDot;
	Res = LED_I2C_Puts (
		tAddr>>1,	//unsigned char SlaveAddr,
		0, 			//unsigned int SubAddr,
		0, 			//unsigned char SubMod,
		&tData, 	//unsigned char *dat,
		1 			//unsigned int Size
	);
	if(Res != 0)
		printf("\r\nRes:%02X\r\n", Res);
	
	//显存地址
	//显示数据
	tDot = ((Dot & 0x02) == 0x02) ? 0x80 : 0x00;
	tAddr = 0x6C;
	tData = Num2 | tDot;
	Res = LED_I2C_Puts (
		tAddr>>1,	//unsigned char SlaveAddr,
		0, 			//unsigned int SubAddr,
		0, 			//unsigned char SubMod,
		&tData, 	//unsigned char *dat,
		1 			//unsigned int Size
	);
	if(Res != 0)
		printf("\r\nRes:%02X\r\n", Res);
	
	//显存地址
	//显示数据
	tDot = ((Dot & 0x01) == 0x01) ? 0x80 : 0x00;
	tAddr = 0x6E;
	tData = Num3 | tDot;
	Res = LED_I2C_Puts (
		tAddr>>1,	//unsigned char SlaveAddr,
		0, 			//unsigned int SubAddr,
		0, 			//unsigned char SubMod,
		&tData, 	//unsigned char *dat,
		1 			//unsigned int Size
	);
	if(Res != 0)
		printf("\r\nRes:%02X\r\n", Res);
}

void LED_Display(char CNum0, char CNum1, char CNum2, char CNum3, UINT8 Dot) {
	UINT8 Num0, Num1, Num2, Num3;
	
	//0
	if((CNum0 >= 'A') && (CNum0 <= 'F')) {
		Num0 = CNum0 - 'A' + 10;
	}
	else if((CNum0 >= '0') && (CNum0 <= '9')) {
		Num0 = CNum0 - '0';
	}
	else if(CNum0 == 'U')
		Num0 = 17;
	else if(CNum0 == 'H')
		Num0 = 18;
	else if(CNum0 == 'L')
		Num0 = 19;
	else if(CNum0 == 'P')
		Num0 = 20;
	else if(CNum0 == '-')
		Num0 = 21;
	else
		Num0 = 16; //灭, 不显示
	
	//1
	if((CNum1 >= 'A') && (CNum1 <= 'F')) {
		Num1 = CNum1 - 'A' + 10;
	}
	else if((CNum1 >= '0') && (CNum1 <= '9')) {
		Num1 = CNum1 - '0';
	}
	else if(CNum1 == 'U')
		Num1 = 17;
	else if(CNum1 == 'H')
		Num1 = 18;
	else if(CNum1 == 'L')
		Num1 = 19;
	else if(CNum1 == 'P')
		Num1 = 20;
	else if(CNum1 == '-')
		Num1 = 21;
	else
		Num1 = 16; //灭, 不显示
	
	//2
	if((CNum2 >= 'A') && (CNum2 <= 'F')) {
		Num2 = CNum2 - 'A' + 10;
	}
	else if((CNum2 >= '0') && (CNum2 <= '9')) {
		Num2 = CNum2 - '0';
	}
	else if(CNum2 == 'U')
		Num2 = 17;
	else if(CNum2 == 'H')
		Num2 = 18;
	else if(CNum2 == 'L')
		Num2 = 19;
	else if(CNum2 == 'P')
		Num2 = 20;
	else if(CNum2 == '-')
		Num2 = 21;
	else
		Num2 = 16; //灭, 不显示
	
	//3
	if((CNum3 >= 'A') && (CNum3 <= 'F')) {
		Num3 = CNum3 - 'A' + 10;
	}
	else if((CNum3 >= '0') && (CNum3 <= '9')) {
		Num3 = CNum3 - '0';
	}
	else if(CNum3 == 'U')
		Num3 = 17;
	else if(CNum3 == 'H')
		Num3 = 18;
	else if(CNum3 == 'L')
		Num3 = 19;
	else if(CNum3 == 'P')
		Num3 = 20;
	else if(CNum3 == '-')
		Num3 = 21;
	else
		Num3 = 16; //灭, 不显示
	
	LED_BasicShow(LED_Convert[Num0], LED_Convert[Num1], LED_Convert[Num2], LED_Convert[Num3], Dot);
}
