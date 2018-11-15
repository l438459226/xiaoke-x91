/**
  ******************************************************************************
  * @file SDIO/sdcard.c 
  * @author  MCD Application Team
  * @version  V3.0.0
  * @date  04/06/2009
  * @brief  This file provides all the SD Card driver firmware functions.
  ******************************************************************************
  * @copy
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2009 STMicroelectronics</center></h2>
  */ 

/* Includes ------------------------------------------------------------------*/
#include "sdcard.h"

/** @addtogroup StdPeriph_Examples
  * @{
  */

/** @addtogroup SDIO_Example
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define NULL 0
#define SDIO_STATIC_FLAGS               ((uint32_t)0x000005FF)
#define SDIO_CMD0TIMEOUT                ((uint32_t)0x00002710)
#define SDIO_FIFO_Address               ((uint32_t)0x40018080)

/* Mask for errors Card Status R1 (OCR Register) */
#define MISD_OCR_ADDR_OUT_OF_RANGE        ((uint32_t)0x80000000)
#define MISD_OCR_ADDR_MISALIGNED          ((uint32_t)0x40000000)
#define MISD_OCR_BLOCK_LEN_ERR            ((uint32_t)0x20000000)
#define MISD_OCR_ERASE_SEQ_ERR            ((uint32_t)0x10000000)
#define MISD_OCR_BAD_ERASE_PARAM          ((uint32_t)0x08000000)
#define MISD_OCR_WRITE_PROT_VIOLATION     ((uint32_t)0x04000000)
#define MISD_OCR_LOCK_UNLOCK_FAILED       ((uint32_t)0x01000000)
#define MISD_OCR_COM_CRC_FAILED           ((uint32_t)0x00800000)
#define MISD_OCR_ILLEGAL_CMD              ((uint32_t)0x00400000)
#define MISD_OCR_CARD_ECC_FAILED          ((uint32_t)0x00200000)
#define MISD_OCR_CC_ERROR                 ((uint32_t)0x00100000)
#define MISD_OCR_GENERAL_UNKNOWN_ERROR    ((uint32_t)0x00080000)
#define MISD_OCR_STREAM_READ_UNDERRUN     ((uint32_t)0x00040000)
#define MISD_OCR_STREAM_WRITE_OVERRUN     ((uint32_t)0x00020000)
#define MISD_OCR_CID_CMISD_OVERWRIETE       ((uint32_t)0x00010000)
#define MISD_OCR_WP_ERASE_SKIP            ((uint32_t)0x00008000)
#define MISD_OCR_CARD_ECC_DISABLED        ((uint32_t)0x00004000)
#define MISD_OCR_ERASE_RESET              ((uint32_t)0x00002000)
#define MISD_OCR_AKE_SEQ_ERROR            ((uint32_t)0x00000008)
#define MISD_OCR_ERRORBITS                ((uint32_t)0xFDFFE008)

/* Masks for R6 Response */
#define MISD_R6_GENERAL_UNKNOWN_ERROR     ((uint32_t)0x00002000)
#define MISD_R6_ILLEGAL_CMD               ((uint32_t)0x00004000)
#define MISD_R6_COM_CRC_FAILED            ((uint32_t)0x00008000)

#define MISD_VOLTAGE_WINDOW_SD            ((uint32_t)0x80100000)
#define MISD_HIGH_CAPACITY                ((uint32_t)0x40000000)
#define MISD_STD_CAPACITY                 ((uint32_t)0x00000000)
#define MISD_CHECK_PATTERN                ((uint32_t)0x000001AA)

#define MISD_MAX_VOLT_TRIAL               ((uint32_t)0x0000FFFF)
#define MISD_ALLZERO                      ((uint32_t)0x00000000)

#define MISD_WIDE_BUS_SUPPORT             ((uint32_t)0x00040000)
#define MISD_SINGLE_BUS_SUPPORT           ((uint32_t)0x00010000)
#define MISD_CARD_LOCKED                  ((uint32_t)0x02000000)
#define MISD_CARD_PROGRAMMING             ((uint32_t)0x00000007)
#define MISD_CARD_RECEIVING               ((uint32_t)0x00000006)
#define MISD_DATATIMEOUT                  ((uint32_t)0x000FFFFF)
#define MISD_0TO7BITS                     ((uint32_t)0x000000FF)
#define MISD_8TO15BITS                    ((uint32_t)0x0000FF00)
#define MISD_16TO23BITS                   ((uint32_t)0x00FF0000)
#define MISD_24TO31BITS                   ((uint32_t)0xFF000000)
#define MISD_MAX_DATA_LENGTH              ((uint32_t)0x01FFFFFF)

#define MISD_HALFFIFO                     ((uint32_t)0x00000008)
#define MISD_HALFFIFOBYTES                ((uint32_t)0x00000020)

/* Command Class Supported */
#define MISD_CCCC_LOCK_UNLOCK             ((uint32_t)0x00000080)
#define MISD_CCCC_WRITE_PROT              ((uint32_t)0x00000040)
#define MISD_CCCC_ERASE                   ((uint32_t)0x00000020)

/* Following commands are SD Card Specific commands.
   SDIO_APP_CMD should be sent before sending these commands. */
#define SDIO_SEND_IF_COND               ((uint32_t)0x00000008)

#define SDIO_INIT_CLK_DIV                  ((uint8_t)0xB2)
#define SDIO_TRANSFER_CLK_DIV              ((uint8_t)0x1) 


/* Supported Memory Cards */

#define SDIO_STD_CAPACITY_MISD_CARD_V1_1     ((uint32_t)0x0)
#define SDIO_STD_CAPACITY_MISD_CARD_V2_0     ((uint32_t)0x1)
#define SDIO_HIGH_CAPACITY_MISD_CARD         ((uint32_t)0x2)
#define SDIO_MULTIMEDIA_CARD               ((uint32_t)0x3)
#define SDIO_SECURE_DIGITAL_IO_CARD        ((uint32_t)0x4)
#define SDIO_HIGH_SPEED_MULTIMEDIA_CARD    ((uint32_t)0x5)
#define SDIO_SECURE_DIGITAL_IO_COMBO_CARD  ((uint32_t)0x6)
#define SDIO_HIGH_CAPACITY_MMC_CARD        ((uint32_t)0x7)

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static uint32_t CardType =  SDIO_STD_CAPACITY_MISD_CARD_V1_1;
static uint32_t CMISD_Tab[4], CID_Tab[4], RCA = 0;
static uint32_t DeviceMode = MISD_POLLING_MODE;
static uint32_t TotalSDNumberOfBytes = 0, StopCondition = 0;
uint32_t *SrcBuffer, *DestBuffer;
volatile MISD_Error SDTransferError = MISD_OK;
__IO uint32_t SDTransferEnd = 0;
__IO uint32_t SDNumberOfBytes = 0;
extern SDIO_InitTypeDef SDIO_InitStructure;
extern SDIO_CmdInitTypeDef SDIO_CmdInitStructure;
extern SDIO_DataInitTypeDef SDIO_DataInitStructure;

/* Private function prototypes -----------------------------------------------*/
static MISD_Error CmdError(void);
static MISD_Error CmdResp1Error(uint8_t cmd);
static MISD_Error CmdResp7Error(void);
static MISD_Error CmdResp3Error(void);
static MISD_Error CmdResp2Error(void);
static MISD_Error CmdResp6Error(uint8_t cmd, uint16_t *prca);
static MISD_Error SDEnWideBus(FunctionalState NewState);
static MISD_Error IsCardProgramming(uint8_t *pstatus);
static MISD_Error FindSCR(uint16_t rca, uint32_t *pscr);
static uint8_t convert_from_bytes_to_power_of_two(uint16_t SDNumberOfBytes);
static void SDIOGPIO_Configuration(void);
static void DMA_TxConfiguration(uint32_t *BufferSRC, uint32_t BufferSize);
static void DMA_RxConfiguration(uint32_t *BufferDST, uint32_t BufferSize);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Initializes the SD Card and put it into StandBy State (Ready 
  *   for data transfer).
  * @param  None
  * @retval : MISD_Error: SD Card Error code.
  */
MISD_Error MISD_Init(void)
{
  MISD_Error errorstatus = MISD_OK;

  /* Configure SDIO interface GPIO */
  SDIOGPIO_Configuration();

  /* Enable the SDIO AHB Clock */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_SDIO, ENABLE);

  /* Enable the DMA2 Clock */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA2, ENABLE);

  SDIO_DeInit(); // ÔÚstm32f10x_sdio.c¶¨Òå

  errorstatus = MISD_PowerON();

  if (errorstatus != MISD_OK)
  {
    /* CMD Response TimeOut (wait for CMDSENT flag) */
    return(errorstatus);
  }

  errorstatus = MISD_InitializeCards();

  if (errorstatus != MISD_OK)
  {
    /* CMD Response TimeOut (wait for CMDSENT flag) */
    return(errorstatus);
  }

  /* Configure the SDIO peripheral */
  /* HCLK = 72 MHz, SDIOCLK = 72 MHz, SDIO_CK = HCLK/(2 + 1) = 24 MHz */  
  SDIO_InitStructure.SDIO_ClockDiv = SDIO_TRANSFER_CLK_DIV; 
  SDIO_InitStructure.SDIO_ClockEdge = SDIO_ClockEdge_Rising;
  SDIO_InitStructure.SDIO_ClockBypass = SDIO_ClockBypass_Disable;
  SDIO_InitStructure.SDIO_ClockPowerSave = SDIO_ClockPowerSave_Disable;
  SDIO_InitStructure.SDIO_BusWide = SDIO_BusWide_1b;
  SDIO_InitStructure.SDIO_HardwareFlowControl = SDIO_HardwareFlowControl_Disable;
  SDIO_Init(&SDIO_InitStructure);

  return(errorstatus);
}

/**
  * @brief  Enquires cards about their operating voltage and configures 
  *   clock controls.
  * @param  None
  * @retval : MISD_Error: SD Card Error code.
  */
MISD_Error MISD_PowerON(void)
{
  MISD_Error errorstatus = MISD_OK;
  uint32_t response = 0, count = 0;
  bool validvoltage = FALSE;
  uint32_t SDType = MISD_STD_CAPACITY;

  /* Power ON Sequence -------------------------------------------------------*/
  /* Configure the SDIO peripheral */
  SDIO_InitStructure.SDIO_ClockDiv = SDIO_INIT_CLK_DIV; /* HCLK = 72MHz, SDIOCLK = 72MHz, SDIO_CK = HCLK/(178 + 2) = 400 KHz */
  SDIO_InitStructure.SDIO_ClockEdge = SDIO_ClockEdge_Rising;
  SDIO_InitStructure.SDIO_ClockBypass = SDIO_ClockBypass_Disable;
  SDIO_InitStructure.SDIO_ClockPowerSave = SDIO_ClockPowerSave_Disable;
  SDIO_InitStructure.SDIO_BusWide = SDIO_BusWide_1b;
  SDIO_InitStructure.SDIO_HardwareFlowControl = SDIO_HardwareFlowControl_Disable;
  SDIO_Init(&SDIO_InitStructure);

  /* Set Power State to ON */
  SDIO_SetPowerState(SDIO_PowerState_ON);

  /* Enable SDIO Clock */
  SDIO_ClockCmd(ENABLE);

  /* CMD0: GO_IDLE_STATE -------------------------------------------------------*/
  /* No CMD response required */
  SDIO_CmdInitStructure.SDIO_Argument = 0x0;
  SDIO_CmdInitStructure.SDIO_CmdIndex = SDIO_GO_IDLE_STATE;
  SDIO_CmdInitStructure.SDIO_Response = SDIO_Response_No;
  SDIO_CmdInitStructure.SDIO_Wait = SDIO_Wait_No;
  SDIO_CmdInitStructure.SDIO_CPSM = SDIO_CPSM_Enable;
  SDIO_SendCommand(&SDIO_CmdInitStructure);

  errorstatus = CmdError();

  if (errorstatus != MISD_OK)
  {
    /* CMD Response TimeOut (wait for CMDSENT flag) */
    return(errorstatus);
  }

  /* CMD8: SEND_IF_COND --------------------------------------------------------*/
  /* Send CMD8 to verify SD card interface operating condition */
  /* Argument: - [31:12]: Reserved (shall be set to '0')
               - [11:8]: Supply Voltage (VHS) 0x1 (Range: 2.7-3.6 V)
               - [7:0]: Check Pattern (recommended 0xAA) */
  /* CMD Response: R7 */
  SDIO_CmdInitStructure.SDIO_Argument = MISD_CHECK_PATTERN;
  SDIO_CmdInitStructure.SDIO_CmdIndex = SDIO_SEND_IF_COND;
  SDIO_CmdInitStructure.SDIO_Response = SDIO_Response_Short;
  SDIO_CmdInitStructure.SDIO_Wait = SDIO_Wait_No;
  SDIO_CmdInitStructure.SDIO_CPSM = SDIO_CPSM_Enable;
  SDIO_SendCommand(&SDIO_CmdInitStructure);

  errorstatus = CmdResp7Error();

  if (errorstatus == MISD_OK)
  {
    CardType = SDIO_STD_CAPACITY_MISD_CARD_V2_0; /* SD Card 2.0 */
    SDType = MISD_HIGH_CAPACITY;
  }
  else
  {
    /* CMD55 */
    SDIO_CmdInitStructure.SDIO_Argument = 0x00;
    SDIO_CmdInitStructure.SDIO_CmdIndex = SDIO_APP_CMD;
    SDIO_CmdInitStructure.SDIO_Response = SDIO_Response_Short;
    SDIO_CmdInitStructure.SDIO_Wait = SDIO_Wait_No;
    SDIO_CmdInitStructure.SDIO_CPSM = SDIO_CPSM_Enable;
    SDIO_SendCommand(&SDIO_CmdInitStructure);
    errorstatus = CmdResp1Error(SDIO_APP_CMD);
  }
  /* CMD55 */
  SDIO_CmdInitStructure.SDIO_Argument = 0x00;
  SDIO_CmdInitStructure.SDIO_CmdIndex = SDIO_APP_CMD;
  SDIO_CmdInitStructure.SDIO_Response = SDIO_Response_Short;
  SDIO_CmdInitStructure.SDIO_Wait = SDIO_Wait_No;
  SDIO_CmdInitStructure.SDIO_CPSM = SDIO_CPSM_Enable;
  SDIO_SendCommand(&SDIO_CmdInitStructure);
  errorstatus = CmdResp1Error(SDIO_APP_CMD);

  /* If errorstatus is Command TimeOut, it is a MMC card */
  /* If errorstatus is MISD_OK it is a SD card: SD card 2.0 (voltage range mismatch)
     or SD card 1.x */
  if (errorstatus == MISD_OK)
  {
    /* SD CARD */
    /* Send ACMD41 MISD_APP_OP_COND with Argument 0x80100000 */
    while ((!validvoltage) && (count < MISD_MAX_VOLT_TRIAL))
    {

      /* SEND CMD55 APP_CMD with RCA as 0 */
      SDIO_CmdInitStructure.SDIO_Argument = 0x00;
      SDIO_CmdInitStructure.SDIO_CmdIndex = SDIO_APP_CMD;
      SDIO_CmdInitStructure.SDIO_Response = SDIO_Response_Short;
      SDIO_CmdInitStructure.SDIO_Wait = SDIO_Wait_No;
      SDIO_CmdInitStructure.SDIO_CPSM = SDIO_CPSM_Enable;
      SDIO_SendCommand(&SDIO_CmdInitStructure);

      errorstatus = CmdResp1Error(SDIO_APP_CMD);

      if (errorstatus != MISD_OK)
      {
        return(errorstatus);
      }
      SDIO_CmdInitStructure.SDIO_Argument = MISD_VOLTAGE_WINDOW_SD | SDType;
      SDIO_CmdInitStructure.SDIO_CmdIndex = SDIO_MISD_APP_OP_COND;
      SDIO_CmdInitStructure.SDIO_Response = SDIO_Response_Short;
      SDIO_CmdInitStructure.SDIO_Wait = SDIO_Wait_No;
      SDIO_CmdInitStructure.SDIO_CPSM = SDIO_CPSM_Enable;
      SDIO_SendCommand(&SDIO_CmdInitStructure);

      errorstatus = CmdResp3Error();
      if (errorstatus != MISD_OK)
      {
        return(errorstatus);
      }

      response = SDIO_GetResponse(SDIO_RESP1);
      validvoltage = (bool) (((response >> 31) == 1) ? 1 : 0);
      count++;
    }
    if (count >= MISD_MAX_VOLT_TRIAL)
    {
      errorstatus = MISD_INVALID_VOLTRANGE;
      return(errorstatus);
    }

    if (response &= MISD_HIGH_CAPACITY)
    {
      CardType = SDIO_HIGH_CAPACITY_MISD_CARD;
    }

  }/* else MMC Card */

  return(errorstatus);
}

