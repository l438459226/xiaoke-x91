#ifndef _I2C_H_
#define _I2C_H_
#include "stm32f10x.h"

#define VSPN_I2C_Port       GPIOE
#define VSPN_SCL_Pin        (GPIO_Pin_3)
#define VSPN_SDA_Pin        (GPIO_Pin_0)

#define VSPN_SCL_Set()      GPIO_SetBits(VSPN_I2C_Port, VSPN_SCL_Pin)
#define VSPN_SCL_Reset()    GPIO_ResetBits(VSPN_I2C_Port, VSPN_SCL_Pin)
#define VSPN_SDA_Set()      GPIO_SetBits(VSPN_I2C_Port, VSPN_SDA_Pin)
#define VSPN_SDA_Reset()    GPIO_ResetBits(VSPN_I2C_Port, VSPN_SDA_Pin)

#define VSPN_SDA_GetValue() GPIO_ReadInputDataBit(VSPN_I2C_Port, VSPN_SDA_Pin)

void VSPN_I2C_Init(void);
void VSPN_I2C_Start(void);
void VSPN_I2C_Stop(void);
void VSPN_I2C_Ack(void);
void VSPN_I2C_NoAck(void);
uint8_t VSPN_I2C_TestAck(void);
void VSPN_I2C_Write8Bit(uint8_t wdata);
uint8_t VSPN_I2C_Read8Bit(void);
#endif
