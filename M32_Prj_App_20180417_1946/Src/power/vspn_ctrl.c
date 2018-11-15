#include "vspn_ctrl.h"
#include "stm32f10x_gpio.h"
#include "stdint.h"

static void VSPN_WriteReg(uint8_t reg, uint8_t wdata)
{
	VSPN_I2C_Start();
	VSPN_I2C_Write8Bit(VSPN_I2C_ADDRESS);
	VSPN_I2C_TestAck();
	VSPN_I2C_Write8Bit(reg & 0x07);
	VSPN_I2C_TestAck();
	VSPN_I2C_Write8Bit(wdata);
	VSPN_I2C_TestAck();
	VSPN_I2C_Stop();
}

uint8_t VSPN_ReadReg(uint8_t reg)
{
	uint8_t ret = 0;
	VSPN_I2C_Start();
	VSPN_I2C_Write8Bit(VSPN_I2C_ADDRESS);
	VSPN_I2C_TestAck();
	VSPN_I2C_Write8Bit(reg & 0x07);
	VSPN_I2C_TestAck();
	VSPN_I2C_Start();
	VSPN_I2C_Write8Bit(VSPN_I2C_ADDRESS | 0x01);
	VSPN_I2C_TestAck();
	ret = VSPN_I2C_Read8Bit();
	VSPN_I2C_Ack();
	VSPN_I2C_Stop();
	return ret;
}

void VSPN_SetVSPVoltage(uint16_t setVoltage)
{
	uint16_t setvalue = 0;
	//uint8_t ret;
	setvalue = (setVoltage - 3200) / 50;
	if(setvalue > 191)
		setvalue = 191;
	VSPN_WriteReg(VSPN_CMDR, 0x07);
	VSPN_WriteReg(VSPN_REG0_OTP0, (uint8_t)setvalue);
	//ret = VSPN_ReadReg(VSPN_REG0_OTP0);
	//ret = VSPN_ReadReg(VSPN_REG1_OTP1);
	//ret = VSPN_ReadReg(VSPN_REG2_OTP2);
	//ret = VSPN_ReadReg(VSPN_CMDR);
}

void VSPN_SetVSNVoltage(uint16_t setVoltage)
{
	uint16_t setvalue = 0;
	setvalue = (setVoltage - 1200) / 50;
	if(setvalue > 255)
		setvalue = 255;
	VSPN_WriteReg(VSPN_CMDR, 0x07);
	VSPN_WriteReg(VSPN_REG1_OTP1, (uint8_t)setvalue);
}

void VSPN_OutOn(void)
{
	VSPN_WriteReg(VSPN_CMDR, 0x07);
	VSPN_WriteReg(VSPN_REG2_OTP2, 0x03);
}

void VSPN_OutOff(void)
{
	VSPN_WriteReg(VSPN_CMDR, 0x07);
	VSPN_WriteReg(VSPN_REG2_OTP2, 0x00);
}