/**
  * @brief  Turns the SDIO output signals off.
  * @param  None
  * @retval : MISD_Error: SD Card Error code.
  */
MISD_Error MISD_PowerOFF(void)
{
  MISD_Error errorstatus = MISD_OK;

  /* Set Power State to OFF */
  SDIO_SetPowerState(SDIO_PowerState_OFF);

  return(errorstatus);
}

/**
  * @brief  Intialises all cards or single card as the case may be. 
  *   Card(s) come into standby state.
  * @param  None
  * @retval : MISD_Error: SD Card Error code.
  */
MISD_Error MISD_InitializeCards(void)
{
  MISD_Error errorstatus = MISD_OK;
  uint16_t rca = 0x01;

  if (SDIO_GetPowerState() == SDIO_PowerState_OFF)
  {
    errorstatus = MISD_REQUEST_NOT_APPLICABLE;
    return(errorstatus);
  }

  if (SDIO_SECURE_DIGITAL_IO_CARD != CardType)
  {
    /* Send CMD2 ALL_SEND_CID */
    SDIO_CmdInitStructure.SDIO_Argument = 0x0;
    SDIO_CmdInitStructure.SDIO_CmdIndex = SDIO_ALL_SEND_CID;
    SDIO_CmdInitStructure.SDIO_Response = SDIO_Response_Long;
    SDIO_CmdInitStructure.SDIO_Wait = SDIO_Wait_No;
    SDIO_CmdInitStructure.SDIO_CPSM = SDIO_CPSM_Enable;
    SDIO_SendCommand(&SDIO_CmdInitStructure);

    errorstatus = CmdResp2Error();

    if (MISD_OK != errorstatus)
    {
      return(errorstatus);
    }

    CID_Tab[0] = SDIO_GetResponse(SDIO_RESP1);
    CID_Tab[1] = SDIO_GetResponse(SDIO_RESP2);
    CID_Tab[2] = SDIO_GetResponse(SDIO_RESP3);
    CID_Tab[3] = SDIO_GetResponse(SDIO_RESP4);
  }
  if ((SDIO_STD_CAPACITY_MISD_CARD_V1_1 == CardType) ||  (SDIO_STD_CAPACITY_MISD_CARD_V2_0 == CardType) ||  (SDIO_SECURE_DIGITAL_IO_COMBO_CARD == CardType)
      ||  (SDIO_HIGH_CAPACITY_MISD_CARD == CardType))
  {
    /* Send CMD3 SET_REL_ADDR with argument 0 */
    /* SD Card publishes its RCA. */
    SDIO_CmdInitStructure.SDIO_Argument = 0x00;
    SDIO_CmdInitStructure.SDIO_CmdIndex = SDIO_SET_REL_ADDR;
    SDIO_CmdInitStructure.SDIO_Response = SDIO_Response_Short;
    SDIO_CmdInitStructure.SDIO_Wait = SDIO_Wait_No;
    SDIO_CmdInitStructure.SDIO_CPSM = SDIO_CPSM_Enable;
    SDIO_SendCommand(&SDIO_CmdInitStructure);

    errorstatus = CmdResp6Error(SDIO_SET_REL_ADDR, &rca);

    if (MISD_OK != errorstatus)
    {
      return(errorstatus);
    }
  }

  if (SDIO_SECURE_DIGITAL_IO_CARD != CardType)
  {
    RCA = rca;

    /* Send CMD9 SEND_CSD with argument as card's RCA */
    SDIO_CmdInitStructure.SDIO_Argument = (uint32_t)(rca << 16);
    SDIO_CmdInitStructure.SDIO_CmdIndex = SDIO_SEND_CSD;
    SDIO_CmdInitStructure.SDIO_Response = SDIO_Response_Long;
    SDIO_CmdInitStructure.SDIO_Wait = SDIO_Wait_No;
    SDIO_CmdInitStructure.SDIO_CPSM = SDIO_CPSM_Enable;
    SDIO_SendCommand(&SDIO_CmdInitStructure);

    errorstatus = CmdResp2Error();

    if (MISD_OK != errorstatus)
    {
      return(errorstatus);
    }

    CMISD_Tab[0] = SDIO_GetResponse(SDIO_RESP1);
    CMISD_Tab[1] = SDIO_GetResponse(SDIO_RESP2);
    CMISD_Tab[2] = SDIO_GetResponse(SDIO_RESP3);
    CMISD_Tab[3] = SDIO_GetResponse(SDIO_RESP4);
  }

  errorstatus = MISD_OK; /* All cards get intialized */

  return(errorstatus);
}

/**
  * @brief  Returns information about specific card.
  * @param cardinfo : pointer to a MISD_CardInfo structure 
  *   that contains all SD card information.
  * @retval : MISD_Error: SD Card Error code.
  */
MISD_Error MISD_GetCardInfo(MISD_CardInfo *cardinfo)
{
  MISD_Error errorstatus = MISD_OK;
  uint8_t tmp = 0;

  cardinfo->CardType = (uint8_t)CardType;
  cardinfo->RCA = (uint16_t)RCA;

  /* Byte 0 */
  tmp = (uint8_t)((CMISD_Tab[0] & 0xFF000000) >> 24);
  cardinfo->MISD_csd.CSDStruct = (tmp & 0xC0) >> 6;
  cardinfo->MISD_csd.SysSpecVersion = (tmp & 0x3C) >> 2;
  cardinfo->MISD_csd.Reserved1 = tmp & 0x03;

  /* Byte 1 */
  tmp = (uint8_t)((CMISD_Tab[0] & 0x00FF0000) >> 16);
  cardinfo->MISD_csd.TAAC = tmp;

  /* Byte 2 */
  tmp = (uint8_t)((CMISD_Tab[0] & 0x0000FF00) >> 8);
  cardinfo->MISD_csd.NSAC = tmp;

  /* Byte 3 */
  tmp = (uint8_t)(CMISD_Tab[0] & 0x000000FF);
  cardinfo->MISD_csd.MaxBusClkFrec = tmp;

  /* Byte 4 */
  tmp = (uint8_t)((CMISD_Tab[1] & 0xFF000000) >> 24);
  cardinfo->MISD_csd.CardComdClasses = tmp << 4;

  /* Byte 5 */
  tmp = (uint8_t)((CMISD_Tab[1] & 0x00FF0000) >> 16);
  cardinfo->MISD_csd.CardComdClasses |= (tmp & 0xF0) >> 4;
  cardinfo->MISD_csd.RdBlockLen = tmp & 0x0F;

  /* Byte 6 */
  tmp = (uint8_t)((CMISD_Tab[1] & 0x0000FF00) >> 8);
  cardinfo->MISD_csd.PartBlockRead = (tmp & 0x80) >> 7;
  cardinfo->MISD_csd.WrBlockMisalign = (tmp & 0x40) >> 6;
  cardinfo->MISD_csd.RdBlockMisalign = (tmp & 0x20) >> 5;
  cardinfo->MISD_csd.DSRImpl = (tmp & 0x10) >> 4;
  cardinfo->MISD_csd.Reserved2 = 0; /* Reserved */

  if ((CardType == SDIO_STD_CAPACITY_MISD_CARD_V1_1) || (CardType == SDIO_STD_CAPACITY_MISD_CARD_V2_0))
  {
    cardinfo->MISD_csd.DeviceSize = (tmp & 0x03) << 10;

    /* Byte 7 */
    tmp = (uint8_t)(CMISD_Tab[1] & 0x000000FF);
    cardinfo->MISD_csd.DeviceSize |= (tmp) << 2;

    /* Byte 8 */
    tmp = (uint8_t)((CMISD_Tab[2] & 0xFF000000) >> 24);
    cardinfo->MISD_csd.DeviceSize |= (tmp & 0xC0) >> 6;

    cardinfo->MISD_csd.MaxRdCurrentVDDMin = (tmp & 0x38) >> 3;
    cardinfo->MISD_csd.MaxRdCurrentVDDMax = (tmp & 0x07);

    /* Byte 9 */
    tmp = (uint8_t)((CMISD_Tab[2] & 0x00FF0000) >> 16);
    cardinfo->MISD_csd.MaxWrCurrentVDDMin = (tmp & 0xE0) >> 5;
    cardinfo->MISD_csd.MaxWrCurrentVDDMax = (tmp & 0x1C) >> 2;
    cardinfo->MISD_csd.DeviceSizeMul = (tmp & 0x03) << 1;
    /* Byte 10 */
    tmp = (uint8_t)((CMISD_Tab[2] & 0x0000FF00) >> 8);
    cardinfo->MISD_csd.DeviceSizeMul |= (tmp & 0x80) >> 7;
    
    cardinfo->CardCapacity = (cardinfo->MISD_csd.DeviceSize + 1) ;
    cardinfo->CardCapacity *= (1 << (cardinfo->MISD_csd.DeviceSizeMul + 2));
    cardinfo->CardBlockSize = 1 << (cardinfo->MISD_csd.RdBlockLen);
    cardinfo->CardCapacity *= cardinfo->CardBlockSize;
  }
  else if (CardType == SDIO_HIGH_CAPACITY_MISD_CARD)
  {
    /* Byte 7 */
    tmp = (uint8_t)(CMISD_Tab[1] & 0x000000FF);
    cardinfo->MISD_csd.DeviceSize = (tmp & 0x3F) << 16;

    /* Byte 8 */
    tmp = (uint8_t)((CMISD_Tab[2] & 0xFF000000) >> 24);

    cardinfo->MISD_csd.DeviceSize |= (tmp << 8);

    /* Byte 9 */
    tmp = (uint8_t)((CMISD_Tab[2] & 0x00FF0000) >> 16);

    cardinfo->MISD_csd.DeviceSize |= (tmp);

    /* Byte 10 */
    tmp = (uint8_t)((CMISD_Tab[2] & 0x0000FF00) >> 8);
    
    cardinfo->CardCapacity = (cardinfo->MISD_csd.DeviceSize + 1) * 512 * 1024;
    cardinfo->CardBlockSize = 512;    
  }


  cardinfo->MISD_csd.EraseGrSize = (tmp & 0x40) >> 6;
  cardinfo->MISD_csd.EraseGrMul = (tmp & 0x3F) << 1;

  /* Byte 11 */
  tmp = (uint8_t)(CMISD_Tab[2] & 0x000000FF);
  cardinfo->MISD_csd.EraseGrMul |= (tmp & 0x80) >> 7;
  cardinfo->MISD_csd.WrProtectGrSize = (tmp & 0x7F);

  /* Byte 12 */
  tmp = (uint8_t)((CMISD_Tab[3] & 0xFF000000) >> 24);
  cardinfo->MISD_csd.WrProtectGrEnable = (tmp & 0x80) >> 7;
  cardinfo->MISD_csd.ManDeflECC = (tmp & 0x60) >> 5;
  cardinfo->MISD_csd.WrSpeedFact = (tmp & 0x1C) >> 2;
  cardinfo->MISD_csd.MaxWrBlockLen = (tmp & 0x03) << 2;

  /* Byte 13 */
  tmp = (uint8_t)((CMISD_Tab[3] & 0x00FF0000) >> 16);
  cardinfo->MISD_csd.MaxWrBlockLen |= (tmp & 0xC0) >> 6;
  cardinfo->MISD_csd.WriteBlockPaPartial = (tmp & 0x20) >> 5;
  cardinfo->MISD_csd.Reserved3 = 0;
  cardinfo->MISD_csd.ContentProtectAppli = (tmp & 0x01);

  /* Byte 14 */
  tmp = (uint8_t)((CMISD_Tab[3] & 0x0000FF00) >> 8);
  cardinfo->MISD_csd.FileFormatGrouop = (tmp & 0x80) >> 7;
  cardinfo->MISD_csd.CopyFlag = (tmp & 0x40) >> 6;
  cardinfo->MISD_csd.PermWrProtect = (tmp & 0x20) >> 5;
  cardinfo->MISD_csd.TempWrProtect = (tmp & 0x10) >> 4;
  cardinfo->MISD_csd.FileFormat = (tmp & 0x0C) >> 2;
  cardinfo->MISD_csd.ECC = (tmp & 0x03);

  /* Byte 15 */
  tmp = (uint8_t)(CMISD_Tab[3] & 0x000000FF);
  cardinfo->MISD_csd.CMISD_CRC = (tmp & 0xFE) >> 1;
  cardinfo->MISD_csd.Reserved4 = 1;


  /* Byte 0 */
  tmp = (uint8_t)((CID_Tab[0] & 0xFF000000) >> 24);
  cardinfo->MISD_cid.ManufacturerID = tmp;

  /* Byte 1 */
  tmp = (uint8_t)((CID_Tab[0] & 0x00FF0000) >> 16);
  cardinfo->MISD_cid.OEM_AppliID = tmp << 8;

  /* Byte 2 */
  tmp = (uint8_t)((CID_Tab[0] & 0x000000FF00) >> 8);
  cardinfo->MISD_cid.OEM_AppliID |= tmp;

  /* Byte 3 */
  tmp = (uint8_t)(CID_Tab[0] & 0x000000FF);
  cardinfo->MISD_cid.ProdName1 = tmp << 24;

  /* Byte 4 */
  tmp = (uint8_t)((CID_Tab[1] & 0xFF000000) >> 24);
  cardinfo->MISD_cid.ProdName1 |= tmp << 16;

  /* Byte 5 */
  tmp = (uint8_t)((CID_Tab[1] & 0x00FF0000) >> 16);
  cardinfo->MISD_cid.ProdName1 |= tmp << 8;

  /* Byte 6 */
  tmp = (uint8_t)((CID_Tab[1] & 0x0000FF00) >> 8);
  cardinfo->MISD_cid.ProdName1 |= tmp;

  /* Byte 7 */
  tmp = (uint8_t)(CID_Tab[1] & 0x000000FF);
  cardinfo->MISD_cid.ProdName2 = tmp;

  /* Byte 8 */
  tmp = (uint8_t)((CID_Tab[2] & 0xFF000000) >> 24);
  cardinfo->MISD_cid.ProdRev = tmp;

  /* Byte 9 */
  tmp = (uint8_t)((CID_Tab[2] & 0x00FF0000) >> 16);
  cardinfo->MISD_cid.ProdSN = tmp << 24;

  /* Byte 10 */
  tmp = (uint8_t)((CID_Tab[2] & 0x0000FF00) >> 8);
  cardinfo->MISD_cid.ProdSN |= tmp << 16;

  /* Byte 11 */
  tmp = (uint8_t)(CID_Tab[2] & 0x000000FF);
  cardinfo->MISD_cid.ProdSN |= tmp << 8;

  /* Byte 12 */
  tmp = (uint8_t)((CID_Tab[3] & 0xFF000000) >> 24);
  cardinfo->MISD_cid.ProdSN |= tmp;

  /* Byte 13 */
  tmp = (uint8_t)((CID_Tab[3] & 0x00FF0000) >> 16);
  cardinfo->MISD_cid.Reserved1 |= (tmp & 0xF0) >> 4;
  cardinfo->MISD_cid.ManufactDate = (tmp & 0x0F) << 8;

  /* Byte 14 */
  tmp = (uint8_t)((CID_Tab[3] & 0x0000FF00) >> 8);
  cardinfo->MISD_cid.ManufactDate |= tmp;

  /* Byte 15 */
  tmp = (uint8_t)(CID_Tab[3] & 0x000000FF);
  cardinfo->MISD_cid.CID_CRC = (tmp & 0xFE) >> 1;
  cardinfo->MISD_cid.Reserved2 = 1;
  
  return(errorstatus);
}

