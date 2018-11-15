#include "BasicDataType.h"
#include "GPU_Cfg.h"
#include "MCU_GPU_fsmc.h"
#include "tools.h"
#include <stdio.h>

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



UINT16 RCA;
UINT16 CardCapacityStatus;


void SD_IP_Config_Init(void) {
    //init config register to 400KHz clock, and SD-1bit mode
    //cpu_write_reg(CPU_REG_CONFIG_REG_ADDR, 0x00);
	MCU_GPU__ADDR = MCU_CFG_GPU__SDIP_CONFIG_REG_ADDR;
	MCU_GPU__DATA = 0x0000;
}

//wait command done
UINT8 SD_IP_Wait_Cmd_Done(void) {
    UINT16 rd_data;

    //first wait command being sampled by SD_IP
    //rd_data = cpu_read_reg(CPU_REG_CTRL_REG_ADDR);
	MCU_GPU__ADDR = MCU_CFG_GPU__SDIP_CTRL_REG_ADDR;
	rd_data = MCU_GPU__DATA;
    rd_data &= 0x01;
    while(rd_data) {
        //rd_data = cpu_read_reg(CPU_REG_CTRL_REG_ADDR);
		rd_data = MCU_GPU__DATA;
        rd_data &= 0x01;
    }

    //last read status register of SD_IP
    //rd_data = cpu_read_reg(CPU_REG_STATUS0_REG_ADDR);
	MCU_GPU__ADDR = MCU_CFG_GPU__SDIP_STATUS_REG_ADDR;
	rd_data = MCU_GPU__DATA;
    rd_data &= 0x07;
    while(!rd_data) {
        //rd_data = cpu_read_reg(CPU_REG_STATUS0_REG_ADDR);
		rd_data = MCU_GPU__DATA;
        rd_data &= 0x07; //bit[2]:Response CRC error, bit[1]:Response CRC ok, bit[0]:Response timeout(CMD0, CMD4, CMD15 has no response, will return a timeout) 
    }
//	printf("\r\n-->%x<--\r\n", rd_data);
	
	return (rd_data & 0x05);
}

//wait clear status register done
void SD_IP_Wait_Status_Reg_Clear_Done(void) {
    UINT16 rd_data;

    //rd_data = cpu_read_reg(CPU_REG_CTRL_REG_ADDR);
	MCU_GPU__ADDR = MCU_CFG_GPU__SDIP_CTRL_REG_ADDR;
	rd_data = MCU_GPU__DATA;
    rd_data &= 0x02;
    while(rd_data) {
        //rd_data = cpu_read_reg(CPU_REG_CTRL_REG_ADDR);
		rd_data = MCU_GPU__DATA;
        rd_data &= 0x02;
    }
}

//wait data done
void SD_IP_Wait_Data_Done(void) {
    UINT16 rd_data;

    //rd_data = cpu_read_reg(CPU_REG_STATUS0_REG_ADDR);
	MCU_GPU__ADDR = MCU_CFG_GPU__SDIP_STATUS_REG_ADDR;
	rd_data = MCU_GPU__DATA;
    rd_data &= 0xF8;
    while(!rd_data) {
        //rd_data = cpu_read_reg(CPU_REG_STATUS0_REG_ADDR);
		rd_data = MCU_GPU__DATA;
        rd_data &= 0xF8;
    }
}

//wait clock change done
void SD_IP_Wait_Clock_Change_Done(void) {
    UINT16 rd_data;

//    rd_data = cpu_read_reg(CPU_REG_STATUS1_REG_ADDR);
//    rd_data &= 0x04;
	MCU_GPU__ADDR = MCU_CFG_GPU__SDIP_STATUS_REG_ADDR;
	rd_data = MCU_GPU__DATA;
	rd_data &= 0x0400;
    while(!rd_data) {
//        rd_data = cpu_read_reg(CPU_REG_STATUS1_REG_ADDR);
//        rd_data &= 0x04;
		rd_data = MCU_GPU__DATA;
		rd_data &= 0x0400;
    }
}

