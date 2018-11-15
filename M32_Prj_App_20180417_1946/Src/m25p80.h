#ifndef __M25P80_H__
#define	__M25P80_H__

#include "BasicDataType.h"
#include "user_gpio_def.h"



#define WREN 0x06
#define WRDI 0x04
#define RDSR 0x05
#define WRSR 0x01
#define READ 0x03
#define FAST_READ 0x0b
#define PAGE_PROG 0x02
#define SECTOR_ERASER 0xD8
#define BULK_ERASER 0xC7
#define DEEP_SLEEP 0xB9
#define RES 0xAB


void M25P80_OPEN(void);
void M25P80_CLOSE(void);
void M25P80_Section_Erase(u32 addr);
void M25P80_Bulk_Erase(void);
void M25P80_Write_1Byte(u32 addr , u8 data);
void M25P80_Write_Bytes(u32 addr , u8* wr_buf_p , u16 no);
u8 M25P80_Read_1Byte(u32 addr );
void M25P80_Read_Bytes(u32 addr , u8* re_buf_p , u16 no);

#endif