/**
  * @brief  Enables wide bus opeartion for the requeseted card if 
  *   supported by card.
  * @param WideMode: Specifies the SD card wide bus mode. 
  *   This parameter can be one of the following values:
  * @arg SDIO_BusWide_8b: 8-bit data transfer (Only for MMC)
  * @arg SDIO_BusWide_4b: 4-bit data transfer
  * @arg SDIO_BusWide_1b: 1-bit data transfer
  * @retval : MISD_Error: SD Card Error code.
  */
MISD_Error MISD_EnableWideBusOperation(uint32_t WideMode)
{
  MISD_Error errorstatus = MISD_OK;

  /* MMC Card doesn't support this feature */
  if (SDIO_MULTIMEDIA_CARD == CardType)
  {
    errorstatus = MISD_UNSUPPORTED_FEATURE;
    return(errorstatus);
  }
  else if ((SDIO_STD_CAPACITY_MISD_CARD_V1_1 == CardType) || (SDIO_STD_CAPACITY_MISD_CARD_V2_0 == CardType) || (SDIO_HIGH_CAPACITY_MISD_CARD == CardType))
  {
    if (SDIO_BusWide_8b == WideMode)
    {
      errorstatus = MISD_UNSUPPORTED_FEATURE;
      return(errorstatus);
    }
    else if (SDIO_BusWide_4b == WideMode)
    {
      errorstatus = SDEnWideBus(ENABLE);

      if (MISD_OK == errorstatus)
      {
        /* Configure the SDIO peripheral */
        SDIO_InitStructure.SDIO_ClockDiv = SDIO_TRANSFER_CLK_DIV; 
        SDIO_InitStructure.SDIO_ClockEdge = SDIO_ClockEdge_Rising;
        SDIO_InitStructure.SDIO_ClockBypass = SDIO_ClockBypass_Disable;
        SDIO_InitStructure.SDIO_ClockPowerSave = SDIO_ClockPowerSave_Disable;
        SDIO_InitStructure.SDIO_BusWide = SDIO_BusWide_4b;
        SDIO_InitStructure.SDIO_HardwareFlowControl = SDIO_HardwareFlowControl_Disable;
        SDIO_Init(&SDIO_InitStructure);
      }
    }
    else
    {
      errorstatus = SDEnWideBus(DISABLE);

      if (MISD_OK == errorstatus)
      {
        /* Configure the SDIO peripheral */
        SDIO_InitStructure.SDIO_ClockDiv = SDIO_TRANSFER_CLK_DIV; 
        SDIO_InitStructure.SDIO_ClockEdge = SDIO_ClockEdge_Rising;
        SDIO_InitStructure.SDIO_ClockBypass = SDIO_ClockBypass_Disable;
        SDIO_InitStructure.SDIO_ClockPowerSave = SDIO_ClockPowerSave_Disable;
        SDIO_InitStructure.SDIO_BusWide = SDIO_BusWide_1b;
        SDIO_InitStructure.SDIO_HardwareFlowControl = SDIO_HardwareFlowControl_Disable;
        SDIO_Init(&SDIO_InitStructure);
      }
    }
  }

  return(errorstatus);
}

/**
  * @brief  Sets device mode whether to operate in Polling, Interrupt or
  *   DMA mode.
  * @param Mode: Specifies the Data Transfer mode.
  *   This parameter can be one of the following values:
  * @arg MISD_DMA_MODE: Data transfer using DMA.
  * @arg MISD_INTERRUPT_MODE: Data transfer using interrupts.
  * @arg MISD_POLLING_MODE: Data transfer using flags.
  * @retval : MISD_Error: SD Card Error code.
  */
MISD_Error MISD_SetDeviceMode(uint32_t Mode)
{
  MISD_Error errorstatus = MISD_OK;

  if ((Mode == MISD_DMA_MODE) || (Mode == MISD_INTERRUPT_MODE) || (Mode == MISD_POLLING_MODE))
  {
    DeviceMode = Mode;
  }
  else
  {
    errorstatus = MISD_INVALID_PARAMETER;
  }
  return(errorstatus);

}

/**
  * @brief  Selects od Deselects the corresponding card.
  * @param addr: Address of the Card to be selected.
  * @retval : MISD_Error: SD Card Error code.
  */
MISD_Error MISD_SelectDeselect(uint32_t addr)
{
  MISD_Error errorstatus = MISD_OK;

  /* Send CMD7 SDIO_SEL_DESEL_CARD */
  SDIO_CmdInitStructure.SDIO_Argument =  addr;
  SDIO_CmdInitStructure.SDIO_CmdIndex = SDIO_SEL_DESEL_CARD;
  SDIO_CmdInitStructure.SDIO_Response = SDIO_Response_Short;
  SDIO_CmdInitStructure.SDIO_Wait = SDIO_Wait_No;
  SDIO_CmdInitStructure.SDIO_CPSM = SDIO_CPSM_Enable;
  SDIO_SendCommand(&SDIO_CmdInitStructure);

  errorstatus = CmdResp1Error(SDIO_SEL_DESEL_CARD);

  return(errorstatus);
}

/**
  * @brief  Allows to read one block from a specified address in a card.
  * @param addr: Address from where data are to be read.
  * @param readbuff: pointer to the buffer that will contain the 
  *   received data
  * @param BlockSize: the SD card Data block size.
  * @retval : MISD_Error: SD Card Error code.
  */
MISD_Error MISD_ReadBlock(uint32_t addr, uint32_t *readbuff, uint16_t BlockSize)
{
  MISD_Error errorstatus = MISD_OK;
  uint32_t count = 0, *tempbuff = readbuff;
  uint8_t power = 0;

  if (NULL == readbuff)
  {
    errorstatus = MISD_INVALID_PARAMETER;
    return(errorstatus);
  }

  SDTransferError = MISD_OK;
  SDTransferEnd = 0;
  TotalSDNumberOfBytes = 0;

  /* Clear all DPSM configuration */
  SDIO_DataInitStructure.SDIO_DataTimeOut = MISD_DATATIMEOUT;
  SDIO_DataInitStructure.SDIO_DataLength = 0;
  SDIO_DataInitStructure.SDIO_DataBlockSize = SDIO_DataBlockSize_1b;
  SDIO_DataInitStructure.SDIO_TransferDir = SDIO_TransferDir_ToCard;
  SDIO_DataInitStructure.SDIO_TransferMode = SDIO_TransferMode_Block;
  SDIO_DataInitStructure.SDIO_DPSM = SDIO_DPSM_Disable;
  SDIO_DataConfig(&SDIO_DataInitStructure);
  SDIO_DMACmd(DISABLE);

  if (SDIO_GetResponse(SDIO_RESP1) & MISD_CARD_LOCKED)
  {
    errorstatus = MISD_LOCK_UNLOCK_FAILED;
    return(errorstatus);
  }
  
  if (CardType == SDIO_HIGH_CAPACITY_MISD_CARD)
  {
    BlockSize = 512;
    addr /= 512;
  }
  if ((BlockSize > 0) && (BlockSize <= 2048) && ((BlockSize & (BlockSize - 1)) == 0))
  {
    power = convert_from_bytes_to_power_of_two(BlockSize);

    /* Set Block Size for Card */
    SDIO_CmdInitStructure.SDIO_Argument = (uint32_t) BlockSize;
    SDIO_CmdInitStructure.SDIO_CmdIndex = SDIO_SET_BLOCKLEN;
    SDIO_CmdInitStructure.SDIO_Response = SDIO_Response_Short;
    SDIO_CmdInitStructure.SDIO_Wait = SDIO_Wait_No;
    SDIO_CmdInitStructure.SDIO_CPSM = SDIO_CPSM_Enable;
    SDIO_SendCommand(&SDIO_CmdInitStructure);

    errorstatus = CmdResp1Error(SDIO_SET_BLOCKLEN);

    if (MISD_OK != errorstatus)
    {
      return(errorstatus);
    }
  }
  else
  {
    errorstatus = MISD_INVALID_PARAMETER;
    return(errorstatus);
  }

  SDIO_DataInitStructure.SDIO_DataTimeOut = MISD_DATATIMEOUT;
  SDIO_DataInitStructure.SDIO_DataLength = BlockSize;
  SDIO_DataInitStructure.SDIO_DataBlockSize = (uint32_t) power << 4;
  SDIO_DataInitStructure.SDIO_TransferDir = SDIO_TransferDir_ToSDIO;
  SDIO_DataInitStructure.SDIO_TransferMode = SDIO_TransferMode_Block;
  SDIO_DataInitStructure.SDIO_DPSM = SDIO_DPSM_Enable;
  SDIO_DataConfig(&SDIO_DataInitStructure);

  TotalSDNumberOfBytes = BlockSize;
  StopCondition = 0;
  DestBuffer = readbuff;

  /* Send CMD17 READ_SINGLE_BLOCK */
  SDIO_CmdInitStructure.SDIO_Argument = (uint32_t)addr;
  SDIO_CmdInitStructure.SDIO_CmdIndex = SDIO_READ_SINGLE_BLOCK;
  SDIO_CmdInitStructure.SDIO_Response = SDIO_Response_Short;
  SDIO_CmdInitStructure.SDIO_Wait = SDIO_Wait_No;
  SDIO_CmdInitStructure.SDIO_CPSM = SDIO_CPSM_Enable;
  SDIO_SendCommand(&SDIO_CmdInitStructure);

  errorstatus = CmdResp1Error(SDIO_READ_SINGLE_BLOCK);

  if (errorstatus != MISD_OK)
  {
    return(errorstatus);
  }
  /* In case of single block transfer, no need of stop transfer at all.*/
  if (DeviceMode == MISD_POLLING_MODE)
  {
    /* Polling mode */
    while (!(SDIO->STA &(SDIO_FLAG_RXOVERR | SDIO_FLAG_DCRCFAIL | SDIO_FLAG_DTIMEOUT | SDIO_FLAG_DBCKEND | SDIO_FLAG_STBITERR)))
    {
      if (SDIO_GetFlagStatus(SDIO_FLAG_RXFIFOHF) != RESET)
      {
        for (count = 0; count < 8; count++)
        {
          *(tempbuff + count) = SDIO_ReadData();
        }
        tempbuff += 8;
      }
    }

    if (SDIO_GetFlagStatus(SDIO_FLAG_DTIMEOUT) != RESET)
    {
      SDIO_ClearFlag(SDIO_FLAG_DTIMEOUT);
      errorstatus = MISD_DATA_TIMEOUT;
      return(errorstatus);
    }
    else if (SDIO_GetFlagStatus(SDIO_FLAG_DCRCFAIL) != RESET)
    {
      SDIO_ClearFlag(SDIO_FLAG_DCRCFAIL);
      errorstatus = MISD_DATA_CRC_FAIL;
      return(errorstatus);
    }
    else if (SDIO_GetFlagStatus(SDIO_FLAG_RXOVERR) != RESET)
    {
      SDIO_ClearFlag(SDIO_FLAG_RXOVERR);
      errorstatus = MISD_RX_OVERRUN;
      return(errorstatus);
    }
    else if (SDIO_GetFlagStatus(SDIO_FLAG_STBITERR) != RESET)
    {
      SDIO_ClearFlag(SDIO_FLAG_STBITERR);
      errorstatus = MISD_START_BIT_ERR;
      return(errorstatus);
    }
    while (SDIO_GetFlagStatus(SDIO_FLAG_RXDAVL) != RESET)
    {
      *tempbuff = SDIO_ReadData();
      tempbuff++;
    }

    /* Clear all the static flags */
    SDIO_ClearFlag(SDIO_STATIC_FLAGS);
  }
  else if (DeviceMode == MISD_INTERRUPT_MODE)
  {
    SDIO_ITConfig(SDIO_IT_DCRCFAIL | SDIO_IT_DTIMEOUT | SDIO_IT_DATAEND | SDIO_IT_RXOVERR | SDIO_IT_RXFIFOHF | SDIO_IT_STBITERR, ENABLE);
    while ((SDTransferEnd == 0) && (SDTransferError == MISD_OK))
    {}
    if (SDTransferError != MISD_OK)
    {
      return(SDTransferError);
    }
  }
  else if (DeviceMode == MISD_DMA_MODE)
  {
    SDIO_ITConfig(SDIO_IT_DCRCFAIL | SDIO_IT_DTIMEOUT | SDIO_IT_DATAEND | SDIO_IT_RXOVERR | SDIO_IT_STBITERR, ENABLE);
    SDIO_DMACmd(ENABLE);
    DMA_RxConfiguration(readbuff, BlockSize);
    while (DMA_GetFlagStatus(DMA2_FLAG_TC4) == RESET)
    {}
  }
  return(errorstatus);
}

/**
  * @brief  Allows to read blocks from a specified address  in a card.
  * @param addr: Address from where data are to be read.
  * @param readbuff: pointer to the buffer that will contain the 
  *   received data.
  * @param BlockSize: the SD card Data block size.
  * @param NumberOfBlocks: number of blocks to be read.
  * @retval : MISD_Error: SD Card Error code.
  */
