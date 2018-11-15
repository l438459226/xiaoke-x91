/**
  ******************************************************************************
  * @file SDIO/sdcard.h 
  * @author  MCD Application Team
  * @version  V3.0.0
  * @date  04/06/2009
  * @brief  This file contains all the functions prototypes for the
*                      SD Card driver firmware library.
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

/** @addtogroup StdPeriph_Examples
  * @{
  */

/** @addtogroup SDIO_Example
  * @{
  */ 

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SDCARD_H
#define __SDCARD_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
//#include "bsp_sdio_sdcard.h"

/* Exported types ------------------------------------------------------------*/
typedef enum
{
  /* SDIO specific error defines */
  MISD_CMD_CRC_FAIL                    = (1), /* Command response received (but CRC check failed) */
  MISD_DATA_CRC_FAIL                   = (2), /* Data bock sent/received (CRC check Failed) */
  MISD_CMD_RSP_TIMEOUT                 = (3), /* Command response timeout */
  MISD_DATA_TIMEOUT                    = (4), /* Data time out */
  MISD_TX_UNDERRUN                     = (5), /* Transmit FIFO under-run */
  MISD_RX_OVERRUN                      = (6), /* Receive FIFO over-run */
  MISD_START_BIT_ERR                   = (7), /* Start bit not detected on all data signals in widE bus mode */
  MISD_CMD_OUT_OF_RANGE                = (8), /* CMD's argument was out of range.*/
  MISD_ADDR_MISALIGNED                 = (9), /* Misaligned address */
  MISD_BLOCK_LEN_ERR                   = (10), /* Transferred block length is not allowed for the card or the number of transferred bytes does not match the block length */
  MISD_ERASE_SEQ_ERR                   = (11), /* An error in the sequence of erase command occurs.*/
  MISD_BAD_ERASE_PARAM                 = (12), /* An Invalid selection for erase groups */
  MISD_WRITE_PROT_VIOLATION            = (13), /* Attempt to program a write protect block */
  MISD_LOCK_UNLOCK_FAILED              = (14), /* Sequence or password error has been detected in unlock command or if there was an attempt to access a locked card */
  MISD_COM_CRC_FAILED                  = (15), /* CRC check of the previous command failed */
  MISD_ILLEGAL_CMD                     = (16), /* Command is not legal for the card state */
  MISD_CARD_ECC_FAILED                 = (17), /* Card internal ECC was applied but failed to correct the data */
  MISD_CC_ERROR                        = (18), /* Internal card controller error */
  MISD_GENERAL_UNKNOWN_ERROR           = (19), /* General or Unknown error */
  MISD_STREAM_READ_UNDERRUN            = (20), /* The card could not sustain data transfer in stream read operation. */
  MISD_STREAM_WRITE_OVERRUN            = (21), /* The card could not sustain data programming in stream mode */
  MISD_CID_CMISD_OVERWRITE               = (22), /* CID/CSD overwrite error */
  MISD_WP_ERASE_SKIP                   = (23), /* only partial address space was erased */
  MISD_CARD_ECC_DISABLED               = (24), /* Command has been executed without using internal ECC */
  MISD_ERASE_RESET                     = (25), /* Erase sequence was cleared before executing because an out of erase sequence command was received */
  MISD_AKE_SEQ_ERROR                   = (26), /* Error in sequence of authentication. */
  MISD_INVALID_VOLTRANGE               = (27),
  MISD_ADDR_OUT_OF_RANGE               = (28),
  MISD_SWITCH_ERROR                    = (29),
  MISD_SDIO_DISABLED                   = (30),
  MISD_SDIO_FUNCTION_BUSY              = (31),
  MISD_SDIO_FUNCTION_FAILED            = (32),
  MISD_SDIO_UNKNOWN_FUNCTION           = (33),

  /* Standard error defines */
  MISD_INTERNAL_ERROR, 
  MISD_NOT_CONFIGURED,
  MISD_REQUEST_PENDING, 
  MISD_REQUEST_NOT_APPLICABLE, 
  MISD_INVALID_PARAMETER,  
  MISD_UNSUPPORTED_FEATURE,  
  MISD_UNSUPPORTED_HW,  
  MISD_ERROR,  
  MISD_OK,  
} MISD_Error;

