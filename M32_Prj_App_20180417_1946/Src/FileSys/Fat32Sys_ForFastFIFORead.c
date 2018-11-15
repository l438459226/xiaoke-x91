#include "BasicDataType.h"
#include "GPU_Cfg.h"
#include <stdio.h>
#include "MCU_GPU_fsmc.h"
#include "tools.h"


//读BMP的速度参数如下:
//SDIO Bus Clock = 50MHz;
//SDIO Bus Width = 4bit;
//理论读取速度为50MHz*4bit=25MByte/s, 即1080p的BMP图片<5.93MB>最快读取并显示时间为 5.93MB/25MB = 0.24s;
//


UINT32 Logic0_SectorIndex; //逻辑0扇区的物理扇区起始地址, 从第0物理扇区的0x01C6~0x01C9共4个Byte可以获取

//从逻辑0扇区里抽取出
UINT16 BPB_BytsPerSec; //Count of bytes per sector, 只能是512/1024/2048/4096这四个中的一个, 大部分是512;
UINT8 BPB_SecPerClus; //Number of sectors per allocation unit, 2的幂次倍, 1,2,4,8,16,32,64,128.
UINT16 BPB_RsvdSecCnt; //Number of reserved sectors in the Reserved region of the volume starting at the first sector of the volume.
UINT8 BPB_NumFATs; //The count of FAT data structures on the volume.
UINT32 BPB_FATSz32; //This field is the FAT32 32-bit count of sectors occupied by ONE FAT.
UINT32 BPB_RootClus; //This is set to the cluster number of the first cluster of the root directory, usually 2 but not required to be 2.

//文件目录项
UINT32 RootSectorIndexStart; //根目录所在扇区起始地址
UINT32 FAT1_SectorIndexStart; //FAT1所在扇区起始地址

#define BMP_MAX_NUM 10
FAT32_BMP_ENTRY BMPInfo[BMP_MAX_NUM] = {0};


UINT8 SD_Buf[4096];
void ExtractBPB_Param(void) {
	SD_ReadDisk(SD_Buf, 0, 1);
	
	
	if(SD_Buf[510] == 0x55 && SD_Buf[511] == 0xAA) {
		if(SD_Buf[0] == 0xEB || SD_Buf[0] == 0xE9) { //DBR前面的隐藏扇区数为0;
			Logic0_SectorIndex = 0;
		}
		else {
			Logic0_SectorIndex = *((UINT32*)(&SD_Buf[0x01C6])); //注意大小端
			printf("\r\n--%d--\r\n", Logic0_SectorIndex);
			SD_ReadDisk(SD_Buf, Logic0_SectorIndex, 1);
		}
			
//		{
//			int i;
//			for(i=0; i<512; i++) {
//				if(i%16 == 0)
//					printf("\r\n");
//				else if(i%8 == 0)
//					printf("  ");
//				
//	//			if(i%512 == 0)
//	//				printf("\r\n");
//				printf("%02X ", SD_Buf[i]);
//			}
//			printf("\r\n");
//		}
		if(SD_Buf[510] == 0x55 && SD_Buf[511] == 0xAA) {
			BPB_BytsPerSec = *((UINT16*)(&SD_Buf[0x0B]));
			BPB_SecPerClus = SD_Buf[0x0D];
			BPB_RsvdSecCnt = *((UINT16*)(&SD_Buf[0x0E]));
			BPB_NumFATs = SD_Buf[0x10];
			BPB_FATSz32 = *((UINT32*)(&SD_Buf[0x24]));
			BPB_RootClus = *((UINT32*)(&SD_Buf[0x2C]));
			
			FAT1_SectorIndexStart = Logic0_SectorIndex + (UINT32)BPB_RsvdSecCnt;
			printf("\r\n%d, %d, %d, %d, %d, %d\r\n", BPB_BytsPerSec, BPB_SecPerClus, BPB_RsvdSecCnt, BPB_NumFATs, BPB_FATSz32, BPB_RootClus);
		}
		else {
			printf("\r\nLogic0 Sector Read Error!\r\n");
			return;
		}
	}
	else {
		printf("\r\nPhy0 Sector Read Error!\r\n");
		return;
	}
}



