/**
  ******************************************************************************
  * @file    usb_endp.c
  * @author  MCD Application Team
  * @version V4.0.0
  * @date    21-January-2013
  * @brief   Endpoint routines
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2013 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */


/* Includes ------------------------------------------------------------------*/
#include "hw_config.h"
#include "usb_lib.h"
#include "usb_istr.h"
#include "usb_conf.h"
#include "bsp_usart1.h"
#include "gxnu.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
extern __IO uint8_t PrevXferComplete;

u8 Receive_Buffer[22];
u8 Transi_Buffer[22];
u8 USB_ReceiveFlg = FALSE;
extern vu8 MsgCmd;
extern u8 hidr;
#define nReportCnt 22
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/*******************************************************************************
* Function Name  : EP1_OUT_Callback.
* Description    : EP1 OUT Callback Routine.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/

void EP1_OUTT_Callback(void)//设备接收主机传送来的数据
{
		 int i;
     USB_ReceiveFlg = TRUE;
     PMAToUserBufferCopy(Receive_Buffer, ENDP1_RXADDR,nReportCnt);
		
     MsgCmd = Receive_Buffer[21];
     SetEPRxStatus(ENDP1, EP_RX_VALID);
		 printf(" Buffer:");
		 for(i=0;i<22;i++)
			printf(" %c",Receive_Buffer[i]);
		 printf(" \r\n");
		 hidr = 1;
}

void EP1_OUT_Callback(void)//设备接收主机传送来的数据
{
		 int i;
		 //int usartnum = 0;
     USB_ReceiveFlg = TRUE;
		 //USART_RX_STA = nReportCnt;
		 //USART_RX_STA |= 0x8000;
     PMAToUserBufferCopy(Receive_Buffer, ENDP1_RXADDR,nReportCnt);
			
     SetEPRxStatus(ENDP1, EP_RX_VALID);

		 for(i=0;i<22;i++){
				if(Receive_Buffer[i] != '\n'){
					USART_RX_BUF[USART_RX_STA++] = Receive_Buffer[i];
				}else {USART_RX_STA |= 0x8000;}
			}
		 printf("Buffer:%s  \r\n",USART_RX_BUF);
		 printf("USART_RX_STA:0x%x \r\n",USART_RX_STA);
		 hidr = 1;
}
void EP2_IN_Callback(void)
{
     u8 ii;
     for (ii=0;ii<nReportCnt;ii++) Transi_Buffer[ii] = 0x00;	//for LED test
	
     if (GPIOA->ODR & 0x0c )  GPIOA->ODR &= (~0x0c);
     else GPIOA->ODR |= 0x0c;
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

