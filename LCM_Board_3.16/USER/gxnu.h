
#ifndef __GXNU_H
#define __GXNU_H

#include "user.h"

#define USART_REC_LEN  			256  	//�����������ֽ��� 200
#define EN_USART1_RX 			1		//ʹ�ܣ�1��/��ֹ��0������1����

extern u16 USART_RX_STA;
extern u8 USART_RX_BUF[USART_REC_LEN];

struct cmmd{
	char cmdbuffer[64];
	u8 pmdbuf[64];
	u8 num;
};


void LED_Init(void);//��ʼ��
int strcmp(const char * cs,const char * ct);
int readline(char *buff,char *pcmd,u8 *valu);
int atoi(char * buf);
	
u8 readiic(u8 *iicdata); 
u8 readiicc(u8 *iicdata);
u8 readiice(u8 *iicdata);
 
 u8 readiicd(u8 *iicdata);
 void Ri2c_Out(void);
 u8 writebyteslave(u8 data);
 
 u8 readiicdD(u8 *iicdata);
	u8 readiice(u8 *iicdat);
void clearstruct(void);	
struct parmeiic{
		u8 type;
		u16 data;
		u8 itype;
		u8 deviati;
		u8 flag;
		u8 result1;
		u8 result2;
		u8 result3;
		u8 compare;
	};
u8 readIIC(void);

#endif
