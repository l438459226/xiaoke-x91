

#ifndef _KEY_H_
#define _KEY_H_

#include "stm32f10x.h"


#define KEY_1 		0x01	//確認
#define KEY_2 		0x04	//上翻
#define KEY_3 		0x02	//下翻
#define KEY_4 		0x08	//显示开关
#define KEY_5     0x10	  
#define KEY_6			0x20	 
#define KEY_7			0x40	
#define KEY_NULL 	0x00


#define SW_NULL 0X00
#define SW_CCW  0X01 
#define SW_CW 	0X02 


typedef enum
{
  	ENCODER_EN,    //encoder
	ENCODER_DI,	  
}KeyInitType;	 

extern void Key_Init(KeyInitType key_enum);

extern unsigned int KeyTrg;	
extern unsigned int KeyCont;	
extern void Key_Read(void);     



extern unsigned int Encoder_Read(void);

#endif