//send command without data
UINT8 SD_IP_Send_Cmd_Non_Data(UINT8 index, UINT32 arg) {
//    cpu_write_reg(CPU_REG_ARG0_REG_ADDR, ((UINT8)(arg)));
//    cpu_write_reg(CPU_REG_ARG1_REG_ADDR, ((UINT8)(arg>>8)));
//    cpu_write_reg(CPU_REG_ARG2_REG_ADDR, ((UINT8)(arg>>16)));
//    cpu_write_reg(CPU_REG_ARG3_REG_ADDR, ((UINT8)(arg>>24)));
	MCU_GPU__ADDR = MCU_CFG_GPU__SDIP_ARG01_REG_ADDR;
	MCU_GPU__DATA = (UINT16)arg;
	MCU_GPU__ADDR = MCU_CFG_GPU__SDIP_ARG23_REG_ADDR;
	MCU_GPU__DATA = (UINT16)(arg>>16);
//    cpu_write_reg(CPU_REG_COMMAND_REG_ADDR, (index & 0x3F));
	MCU_GPU__ADDR = MCU_CFG_GPU__SDIP_COMMAND_REG_ADDR;
	MCU_GPU__DATA = (index & 0x003F);
//    cpu_write_reg(CPU_REG_CTRL_REG_ADDR, 0x01);
	MCU_GPU__ADDR = MCU_CFG_GPU__SDIP_CTRL_REG_ADDR;
	MCU_GPU__DATA = 0x0001;
	
    return SD_IP_Wait_Cmd_Done(); //when 0: Response CRC OK; otherwise Response Timeout/CRC Error
}

//send command with data, read from card or write to card
//for SD card: CMD24, CMD25, CMD56, CMD42, CMD27, CMD17, CMD18, CMD30, ACMD51, CMD6, ACMD13, ACMD22
UINT8 SD_IP_Send_Cmd_Has_Data(UINT8 index, UINT32 arg, UINT8 RWFlag, UINT16 BLK_CNT, UINT16 BYTE_CNT) {
    //Write when RWFlag be 1, Read when RWFlag be 0
//    cpu_write_reg(CPU_REG_ARG0_REG_ADDR, ((UINT8)(arg)));
//    cpu_write_reg(CPU_REG_ARG1_REG_ADDR, ((UINT8)(arg>>8)));
//    cpu_write_reg(CPU_REG_ARG2_REG_ADDR, ((UINT8)(arg>>16)));
//    cpu_write_reg(CPU_REG_ARG3_REG_ADDR, ((UINT8)(arg>>24)));
	MCU_GPU__ADDR = MCU_CFG_GPU__SDIP_ARG01_REG_ADDR;
	MCU_GPU__DATA = (UINT16)arg;
	MCU_GPU__ADDR = MCU_CFG_GPU__SDIP_ARG23_REG_ADDR;
	MCU_GPU__DATA = (UINT16)(arg>>16);
    if(RWFlag) {
//        cpu_write_reg(CPU_REG_COMMAND_REG_ADDR, ((index & 0x3F) | 0xC0));
		MCU_GPU__ADDR = MCU_CFG_GPU__SDIP_COMMAND_REG_ADDR;
		MCU_GPU__DATA = ((index & 0x3F) | 0xC0);
    }
    else {
//        cpu_write_reg(CPU_REG_COMMAND_REG_ADDR, ((index & 0x3F) | 0x40));
		MCU_GPU__ADDR = MCU_CFG_GPU__SDIP_COMMAND_REG_ADDR;
		MCU_GPU__DATA = ((index & 0x3F) | 0x40);
    }

//    cpu_write_reg(CPU_REG_BLK_CNT0_REG_ADDR, ((UINT8)(BLK_CNT)));
//    cpu_write_reg(CPU_REG_BLK_CNT1_REG_ADDR, ((UINT8)(BLK_CNT>>8)));
	MCU_GPU__ADDR = MCU_CFG_GPU__SDIP_BLK_CNT_REG_ADDR;
	MCU_GPU__DATA = BLK_CNT;
//    cpu_write_reg(CPU_REG_BYTE_CNT0_REG_ADDR, ((UINT8)(BYTE_CNT)));
//    cpu_write_reg(CPU_REG_BYTE_CNT1_REG_ADDR, ((UINT8)(BYTE_CNT>>8)));
	MCU_GPU__ADDR = MCU_CFG_GPU__SDIP_BYTE_CNT_REG_ADDR;
	MCU_GPU__DATA = BYTE_CNT;

//    cpu_write_reg(CPU_REG_CTRL_REG_ADDR, 0x01);
	MCU_GPU__ADDR = MCU_CFG_GPU__SDIP_CTRL_REG_ADDR;
	MCU_GPU__DATA = 0x0001;
    SD_IP_Wait_Cmd_Done();
    SD_IP_Wait_Data_Done(); //each block will assert 
//			cpu_write_reg(CPU_REG_CTRL_REG_ADDR, 0x02);//clear status register bits of each block
			MCU_GPU__ADDR = MCU_CFG_GPU__SDIP_CTRL_REG_ADDR;
			MCU_GPU__DATA = 0x0002;
			SD_IP_Wait_Status_Reg_Clear_Done();
    
    return 0;
}

