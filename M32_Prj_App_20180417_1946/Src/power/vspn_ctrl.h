#ifndef _VSPN_CTRL_H_
#define _VSPN_CTRL_H_
#include "i2c.h"
#include "stm32f10x_gpio.h"
#include "stdint.h"

#define VSPN_CA      0

#if (VSPN_CA == 0)
#define VSPN_I2C_ADDRESS   0x8A
#else
#define VSPN_I2C_ADDRESS   0x62
#endif

#define VSPN_REG0_OTP0    0
#define VSPN_REG1_OTP1    1
#define VSPN_REG2_OTP2    2
#define VSPN_CMDR         4

static void VSPN_WriteReg(uint8_t reg, uint8_t wdata);
void VSPN_SetVSPVoltage(uint16_t setVoltage);
void VSPN_SetVSNVoltage(uint16_t setVoltage);
void VSPN_OutOn(void);
void VSPN_OutOff(void);

#endif
