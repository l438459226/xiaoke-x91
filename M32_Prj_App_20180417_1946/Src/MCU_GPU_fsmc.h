#ifndef __MCU_GPU_FSMC_H
#define __MCU_GPU_FSMC_H

#include "BasicDataType.h"


#define MCU_GPU__ADDR  	*(volatile UINT16 *)0x60000000
//#define MCU_GPU__DATA  	*(volatile UINT8 *)0x60010000  	//8位地址访问
#define MCU_GPU__DATA  	*(volatile UINT16 *)0x60020000 	//16位地址访问，ST的设计师规定在使用16位地址的时候，CPU地址线的A1输出到FMSC的A0，A17-->A16, 就这么简单。。。

#define MCU_GPU__DATAH  *(volatile UINT16 *)0x60060000 //[31:16]


void MCU_GPU_FSMCConfig(void);


#endif