//Initialize of SD
UINT8 SD_IP_Card_Init(void)
{
	UINT32 arg;
	UINT16 rd_data;

	//init config register to 400KHz clock, and SD-1bit mode
	SD_IP_Config_Init();

	//CMD0, Resets all cards to idle state
	arg = 0;
	SD_IP_Send_Cmd_Non_Data(CMD0, arg); //CMD0没有Response

	//CMD8, SEND_IF_COND
	arg = 0x000001aa;
	SD_IP_Send_Cmd_Non_Data(CMD8, arg); //Ver2.00及以后版本有Response, 但Ver1.X SD Card没有Response
	
	
	//ACMD41: CMD55+CMD41, SD_SEND_OP_COND
	rd_data = 0;
	while(!rd_data) {
		arg = 0;
		if(0 != SD_IP_Send_Cmd_Non_Data(CMD55, arg)) //Response Timeout/CRC-Error, 可能SD卡没接上
			return 1;
//		SD_IP_Send_Cmd_Non_Data(CMD55, arg);
		arg = 0x40ff8000;
		SD_IP_Send_Cmd_Non_Data(ACMD41, arg);

		//read response
//		rd_data = cpu_read_reg(CPU_REG_RSPNS_REG_ADDR0+3);
		MCU_GPU__ADDR = MCU_CFG_GPU__SDIP_RSPNS23_REG_ADDR;
		rd_data = MCU_GPU__DATA;
		CardCapacityStatus = rd_data & 0x4000; //card capacity status
		rd_data &= 0x8000; //power_up_finish
	}
	
	
	//CMD2, ALL_SEND_CID
	arg = 0;
	SD_IP_Send_Cmd_Non_Data(CMD2, arg);
	
	
	//CMD3, SEND_RELATIVE_ADDR
	arg = 0;
	SD_IP_Send_Cmd_Non_Data(CMD3, arg);
//	rd_data1 = cpu_read_reg((CPU_REG_RSPNS_REG_ADDR0+3));
//	rd_data = cpu_read_reg((CPU_REG_RSPNS_REG_ADDR0+2));
//	RCA = (((UINT16) rd_data1) << 8) | (((UINT16) rd_data) & 0x00FF);
	MCU_GPU__ADDR = MCU_CFG_GPU__SDIP_RSPNS23_REG_ADDR;
	rd_data = MCU_GPU__DATA;
	RCA = rd_data;

	//CMD9, SEND_CSD
	arg = ((UINT32) RCA) << 16;
	SD_IP_Send_Cmd_Non_Data(CMD9, arg);

	//CMD7, SELECT/DESELECT_CARD
	arg = ((UINT32) RCA) << 16;
	SD_IP_Send_Cmd_Non_Data(CMD7, arg);

	//after select card, change clock from 400KHz to 25MHz
//	cpu_write_reg(CPU_REG_CONFIG_REG_ADDR, 0x08);
	MCU_GPU__ADDR = MCU_CFG_GPU__SDIP_CONFIG_REG_ADDR;
	MCU_GPU__DATA = 0x08;
	SD_IP_Wait_Clock_Change_Done();

	//ACMD51, SEND_SCR
	arg = ((UINT32) RCA) << 16;
	SD_IP_Send_Cmd_Non_Data(CMD55, arg);
	arg = 0;
	SD_IP_Send_Cmd_Has_Data(ACMD51, arg, 0, 0, 0x0007); //(UINT8 index, UINT32 arg, UINT8 RWFlag, UINT16 BLK_CNT, UINT16 BYTE_CNT)

	//ACMD6, SET_BUS_WIDTH
	arg = ((UINT32) RCA) << 16;
	SD_IP_Send_Cmd_Non_Data(CMD55, arg);
	arg = 0x00000002;
	SD_IP_Send_Cmd_Non_Data(ACMD6, arg);

	//after SET_BUS_WIDTH, change width to bus_width_kind
//	rd_data = cpu_read_reg(CPU_REG_CONFIG_REG_ADDR);
	MCU_GPU__ADDR = MCU_CFG_GPU__SDIP_CONFIG_REG_ADDR;
	rd_data = MCU_GPU__DATA;
	rd_data = (rd_data & 0xFC) | 0x01; //4bit width
//	cpu_write_reg(CPU_REG_CONFIG_REG_ADDR, rd_data);
	MCU_GPU__DATA = rd_data;
	
	//CMD6 Check function
	arg = 0x00ffff01;
	SD_IP_Send_Cmd_Has_Data(CMD6, arg, 0, 0, 0x003f); //(UINT8 index, UINT32 arg, UINT8 RWFlag, UINT16 BLK_CNT, UINT16 BYTE_CNT)
  
	//CMD6 Switch function, to high speed
	arg = 0x80ffff01;
	SD_IP_Send_Cmd_Has_Data(CMD6, arg, 0, 0, 0x003f); //(UINT8 index, UINT32 arg, UINT8 RWFlag, UINT16 BLK_CNT, UINT16 BYTE_CNT)

  //after change from Normal Speed to High Speed, change clock from 25MHz to 50MHz
//	rd_data = cpu_read_reg(CPU_REG_CONFIG_REG_ADDR);
	MCU_GPU__ADDR = MCU_CFG_GPU__SDIP_CONFIG_REG_ADDR;
	rd_data = MCU_GPU__DATA;
	rd_data = (rd_data & 0xF3) | 0x04; // set 2'b01 to bit[3:2]
//	cpu_write_reg(CPU_REG_CONFIG_REG_ADDR, rd_data);
	MCU_GPU__DATA = rd_data;
	SD_IP_Wait_Clock_Change_Done();

	return 0;
}

