#ifndef __SD_H__
#define __SD_H__

#include "BasicDataType.h"

#define SD_HC_IP_BASE_ADDR	        0x040000

#define CPU_REG_ARG0_REG_ADDR       (SD_HC_IP_BASE_ADDR + 0x00)
#define CPU_REG_ARG1_REG_ADDR       (SD_HC_IP_BASE_ADDR + 0x01)
#define CPU_REG_ARG2_REG_ADDR       (SD_HC_IP_BASE_ADDR + 0x02)
#define CPU_REG_ARG3_REG_ADDR       (SD_HC_IP_BASE_ADDR + 0x03)
#define CPU_REG_COMMAND_REG_ADDR    (SD_HC_IP_BASE_ADDR + 0x04)
#define CPU_REG_BLK_CNT0_REG_ADDR   (SD_HC_IP_BASE_ADDR + 0x08)
#define CPU_REG_BLK_CNT1_REG_ADDR   (SD_HC_IP_BASE_ADDR + 0x09)
#define CPU_REG_BYTE_CNT0_REG_ADDR  (SD_HC_IP_BASE_ADDR + 0x0C)
#define CPU_REG_BYTE_CNT1_REG_ADDR  (SD_HC_IP_BASE_ADDR + 0x0D)
#define CPU_REG_CTRL_REG_ADDR       (SD_HC_IP_BASE_ADDR + 0x10)
#define CPU_REG_CONFIG_REG_ADDR     (SD_HC_IP_BASE_ADDR + 0x14)
#define CPU_REG_INTR_ENABLE_ADDR    (SD_HC_IP_BASE_ADDR + 0x18)
#define CPU_REG_STATUS0_REG_ADDR    (SD_HC_IP_BASE_ADDR + 0x1C)
#define CPU_REG_STATUS1_REG_ADDR    (SD_HC_IP_BASE_ADDR + 0x1D)
#define CPU_REG_RSPNS_REG_ADDR0     (SD_HC_IP_BASE_ADDR + 0x20)
#define CPU_REG_BUFFER_REG_ADDR0    (SD_HC_IP_BASE_ADDR + 0x2000)


#define CMD0    0
#define CMD2    2
#define CMD3    3
#define CMD6    6
#define CMD7    7
#define CMD8    8
#define CMD9    9
#define CMD12   12
#define CMD24   24
#define CMD25   25
#define CMD17   17
#define CMD18   18

#define CMD55   55
#define ACMD41  41
#define ACMD51  51
#define ACMD6   6


extern UINT16 RCA;
extern UINT8 CardCapacityStatus;


void cpu_write_reg(UINT32 addr, U8 dat);
U8 cpu_read_reg(UINT32 addr);
void SD_IP_Config_Init(void);
void SD_IP_Wait_Cmd_Done(void);
void SD_IP_Wait_Data_Done(void);
void SD_IP_Wait_Clock_Change_Done(void);
UINT8 SD_IP_Send_Cmd_Non_Data(UINT8 index, UINT32 arg);
UINT8 SD_IP_Send_Cmd_Has_Data(UINT8 index, UINT32 arg, UINT8 RWFlag, UINT16 BLK_CNT, UINT16 BYTE_CNT);
UINT8 SD_IP_Card_Init(void);
UINT8 SD_ReadDisk(UINT8 *buf, UINT32 sector, UINT8 cnt);
UINT8 SD_WriteDisk(UINT8 *buf, UINT32 sector, UINT8 cnt);


#endif
