#ifndef __BOARDANDCOREINF_H
#define __BOARDANDCOREINF_H

#include "BasicDataType.h"
#include "stm32f10x.h"


//
void Sys_Beep(u16 delay);
void Show_Curr(void);
U32 Arm_Get_Current(U8 cmd,U8 index);

u32 Get_Sys_Curr(void);
void Init_System(void);

#endif /* __BOARDANDCOREINF_H */