MISD_Error MISD_ReadMultiBlocks(uint32_t addr, uint32_t *readbuff, uint16_t BlockSize, uint32_t NumberOfBlocks)
{
  MISD_Error errorstatus = MISD_OK;
  uint32_t count = 0, *tempbuff = readbuff;
  uint8_t power = 0;

  if (NULL == readbuff)
  {
    errorstatus = MISD_INVALID_PARAMETER;
    return(errorstatus);
  }

  SDTransferError = MISD_OK;
  SDTransferEnd = 0;
  TotalSDNumberOfBytes = 0;

  /* Clear all DPSM configuration */
  SDIO_DataInitStructure.SDIO_DataTimeOut = MISD_DATATIMEOUT;
  SDIO_DataInitStructure.SDIO_DataLength = 0;
  SDIO_DataInitStructure.SDIO_DataBlockSize = SDIO_DataBlockSize_1b;
  SDIO_DataInitStructure.SDIO_TransferDir = SDIO_TransferDir_ToCard;
  SDIO_DataInitStructure.SDIO_TransferMode = SDIO_TransferMode_Block;
  SDIO_DataInitStructure.SDIO_DPSM = SDIO_DPSM_Disable;
  SDIO_DataConfig(&SDIO_DataInitStructure);
  SDIO_DMACmd(DISABLE);

  if (SDIO_GetResponse(SDIO_RESP1) & MISD_CARD_LOCKED)
  {
    errorstatus = MISD_LOCK_UNLOCK_FAILED;
    return(errorstatus);
  }

  if (CardType == SDIO_HIGH_CAPACITY_MISD_CARD)
  {
    BlockSize = 512;
    addr /= 512;
  }
  
  if ((BlockSize > 0) && (BlockSize <= 2048) && (0 == (BlockSize & (BlockSize - 1))))
  {
    power = convert_from_bytes_to_power_of_two(BlockSize);

    /* Set Block Size for Card */
    SDIO_CmdInitStructure.SDIO_Argument = (uint32_t) BlockSize;
    SDIO_CmdInitStructure.SDIO_CmdIndex = SDIO_SET_BLOCKLEN;
    SDIO_CmdInitStructure.SDIO_Response = SDIO_Response_Short;
    SDIO_CmdInitStructure.SDIO_Wait = SDIO_Wait_No;
    SDIO_CmdInitStructure.SDIO_CPSM = SDIO_CPSM_Enable;
    SDIO_SendCommand(&SDIO_CmdInitStructure);

    errorstatus = CmdResp1Error(SDIO_SET_BLOCKLEN);

    if (MISD_OK != errorstatus)
    {
      return(errorstatus);
    }
  }
  else
  {
    errorstatus = MISD_INVALID_PARAMETER;
    return(errorstatus);
  }

  if (NumberOfBlocks > 1)
  {
    /* Common to all modes */
    if (NumberOfBlocks * BlockSize > MISD_MAX_DATA_LENGTH)
    {
      errorstatus = MISD_INVALID_PARAMETER;
      return(errorstatus);
    }

    TotalSDNumberOfBytes = NumberOfBlocks * BlockSize;
    StopCondition = 1;
    DestBuffer = readbuff;

    SDIO_DataInitStructure.SDIO_DataTimeOut = MISD_DATATIMEOUT;
    SDIO_DataInitStructure.SDIO_DataLength = NumberOfBlocks * BlockSize;
    SDIO_DataInitStructure.SDIO_DataBlockSize = (uint32_t) power << 4;
    SDIO_DataInitStructure.SDIO_TransferDir = SDIO_TransferDir_ToSDIO;
    SDIO_DataInitStructure.SDIO_TransferMode = SDIO_TransferMode_Block;
    SDIO_DataInitStructure.SDIO_DPSM = SDIO_DPSM_Enable;
    SDIO_DataConfig(&SDIO_DataInitStructure);

    /* Send CMD18 READ_MULT_BLOCK with argument data address */
    SDIO_CmdInitStructure.SDIO_Argument = (uint32_t)addr;
    SDIO_CmdInitStructure.SDIO_CmdIndex = SDIO_READ_MULT_BLOCK;
    SDIO_CmdInitStructure.SDIO_Response = SDIO_Response_Short;
    SDIO_CmdInitStructure.SDIO_Wait = SDIO_Wait_No;
    SDIO_CmdInitStructure.SDIO_CPSM = SDIO_CPSM_Enable;
    SDIO_SendCommand(&SDIO_CmdInitStructure);

    errorstatus = CmdResp1Error(SDIO_READ_MULT_BLOCK);

    if (errorstatus != MISD_OK)
    {
      return(errorstatus);
    }

    if (DeviceMode == MISD_POLLING_MODE)
    {
      /* Polling mode */
      while (!(SDIO->STA &(SDIO_FLAG_RXOVERR | SDIO_FLAG_DCRCFAIL | SDIO_FLAG_DATAEND | SDIO_FLAG_DTIMEOUT | SDIO_FLAG_STBITERR)))
      {
        if (SDIO_GetFlagStatus(SDIO_FLAG_RXFIFOHF) != RESET)
        {
          for (count = 0; count < MISD_HALFFIFO; count++)
          {
            *(tempbuff + count) = SDIO_ReadData();
          }
          tempbuff += MISD_HALFFIFO;
        }
      }

      if (SDIO_GetFlagStatus(SDIO_FLAG_DTIMEOUT) != RESET)
      {
        SDIO_ClearFlag(SDIO_FLAG_DTIMEOUT);
        errorstatus = MISD_DATA_TIMEOUT;
        return(errorstatus);
      }
      else if (SDIO_GetFlagStatus(SDIO_FLAG_DCRCFAIL) != RESET)
      {
        SDIO_ClearFlag(SDIO_FLAG_DCRCFAIL);
        errorstatus = MISD_DATA_CRC_FAIL;
        return(errorstatus);
      }
      else if (SDIO_GetFlagStatus(SDIO_FLAG_RXOVERR) != RESET)
      {
        SDIO_ClearFlag(SDIO_FLAG_RXOVERR);
        errorstatus = MISD_RX_OVERRUN;
        return(errorstatus);
      }
      else if (SDIO_GetFlagStatus(SDIO_FLAG_STBITERR) != RESET)
      {
        SDIO_ClearFlag(SDIO_FLAG_STBITERR);
        errorstatus = MISD_START_BIT_ERR;
        return(errorstatus);
      }
      while (SDIO_GetFlagStatus(SDIO_FLAG_RXDAVL) != RESET)
      {
        *tempbuff = SDIO_ReadData();
        tempbuff++;
      }

      if (SDIO_GetFlagStatus(SDIO_FLAG_DATAEND) != RESET)
      {
        /* In Case Of SD-CARD Send Command STOP_TRANSMISSION */
        if ((SDIO_STD_CAPACITY_MISD_CARD_V1_1 == CardType) || (SDIO_HIGH_CAPACITY_MISD_CARD == CardType) || (SDIO_STD_CAPACITY_MISD_CARD_V2_0 == CardType))
        {
          /* Send CMD12 STOP_TRANSMISSION */
          SDIO_CmdInitStructure.SDIO_Argument = 0x0;
          SDIO_CmdInitStructure.SDIO_CmdIndex = SDIO_STOP_TRANSMISSION;
          SDIO_CmdInitStructure.SDIO_Response = SDIO_Response_Short;
          SDIO_CmdInitStructure.SDIO_Wait = SDIO_Wait_No;
          SDIO_CmdInitStructure.SDIO_CPSM = SDIO_CPSM_Enable;
          SDIO_SendCommand(&SDIO_CmdInitStructure);

          errorstatus = CmdResp1Error(SDIO_STOP_TRANSMISSION);

          if (errorstatus != MISD_OK)
          {
            return(errorstatus);
          }
        }
      }
      /* Clear all the static flags */
      SDIO_ClearFlag(SDIO_STATIC_FLAGS);
    }
    else if (DeviceMode == MISD_INTERRUPT_MODE)
    {
      SDIO_ITConfig(SDIO_IT_DCRCFAIL | SDIO_IT_DTIMEOUT | SDIO_IT_DATAEND | SDIO_IT_RXOVERR | SDIO_IT_RXFIFOHF | SDIO_IT_STBITERR, ENABLE);
      while ((SDTransferEnd == 0) && (SDTransferError == MISD_OK))
      {}
      if (SDTransferError != MISD_OK)
      {
        return(SDTransferError);
      }
    }
    else if (DeviceMode == MISD_DMA_MODE)
    {
      SDIO_ITConfig(SDIO_IT_DCRCFAIL | SDIO_IT_DTIMEOUT | SDIO_IT_DATAEND | SDIO_IT_RXOVERR | SDIO_IT_STBITERR, ENABLE);
      SDIO_DMACmd(ENABLE);
      DMA_RxConfiguration(readbuff, (NumberOfBlocks * BlockSize));
      while (DMA_GetFlagStatus(DMA2_FLAG_TC4) == RESET)
      {}
      while ((SDTransferEnd == 0) && (SDTransferError == MISD_OK))
      {}
      if (SDTransferError != MISD_OK)
      {
        return(SDTransferError);
      }
    }
  }
  return(errorstatus);
}

/**
  * @brief  Allows to write one block starting from a specified address 
  *   in a card.
  * @param addr: Address from where data are to be read.
  * @param writebuff: pointer to the buffer that contain the data to be
  *   transferred.
  * @param BlockSize: the SD card Data block size.
  * @retval : MISD_Error: SD Card Error code.
  */
MISD_Error MISD_WriteBlock(uint32_t addr, uint32_t *writebuff, uint16_t BlockSize)
{
  MISD_Error errorstatus = MISD_OK;
  uint8_t  power = 0, cardstate = 0;
  uint32_t timeout = 0, bytestransferred = 0;
  uint32_t cardstatus = 0, count = 0, restwords = 0;
  uint32_t *tempbuff = writebuff;

  if (writebuff == NULL)
  {
    errorstatus = MISD_INVALID_PARAMETER;
    return(errorstatus);
  }

  SDTransferError = MISD_OK;
  SDTransferEnd = 0;
  TotalSDNumberOfBytes = 0;

  SDIO_DataInitStructure.SDIO_DataTimeOut = MISD_DATATIMEOUT;
  SDIO_DataInitStructure.SDIO_DataLength = 0;
  SDIO_DataInitStructure.SDIO_DataBlockSize = SDIO_DataBlockSize_1b;
  SDIO_DataInitStructure.SDIO_TransferDir = SDIO_TransferDir_ToCard;
  SDIO_DataInitStructure.SDIO_TransferMode = SDIO_TransferMode_Block;
  SDIO_DataInitStructure.SDIO_DPSM = SDIO_DPSM_Disable;
  SDIO_DataConfig(&SDIO_DataInitStructure);
  SDIO_DMACmd(DISABLE);

  if (SDIO_GetResponse(SDIO_RESP1) & MISD_CARD_LOCKED)
  {
    errorstatus = MISD_LOCK_UNLOCK_FAILED;
    return(errorstatus);
  }

  if (CardType == SDIO_HIGH_CAPACITY_MISD_CARD)
  {
    BlockSize = 512;
    addr /= 512;
  }
  
  /* Set the block size, both on controller and card */
  if ((BlockSize > 0) && (BlockSize <= 2048) && ((BlockSize & (BlockSize - 1)) == 0))
  {
    power = convert_from_bytes_to_power_of_two(BlockSize);

    SDIO_CmdInitStructure.SDIO_Argument = (uint32_t) BlockSize;
    SDIO_CmdInitStructure.SDIO_CmdIndex = SDIO_SET_BLOCKLEN;
    SDIO_CmdInitStructure.SDIO_Response = SDIO_Response_Short;
    SDIO_CmdInitStructure.SDIO_Wait = SDIO_Wait_No;
    SDIO_CmdInitStructure.SDIO_CPSM = SDIO_CPSM_Enable;
    SDIO_SendCommand(&SDIO_CmdInitStructure);

    errorstatus = CmdResp1Error(SDIO_SET_BLOCKLEN);

    if (errorstatus != MISD_OK)
    {
      return(errorstatus);
    }
  }
  else
  {
    errorstatus = MISD_INVALID_PARAMETER;
    return(errorstatus);
  }

  /* Wait till card is ready for data Added */
  SDIO_CmdInitStructure.SDIO_Argument = (uint32_t) (RCA << 16);
  SDIO_CmdInitStructure.SDIO_CmdIndex = SDIO_SEND_STATUS;
  SDIO_CmdInitStructure.SDIO_Response = SDIO_Response_Short;
  SDIO_CmdInitStructure.SDIO_Wait = SDIO_Wait_No;
  SDIO_CmdInitStructure.SDIO_CPSM = SDIO_CPSM_Enable;
  SDIO_SendCommand(&SDIO_CmdInitStructure);

  errorstatus = CmdResp1Error(SDIO_SEND_STATUS);

  if (errorstatus != MISD_OK)
  {
    return(errorstatus);
  }

  cardstatus = SDIO_GetResponse(SDIO_RESP1);

  timeout = MISD_DATATIMEOUT;

  while (((cardstatus & 0x00000100) == 0) && (timeout > 0))
  {
    timeout--;
    SDIO_CmdInitStructure.SDIO_Argument = (uint32_t) (RCA << 16);
    SDIO_CmdInitStructure.SDIO_CmdIndex = SDIO_SEND_STATUS;
    SDIO_CmdInitStructure.SDIO_Response = SDIO_Response_Short;
    SDIO_CmdInitStructure.SDIO_Wait = SDIO_Wait_No;
    SDIO_CmdInitStructure.SDIO_CPSM = SDIO_CPSM_Enable;
    SDIO_SendCommand(&SDIO_CmdInitStructure);

    errorstatus = CmdResp1Error(SDIO_SEND_STATUS);

    if (errorstatus != MISD_OK)
    {
      return(errorstatus);
    }
    cardstatus = SDIO_GetResponse(SDIO_RESP1);
  }

  if (timeout == 0)
  {
    return(MISD_ERROR);
  }

  /* Send CMD24 WRITE_SINGLE_BLOCK */
  SDIO_CmdInitStructure.SDIO_Argument = addr;
  SDIO_CmdInitStructure.SDIO_CmdIndex = SDIO_WRITE_SINGLE_BLOCK;
  SDIO_CmdInitStructure.SDIO_Response = SDIO_Response_Short;
  SDIO_CmdInitStructure.SDIO_Wait = SDIO_Wait_No;
  SDIO_CmdInitStructure.SDIO_CPSM = SDIO_CPSM_Enable;
  SDIO_SendCommand(&SDIO_CmdInitStructure);

  errorstatus = CmdResp1Error(SDIO_WRITE_SINGLE_BLOCK);

  if (errorstatus != MISD_OK)
  {
    return(errorstatus);
  }

  TotalSDNumberOfBytes = BlockSize;
  StopCondition = 0;
  SrcBuffer = writebuff;

  SDIO_DataInitStructure.SDIO_DataTimeOut = MISD_DATATIMEOUT;
  SDIO_DataInitStructure.SDIO_DataLength = BlockSize;
  SDIO_DataInitStructure.SDIO_DataBlockSize = (uint32_t) power << 4;
  SDIO_DataInitStructure.SDIO_TransferDir = SDIO_TransferDir_ToCard;
  SDIO_DataInitStructure.SDIO_TransferMode = SDIO_TransferMode_Block;
  SDIO_DataInitStructure.SDIO_DPSM = SDIO_DPSM_Enable;
  SDIO_DataConfig(&SDIO_DataInitStructure);

  /* In case of single data block transfer no need of stop command at all */
  if (DeviceMode == MISD_POLLING_MODE)
  {
    while (!(SDIO->STA & (SDIO_FLAG_DBCKEND | SDIO_FLAG_TXUNDERR | SDIO_FLAG_DCRCFAIL | SDIO_FLAG_DTIMEOUT | SDIO_FLAG_STBITERR)))
    {
      if (SDIO_GetFlagStatus(SDIO_FLAG_TXFIFOHE) != RESET)
      {
        if ((TotalSDNumberOfBytes - bytestransferred) < 32)
        {
          restwords = ((TotalSDNumberOfBytes - bytestransferred) % 4 == 0) ? ((TotalSDNumberOfBytes - bytestransferred) / 4) : (( TotalSDNumberOfBytes -  bytestransferred) / 4 + 1);

          for (count = 0; count < restwords; count++, tempbuff++, bytestransferred += 4)
          {
            SDIO_WriteData(*tempbuff);
          }
        }
        else
        {
          for (count = 0; count < 8; count++)
          {
            SDIO_WriteData(*(tempbuff + count));
          }
          tempbuff += 8;
          bytestransferred += 32;
        }
      }
    }
    if (SDIO_GetFlagStatus(SDIO_FLAG_DTIMEOUT) != RESET)
    {
      SDIO_ClearFlag(SDIO_FLAG_DTIMEOUT);
      errorstatus = MISD_DATA_TIMEOUT;
      return(errorstatus);
    }
    else if (SDIO_GetFlagStatus(SDIO_FLAG_DCRCFAIL) != RESET)
    {
      SDIO_ClearFlag(SDIO_FLAG_DCRCFAIL);
      errorstatus = MISD_DATA_CRC_FAIL;
      return(errorstatus);
    }
    else if (SDIO_GetFlagStatus(SDIO_FLAG_TXUNDERR) != RESET)
    {
      SDIO_ClearFlag(SDIO_FLAG_TXUNDERR);
      errorstatus = MISD_TX_UNDERRUN;
      return(errorstatus);
    }
    else if (SDIO_GetFlagStatus(SDIO_FLAG_STBITERR) != RESET)
    {
      SDIO_ClearFlag(SDIO_FLAG_STBITERR);
      errorstatus = MISD_START_BIT_ERR;
      return(errorstatus);
    }
  }
  else if (DeviceMode == MISD_INTERRUPT_MODE)
  {
    SDIO_ITConfig(SDIO_IT_DCRCFAIL | SDIO_IT_DTIMEOUT | SDIO_IT_DATAEND | SDIO_FLAG_TXFIFOHE | SDIO_IT_TXUNDERR | SDIO_IT_STBITERR, ENABLE);
    while ((SDTransferEnd == 0) && (SDTransferError == MISD_OK))
    {}
    if (SDTransferError != MISD_OK)
    {
      return(SDTransferError);
    }
  }
  else if (DeviceMode == MISD_DMA_MODE)
  {
    SDIO_ITConfig(SDIO_IT_DCRCFAIL | SDIO_IT_DTIMEOUT | SDIO_IT_DATAEND | SDIO_IT_TXUNDERR | SDIO_IT_STBITERR, ENABLE);
    DMA_TxConfiguration(writebuff, BlockSize);
    SDIO_DMACmd(ENABLE);
    while (DMA_GetFlagStatus(DMA2_FLAG_TC4) == RESET)
    {}
    while ((SDTransferEnd == 0) && (SDTransferError == MISD_OK))
    {}
    if (SDTransferError != MISD_OK)
    {
      return(SDTransferError);
    }
  }

  /* Clear all the static flags */
  SDIO_ClearFlag(SDIO_STATIC_FLAGS);

  /* Wait till the card is in programming state */
  errorstatus = IsCardProgramming(&cardstate);

  while ((errorstatus == MISD_OK) && ((cardstate == MISD_CARD_PROGRAMMING) || (cardstate == MISD_CARD_RECEIVING)))
  {
    errorstatus = IsCardProgramming(&cardstate);
  }

  return(errorstatus);
}

