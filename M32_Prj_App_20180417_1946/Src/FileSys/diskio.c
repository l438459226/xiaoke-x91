/*-----------------------------------------------------------------------*/
/* Low level disk I/O module skeleton for FatFs     (C)ChaN, 2014        */
/*-----------------------------------------------------------------------*/
/* If a working storage control module is available, it should be        */
/* attached to the FatFs via a glue function rather than modifying it.   */
/* This is an example of glue functions to attach various exsisting      */
/* storage control modules to the FatFs module with a defined API.       */
/*-----------------------------------------------------------------------*/

#include "diskio.h"		/* FatFs lower layer API */
#include "sd.h"		/* Example: MMC/SDC contorl */

/* Definitions of physical drive number for each drive */
#define ATA		0	/* Example: Map ATA drive to drive number 0 */
#define MMC		1	/* Example: Map MMC/SD card to drive number 1 */
#define USB		2	/* Example: Map USB drive to drive number 2 */


/*-----------------------------------------------------------------------*/
/* Initialize Disk Drive                                                 */
/*-----------------------------------------------------------------------*/
DSTATUS disk_initialize (
	BYTE drv		/* Physical drive number (0) */
)
{
	BYTE rets;

	if (drv) return STA_NOINIT;			/* Supports only single drive */
		rets = SD_IP_Card_Init();
	if(rets)
		return STA_NODISK;
		
	return rets;
}

/*-----------------------------------------------------------------------*/
/* Get Disk Status                                                       */
/*-----------------------------------------------------------------------*/
DSTATUS disk_status (
	BYTE drv		/* Physical drive number (0) */
)
{
	if (drv) return STA_NOINIT;		/* Supports only single drive */
	return 0;//Stat;
}

/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */
/*-----------------------------------------------------------------------*/
DRESULT disk_read (
	BYTE drv,			/* Physical drive number (0) */
	BYTE *buff,			/* Pointer to the data buffer to store read data */
	DWORD sector,		/* Start sector number (LBA) */
	BYTE count			/* Sector count (1..255) */
)
{
	BYTE rets;
	if (drv || !count) return RES_PARERR;
//	if (Stat & STA_NOINIT) return RES_NOTRDY;

//buf: store the read data from SD card
//sector: physical sector number/address
//cnt: how many sectors/blocks will be read
//uint8_t SD_ReadDisk(uint8_t *buf, uint32_t sector, uint8_t cnt)
  rets = SD_ReadDisk(buff, sector, count);
	
	return (DRESULT)rets;//RES_OK or RES_ERROR
}

/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */
/*-----------------------------------------------------------------------*/

DRESULT disk_write (
	BYTE drv,			/* Physical drive number (0) */
	const BYTE *buff,	/* Pointer to the data to be written */
	DWORD sector,		/* Start sector number (LBA) */
	BYTE count			/* Sector count (1..255) */
)
{
	BYTE rets;
	if (drv || !count) return RES_PARERR;
// 	if (Stat & STA_NOINIT) return RES_NOTRDY;
// 	if (Stat & STA_PROTECT) return RES_WRPRT;

//Write SD sector(512bytes each)
//buf: store the data that will be written into SD card
//sector: physical sector number/address
//cnt: how many sectors/blocks will be written
//uint8_t SD_WriteDisk(uint8_t *buf, uint32_t sector, uint8_t cnt)
  rets = SD_WriteDisk((UINT8*)buff, sector, count);
	
	return (DRESULT)rets; //RES_OK or RES_ERROR;
}


/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */
/*-----------------------------------------------------------------------*/

DRESULT disk_ioctl (
	BYTE drv,		/* Physical drive number (0) */
	BYTE ctrl,		/* Control code */
	void *buff		/* Buffer to send/receive control data */
)
{
	DRESULT res;

	if (drv) return RES_PARERR;

	res = RES_OK;

	return res;
}

DWORD get_fattime (void)
{
	DWORD res;
	
	res = 0;

	return res;
}


