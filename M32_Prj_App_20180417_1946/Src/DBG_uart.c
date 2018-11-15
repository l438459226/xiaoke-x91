#include "stm32f10x_usart.h"
#include <stdio.h>
#include "DBG_uart.h"
#include "GPU_SPI_Flash_protocol.h"


unsigned char  gUart1RecBuf[UART1_RX_BUF_SIZE];
unsigned short gUart1RecBufPtr = 0;					// 接收缓冲区指针
unsigned char  gUart1RecTimer  = 0;					// 接收数据定时器
unsigned char  gUart1RecFinish = 0;					// 接收帧完毕
unsigned char  sUart1SentBusy  = 0;					// 发送忙标志
unsigned short gUart1RecLen	   = 0;					// 接收数据长度

unsigned char  gUart1ProtocolDetect = PROTOCOL_GPU_SPI_FLASH; // 接收或发送指令所遵循的协议: GPU_SPI_FLASH/User, default GPU_SPI_FLASH


/*******************************************
函数名称：  DBG_UART_Init
功    能：  设置波特率和工作方式
参    数：  无
返回值  ：  无
********************************************/
void DBG_UART_Init(UINT32 SetBaudRate)
{
    //--- 由于USART1 TX和RX是复用的GPIO PA9和PA10, 所以在本函数之前要先将GPIO初始化
    //--- USART1 初始化
    USART_InitTypeDef USART_InitStructure;//声明一个USART初始化结构体(固件库中貌似很喜欢用这种风格来初始化设备)
    USART_ClockInitTypeDef USART_ClockInitStructure;

    USART_InitStructure.USART_BaudRate = SetBaudRate; //初始化波特率
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;//设置数据长度为8bit
    USART_InitStructure.USART_StopBits = USART_StopBits_1;//停止位为1
    USART_InitStructure.USART_Parity = USART_Parity_No;//无校验位
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//数据流控制为none
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;//接收和发送模式都打开

    USART_ClockStructInit(&USART_ClockInitStructure);
    USART_ClockInit(USART1, &USART_ClockInitStructure);

    /* Configure USART1 */
    USART_Init(USART1, &USART_InitStructure);//初始化1口

    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);

    /* Enable the USART1 */
    USART_Cmd(USART1, ENABLE);//打开1口
}



/*******************************************
函数名称： DBG_UART_RxChar
功    能： 接收一个字节数据
参    数： 无
返回值  ： 接收数据
********************************************/
//UINT8 DBG_UART_RxChar()
//{
//  UINT8 u8RxData;

//  UART5_DISABLE_INTERRUPT();
//  u8RxData = sUart0Cb.pu8RxBuffer[sUart0Cb.u16RxHeader];

//  UART5_ENABLE_INTERRUPT();

//  return u8RxData;
//}
/*******************************************
函数名称： DBG_UART_TxChar
功    能： 发送一个字节数据
参    数： bData--发送的数据
返回值  ： 无
********************************************/
void DBG_UART_TxChar(UINT8 u8Data)
{
	//USART_SendData(USART4, u8Data);
	USART1->DR = (uint16_t)u8Data;	/* Transmit Data */
	while(!(USART1->SR & USART_FLAG_TXE));
}

void Uart1SendBuffer(UINT8 *pu8Data, UINT16 u16Length)
{
	UINT16 i = 0;
	while(i<u16Length) {
		DBG_UART_TxChar(pu8Data[i++]);
	}
}


void Uart1RecProc(unsigned char val)
{
	// 如果已接收到数据还没处理，不接收数据
	if(gUart1RecBufPtr < UART1_RX_BUF_SIZE && 0 == gUart1RecFinish)
	{
		if(MESSAGE_START_INDEX == gUart1RecBufPtr)						// 指令头
		{
			if(MESSAGE_START_VAL == val) { //standard
				gUart1ProtocolDetect = PROTOCOL_GPU_SPI_FLASH;
			}
			else {//user
				gUart1ProtocolDetect = PROTOCOL_USER;
				gUart1RecBufPtr = 0;
				gUart1RecTimer  = 0;									// 丢弃数据
			}
		}
		else if(gUart1ProtocolDetect == PROTOCOL_GPU_SPI_FLASH)
		{
			if(MESSAGE_SIZE_HIGH_INDEX == gUart1RecBufPtr)				// 数据长度高位
			{
				gUart1RecLen = ((unsigned short)val) << 8;					
			}
			else if(MESSAGE_SIZE_LOW_INDEX == gUart1RecBufPtr)				// 数据长度低位
			{
				gUart1RecLen |= val;
				if(gUart1RecLen > (UART1_RX_BUF_SIZE - 10))					// 数据长度过长
				{
					gUart1RecBufPtr = 0;
					gUart1RecTimer  = 0;									// 丢弃数据
					return;
				}
			}
			else if(TOKE_INEXE == gUart1RecBufPtr)							// 令牌
			{
				if(TOKE_VAL!= val)											// 令牌错误
				{
					gUart1RecBufPtr = 0;
					gUart1RecTimer  = 0;									// 丢弃数据
					return;
				}
			}
		}
				
		gUart1RecBuf[gUart1RecBufPtr++] = val;							// 接收数据, 并下移接收Buf指针
		
		if(gUart1ProtocolDetect == PROTOCOL_GPU_SPI_FLASH) {
			if((gUart1RecLen + 6) == gUart1RecBufPtr)					// 接收到完整的数据帧
			{
				gUart1RecFinish = 1;
				gUart1RecBufPtr = 0;
				gUart1RecTimer  = 0;
				return;
			}
			
			gUart1RecTimer = UART1_REC_TIMER_VAL;							// 启动超时定时器
		}
//		else if(gUart1ProtocolDetect == PROTOCOL_USER) {
//			//cpu_write_reg(EXTMCU_UART_FIFO_ADDR, val);
//		}
		
	}
}


//---------------------------------------------------------------------------------------------------
// 串口1(MCU_TX/MCU_RX)中断
void USART1_IRQHandler(void) {
  //if(USART_GetFlagStatus(USART1, USART_FLAG_RXNE)) {
	if(USART1->SR & USART_FLAG_RXNE) {
		USART_ClearFlag(USART1, USART_FLAG_RXNE);//清空接收标志位
		
		//
		//Receive = USART_ReceiveData(USART1); //取得数据
		Uart1RecProc((uint8_t)(USART1->DR & (uint16_t)0x00FF));
	}
}