//void FindALLBMP_Entry(FAT32_BMP_ENTRY *ptrDirEntry) { //只支持根目录下的
void FindALLBMP_Entry(void) { //只支持根目录下的
	int i;
	UINT16 BmpNum;
	UINT8 NumH, NumL;
	UINT16 FstClusHI, FstClusLO;
	
	RootSectorIndexStart = Logic0_SectorIndex + (UINT32)BPB_RsvdSecCnt + ((UINT32)BPB_NumFATs)*BPB_FATSz32; //
	SD_ReadDisk(SD_Buf, RootSectorIndexStart, 4);
	
	for(i=0; i<512*4; i+=32) {
		if(SD_Buf[i] == 'F' && SD_Buf[i+3] == 0x20) {
			if(SD_Buf[i+1] < 0x40 && SD_Buf[i+2] < 0x40 && SD_Buf[i+1] > 0x29 && SD_Buf[i+2] > 0x29) {
				NumH = (SD_Buf[i+1] - 0x30);
				NumL = (SD_Buf[i+2] - 0x30);
				BmpNum = ((UINT16)NumH)*10 + NumL;
				if(BmpNum < BMP_MAX_NUM) { //数值过大不支持
					//ptrDirEntry[BmpNum].FileSize = *((UINT32*)(&SD_Buf[i+28]));
					BMPInfo[BmpNum].FileSize = *((UINT32*)(&SD_Buf[i+28]));
					FstClusHI = *((UINT16*)(&SD_Buf[i+20]));
					FstClusLO = *((UINT16*)(&SD_Buf[i+26]));
					//ptrDirEntry[BmpNum].FileFstClus = (((UINT32)FstClusHI) << 16) | ((UINT32)FstClusLO);
					BMPInfo[BmpNum].FileFstClus = (((UINT32)FstClusHI) << 16) | ((UINT32)FstClusLO);
				}
			}
		}
	}
}

void DisplayBMP(UINT16 Num) { //Use FIFO channel for fast display
	UINT32 BMPStartSector;
	UINT32 SectorCnt;
	UINT32 iBMPStartSector;
	UINT32 iSectorCnt;
	UINT8 ddr_current_display_region_addr;
	UINT16 valueH;
	
	BMPStartSector = RootSectorIndexStart + (BMPInfo[Num].FileFstClus - BPB_RootClus) * (UINT32)BPB_SecPerClus;
	SectorCnt = (BMPInfo[Num].FileSize >> 9) + 1; // FileSize/512 + 1
	
	printf("\r\nBMP: %d, %d\r\n", BMPStartSector, SectorCnt);
	
	
	//Select the FIFO channel of BMP display(FIFO-BUF-DDR), not MCU-BUF-DDR,
	MCU_GPU__ADDR = MCU_CFG_GPU__SDIP_BUFFER_CTRL_REG_ADDR;
	MCU_GPU__DATA = 0x1000; //bit[12], 1 mean select SDIP to DDR FIFO channel; 0 mean select SD-MCU-buffer;
	
	MCU_GPU__ADDR = MCU_CFG_GPU__DDR_FRAMEREGION_READ_START_ADDR;//read the current display region, [29:26] of DDR-BYTE-ADDRESS
	ddr_current_display_region_addr = MCU_GPU__DATA;
	
	
	//Reset FIFO to clear FIFO
	MCU_GPU__ADDR = MCU_CFG_GPU__SDIP_FIFO_RESET_ADDR;
	MCU_GPU__DATA = 0x0003; //bit[0], 1 mean Reset FIFO
	delayus(1);
	MCU_GPU__DATA = 0x0002;
	
	//Set DDR page address of Write
	if(ddr_current_display_region_addr == 0) { //process with ddr-byte-addr[26]
		valueH = 0x0400;
	}
	else {
		valueH = 0x0000;
	}
	MCU_GPU__ADDR = MCU_CFG_GPU__DDR_ACCESS_BYTE_ADDR1;
	MCU_GPU__DATA = valueH;
	MCU_GPU__ADDR = MCU_CFG_GPU__DDR_ACCESS_BYTE_ADDR0;
	MCU_GPU__DATA = 0x0000;
	
	//
	iSectorCnt = SectorCnt;
	iBMPStartSector = BMPStartSector;
//	while(iSectorCnt > 512) {
//		SD_ReadDisk_to_FIFO(iBMPStartSector, 512);
//		iSectorCnt -= 512;
//		iBMPStartSector += 512;
//	}
	SD_ReadDisk_to_FIFO(iBMPStartSector, iSectorCnt); //每次读取的block个数越多, SDIO总线效率越高
	
	
	//update the figure display region in DDR
	if(ddr_current_display_region_addr == 0) {
		MCU_GPU__ADDR = MCU_CFG_GPU__DDR_FRAMEREGION_READ_START_ADDR;
		MCU_GPU__DATA = 0x01;
	}
	else {
		MCU_GPU__ADDR = MCU_CFG_GPU__DDR_FRAMEREGION_READ_START_ADDR;
		MCU_GPU__DATA = 0x00;
	}
	
	//close pure color mode to BMP display mode, if previous display is Pure-Color-Mode
	{
		MCU_GPU__ADDR = MCU_CFG_GPU__PURECOLOR_ADDR1;
		MCU_GPU__DATA = 0x0000;
	}
}
