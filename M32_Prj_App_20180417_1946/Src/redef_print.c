#include "DBG_uart.h"
#include "lcd_cfg.h"
#include "redef_print.h"
#include <stdio.h>

//ÖØ¶¨Òåputcharº¯Êı£¬½«ÖÕ¶ËÏÔÊ¾¸Äµ½PC¶ËLCDTest.exeĞ¡¹¤¾ßÉÏ
//ÕâÑùÔÚµ÷ÓÃprintf¸ñÊ½Êä³öº¯ÊıÊ±£¬¾ÍÄÜ½«×Ö·û´òÓ¡Êä³öµ½PC¶ËLCDTest.exeÉÏ
//char putc (char c, FILE *f)
//{        
//	Send_CharToCpu(c);
//	return 0;
//}										

#pragma import(__use_no_semihosting)
/******************************************************************************  
*±ê×¼¿âĞèÒªµÄÖ§³Öº¯Êı
******************************************************************************/  
struct __FILE  
{  
int handle;  
/* Whatever you require here. If the only file you are using is */  
/* standard output using printf() for debugging, no file handling */  
/* is required. */  
};  
/* FILE is typedef’ d in stdio.h. */  
FILE __stdout;  

/// <summary>  
/// ¶¨Òå_sys_exit()ÒÔ±ÜÃâÊ¹ÓÃ°ëÖ÷»úÄ£Ê½
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