//Read SD sector(512bytes each)
//buf: store the read data from SD card
//sector: physical sector number
//cnt: how many sectors/blocks will be read
UINT8 SD_ReadDisk(UINT8 *buf, UINT32 sector, UINT8 cnt)
{
	UINT16 i,j;
	UINT16 blk_cnt;

	blk_cnt = 0;
	if(!CardCapacityStatus)
		sector <<= 9;       //translate into bytes address when Standard SD, under 512bytes per sector

	if(cnt==1)
	{
		SD_IP_Send_Cmd_Has_Data(CMD17, sector, 0, 0, 0x01FF); //(UINT8 index, UINT32 arg, UINT8 RWFlag, UINT16 BLK_CNT, UINT16 BYTE_CNT)
		//read the following data(512bytes) into buf
//		for(i=0; i<512; i++) {
//			*(buf + i) = cpu_read_reg((CPU_REG_BUFFER_REG_ADDR0 + i));
//		}
		MCU_GPU__ADDR = MCU_CFG_GPU__SDIP_BUFFER_CTRL_REG_ADDR;
		MCU_GPU__DATA = 0x0000;
		MCU_GPU__ADDR = MCU_CFG_GPU__SDIP_BUFFER_DATA_REG_ADDR;
		for(i=0; i<512; i+=2) {
			*((UINT16 *)(buf + i)) = MCU_GPU__DATA;
		}
	}
	else
	{
		blk_cnt = cnt - 1;
		SD_IP_Send_Cmd_Has_Data(CMD18, sector, 0, blk_cnt, 0x01FF); //(UINT8 index, UINT32 arg, UINT8 RWFlag, UINT16 BLK_CNT, UINT16 BYTE_CNT)
		SD_IP_Send_Cmd_Non_Data(CMD12, 0);
//		for(j=0; j<cnt; j++) {
//			//each block 512bytes
//			for(i=0; i<512; i++) {
//				*(buf + i + j*512) = cpu_read_reg((CPU_REG_BUFFER_REG_ADDR0 + i + j*512));
//			}
//		}
		
		MCU_GPU__ADDR = MCU_CFG_GPU__SDIP_BUFFER_CTRL_REG_ADDR;
		MCU_GPU__DATA = 0x0000;
		MCU_GPU__ADDR = MCU_CFG_GPU__SDIP_BUFFER_DATA_REG_ADDR;
		for(j=0; j<cnt; j++) {
			//each block 512bytes
			for(i=0; i<512; i+=2) {
				*((UINT16 *)(buf + i + j*512)) = MCU_GPU__DATA;
			}
		}
	}

	return 0;
}

