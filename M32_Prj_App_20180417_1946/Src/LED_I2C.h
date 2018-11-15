#ifndef _LED_I2C_H_ 
#define _LED_I2C_H_ 

#include "BasicDataType.h"

#define LED_I2C_STOP_WAIT_VALUE	2000

void LED_I2C_Init(void);

void LED_Control_Init(void);
void LED_Display(char CNum0, char CNum1, char CNum2, char CNum3, UINT8 Dot);


#endif /* _LED_I2C_H_ */
