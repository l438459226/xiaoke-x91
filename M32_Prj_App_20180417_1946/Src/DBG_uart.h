
#ifndef  __DBG_UART_H__
#define  __DBG_UART_H__

#include "BasicDataType.h"


#define DBG_SERIAL_LCD__UART_BAUD 	115200 		// Baud rate
#define GPU_CFG_SPI__UART_BAUD      921600      // Baud rate

//#define TG_RX_BUFFER_SIZE    		50  		// FIFO size


// 尺寸最小要大于1个Page(256Byte)
#define UART1_RX_BUF_SIZE				640
#define UART1_TX_BUF_SIZE				640

// 如果连续100ms没有接收到数据, 之前接收到的数据丢弃
#define UART1_REC_TIMER_VAL			100


extern unsigned char  gUart1RecBuf[UART1_RX_BUF_SIZE];
extern unsigned short gUart1RecBufPtr ;					// 接收缓冲区指针
extern unsigned char  gUart1RecTimer  ;					// 接收数据定时器
extern unsigned char  gUart1RecFinish ;					// 接收帧完毕
extern unsigned short gUart1RecLen;					  	// 接收数据长度
extern unsigned char  gUart1ProtocolDetect;     // 接收或发送指令所遵循的协议


//--------------------------------------------------------
void DBG_UART_Init(UINT32 SetBaudRate);
void DBG_UART_TxChar(UINT8 u8Data);
void Uart1SendBuffer(UINT8 *pu8Data, UINT16 u16Length);

#endif