//Write SD sector(512bytes each)
//buf: store the data that will be written into SD card
//sector: physical sector number
//cnt: how many sectors/blocks will be written
UINT8 SD_WriteDisk(UINT8 *buf, UINT32 sector, UINT8 cnt)
{
    UINT16 i,j;
    UINT16 blk_cnt;

    if(!CardCapacityStatus)
        sector <<= 9;                     //translate into bytes address when Standard SD, under 512bytes per sector

    if(cnt==1) {
//        for(i=0; i<512; i++) {
//            cpu_write_reg((CPU_REG_BUFFER_REG_ADDR0 + i), *(buf + i));
//        }
		MCU_GPU__ADDR = MCU_CFG_GPU__SDIP_BUFFER_CTRL_REG_ADDR;
		MCU_GPU__DATA = 0x0000;
		MCU_GPU__ADDR = MCU_CFG_GPU__SDIP_BUFFER_DATA_REG_ADDR;
        for(i=0; i<512; i+=2) {
            MCU_GPU__DATA = *((UINT16 *)(buf + i));
        }
        //Single block write
        SD_IP_Send_Cmd_Has_Data(CMD24, sector, 1, 0, 0x01FF); //(UINT8 index, UINT32 arg, UINT8 RWFlag, UINT16 BLK_CNT, UINT16 BYTE_CNT)
    }
    else
    {
//        for(j=0; j<cnt; j++) {
//            //each block 512bytes
//            for(i=0; i<512; i++) {
//                 cpu_write_reg((CPU_REG_BUFFER_REG_ADDR0 + i + j*512), *(buf + i + j*512));
//            }
//        }
		MCU_GPU__ADDR = MCU_CFG_GPU__SDIP_BUFFER_CTRL_REG_ADDR;
		MCU_GPU__DATA = 0x0000;
		MCU_GPU__ADDR = MCU_CFG_GPU__SDIP_BUFFER_DATA_REG_ADDR;
        for(j=0; j<cnt; j++) {
            //each block 512bytes
            for(i=0; i<512; i+=2) {
                 MCU_GPU__DATA = *((UINT16 *)(buf + i + j*512));
            }
        }
        blk_cnt = cnt - 1;
        SD_IP_Send_Cmd_Has_Data(CMD25, sector, 1, blk_cnt, 0x01FF); //(UINT8 index, UINT32 arg, UINT8 RWFlag, UINT16 BLK_CNT, UINT16 BYTE_CNT)
        SD_IP_Send_Cmd_Non_Data(CMD12, 0);
    }

    return 0;
}


//Read SD sector(512bytes each)
//buf: store the read data from SD card
//sector: physical sector number/address
//cnt: how many sectors/blocks will be read (Max: 65536 blocks), 因为SD卡每次读Block命令发出到数据返回需要等待的时间基本都是ms级的, 所以一次读取的Block个数越多读取效率越高
UINT8 SD_ReadDisk_to_FIFO(UINT32 sector, UINT16 cnt)
{
	UINT16 blk_cnt;
//	cnt = 80; //burst 96 block(512Byte)

	blk_cnt = 0;
	if(!CardCapacityStatus)
		sector <<= 9;       //translate into bytes address when Standard SD, under 512bytes per sector

//	//Select the FIFO channel
//	MCU_GPU__ADDR = MCU_CFG_GPU__SDIP_BUFFER_CTRL_REG_ADDR;
//	MCU_GPU__DATA = 0x1000; //bit[12], 1 mean select SDIP to DDR FIFO channel; 0 mean select SD-MCU-buffer;

	blk_cnt = cnt - 1;
	SD_IP_Send_Cmd_Has_Data(CMD18, sector, 0, blk_cnt, 0x01FF); //(UINT8 index, UINT32 arg, UINT8 RWFlag, UINT16 BLK_CNT, UINT16 BYTE_CNT)
	SD_IP_Send_Cmd_Non_Data(CMD12, 0);
  
  return 0;
}