/* SDIO Commands  Index */
#define SDIO_GO_IDLE_STATE                       ((uint8_t)0)
#define SDIO_SEND_OP_COND                        ((uint8_t)1)
#define SDIO_ALL_SEND_CID                        ((uint8_t)2)
#define SDIO_SET_REL_ADDR                        ((uint8_t)3) /* SDIO_SEND_REL_ADDR for SD Card */
#define SDIO_SET_DSR                             ((uint8_t)4)
#define SDIO_SDIO_SEN_OP_COND                    ((uint8_t)5)
#define SDIO_HS_SWITCH                           ((uint8_t)6)
#define SDIO_SEL_DESEL_CARD                      ((uint8_t)7)
#define SDIO_HS_SEND_EXT_CSD                     ((uint8_t)8)
#define SDIO_SEND_CSD                            ((uint8_t)9)
#define SDIO_SEND_CID                            ((uint8_t)10)
#define SDIO_READ_DAT_UNTIL_STOP                 ((uint8_t)11) /* SD Card doesn't support it */
#define SDIO_STOP_TRANSMISSION                   ((uint8_t)12)
#define SDIO_SEND_STATUS                         ((uint8_t)13)
#define SDIO_HS_BUSTEST_READ                     ((uint8_t)14)
#define SDIO_GO_INACTIVE_STATE                   ((uint8_t)15)
#define SDIO_SET_BLOCKLEN                        ((uint8_t)16)//MISD_CMD_SET_BLOCKLEN
#define SDIO_READ_SINGLE_BLOCK                   ((uint8_t)17)
#define SDIO_READ_MULT_BLOCK                     ((uint8_t)18)
#define SDIO_HS_BUSTEST_WRITE                    ((uint8_t)19)
#define SDIO_WRITE_DAT_UNTIL_STOP                ((uint8_t)20) /* SD Card doesn't support it */
#define SDIO_SET_BLOCK_COUNT                     ((uint8_t)23) /* SD Card doesn't support it */
#define SDIO_WRITE_SINGLE_BLOCK                  ((uint8_t)24)
#define SDIO_WRITE_MULT_BLOCK                    ((uint8_t)25)
#define SDIO_PROG_CID                            ((uint8_t)26) /* reserved for manufacturers */
#define SDIO_PROG_CSD                            ((uint8_t)27)
#define SDIO_SET_WRITE_PROT                      ((uint8_t)28)
#define SDIO_CLR_WRITE_PROT                      ((uint8_t)29)
#define SDIO_SEND_WRITE_PROT                     ((uint8_t)30)
#define SDIO_MISD_ERASE_GRP_START                  ((uint8_t)32) /* To set the address of the first write
                                                                  block to be erased. (For SD card only) */
#define SDIO_MISD_ERASE_GRP_END                    ((uint8_t)33) /* To set the address of the last write block of the
                                                                  continuous range to be erased. (For SD card only) */
#define SDIO_ERASE_GRP_START                     ((uint8_t)35) /* To set the address of the first write block to be erased.
                                                                  (For MMC card only spec 3.31) */

#define SDIO_ERASE_GRP_END                       ((uint8_t)36) /* To set the address of the last write block of the
                                                                  continuous range to be erased. (For MMC card only spec 3.31) */

#define SDIO_ERASE                               ((uint8_t)38)
#define SDIO_FAST_IO                             ((uint8_t)39) /* SD Card doesn't support it */
#define SDIO_GO_IRQ_STATE                        ((uint8_t)40) /* SD Card doesn't support it */
#define SDIO_LOCK_UNLOCK                         ((uint8_t)42)
#define SDIO_APP_CMD                             ((uint8_t)55)
#define SDIO_GEN_CMD                             ((uint8_t)56)
#define SDIO_NO_CMD                              ((uint8_t)64)

/* Following commands are SD Card Specific commands.
   SDIO_APP_CMD should be sent before sending these
   commands. */
