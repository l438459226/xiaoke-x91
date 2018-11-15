
#ifndef  __DBG_UART_H__
#define  __DBG_UART_H__

#include "BasicDataType.h"


#define DBG_SERIAL_LCD__UART_BAUD 	115200 		// Baud rate
#define GPU_CFG_SPI__UART_BAUD      921600      // Baud rate

//#define TG_RX_BUFFER_SIZE    		50  		// FIFO size


// �ߴ���СҪ����1��Page(256Byte)
#define UART1_RX_BUF_SIZE				640
#define UART1_TX_BUF_SIZE				640

// �������100msû�н��յ�����, ֮ǰ���յ������ݶ���
#define UART1_REC_TIMER_VAL			100


extern unsigned char  gUart1RecBuf[UART1_RX_BUF_SIZE];
extern unsigned short gUart1RecBufPtr ;					// ���ջ�����ָ��
extern unsigned char  gUart1RecTimer  ;					// �������ݶ�ʱ��
extern unsigned char  gUart1RecFinish ;					// ����֡���
extern unsigned short gUart1RecLen;					  	// �������ݳ���
extern unsigned char  gUart1ProtocolDetect;     // ���ջ���ָ������ѭ��Э��


//--------------------------------------------------------
void DBG_UART_Init(UINT32 SetBaudRate);
void DBG_UART_TxChar(UINT8 u8Data);
void Uart1SendBuffer(UINT8 *pu8Data, UINT16 u16Length);

#endif