/**
  * @brief  Allows to write blocks starting from a specified address in 
  *   a card.
  * @param addr: Address from where data are to be read.
  * @param writebuff: pointer to the buffer that contain the data to be
  *   transferred.
  * @param BlockSize: the SD card Data block size.
  * @param NumberOfBlocks: number of blocks to be written.
  * @retval : MISD_Error: SD Card Error code.
  */
MISD_Error MISD_WriteMultiBlocks(uint32_t addr, uint32_t *writebuff, uint16_t BlockSize, uint32_t NumberOfBlocks)
{
  MISD_Error errorstatus = MISD_OK;
  uint8_t  power = 0, cardstate = 0;
  uint32_t bytestransferred = 0;
  uint32_t count = 0, restwords = 0;
  uint32_t *tempbuff = writebuff;

  if (writebuff == NULL)
  {
    errorstatus = MISD_INVALID_PARAMETER;
    return(errorstatus);
  }

  SDTransferError = MISD_OK;
  SDTransferEnd = 0;
  TotalSDNumberOfBytes = 0;

  SDIO_DataInitStructure.SDIO_DataTimeOut = MISD_DATATIMEOUT;
  SDIO_DataInitStructure.SDIO_DataLength = 0;
  SDIO_DataInitStructure.SDIO_DataBlockSize = SDIO_DataBlockSize_1b;
  SDIO_DataInitStructure.SDIO_TransferDir = SDIO_TransferDir_ToCard;
  SDIO_DataInitStructure.SDIO_TransferMode = SDIO_TransferMode_Block;
  SDIO_DataInitStructure.SDIO_DPSM = SDIO_DPSM_Disable;
  SDIO_DataConfig(&SDIO_DataInitStructure);
  SDIO_DMACmd(DISABLE);

  if (SDIO_GetResponse(SDIO_RESP1) & MISD_CARD_LOCKED)
  {
    errorstatus = MISD_LOCK_UNLOCK_FAILED;
    return(errorstatus);
  }

  if (CardType == SDIO_HIGH_CAPACITY_MISD_CARD)
  {
    BlockSize = 512;
    addr /= 512;
  }
  
  /* Set the block size, both on controller and card */
  if ((BlockSize > 0) && (BlockSize <= 2048) && ((BlockSize & (BlockSize - 1)) == 0))
  {
    power = convert_from_bytes_to_power_of_two(BlockSize);

    SDIO_CmdInitStructure.SDIO_Argument = (uint32_t) BlockSize;
    SDIO_CmdInitStructure.SDIO_CmdIndex = SDIO_SET_BLOCKLEN;
    SDIO_CmdInitStructure.SDIO_Response = SDIO_Response_Short;
    SDIO_CmdInitStructure.SDIO_Wait = SDIO_Wait_No;
    SDIO_CmdInitStructure.SDIO_CPSM = SDIO_CPSM_Enable;
    SDIO_SendCommand(&SDIO_CmdInitStructure);

    errorstatus = CmdResp1Error(SDIO_SET_BLOCKLEN);

    if (errorstatus != MISD_OK)
    {
      return(errorstatus);
    }
  }
  else
  {
    errorstatus = MISD_INVALID_PARAMETER;
    return(errorstatus);
  }

  /* Wait till card is ready for data Added */
  SDIO_CmdInitStructure.SDIO_Argument = (uint32_t) (RCA << 16);
  SDIO_CmdInitStructure.SDIO_CmdIndex = SDIO_SEND_STATUS;
  SDIO_CmdInitStructure.SDIO_Response = SDIO_Response_Short;
  SDIO_CmdInitStructure.SDIO_Wait = SDIO_Wait_No;
  SDIO_CmdInitStructure.SDIO_CPSM = SDIO_CPSM_Enable;
  SDIO_SendCommand(&SDIO_CmdInitStructure);

  errorstatus = CmdResp1Error(SDIO_SEND_STATUS);

  if (errorstatus != MISD_OK)
  {
    return(errorstatus);
  }

  if (NumberOfBlocks > 1)
  {
    /* Common to all modes */
    if (NumberOfBlocks * BlockSize > MISD_MAX_DATA_LENGTH)
    {
      errorstatus = MISD_INVALID_PARAMETER;
      return(errorstatus);
    }

    if ((SDIO_STD_CAPACITY_MISD_CARD_V1_1 == CardType) || (SDIO_STD_CAPACITY_MISD_CARD_V2_0 == CardType) || (SDIO_HIGH_CAPACITY_MISD_CARD == CardType))
    {
      /* To improve performance */
      SDIO_CmdInitStructure.SDIO_Argument = (uint32_t) (RCA << 16);
      SDIO_CmdInitStructure.SDIO_CmdIndex = SDIO_APP_CMD;
      SDIO_CmdInitStructure.SDIO_Response = SDIO_Response_Short;
      SDIO_CmdInitStructure.SDIO_Wait = SDIO_Wait_No;
      SDIO_CmdInitStructure.SDIO_CPSM = SDIO_CPSM_Enable;
      SDIO_SendCommand(&SDIO_CmdInitStructure);


      errorstatus = CmdResp1Error(SDIO_APP_CMD);

      if (errorstatus != MISD_OK)
      {
        return(errorstatus);
      }
      /* To improve performance */
      SDIO_CmdInitStructure.SDIO_Argument = (uint32_t)NumberOfBlocks;
      SDIO_CmdInitStructure.SDIO_CmdIndex = SDIO_SET_BLOCK_COUNT;
      SDIO_CmdInitStructure.SDIO_Response = SDIO_Response_Short;
      SDIO_CmdInitStructure.SDIO_Wait = SDIO_Wait_No;
      SDIO_CmdInitStructure.SDIO_CPSM = SDIO_CPSM_Enable;
      SDIO_SendCommand(&SDIO_CmdInitStructure);

      errorstatus = CmdResp1Error(SDIO_SET_BLOCK_COUNT);

      if (errorstatus != MISD_OK)
      {
        return(errorstatus);
      }
    }

    /* Send CMD25 WRITE_MULT_BLOCK with argument data address */
    SDIO_CmdInitStructure.SDIO_Argument = (uint32_t)addr;
    SDIO_CmdInitStructure.SDIO_CmdIndex = SDIO_WRITE_MULT_BLOCK;
    SDIO_CmdInitStructure.SDIO_Response = SDIO_Response_Short;
    SDIO_CmdInitStructure.SDIO_Wait = SDIO_Wait_No;
    SDIO_CmdInitStructure.SDIO_CPSM = SDIO_CPSM_Enable;
    SDIO_SendCommand(&SDIO_CmdInitStructure);

    errorstatus = CmdResp1Error(SDIO_WRITE_MULT_BLOCK);

    if (MISD_OK != errorstatus)
    {
      return(errorstatus);
    }

    TotalSDNumberOfBytes = NumberOfBlocks * BlockSize;
    StopCondition = 1;
    SrcBuffer = writebuff;

    SDIO_DataInitStructure.SDIO_DataTimeOut = MISD_DATATIMEOUT;
    SDIO_DataInitStructure.SDIO_DataLength = NumberOfBlocks * BlockSize;
    SDIO_DataInitStructure.SDIO_DataBlockSize = (uint32_t) power << 4;
    SDIO_DataInitStructure.SDIO_TransferDir = SDIO_TransferDir_ToCard;
    SDIO_DataInitStructure.SDIO_TransferMode = SDIO_TransferMode_Block;
    SDIO_DataInitStructure.SDIO_DPSM = SDIO_DPSM_Enable;
    SDIO_DataConfig(&SDIO_DataInitStructure);

    if (DeviceMode == MISD_POLLING_MODE)
    {
      while (!(SDIO->STA & (SDIO_FLAG_TXUNDERR | SDIO_FLAG_DCRCFAIL | SDIO_FLAG_DATAEND | SDIO_FLAG_DTIMEOUT | SDIO_FLAG_STBITERR)))
      {
        if (SDIO_GetFlagStatus(SDIO_FLAG_TXFIFOHE) != RESET)
        {
          if (!((TotalSDNumberOfBytes - bytestransferred) < MISD_HALFFIFOBYTES))
          {
            for (count = 0; count < MISD_HALFFIFO; count++)
            {
              SDIO_WriteData(*(tempbuff + count));
            }
            tempbuff += MISD_HALFFIFO;
            bytestransferred += MISD_HALFFIFOBYTES;
          }
          else
          {
            restwords = ((TotalSDNumberOfBytes - bytestransferred) % 4 == 0) ? ((TotalSDNumberOfBytes - bytestransferred) / 4) :
                        ((TotalSDNumberOfBytes - bytestransferred) / 4 + 1);

            for (count = 0; count < restwords; count++, tempbuff++, bytestransferred += 4)
            {
              SDIO_WriteData(*tempbuff);
            }
          }
        }
      }

      if (SDIO_GetFlagStatus(SDIO_FLAG_DTIMEOUT) != RESET)
      {
        SDIO_ClearFlag(SDIO_FLAG_DTIMEOUT);
        errorstatus = MISD_DATA_TIMEOUT;
        return(errorstatus);
      }
      else if (SDIO_GetFlagStatus(SDIO_FLAG_DCRCFAIL) != RESET)
      {
        SDIO_ClearFlag(SDIO_FLAG_DCRCFAIL);
        errorstatus = MISD_DATA_CRC_FAIL;
        return(errorstatus);
      }
      else if (SDIO_GetFlagStatus(SDIO_FLAG_TXUNDERR) != RESET)
      {
        SDIO_ClearFlag(SDIO_FLAG_TXUNDERR);
        errorstatus = MISD_TX_UNDERRUN;
        return(errorstatus);
      }
      else if (SDIO_GetFlagStatus(SDIO_FLAG_STBITERR) != RESET)
      {
        SDIO_ClearFlag(SDIO_FLAG_STBITERR);
        errorstatus = MISD_START_BIT_ERR;
        return(errorstatus);
      }

      if (SDIO_GetFlagStatus(SDIO_FLAG_DATAEND) != RESET)
      {
       if ((SDIO_STD_CAPACITY_MISD_CARD_V1_1 == CardType) || (SDIO_STD_CAPACITY_MISD_CARD_V2_0 == CardType) || (SDIO_HIGH_CAPACITY_MISD_CARD == CardType))
        {
          /* Send CMD12 STOP_TRANSMISSION */
          SDIO_CmdInitStructure.SDIO_Argument = 0x0;
          SDIO_CmdInitStructure.SDIO_CmdIndex = SDIO_STOP_TRANSMISSION;
          SDIO_CmdInitStructure.SDIO_Response = SDIO_Response_Short;
          SDIO_CmdInitStructure.SDIO_Wait = SDIO_Wait_No;
          SDIO_CmdInitStructure.SDIO_CPSM = SDIO_CPSM_Enable;
          SDIO_SendCommand(&SDIO_CmdInitStructure);


          errorstatus = CmdResp1Error(SDIO_STOP_TRANSMISSION);

          if (errorstatus != MISD_OK)
          {
            return(errorstatus);
          }
        }
      }
    }
    else if (DeviceMode == MISD_INTERRUPT_MODE)
    {
      SDIO_ITConfig(SDIO_IT_DCRCFAIL | SDIO_IT_DTIMEOUT | SDIO_IT_DATAEND | SDIO_IT_TXFIFOHE | SDIO_IT_TXUNDERR | SDIO_IT_STBITERR, ENABLE);
      while ((SDTransferEnd == 0) && (SDTransferError == MISD_OK))
      {}
      if (SDTransferError != MISD_OK)
      {
        return(SDTransferError);
      }
    }
    else if (DeviceMode == MISD_DMA_MODE)
    {
      SDIO_ITConfig(SDIO_IT_DCRCFAIL | SDIO_IT_DTIMEOUT | SDIO_IT_DATAEND | SDIO_IT_TXUNDERR | SDIO_IT_STBITERR, ENABLE);
      SDIO_DMACmd(ENABLE);
      DMA_TxConfiguration(writebuff, (NumberOfBlocks * BlockSize));
      while (DMA_GetFlagStatus(DMA2_FLAG_TC4) == RESET)
      {}
      while ((SDTransferEnd == 0) && (SDTransferError == MISD_OK))
      {}
      if (SDTransferError != MISD_OK)
      {
        return(SDTransferError);
      }
    }
  }
  /* Clear all the static flags */
  SDIO_ClearFlag(SDIO_STATIC_FLAGS);

  /* Wait till the card is in programming state */
  errorstatus = IsCardProgramming(&cardstate);

  while ((errorstatus == MISD_OK) && ((cardstate == MISD_CARD_PROGRAMMING) || (cardstate == MISD_CARD_RECEIVING)))
  {
    errorstatus = IsCardProgramming(&cardstate);
  }

  return(errorstatus);
}

/**
  * @brief  Gets the cuurent data transfer state.
  * @param  None
  * @retval : SDTransferState: Data Transfer state.
  *   This value can be: 
  *             - MISD_NO_TRANSFER: No data transfer is acting
  *             - MISD_TRANSFER_IN_PROGRESS: Data transfer is acting
  */
MISDTransferState MISD_GetTransferState(void)
{
  if (SDIO->STA & (SDIO_FLAG_TXACT | SDIO_FLAG_RXACT))
  {
    return(MISD_TRANSFER_IN_PROGRESS);
  }
  else
  {
    return(MISD_NO_TRANSFER);
  }
}

/**
  * @brief  Aborts an ongoing data transfer.
  * @param  None
  * @retval : MISD_Error: SD Card Error code.
  */
MISD_Error MISD_StopTransfer(void)
{
  MISD_Error errorstatus = MISD_OK;

  /* Send CMD12 STOP_TRANSMISSION  */
  SDIO_CmdInitStructure.SDIO_Argument = 0x0;
  SDIO_CmdInitStructure.SDIO_CmdIndex = SDIO_STOP_TRANSMISSION;
  SDIO_CmdInitStructure.SDIO_Response = SDIO_Response_Short;
  SDIO_CmdInitStructure.SDIO_Wait = SDIO_Wait_No;
  SDIO_CmdInitStructure.SDIO_CPSM = SDIO_CPSM_Enable;
  SDIO_SendCommand(&SDIO_CmdInitStructure);

  errorstatus = CmdResp1Error(SDIO_STOP_TRANSMISSION);

  return(errorstatus);
}