#define SDIO_APP_MISD_SET_BUSWIDTH                 ((uint8_t)6)  /* For SD Card only */
#define SDIO_MISD_APP_STAUS                        ((uint8_t)13) /* For SD Card only */
#define SDIO_MISD_APP_SEND_NUM_WRITE_BLOCKS        ((uint8_t)22) /* For SD Card only */
#define SDIO_MISD_APP_OP_COND                      ((uint8_t)41) /* For SD Card only */
#define SDIO_MISD_APP_SET_CLR_CARD_DETECT          ((uint8_t)42) /* For SD Card only */
#define SDIO_MISD_APP_SEND_SCR                     ((uint8_t)51) /* For SD Card only */
#define SDIO_SDIO_RW_DIRECT                      ((uint8_t)52) /* For SD I/O Card only */
#define SDIO_SDIO_RW_EXTENDED                    ((uint8_t)53) /* For SD I/O Card only */

/* Following commands are SD Card Specific security commands.
   SDIO_APP_CMD should be sent before sending these commands. */
#define SDIO_MISD_APP_GET_MKB                      ((uint8_t)43) /* For SD Card only */
#define SDIO_MISD_APP_GET_MID                      ((uint8_t)44) /* For SD Card only */
#define SDIO_MISD_APP_SET_CER_RN1                  ((uint8_t)45) /* For SD Card only */
#define SDIO_MISD_APP_GET_CER_RN2                  ((uint8_t)46) /* For SD Card only */
#define SDIO_MISD_APP_SET_CER_RES2                 ((uint8_t)47) /* For SD Card only */
#define SDIO_MISD_APP_GET_CER_RES1                 ((uint8_t)48) /* For SD Card only */
#define SDIO_MISD_APP_SECURE_READ_MULTIPLE_BLOCK   ((uint8_t)18) /* For SD Card only */
#define SDIO_MISD_APP_SECURE_WRITE_MULTIPLE_BLOCK  ((uint8_t)25) /* For SD Card only */
#define SDIO_MISD_APP_SECURE_ERASE                 ((uint8_t)38) /* For SD Card only */
#define SDIO_MISD_APP_CHANGE_SECURE_AREA           ((uint8_t)49) /* For SD Card only */
#define SDIO_MISD_APP_SECURE_WRITE_MKB             ((uint8_t)48) /* For SD Card only */

typedef enum
{
  MISD_NO_TRANSFER  = 0,
  MISD_TRANSFER_IN_PROGRESS
} MISDTransferState;

typedef struct
{
  uint16_t TransferredBytes;
  MISD_Error TransferError;
  uint8_t  padding;
} SDLastTransferInfo;

typedef struct       /* Card Specific Data */
{
  __IO uint8_t  CSDStruct;            /* CSD structure */
  __IO uint8_t  SysSpecVersion;       /* System specification version */
  __IO uint8_t  Reserved1;            /* Reserved */
  __IO uint8_t  TAAC;                 /* Data read access-time 1 */
  __IO uint8_t  NSAC;                 /* Data read access-time 2 in CLK cycles */
  __IO uint8_t  MaxBusClkFrec;        /* Max. bus clock frequency */
  __IO uint16_t CardComdClasses;      /* Card command classes */
  __IO uint8_t  RdBlockLen;           /* Max. read data block length */
  __IO uint8_t  PartBlockRead;        /* Partial blocks for read allowed */
  __IO uint8_t  WrBlockMisalign;      /* Write block misalignment */
  __IO uint8_t  RdBlockMisalign;      /* Read block misalignment */
  __IO uint8_t  DSRImpl;              /* DSR implemented */
  __IO uint8_t  Reserved2;            /* Reserved */
  __IO uint32_t DeviceSize;           /* Device Size */
  __IO uint8_t  MaxRdCurrentVDDMin;   /* Max. read current @ VDD min */
  __IO uint8_t  MaxRdCurrentVDDMax;   /* Max. read current @ VDD max */
  __IO uint8_t  MaxWrCurrentVDDMin;   /* Max. write current @ VDD min */
  __IO uint8_t  MaxWrCurrentVDDMax;   /* Max. write current @ VDD max */
  __IO uint8_t  DeviceSizeMul;        /* Device size multiplier */
  __IO uint8_t  EraseGrSize;          /* Erase group size */
  __IO uint8_t  EraseGrMul;           /* Erase group size multiplier */
  __IO uint8_t  WrProtectGrSize;      /* Write protect group size */
  __IO uint8_t  WrProtectGrEnable;    /* Write protect group enable */
  __IO uint8_t  ManDeflECC;           /* Manufacturer default ECC */
  __IO uint8_t  WrSpeedFact;          /* Write speed factor */
  __IO uint8_t  MaxWrBlockLen;        /* Max. write data block length */
  __IO uint8_t  WriteBlockPaPartial;  /* Partial blocks for write allowed */
  __IO uint8_t  Reserved3;            /* Reserded */
  __IO uint8_t  ContentProtectAppli;  /* Content protection application */
  __IO uint8_t  FileFormatGrouop;     /* File format group */
  __IO uint8_t  CopyFlag;             /* Copy flag (OTP) */
  __IO uint8_t  PermWrProtect;        /* Permanent write protection */
  __IO uint8_t  TempWrProtect;        /* Temporary write protection */
  __IO uint8_t  FileFormat;           /* File Format */
  __IO uint8_t  ECC;                  /* ECC code */
  __IO uint8_t  CMISD_CRC;              /* CSD CRC */
  __IO uint8_t  Reserved4;            /* always 1*/
} MISD_CSD;

