#include "DBG_uart.h"
#include "lcd_cfg.h"
#include "redef_print.h"
#include <stdio.h>

//�ض���putchar���������ն���ʾ�ĵ�PC��LCDTest.exeС������
//�����ڵ���printf��ʽ�������ʱ�����ܽ��ַ���ӡ�����PC��LCDTest.exe��
//char putc (char c, FILE *f)
//{        
//	Send_CharToCpu(c);
//	return 0;
//}										

#pragma import(__use_no_semihosting)
/******************************************************************************  
*��׼����Ҫ��֧�ֺ���
******************************************************************************/  
struct __FILE  
{  
int handle;  
/* Whatever you require here. If the only file you are using is */  
/* standard output using printf() for debugging, no file handling */  
/* is required. */  
};  
/* FILE is typedef� d in stdio.h. */  
FILE __stdout;  

/// <summary>  
/// ����_sys_exit()�Ա���ʹ�ð�����ģʽ
/// </summary>  
/// <param name="x"></param>  
/// <returns></returns>  
void _sys_exit(int x)  
{  
x = x;  
}  

 

int fputc(int ch, FILE *f)
{ 
    DBG_UART_TxChar(ch);
    return ch; 
}   