/**
  * @brief  Allows to erase memory area specified for the given card.
  * @param startaddr: the start address.
  * @param endaddr: the end address.
  * @retval : MISD_Error: SD Card Error code.
  */
MISD_Error MISD_Erase(uint32_t startaddr, uint32_t endaddr)
{
  MISD_Error errorstatus = MISD_OK;
  uint32_t delay = 0;
  __IO uint32_t maxdelay = 0;
  uint8_t cardstate = 0;

  /* Check if the card coomnd class supports erase command */
  if (((CMISD_Tab[1] >> 20) & MISD_CCCC_ERASE) == 0)
  {
    errorstatus = MISD_REQUEST_NOT_APPLICABLE;
    return(errorstatus);
  }

  maxdelay = 72000 / ((SDIO->CLKCR & 0xFF) + 2);

  if (SDIO_GetResponse(SDIO_RESP1) & MISD_CARD_LOCKED)
  {
    errorstatus = MISD_LOCK_UNLOCK_FAILED;
    return(errorstatus);
  }

  if (CardType == SDIO_HIGH_CAPACITY_MISD_CARD)
  {
    startaddr /= 512;
    endaddr /= 512;
  }
  
  /* According to sd-card spec 1.0 ERASE_GROUP_START (CMD32) and erase_group_end(CMD33) */
  if ((SDIO_STD_CAPACITY_MISD_CARD_V1_1 == CardType) || (SDIO_STD_CAPACITY_MISD_CARD_V2_0 == CardType) || (SDIO_HIGH_CAPACITY_MISD_CARD == CardType))
  {
    /* Send CMD32 MISD_ERASE_GRP_START with argument as addr  */
    SDIO_CmdInitStructure.SDIO_Argument = startaddr;
    SDIO_CmdInitStructure.SDIO_CmdIndex = SDIO_MISD_ERASE_GRP_START;
    SDIO_CmdInitStructure.SDIO_Response = SDIO_Response_Short;
    SDIO_CmdInitStructure.SDIO_Wait = SDIO_Wait_No;
    SDIO_CmdInitStructure.SDIO_CPSM = SDIO_CPSM_Enable;
    SDIO_SendCommand(&SDIO_CmdInitStructure);

    errorstatus = CmdResp1Error(SDIO_MISD_ERASE_GRP_START);
    if (errorstatus != MISD_OK)
    {
      return(errorstatus);
    }

    /* Send CMD33 MISD_ERASE_GRP_END with argument as addr  */
    SDIO_CmdInitStructure.SDIO_Argument = endaddr;
    SDIO_CmdInitStructure.SDIO_CmdIndex = SDIO_MISD_ERASE_GRP_END;
    SDIO_CmdInitStructure.SDIO_Response = SDIO_Response_Short;
    SDIO_CmdInitStructure.SDIO_Wait = SDIO_Wait_No;
    SDIO_CmdInitStructure.SDIO_CPSM = SDIO_CPSM_Enable;
    SDIO_SendCommand(&SDIO_CmdInitStructure);

    errorstatus = CmdResp1Error(SDIO_MISD_ERASE_GRP_END);
    if (errorstatus != MISD_OK)
    {
      return(errorstatus);
    }
  }

  /* Send CMD38 ERASE */
  SDIO_CmdInitStructure.SDIO_Argument = 0;
  SDIO_CmdInitStructure.SDIO_CmdIndex = SDIO_ERASE;
  SDIO_CmdInitStructure.SDIO_Response = SDIO_Response_Short;
  SDIO_CmdInitStructure.SDIO_Wait = SDIO_Wait_No;
  SDIO_CmdInitStructure.SDIO_CPSM = SDIO_CPSM_Enable;
  SDIO_SendCommand(&SDIO_CmdInitStructure);

  errorstatus = CmdResp1Error(SDIO_ERASE);

  if (errorstatus != MISD_OK)
  {
    return(errorstatus);
  }

  for (delay = 0; delay < maxdelay; delay++)
  {}

  /* Wait till the card is in programming state */
  errorstatus = IsCardProgramming(&cardstate);

  while ((errorstatus == MISD_OK) && ((MISD_CARD_PROGRAMMING == cardstate) || (MISD_CARD_RECEIVING == cardstate)))
  {
    errorstatus = IsCardProgramming(&cardstate);
  }

  return(errorstatus);
}

/**
  * @brief  Returns the current card's status.
  * @param pcardstatus: pointer to the buffer that will contain the SD 
  *   card status (Card Status register).
  * @retval : MISD_Error: SD Card Error code.
  */
MISD_Error MISD_SendStatus(uint32_t *pcardstatus)
{
  MISD_Error errorstatus = MISD_OK;

  if (pcardstatus == NULL)
  {
    errorstatus = MISD_INVALID_PARAMETER;
    return(errorstatus);
  }

  SDIO_CmdInitStructure.SDIO_Argument = (uint32_t) RCA << 16;
  SDIO_CmdInitStructure.SDIO_CmdIndex = SDIO_SEND_STATUS;
  SDIO_CmdInitStructure.SDIO_Response = SDIO_Response_Short;
  SDIO_CmdInitStructure.SDIO_Wait = SDIO_Wait_No;
  SDIO_CmdInitStructure.SDIO_CPSM = SDIO_CPSM_Enable;
  SDIO_SendCommand(&SDIO_CmdInitStructure);


  errorstatus = CmdResp1Error(SDIO_SEND_STATUS);

  if (errorstatus != MISD_OK)
  {
    return(errorstatus);
  }

  *pcardstatus = SDIO_GetResponse(SDIO_RESP1);

  return(errorstatus);
}

/**
  * @brief  Returns the current SD card's status.
  * @param psdstatus: pointer to the buffer that will contain the SD 
  *   card status (SD Status register).
  * @retval : MISD_Error: SD Card Error code.
  */
MISD_Error MISD_SendSDStatus(uint32_t *psdstatus)
{
  MISD_Error errorstatus = MISD_OK;
  uint32_t count = 0;

  if (SDIO_GetResponse(SDIO_RESP1) & MISD_CARD_LOCKED)
  {
    errorstatus = MISD_LOCK_UNLOCK_FAILED;
    return(errorstatus);
  }

  /* Set block size for card if it is not equal to current block size for card. */
  SDIO_CmdInitStructure.SDIO_Argument = 64;
  SDIO_CmdInitStructure.SDIO_CmdIndex = SDIO_SET_BLOCKLEN;
  SDIO_CmdInitStructure.SDIO_Response = SDIO_Response_Short;
  SDIO_CmdInitStructure.SDIO_Wait = SDIO_Wait_No;
  SDIO_CmdInitStructure.SDIO_CPSM = SDIO_CPSM_Enable;
  SDIO_SendCommand(&SDIO_CmdInitStructure);

  errorstatus = CmdResp1Error(SDIO_SET_BLOCKLEN);

  if (errorstatus != MISD_OK)
  {
    return(errorstatus);
  }

  /* CMD55 */
  SDIO_CmdInitStructure.SDIO_Argument = (uint32_t) RCA << 16;
  SDIO_CmdInitStructure.SDIO_CmdIndex = SDIO_APP_CMD;
  SDIO_CmdInitStructure.SDIO_Response = SDIO_Response_Short;
  SDIO_CmdInitStructure.SDIO_Wait = SDIO_Wait_No;
  SDIO_CmdInitStructure.SDIO_CPSM = SDIO_CPSM_Enable;
  SDIO_SendCommand(&SDIO_CmdInitStructure);
  errorstatus = CmdResp1Error(SDIO_APP_CMD);

  if (errorstatus != MISD_OK)
  {
    return(errorstatus);
  }

  SDIO_DataInitStructure.SDIO_DataTimeOut = MISD_DATATIMEOUT;
  SDIO_DataInitStructure.SDIO_DataLength = 64;
  SDIO_DataInitStructure.SDIO_DataBlockSize = SDIO_DataBlockSize_64b;
  SDIO_DataInitStructure.SDIO_TransferDir = SDIO_TransferDir_ToSDIO;
  SDIO_DataInitStructure.SDIO_TransferMode = SDIO_TransferMode_Block;
  SDIO_DataInitStructure.SDIO_DPSM = SDIO_DPSM_Enable;
  SDIO_DataConfig(&SDIO_DataInitStructure);

  /* Send ACMD13 MISD_APP_STAUS  with argument as card's RCA.*/
  SDIO_CmdInitStructure.SDIO_Argument = 0;
  SDIO_CmdInitStructure.SDIO_CmdIndex = SDIO_MISD_APP_STAUS;
  SDIO_CmdInitStructure.SDIO_Response = SDIO_Response_Short;
  SDIO_CmdInitStructure.SDIO_Wait = SDIO_Wait_No;
  SDIO_CmdInitStructure.SDIO_CPSM = SDIO_CPSM_Enable;
  SDIO_SendCommand(&SDIO_CmdInitStructure);
  errorstatus = CmdResp1Error(SDIO_MISD_APP_STAUS);

  if (errorstatus != MISD_OK)
  {
    return(errorstatus);
  }

  while (!(SDIO->STA &(SDIO_FLAG_RXOVERR | SDIO_FLAG_DCRCFAIL | SDIO_FLAG_DTIMEOUT | SDIO_FLAG_DBCKEND | SDIO_FLAG_STBITERR)))
  {
    if (SDIO_GetFlagStatus(SDIO_FLAG_RXFIFOHF) != RESET)
    {
      for (count = 0; count < 8; count++)
      {
        *(psdstatus + count) = SDIO_ReadData();
      }
      psdstatus += 8;
    }
  }

  if (SDIO_GetFlagStatus(SDIO_FLAG_DTIMEOUT) != RESET)
  {
    SDIO_ClearFlag(SDIO_FLAG_DTIMEOUT);
    errorstatus = MISD_DATA_TIMEOUT;
    return(errorstatus);
  }
  else if (SDIO_GetFlagStatus(SDIO_FLAG_DCRCFAIL) != RESET)
  {
    SDIO_ClearFlag(SDIO_FLAG_DCRCFAIL);
    errorstatus = MISD_DATA_CRC_FAIL;
    return(errorstatus);
  }
  else if (SDIO_GetFlagStatus(SDIO_FLAG_RXOVERR) != RESET)
  {
    SDIO_ClearFlag(SDIO_FLAG_RXOVERR);
    errorstatus = MISD_RX_OVERRUN;
    return(errorstatus);
  }
  else if (SDIO_GetFlagStatus(SDIO_FLAG_STBITERR) != RESET)
  {
    SDIO_ClearFlag(SDIO_FLAG_STBITERR);
    errorstatus = MISD_START_BIT_ERR;
    return(errorstatus);
  }

  while (SDIO_GetFlagStatus(SDIO_FLAG_RXDAVL) != RESET)
  {
    *psdstatus = SDIO_ReadData();
    psdstatus++;
  }

  /* Clear all the static status flags*/
  SDIO_ClearFlag(SDIO_STATIC_FLAGS);
  psdstatus -= 16;
  for (count = 0; count < 16; count++)
  {
    psdstatus[count] = ((psdstatus[count] & MISD_0TO7BITS) << 24) |((psdstatus[count] & MISD_8TO15BITS) << 8) |
                       ((psdstatus[count] & MISD_16TO23BITS) >> 8) |((psdstatus[count] & MISD_24TO31BITS) >> 24);
  }
  return(errorstatus);
}

/**
  * @brief  Allows to process all the interrupts that are high.
  * @param  None
  * @retval : MISD_Error: SD Card Error code.
  */
MISD_Error MISD_ProcessIRQSrc(void)
{
  uint32_t count = 0, restwords = 0;

  if (DeviceMode == MISD_INTERRUPT_MODE)
  {
    if (SDIO_GetITStatus(SDIO_IT_RXFIFOHF) != RESET)
    {
      for (count = 0; count < MISD_HALFFIFO; count++)
      {
        *(DestBuffer + count) = SDIO_ReadData();
      }
      DestBuffer += MISD_HALFFIFO;
      SDNumberOfBytes += MISD_HALFFIFOBYTES;
    }
    else if (SDIO_GetITStatus(SDIO_IT_TXFIFOHE) != RESET)
    {
      if ((TotalSDNumberOfBytes - SDNumberOfBytes) < MISD_HALFFIFOBYTES)
      {
        restwords = ((TotalSDNumberOfBytes - SDNumberOfBytes) %  4 == 0) ?
                    ((TotalSDNumberOfBytes - SDNumberOfBytes) / 4) :
                    ((TotalSDNumberOfBytes - SDNumberOfBytes) / 4 + 1);

        for (count = 0; count < restwords;  count++, SrcBuffer++, SDNumberOfBytes += 4)
        {
          SDIO_WriteData(*SrcBuffer);
        }
      }
      else
      {
        for (count = 0; count < MISD_HALFFIFO; count++)
        {
          SDIO_WriteData(*(SrcBuffer + count));
        }

        SrcBuffer += MISD_HALFFIFO;
        SDNumberOfBytes += MISD_HALFFIFOBYTES;
      }
    }
  }

  if (SDIO_GetITStatus(SDIO_IT_DATAEND) != RESET)
  {
    if (DeviceMode != MISD_DMA_MODE)
    {
      while ((SDIO_GetFlagStatus(SDIO_FLAG_RXDAVL) != RESET)  &&  (SDNumberOfBytes < TotalSDNumberOfBytes))
      {
        *DestBuffer = SDIO_ReadData();
        DestBuffer++;
        SDNumberOfBytes += 4;
      }
    }

    if (StopCondition == 1)
    {
      SDTransferError = MISD_StopTransfer();
    }
    else
    {
      SDTransferError = MISD_OK;
    }
    SDIO_ClearITPendingBit(SDIO_IT_DATAEND);
    SDIO_ITConfig(SDIO_IT_DCRCFAIL | SDIO_IT_DTIMEOUT | SDIO_IT_DATAEND |
                  SDIO_IT_TXFIFOHE | SDIO_IT_RXFIFOHF | SDIO_IT_TXUNDERR |
                  SDIO_IT_RXOVERR | SDIO_IT_STBITERR, DISABLE);
    SDTransferEnd = 1;
    SDNumberOfBytes = 0;
    return(SDTransferError);
  }

  if (SDIO_GetITStatus(SDIO_IT_DCRCFAIL) != RESET)
  {
    SDIO_ClearITPendingBit(SDIO_IT_DCRCFAIL);
    SDIO_ITConfig(SDIO_IT_DCRCFAIL | SDIO_IT_DTIMEOUT | SDIO_IT_DATAEND |
                  SDIO_IT_TXFIFOHE | SDIO_IT_RXFIFOHF | SDIO_IT_TXUNDERR |
                  SDIO_IT_RXOVERR | SDIO_IT_STBITERR, DISABLE);
    SDNumberOfBytes = 0;
    SDTransferError = MISD_DATA_CRC_FAIL;
    return(MISD_DATA_CRC_FAIL);
  }

  if (SDIO_GetITStatus(SDIO_IT_DTIMEOUT) != RESET)
  {
    SDIO_ClearITPendingBit(SDIO_IT_DTIMEOUT);
    SDIO_ITConfig(SDIO_IT_DCRCFAIL | SDIO_IT_DTIMEOUT | SDIO_IT_DATAEND |
                  SDIO_IT_TXFIFOHE | SDIO_IT_RXFIFOHF | SDIO_IT_TXUNDERR |
                  SDIO_IT_RXOVERR | SDIO_IT_STBITERR, DISABLE);
    SDNumberOfBytes = 0;
    SDTransferError = MISD_DATA_TIMEOUT;
    return(MISD_DATA_TIMEOUT);
  }

  if (SDIO_GetITStatus(SDIO_IT_RXOVERR) != RESET)
  {
    SDIO_ClearITPendingBit(SDIO_IT_RXOVERR);
    SDIO_ITConfig(SDIO_IT_DCRCFAIL | SDIO_IT_DTIMEOUT | SDIO_IT_DATAEND |
                  SDIO_IT_TXFIFOHE | SDIO_IT_RXFIFOHF | SDIO_IT_TXUNDERR |
                  SDIO_IT_RXOVERR | SDIO_IT_STBITERR, DISABLE);
    SDNumberOfBytes = 0;
    SDTransferError = MISD_RX_OVERRUN;
    return(MISD_RX_OVERRUN);
  }

  if (SDIO_GetITStatus(SDIO_IT_TXUNDERR) != RESET)
  {
    SDIO_ClearITPendingBit(SDIO_IT_TXUNDERR);
    SDIO_ITConfig(SDIO_IT_DCRCFAIL | SDIO_IT_DTIMEOUT | SDIO_IT_DATAEND |
                  SDIO_IT_TXFIFOHE | SDIO_IT_RXFIFOHF | SDIO_IT_TXUNDERR |
                  SDIO_IT_RXOVERR | SDIO_IT_STBITERR, DISABLE);
    SDNumberOfBytes = 0;
    SDTransferError = MISD_TX_UNDERRUN;
    return(MISD_TX_UNDERRUN);
  }

  if (SDIO_GetITStatus(SDIO_IT_STBITERR) != RESET)
  {
    SDIO_ClearITPendingBit(SDIO_IT_STBITERR);
    SDIO_ITConfig(SDIO_IT_DCRCFAIL | SDIO_IT_DTIMEOUT | SDIO_IT_DATAEND |
                  SDIO_IT_TXFIFOHE | SDIO_IT_RXFIFOHF | SDIO_IT_TXUNDERR |
                  SDIO_IT_RXOVERR | SDIO_IT_STBITERR, DISABLE);
    SDNumberOfBytes = 0;
    SDTransferError = MISD_START_BIT_ERR;
    return(MISD_START_BIT_ERR);
  }

  return(MISD_OK);
}

