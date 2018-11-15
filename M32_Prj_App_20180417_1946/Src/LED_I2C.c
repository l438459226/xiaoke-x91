#include "LED_I2C.h"
#include "user_config.h"
#include "tools.h"
#include "user_gpio_def.h"
#include <stdio.h>

/*
������I2C_Delay()
���ܣ���ʱ��ģ��I2C����ר��
*/
void LED_I2C_Delay()
{
	delayus(5);
}


/*
������I2C_Init()
���ܣ�I2C���߳�ʼ����ʹ���ߴ��ڿ���״̬
˵������main()�����Ŀ�ʼ����ͨ��Ӧ��Ҫִ��һ�α�����
*/
void LED_I2C_Init(void)
{
	
	LED_I2C_SDA(1);
	LED_I2C_SCL(1);
}


/*
������I2C_Start()
���ܣ�����I2C���ߵ���ʼ״̬
˵����
    SCL���ڸߵ�ƽ�ڼ䣬��SDA�����½���ʱ����I2C����
    ����SDA��SCL����ʲô��ƽ״̬��������������ȷ������ʼ״̬
    ������Ҳ�������������ظ���ʼ״̬
    ������ִ�к�I2C���ߴ���æ״̬
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
������I2C_Write()
���ܣ���I2C����д1���ֽڵ�����
������
    dat��Ҫд�������ϵ�����
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
������I2C_Read()
���ܣ��Ӵӻ���ȡ1���ֽڵ�����
���أ���ȡ��һ���ֽ�����
*/
unsigned char LED_I2C_Read(void)
{
    unsigned char dat;
    unsigned char t = 8;

	
	LED_I2C_SDA(1);    //�ڶ�ȡ����֮ǰ��Ҫ��SDA����
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
������I2C_GetAck()
���ܣ���ȡ�ӻ�Ӧ��λ
���أ�
    0���ӻ�Ӧ��
    1���ӻ���Ӧ��
˵����
    �ӻ����յ�ÿ���ֽڵ����ݺ�Ҫ����Ӧ��λ
    �ӻ����յ����1���ֽڵ����ݺ�һ��Ҫ������Ӧ��λ
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
������I2C_PutAck()
���ܣ���������Ӧ��λ���Ӧ��λ
������
    ack=0����������Ӧ��λ
    ack=1������������Ӧ��λ
˵����
    �����ڽ�����ÿһ���ֽڵ����ݺ󣬶�Ӧ������Ӧ��λ
    �����ڽ��������һ���ֽڵ����ݺ�Ӧ��������Ӧ��λ
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
������I2C_Stop()
���ܣ�����I2C���ߵ�ֹͣ״̬
˵����
    SCL���ڸߵ�ƽ�ڼ䣬��SDA����������ʱֹͣI2C����
    ����SDA��SCL����ʲô��ƽ״̬��������������ȷ����ֹͣ״̬
    ������ִ�к�I2C���ߴ��ڿ���״̬
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
	while ( --t != 0 );     //����һ�β���Start֮ǰ��Ҫ��һ������ʱ
}