typedef struct      /*Card Identification Data*/
{
  __IO uint8_t  ManufacturerID;       /* ManufacturerID */
  __IO uint16_t OEM_AppliID;          /* OEM/Application ID */
  __IO uint32_t ProdName1;            /* Product Name part1 */
  __IO uint8_t  ProdName2;            /* Product Name part2*/
  __IO uint8_t  ProdRev;              /* Product Revision */
  __IO uint32_t ProdSN;               /* Product Serial Number */
  __IO uint8_t  Reserved1;            /* Reserved1 */
  __IO uint16_t ManufactDate;         /* Manufacturing Date */
  __IO uint8_t  CID_CRC;              /* CID CRC */
  __IO uint8_t  Reserved2;            /* always 1 */
} MISD_CID;

typedef struct
{
  MISD_CSD MISD_csd;
  MISD_CID MISD_cid;
  uint32_t CardCapacity; /* Card Capacity */
  uint32_t CardBlockSize; /* Card Block Size */
  uint16_t RCA;
  uint8_t CardType;
} MISD_CardInfo;

/* Exported constants --------------------------------------------------------*/
#define MISD_DMA_MODE                     ((uint32_t)0x00000000)
#define MISD_INTERRUPT_MODE               ((uint32_t)0x00000001)
#define MISD_POLLING_MODE                 ((uint32_t)0x00000002)


/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
MISD_Error MISD_Init(void);
MISD_Error MISD_PowerON(void);
MISD_Error MISD_PowerOFF(void);
MISD_Error MISD_InitializeCards(void);
MISD_Error MISD_GetCardInfo(MISD_CardInfo *cardinfo);
MISD_Error MISD_EnableWideBusOperation(uint32_t WideMode);
MISD_Error MISD_SetDeviceMode(uint32_t Mode);
MISD_Error MISD_SelectDeselect(uint32_t addr);
MISD_Error MISD_ReadBlock(uint32_t addr, uint32_t *readbuff, uint16_t BlockSize);
MISD_Error MISD_ReadMultiBlocks(uint32_t addr, uint32_t *readbuff, uint16_t BlockSize, uint32_t NumberOfBlocks);
MISD_Error MISD_WriteBlock(uint32_t addr, uint32_t *writebuff, uint16_t BlockSize);
MISD_Error MISD_WriteMultiBlocks(uint32_t addr, uint32_t *writebuff, uint16_t BlockSize, uint32_t NumberOfBlocks);
MISDTransferState MISD_GetTransferState(void);
MISD_Error MISD_StopTransfer(void);
MISD_Error MISD_Erase(uint32_t startaddr, uint32_t endaddr);
MISD_Error MISD_SendStatus(uint32_t *pcardstatus);
MISD_Error MISD_SendSDStatus(uint32_t *psdstatus);
MISD_Error MISD_ProcessIRQSrc(void);

#endif /* __SDCARD_H */

/**
  * @}
  */

/**
  * @}
  */
  
/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/