/**
  * @brief  Checks for error conditions for CMD0.
  * @param  None
  * @retval : MISD_Error: SD Card Error code.
  */
static MISD_Error CmdError(void)
{
  MISD_Error errorstatus = MISD_OK;
  uint32_t timeout;

  timeout = SDIO_CMD0TIMEOUT; /* 10000 */

  while ((timeout > 0) && (SDIO_GetFlagStatus(SDIO_FLAG_CMDSENT) == RESET))
  {
    timeout--;
  }

  if (timeout == 0)
  {
    errorstatus = MISD_CMD_RSP_TIMEOUT;
    return(errorstatus);
  }

  /* Clear all the static flags */
  SDIO_ClearFlag(SDIO_STATIC_FLAGS);

  return(errorstatus);
}

/**
  * @brief  Checks for error conditions for R7.
  *   response.
  * @param  None
  * @retval : MISD_Error: SD Card Error code.
  */
static MISD_Error CmdResp7Error(void)
{
  MISD_Error errorstatus = MISD_OK;
  uint32_t status;
  uint32_t timeout = SDIO_CMD0TIMEOUT;

  status = SDIO->STA;

  while (!(status & (SDIO_FLAG_CCRCFAIL | SDIO_FLAG_CMDREND | SDIO_FLAG_CTIMEOUT)) && (timeout > 0))
  {
    timeout--;
    status = SDIO->STA;
  }

  if ((timeout == 0) || (status & SDIO_FLAG_CTIMEOUT))
  {
    /* Card is not V2.0 complient or card does not support the set voltage range */
    errorstatus = MISD_CMD_RSP_TIMEOUT;
    SDIO_ClearFlag(SDIO_FLAG_CTIMEOUT);
    return(errorstatus);
  }

  if (status & SDIO_FLAG_CMDREND)
  {
    /* Card is SD V2.0 compliant */
    errorstatus = MISD_OK;
    SDIO_ClearFlag(SDIO_FLAG_CMDREND);
    return(errorstatus);
  }
  return(errorstatus);
}

/**
  * @brief  Checks for error conditions for R1.
  *   response
  * @param cmd: The sent command index.
  * @retval : MISD_Error: SD Card Error code.
  */
static MISD_Error CmdResp1Error(uint8_t cmd)
{
  MISD_Error errorstatus = MISD_OK;
  uint32_t status;
  uint32_t response_r1;

  status = SDIO->STA;

  while (!(status & (SDIO_FLAG_CCRCFAIL | SDIO_FLAG_CMDREND | SDIO_FLAG_CTIMEOUT)))
  {
    status = SDIO->STA;
  }

  if (status & SDIO_FLAG_CTIMEOUT)
  {
    errorstatus = MISD_CMD_RSP_TIMEOUT;
    SDIO_ClearFlag(SDIO_FLAG_CTIMEOUT);
    return(errorstatus);
  }
  else if (status & SDIO_FLAG_CCRCFAIL)
  {
    errorstatus = MISD_CMD_CRC_FAIL;
    SDIO_ClearFlag(SDIO_FLAG_CCRCFAIL);
    return(errorstatus);
  }

  /* Check response received is of desired command */
  if (SDIO_GetCommandResponse() != cmd)
  {
    errorstatus = MISD_ILLEGAL_CMD;
    return(errorstatus);
  }

  /* Clear all the static flags */
  SDIO_ClearFlag(SDIO_STATIC_FLAGS);

  /* We have received response, retrieve it for analysis  */
  response_r1 = SDIO_GetResponse(SDIO_RESP1);

  if ((response_r1 & MISD_OCR_ERRORBITS) == MISD_ALLZERO)
  {
    return(errorstatus);
  }

  if (response_r1 & MISD_OCR_ADDR_OUT_OF_RANGE)
  {
    return(MISD_ADDR_OUT_OF_RANGE);
  }

  if (response_r1 & MISD_OCR_ADDR_MISALIGNED)
  {
    return(MISD_ADDR_MISALIGNED);
  }

  if (response_r1 & MISD_OCR_BLOCK_LEN_ERR)
  {
    return(MISD_BLOCK_LEN_ERR);
  }

  if (response_r1 & MISD_OCR_ERASE_SEQ_ERR)
  {
    return(MISD_ERASE_SEQ_ERR);
  }

  if (response_r1 & MISD_OCR_BAD_ERASE_PARAM)
  {
    return(MISD_BAD_ERASE_PARAM);
  }

  if (response_r1 & MISD_OCR_WRITE_PROT_VIOLATION)
  {
    return(MISD_WRITE_PROT_VIOLATION);
  }

  if (response_r1 & MISD_OCR_LOCK_UNLOCK_FAILED)
  {
    return(MISD_LOCK_UNLOCK_FAILED);
  }

  if (response_r1 & MISD_OCR_COM_CRC_FAILED)
  {
    return(MISD_COM_CRC_FAILED);
  }

  if (response_r1 & MISD_OCR_ILLEGAL_CMD)
  {
    return(MISD_ILLEGAL_CMD);
  }

  if (response_r1 & MISD_OCR_CARD_ECC_FAILED)
  {
    return(MISD_CARD_ECC_FAILED);
  }

  if (response_r1 & MISD_OCR_CC_ERROR)
  {
    return(MISD_CC_ERROR);
  }

  if (response_r1 & MISD_OCR_GENERAL_UNKNOWN_ERROR)
  {
    return(MISD_GENERAL_UNKNOWN_ERROR);
  }

  if (response_r1 & MISD_OCR_STREAM_READ_UNDERRUN)
  {
    return(MISD_STREAM_READ_UNDERRUN);
  }

  if (response_r1 & MISD_OCR_STREAM_WRITE_OVERRUN)
  {
    return(MISD_STREAM_WRITE_OVERRUN);
  }

  if (response_r1 & MISD_OCR_CID_CMISD_OVERWRIETE)
  {
    return(MISD_CID_CMISD_OVERWRITE);
  }

  if (response_r1 & MISD_OCR_WP_ERASE_SKIP)
  {
    return(MISD_WP_ERASE_SKIP);
  }

  if (response_r1 & MISD_OCR_CARD_ECC_DISABLED)
  {
    return(MISD_CARD_ECC_DISABLED);
  }

  if (response_r1 & MISD_OCR_ERASE_RESET)
  {
    return(MISD_ERASE_RESET);
  }

  if (response_r1 & MISD_OCR_AKE_SEQ_ERROR)
  {
    return(MISD_AKE_SEQ_ERROR);
  }
  return(errorstatus);
}

/**
  * @brief  Checks for error conditions for R3 (OCR).
  *   response.
  * @param  None
  * @retval : MISD_Error: SD Card Error code.
  */
static MISD_Error CmdResp3Error(void)
{
  MISD_Error errorstatus = MISD_OK;
  uint32_t status;

  status = SDIO->STA;

  while (!(status & (SDIO_FLAG_CCRCFAIL | SDIO_FLAG_CMDREND | SDIO_FLAG_CTIMEOUT)))
  {
    status = SDIO->STA;
  }

  if (status & SDIO_FLAG_CTIMEOUT)
  {
    errorstatus = MISD_CMD_RSP_TIMEOUT;
    SDIO_ClearFlag(SDIO_FLAG_CTIMEOUT);
    return(errorstatus);
  }
  /* Clear all the static flags */
  SDIO_ClearFlag(SDIO_STATIC_FLAGS);
  return(errorstatus);
}

/**
  * @brief  Checks for error conditions for R2 (CID or CSD).
  *   response.
  * @param  None
  * @retval : MISD_Error: SD Card Error code.
  */
static MISD_Error CmdResp2Error(void)
{
  MISD_Error errorstatus = MISD_OK;
  uint32_t status;

  status = SDIO->STA;

  while (!(status & (SDIO_FLAG_CCRCFAIL | SDIO_FLAG_CTIMEOUT | SDIO_FLAG_CMDREND)))
  {
    status = SDIO->STA;
  }

  if (status & SDIO_FLAG_CTIMEOUT)
  {
    errorstatus = MISD_CMD_RSP_TIMEOUT;
    SDIO_ClearFlag(SDIO_FLAG_CTIMEOUT);
    return(errorstatus);
  }
  else if (status & SDIO_FLAG_CCRCFAIL)
  {
    errorstatus = MISD_CMD_CRC_FAIL;
    SDIO_ClearFlag(SDIO_FLAG_CCRCFAIL);
    return(errorstatus);
  }

  /* Clear all the static flags */
  SDIO_ClearFlag(SDIO_STATIC_FLAGS);

  return(errorstatus);
}

/**
  * @brief  Checks for error conditions for R6 (RCA).
  *   response.
  * @param cmd: The sent command index.
  * @param prca: pointer to the variable that will contain the SD
  *   card relative address RCA. 
  * @retval : MISD_Error: SD Card Error code.
  */
static MISD_Error CmdResp6Error(uint8_t cmd, uint16_t *prca)
{
  MISD_Error errorstatus = MISD_OK;
  uint32_t status;
  uint32_t response_r1;

  status = SDIO->STA;

  while (!(status & (SDIO_FLAG_CCRCFAIL | SDIO_FLAG_CTIMEOUT | SDIO_FLAG_CMDREND)))
  {
    status = SDIO->STA;
  }

  if (status & SDIO_FLAG_CTIMEOUT)
  {
    errorstatus = MISD_CMD_RSP_TIMEOUT;
    SDIO_ClearFlag(SDIO_FLAG_CTIMEOUT);
    return(errorstatus);
  }
  else if (status & SDIO_FLAG_CCRCFAIL)
  {
    errorstatus = MISD_CMD_CRC_FAIL;
    SDIO_ClearFlag(SDIO_FLAG_CCRCFAIL);
    return(errorstatus);
  }

  /* Check response received is of desired command */
  if (SDIO_GetCommandResponse() != cmd)
  {
    errorstatus = MISD_ILLEGAL_CMD;
    return(errorstatus);
  }

  /* Clear all the static flags */
  SDIO_ClearFlag(SDIO_STATIC_FLAGS);

  /* We have received response, retrieve it.  */
  response_r1 = SDIO_GetResponse(SDIO_RESP1);

  if (MISD_ALLZERO == (response_r1 & (MISD_R6_GENERAL_UNKNOWN_ERROR | MISD_R6_ILLEGAL_CMD | MISD_R6_COM_CRC_FAILED)))
  {
    *prca = (uint16_t) (response_r1 >> 16);
    return(errorstatus);
  }

  if (response_r1 & MISD_R6_GENERAL_UNKNOWN_ERROR)
  {
    return(MISD_GENERAL_UNKNOWN_ERROR);
  }

  if (response_r1 & MISD_R6_ILLEGAL_CMD)
  {
    return(MISD_ILLEGAL_CMD);
  }

  if (response_r1 & MISD_R6_COM_CRC_FAILED)
  {
    return(MISD_COM_CRC_FAILED);
  }

  return(errorstatus);
}

/**
  * @brief  Enables or disables the SDIO wide bus mode.
  * @param NewState: new state of the SDIO wide bus mode.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval : MISD_Error: SD Card Error code.
  */
static MISD_Error SDEnWideBus(FunctionalState NewState)
{
  MISD_Error errorstatus = MISD_OK;

  uint32_t scr[2] = {0, 0};

  if (SDIO_GetResponse(SDIO_RESP1) & MISD_CARD_LOCKED)
  {
    errorstatus = MISD_LOCK_UNLOCK_FAILED;
    return(errorstatus);
  }

  /* Get SCR Register */
  errorstatus = FindSCR(RCA, scr);

  if (errorstatus != MISD_OK)
  {
    return(errorstatus);
  }

  /* If wide bus operation to be enabled */
  if (NewState == ENABLE)
  {
    /* If requested card supports wide bus operation */
    if ((scr[1] & MISD_WIDE_BUS_SUPPORT) != MISD_ALLZERO)
    {
      /* Send CMD55 APP_CMD with argument as card's RCA.*/
      SDIO_CmdInitStructure.SDIO_Argument = (uint32_t) RCA << 16;
      SDIO_CmdInitStructure.SDIO_CmdIndex = SDIO_APP_CMD;
      SDIO_CmdInitStructure.SDIO_Response = SDIO_Response_Short;
      SDIO_CmdInitStructure.SDIO_Wait = SDIO_Wait_No;
      SDIO_CmdInitStructure.SDIO_CPSM = SDIO_CPSM_Enable;
      SDIO_SendCommand(&SDIO_CmdInitStructure);

      errorstatus = CmdResp1Error(SDIO_APP_CMD);

      if (errorstatus != MISD_OK)
      {
        return(errorstatus);
      }

      /* Send ACMD6 APP_CMD with argument as 2 for wide bus mode */
      SDIO_CmdInitStructure.SDIO_Argument = 0x2;
      SDIO_CmdInitStructure.SDIO_CmdIndex = SDIO_APP_MISD_SET_BUSWIDTH;
      SDIO_CmdInitStructure.SDIO_Response = SDIO_Response_Short;
      SDIO_CmdInitStructure.SDIO_Wait = SDIO_Wait_No;
      SDIO_CmdInitStructure.SDIO_CPSM = SDIO_CPSM_Enable;
      SDIO_SendCommand(&SDIO_CmdInitStructure);

      errorstatus = CmdResp1Error(SDIO_APP_MISD_SET_BUSWIDTH);

      if (errorstatus != MISD_OK)
      {
        return(errorstatus);
      }
      return(errorstatus);
    }
    else
    {
      errorstatus = MISD_REQUEST_NOT_APPLICABLE;
      return(errorstatus);
    }
  }   /* If wide bus operation to be disabled */
  else
  {
    /* If requested card supports 1 bit mode operation */
    if ((scr[1] & MISD_SINGLE_BUS_SUPPORT) != MISD_ALLZERO)
    {
      /* Send CMD55 APP_CMD with argument as card's RCA.*/
      SDIO_CmdInitStructure.SDIO_Argument = (uint32_t) RCA << 16;
      SDIO_CmdInitStructure.SDIO_CmdIndex = SDIO_APP_CMD;
      SDIO_CmdInitStructure.SDIO_Response = SDIO_Response_Short;
      SDIO_CmdInitStructure.SDIO_Wait = SDIO_Wait_No;
      SDIO_CmdInitStructure.SDIO_CPSM = SDIO_CPSM_Enable;
      SDIO_SendCommand(&SDIO_CmdInitStructure);


      errorstatus = CmdResp1Error(SDIO_APP_CMD);

      if (errorstatus != MISD_OK)
      {
        return(errorstatus);
      }

      /* Send ACMD6 APP_CMD with argument as 2 for wide bus mode */
      SDIO_CmdInitStructure.SDIO_Argument = 0x00;
      SDIO_CmdInitStructure.SDIO_CmdIndex = SDIO_APP_MISD_SET_BUSWIDTH;
      SDIO_CmdInitStructure.SDIO_Response = SDIO_Response_Short;
      SDIO_CmdInitStructure.SDIO_Wait = SDIO_Wait_No;
      SDIO_CmdInitStructure.SDIO_CPSM = SDIO_CPSM_Enable;
      SDIO_SendCommand(&SDIO_CmdInitStructure);

      errorstatus = CmdResp1Error(SDIO_APP_MISD_SET_BUSWIDTH);

      if (errorstatus != MISD_OK)
      {
        return(errorstatus);
      }

      return(errorstatus);
    }
    else
    {
      errorstatus = MISD_REQUEST_NOT_APPLICABLE;
      return(errorstatus);
    }
  }
}