/*
������I2C_Puts()
���ܣ�I2C�����ۺϷ��ͺ�������ӻ����Ͷ���ֽڵ�����
������
    SlaveAddr���ӻ���ַ��7λ����ַ��������дλ��
    SubAddr���ӻ����ӵ�ַ
    SubMod���ӵ�ַģʽ��0�����ӵ�ַ��1�����ֽ��ӵ�ַ��2��˫�ֽ��ӵ�ַ
    *dat��Ҫ���͵�����
    Size�����ݵ��ֽ���
���أ�
    0�����ͳɹ�
    1���ڷ��͹����г����쳣
˵����
    �������ܹ��ܺõ���Ӧ���г�����I2C�������������Ƿ����ӵ�ַ
    ���ӻ�û���ӵ�ַʱ������SubAddr���⣬��SubModӦ��Ϊ0
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
//������ʱ����
    unsigned char i;
    char a[3];
//��鳤��
    if ( Size == 0 ) return 0;
//׼���ӻ���ַ
    a[0] = (SlaveAddr << 1);
//����ӵ�ַģʽ
    if ( SubMod > 2 ) SubMod = 2;
//ȷ���ӵ�ַ
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
//���ʹӻ���ַ�����ŷ����ӵ�ַ��������ӵ�ַ�Ļ���
    SubMod++;
    LED_I2C_Start();
    for ( i=0; i<SubMod; i++ ) {
		LED_I2C_Write(a[i]);
        if ( LED_I2C_GetAck() ) {
            LED_I2C_Stop();
            return 1;
        }
    }
//��������
    do
    {
        LED_I2C_Write(*dat++);
        if ( LED_I2C_GetAck() ) break;
    } while ( --Size != 0 );
//������ϣ�ֹͣI2C���ߣ������ؽ��
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
������I2C_Gets()
���ܣ�I2C�����ۺϽ��պ������Ӵӻ����ն���ֽڵ�����
������
    SlaveAddr���ӻ���ַ��7λ����ַ��������дλ��
    SubAddr���ӻ����ӵ�ַ
    SubMod���ӵ�ַģʽ��0�����ӵ�ַ��1�����ֽ��ӵ�ַ��2��˫�ֽ��ӵ�ַ
    *dat��������յ�������
    Size�����ݵ��ֽ���
���أ�
    0�����ճɹ�
    1���ڽ��չ����г����쳣
˵����
    �������ܹ��ܺõ���Ӧ���г�����I2C�������������Ƿ����ӵ�ַ
    ���ӻ�û���ӵ�ַʱ������SubAddr���⣬��SubModӦ��Ϊ0
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
//������ʱ����
    unsigned char i;
    char a[3];
//��鳤��
    if ( Size == 0 ) return 3;
//׼���ӻ���ַ
    a[0] = (SlaveAddr << 1);
//����ӵ�ַģʽ
    if ( SubMod > 2 ) SubMod = 2;
//��������ӵ�ַ�Ĵӻ�����Ҫ�ȷ��ʹӻ���ַ���ӵ�ַ
    if ( SubMod != 0 )
    {
    //ȷ���ӵ�ַ
        if ( SubMod == 1 )
        {
            a[1] = (char)(SubAddr);
        }
        else
        {
            a[1] = (char)(SubAddr >> 8);
            a[2] = (char)(SubAddr);
        }
    //���ʹӻ���ַ�����ŷ����ӵ�ַ
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
//�����I2C_Start()�������ӵ�ַ�Ĵӻ����ظ���ʼ״̬
//�������ӵ�ַ�Ĵӻ�������������ʼ״̬
    LED_I2C_Start();
//���ʹӻ���ַ
    LED_I2C_Write(a[0]+1);
    if ( LED_I2C_GetAck() )
    {
        LED_I2C_Stop();
        return 5;
    }
//��������
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
//������ϣ�ֹͣI2C���ߣ������ؽ��
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
	
	//Command1, ��������:48H
	//Command2, ����ʾ, ��ʾ���ȼ�
	tAddr = 0x48;
	tData = BRIGHTNESS_4 | SEGMENT_8 | 0x01; //����ʾ
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

UINT8 LED_Convert[22] = { //0~9,  A,b,C,d,E,F,  ��, U,H,L,P,-,
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
	0x00, //��---
	0x3E, //U ---
	0x76, //H ---
	0x38, //L ---
	0x73, //P ---
	0x40, //- ---
};

void LED_BasicShow(UINT8 Num0, UINT8 Num1, UINT8 Num2, UINT8 Num3, UINT8 Dot) { //Dot, bit[3:0]��ӦLED0,LED1,LED2,LED3
	UINT8 Res;
	UINT8 tAddr, tData;
	UINT8 tDot;
	
	//�Դ��ַ
	//��ʾ����
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
	
	//�Դ��ַ
	//��ʾ����
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
	
	//�Դ��ַ
	//��ʾ����
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
	
	//�Դ��ַ
	//��ʾ����
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
		Num0 = 16; //��, ����ʾ
	
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
		Num1 = 16; //��, ����ʾ
	
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
		Num2 = 16; //��, ����ʾ
	
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
		Num3 = 16; //��, ����ʾ
	
	LED_BasicShow(LED_Convert[Num0], LED_Convert[Num1], LED_Convert[Num2], LED_Convert[Num3], Dot);
}
