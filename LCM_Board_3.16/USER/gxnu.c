#include "gxnu.h"
#include "bsp_usart1.h"
#include "stdarg.h"
#include "ssd2828.h"
/*********************ADD*****************************************/
u16 USART_RX_STA=0;
u8 USART_RX_BUF[USART_REC_LEN];

u8 commd;
char mbuffer[128];
struct cmmd cmd;

//LED状态设置函数
void led_set(u8 sta)
{
	u8 regdat;
	if(sta==1)	{printf("led on\r\n");DCS_R(0xDA,1,&regdat);printf("led on!  regdat:0x%x\r\n",regdat);USB_SendString("hello world!");}
	else {printf("led off\r\n");DCS_R(0x53,1,&regdat);printf("led off!  regdat:0x%x\r\n",regdat);}
} 
//函数参数调用测试函数
void test_fun(void(*ledset)(u8),u8 sta)
{
	ledset(sta);
}  	

/*
int atoi(char *buf)		//
{
	
	int value = 0;	
	int base = 10;
	int i = 0;
	int tmp=0;
	
	if (buf[0] == '0' && buf[1] == 'x')
	{
		base = 16;
		i = 2;
	}	
	// 123 = (1 * 10 + 2) * 10 + 3
	// 0x1F = 1 * 16 + F(15)	
	while (buf[i])
	{
		if (buf[i] <= '9' && buf[i] >= '0') tmp = buf[i] - '0';
		else if(buf[i] <= 'f' && buf[i] >= 'a')	tmp = buf[i] - 'a' + 10;
		else if(buf[i] <= 'F' && buf[i] >= 'A')	tmp = buf[i] - 'A' + 10;
		
		value = value * base + tmp;
		i++;
	}
	return value;
}
*/




int readline(char *buff,char *pcmd,u8 *valu)
{
	char *buf = buff;
	int argc = 0;
	u8 i;
	char *argv[65];
	
	int state = 0;
	
	while (*buf)
	{
		if (*buf != ' ' && state == 0)
		{
			argv[argc++] = buf;
			state = 1;
		}
		if (*buf == ' ' && state == 1)
		{
			*buf = '\0';
	  	state = 0;
		}
		buf++;		
	}
	
	for(i=0;i<argc;i++)
	{
		valu[i] = atoi(argv[i]);
	}
	
	return argc;
}


int strcmp(const char * cs,const char * ct)
{
	register signed char __res;

	while (1) {
		if ((__res = *cs - *ct++) != 0 || !*cs++)
			break;
	}

	return __res;
}

u8	commd_fun(char *p)
{
		char *pp = p;
		u8 i;
		for(i=0;i<64;i++){
			if((*(pp+i))!='\0')
				cmd.cmdbuffer[i]=*(pp+i);
			else cmd.cmdbuffer[i]='\0';
		}
		printf(" cmd.cmdbuffer:%s \r\n",cmd.cmdbuffer);
		cmd.num = readline(cmd.cmdbuffer,mbuffer,cmd.pmdbuf);//返回个数
		printf(" cmd.cmdbuffer:%s \r\n",cmd.cmdbuffer);
		printf(" cmd.num:%X \r\n",cmd.num);
		return 0;
}

size_t strlenn(const char * s)
{
	const char *sc;

	for (sc = s; *sc != '\0'; ++sc)
		/* nothing */;
	return sc - s;
}