/**
  * @brief  Checks if the SD card is in programming state.
  * @param pstatus: pointer to the variable that will contain the SD
  *   card state.
  * @retval : MISD_Error: SD Card Error code.
  */
static MISD_Error IsCardProgramming(uint8_t *pstatus)
{
  MISD_Error errorstatus = MISD_OK;
  __IO uint32_t respR1 = 0, status = 0;

  SDIO_CmdInitStructure.SDIO_Argument = (uint32_t) RCA << 16;
  SDIO_CmdInitStructure.SDIO_CmdIndex = SDIO_SEND_STATUS;
  SDIO_CmdInitStructure.SDIO_Response = SDIO_Response_Short;
  SDIO_CmdInitStructure.SDIO_Wait = SDIO_Wait_No;
  SDIO_CmdInitStructure.SDIO_CPSM = SDIO_CPSM_Enable;
  SDIO_SendCommand(&SDIO_CmdInitStructure);

  status = SDIO->STA;
  while (!(status & (SDIO_FLAG_CCRCFAIL | SDIO_FLAG_CMDREND | SDIO_FLAG_CTIMEOUT)))
  {
    status = SDIO->STA;
  }

  if (status & SDIO_FLAG_CTIMEOUT)
  {
    errorstatus = MISD_CMD_RSP_TIMEOUT;
    SDIO_ClearFlag(SDIO_FLAG_CTIMEOUT);
    return(errorstatus);
  }
  else if (status & SDIO_FLAG_CCRCFAIL)
  {
    errorstatus = MISD_CMD_CRC_FAIL;
    SDIO_ClearFlag(SDIO_FLAG_CCRCFAIL);
    return(errorstatus);
  }

  status = (uint32_t)SDIO_GetCommandResponse();

  /* Check response received is of desired command */
  if (status != SDIO_SEND_STATUS)
  {
    errorstatus = MISD_ILLEGAL_CMD;
    return(errorstatus);
  }

  /* Clear all the static flags */
  SDIO_ClearFlag(SDIO_STATIC_FLAGS);


  /* We have received response, retrieve it for analysis  */
  respR1 = SDIO_GetResponse(SDIO_RESP1);

  /* Find out card status */
  *pstatus = (uint8_t) ((respR1 >> 9) & 0x0000000F);

  if ((respR1 & MISD_OCR_ERRORBITS) == MISD_ALLZERO)
  {
    return(errorstatus);
  }

  if (respR1 & MISD_OCR_ADDR_OUT_OF_RANGE)
  {
    return(MISD_ADDR_OUT_OF_RANGE);
  }

  if (respR1 & MISD_OCR_ADDR_MISALIGNED)
  {
    return(MISD_ADDR_MISALIGNED);
  }

  if (respR1 & MISD_OCR_BLOCK_LEN_ERR)
  {
    return(MISD_BLOCK_LEN_ERR);
  }

  if (respR1 & MISD_OCR_ERASE_SEQ_ERR)
  {
    return(MISD_ERASE_SEQ_ERR);
  }

  if (respR1 & MISD_OCR_BAD_ERASE_PARAM)
  {
    return(MISD_BAD_ERASE_PARAM);
  }

  if (respR1 & MISD_OCR_WRITE_PROT_VIOLATION)
  {
    return(MISD_WRITE_PROT_VIOLATION);
  }

  if (respR1 & MISD_OCR_LOCK_UNLOCK_FAILED)
  {
    return(MISD_LOCK_UNLOCK_FAILED);
  }

  if (respR1 & MISD_OCR_COM_CRC_FAILED)
  {
    return(MISD_COM_CRC_FAILED);
  }

  if (respR1 & MISD_OCR_ILLEGAL_CMD)
  {
    return(MISD_ILLEGAL_CMD);
  }

  if (respR1 & MISD_OCR_CARD_ECC_FAILED)
  {
    return(MISD_CARD_ECC_FAILED);
  }

  if (respR1 & MISD_OCR_CC_ERROR)
  {
    return(MISD_CC_ERROR);
  }

  if (respR1 & MISD_OCR_GENERAL_UNKNOWN_ERROR)
  {
    return(MISD_GENERAL_UNKNOWN_ERROR);
  }

  if (respR1 & MISD_OCR_STREAM_READ_UNDERRUN)
  {
    return(MISD_STREAM_READ_UNDERRUN);
  }

  if (respR1 & MISD_OCR_STREAM_WRITE_OVERRUN)
  {
    return(MISD_STREAM_WRITE_OVERRUN);
  }

  if (respR1 & MISD_OCR_CID_CMISD_OVERWRIETE)
  {
    return(MISD_CID_CMISD_OVERWRITE);
  }

  if (respR1 & MISD_OCR_WP_ERASE_SKIP)
  {
    return(MISD_WP_ERASE_SKIP);
  }

  if (respR1 & MISD_OCR_CARD_ECC_DISABLED)
  {
    return(MISD_CARD_ECC_DISABLED);
  }

  if (respR1 & MISD_OCR_ERASE_RESET)
  {
    return(MISD_ERASE_RESET);
  }

  if (respR1 & MISD_OCR_AKE_SEQ_ERROR)
  {
    return(MISD_AKE_SEQ_ERROR);
  }

  return(errorstatus);
}

/**
  * @brief  Find the SD card SCR register value.
  * @param rca: selected card address.
  * @param pscr: pointer to the buffer that will contain the SCR value.
  * @retval : MISD_Error: SD Card Error code.
  */
static MISD_Error FindSCR(uint16_t rca, uint32_t *pscr)
{
  uint32_t index = 0;
  MISD_Error errorstatus = MISD_OK;
  uint32_t tempscr[2] = {0, 0};

  /* Set Block Size To 8 Bytes */
  /* Send CMD55 APP_CMD with argument as card's RCA */
  SDIO_CmdInitStructure.SDIO_Argument = (uint32_t)8;
  SDIO_CmdInitStructure.SDIO_CmdIndex = SDIO_SET_BLOCKLEN;
  SDIO_CmdInitStructure.SDIO_Response = SDIO_Response_Short;
  SDIO_CmdInitStructure.SDIO_Wait = SDIO_Wait_No;
  SDIO_CmdInitStructure.SDIO_CPSM = SDIO_CPSM_Enable;
  SDIO_SendCommand(&SDIO_CmdInitStructure);

  errorstatus = CmdResp1Error(SDIO_SET_BLOCKLEN);

  if (errorstatus != MISD_OK)
  {
    return(errorstatus);
  }

  /* Send CMD55 APP_CMD with argument as card's RCA */
  SDIO_CmdInitStructure.SDIO_Argument = (uint32_t) RCA << 16;
  SDIO_CmdInitStructure.SDIO_CmdIndex = SDIO_APP_CMD;
  SDIO_CmdInitStructure.SDIO_Response = SDIO_Response_Short;
  SDIO_CmdInitStructure.SDIO_Wait = SDIO_Wait_No;
  SDIO_CmdInitStructure.SDIO_CPSM = SDIO_CPSM_Enable;
  SDIO_SendCommand(&SDIO_CmdInitStructure);

  errorstatus = CmdResp1Error(SDIO_APP_CMD);

  if (errorstatus != MISD_OK)
  {
    return(errorstatus);
  }
  SDIO_DataInitStructure.SDIO_DataTimeOut = MISD_DATATIMEOUT;
  SDIO_DataInitStructure.SDIO_DataLength = 8;
  SDIO_DataInitStructure.SDIO_DataBlockSize = SDIO_DataBlockSize_8b;
  SDIO_DataInitStructure.SDIO_TransferDir = SDIO_TransferDir_ToSDIO;
  SDIO_DataInitStructure.SDIO_TransferMode = SDIO_TransferMode_Block;
  SDIO_DataInitStructure.SDIO_DPSM = SDIO_DPSM_Enable;
  SDIO_DataConfig(&SDIO_DataInitStructure);


  /* Send ACMD51 MISD_APP_SEND_SCR with argument as 0 */
  SDIO_CmdInitStructure.SDIO_Argument = 0x0;
  SDIO_CmdInitStructure.SDIO_CmdIndex = SDIO_MISD_APP_SEND_SCR;
  SDIO_CmdInitStructure.SDIO_Response = SDIO_Response_Short;
  SDIO_CmdInitStructure.SDIO_Wait = SDIO_Wait_No;
  SDIO_CmdInitStructure.SDIO_CPSM = SDIO_CPSM_Enable;
  SDIO_SendCommand(&SDIO_CmdInitStructure);

  errorstatus = CmdResp1Error(SDIO_MISD_APP_SEND_SCR);

  if (errorstatus != MISD_OK)
  {
    return(errorstatus);
  }

  while (!(SDIO->STA & (SDIO_FLAG_RXOVERR | SDIO_FLAG_DCRCFAIL | SDIO_FLAG_DTIMEOUT | SDIO_FLAG_DBCKEND | SDIO_FLAG_STBITERR)))
  {
    if (SDIO_GetFlagStatus(SDIO_FLAG_RXDAVL) != RESET)
    {
      *(tempscr + index) = SDIO_ReadData();
      index++;
    }
  }

  if (SDIO_GetFlagStatus(SDIO_FLAG_DTIMEOUT) != RESET)
  {
    SDIO_ClearFlag(SDIO_FLAG_DTIMEOUT);
    errorstatus = MISD_DATA_TIMEOUT;
    return(errorstatus);
  }
  else if (SDIO_GetFlagStatus(SDIO_FLAG_DCRCFAIL) != RESET)
  {
    SDIO_ClearFlag(SDIO_FLAG_DCRCFAIL);
    errorstatus = MISD_DATA_CRC_FAIL;
    return(errorstatus);
  }
  else if (SDIO_GetFlagStatus(SDIO_FLAG_RXOVERR) != RESET)
  {
    SDIO_ClearFlag(SDIO_FLAG_RXOVERR);
    errorstatus = MISD_RX_OVERRUN;
    return(errorstatus);
  }
  else if (SDIO_GetFlagStatus(SDIO_FLAG_STBITERR) != RESET)
  {
    SDIO_ClearFlag(SDIO_FLAG_STBITERR);
    errorstatus = MISD_START_BIT_ERR;
    return(errorstatus);
  }

  /* Clear all the static flags */
  SDIO_ClearFlag(SDIO_STATIC_FLAGS);

  *(pscr + 1) = ((tempscr[0] & MISD_0TO7BITS) << 24) | ((tempscr[0] & MISD_8TO15BITS) << 8) | ((tempscr[0] & MISD_16TO23BITS) >> 8) | ((tempscr[0] & MISD_24TO31BITS) >> 24);

  *(pscr) = ((tempscr[1] & MISD_0TO7BITS) << 24) | ((tempscr[1] & MISD_8TO15BITS) << 8) | ((tempscr[1] & MISD_16TO23BITS) >> 8) | ((tempscr[1] & MISD_24TO31BITS) >> 24);

  return(errorstatus);
}

/**
  * @brief  Converts the number of bytes in power of two and returns the
  *   power.
  * @param SDNumberOfBytes: number of bytes.
  * @retval : None
  */
static uint8_t convert_from_bytes_to_power_of_two(uint16_t SDNumberOfBytes)
{
  uint8_t count = 0;

  while (SDNumberOfBytes != 1)
  {
    SDNumberOfBytes >>= 1;
    count++;
  }
  return(count);
}

/**
  * @brief  Configures the SDIO Corresponding GPIO Ports
  * @param  None
  * @retval : None
  */
static void SDIOGPIO_Configuration(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;

  /* GPIOC and GPIOD Periph clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD, ENABLE);

  /* Configure PC.08, PC.09, PC.10, PC.11, PC.12 pin: D0, D1, D2, D3, CLK pin */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOC, &GPIO_InitStructure);

  /* Configure PD.02 CMD line */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
  GPIO_Init(GPIOD, &GPIO_InitStructure);
}

/**
  * @brief  Configures the DMA2 Channel4 for SDIO Tx request.
  * @param BufferSRC: pointer to the source buffer
  * @param BufferSize: buffer size
  * @retval : None
  */
static void DMA_TxConfiguration(uint32_t *BufferSRC, uint32_t BufferSize)
{
  DMA_InitTypeDef DMA_InitStructure;

  DMA_ClearFlag(DMA2_FLAG_TC4 | DMA2_FLAG_TE4 | DMA2_FLAG_HT4 | DMA2_FLAG_GL4);

  /* DMA2 Channel4 disable */
  DMA_Cmd(DMA2_Channel4, DISABLE);

  /* DMA2 Channel4 Config */
  DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)SDIO_FIFO_Address;
  DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)BufferSRC;
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
  DMA_InitStructure.DMA_BufferSize = BufferSize / 4;
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Word;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;
  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
  DMA_Init(DMA2_Channel4, &DMA_InitStructure);

  /* DMA2 Channel4 enable */
  DMA_Cmd(DMA2_Channel4, ENABLE);
}

/**
  * @brief  Configures the DMA2 Channel4 for SDIO Rx request.
  * @param BufferDST: pointer to the destination buffer
  * @param BufferSize: buffer size
  * @retval : None
  */
static void DMA_RxConfiguration(uint32_t *BufferDST, uint32_t BufferSize)
{
  DMA_InitTypeDef DMA_InitStructure;

  DMA_ClearFlag(DMA2_FLAG_TC4 | DMA2_FLAG_TE4 | DMA2_FLAG_HT4 | DMA2_FLAG_GL4);

  /* DMA2 Channel4 disable */
  DMA_Cmd(DMA2_Channel4, DISABLE);

  /* DMA2 Channel4 Config */
  DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)SDIO_FIFO_Address;
  DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)BufferDST;
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
  DMA_InitStructure.DMA_BufferSize = BufferSize / 4;
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Word;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;
  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
  DMA_Init(DMA2_Channel4, &DMA_InitStructure);

  /* DMA2 Channel4 enable */
  DMA_Cmd(DMA2_Channel4, ENABLE);
}

/**
  * @}
  */

/**
  * @}
  */

/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/
