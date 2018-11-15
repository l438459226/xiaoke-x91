#include "i2c.h"
#include "stm32f10x_gpio.h"
#include "stdint.h"

#define I2C_DELAY      100

void delay(uint16_t t)
{
	while(--t);
}

void VSPN_I2C_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = VSPN_SCL_Pin | VSPN_SDA_Pin;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
  GPIO_Init(VSPN_I2C_Port, &GPIO_InitStructure);
}

void VSPN_I2C_Start(void)
{
	VSPN_SDA_Set();
	VSPN_SCL_Set();
	delay(I2C_DELAY);
	VSPN_SDA_Reset();
	delay(I2C_DELAY);
	VSPN_SCL_Reset();
}

void VSPN_I2C_Stop(void)
{
	VSPN_SCL_Reset();
	VSPN_SDA_Reset();
	delay(I2C_DELAY);
	VSPN_SCL_Set();
	delay(I2C_DELAY);
	VSPN_SDA_Set();
}

void VSPN_I2C_Ack(void)
{
	VSPN_SDA_Reset();
	VSPN_SCL_Set();
	delay(I2C_DELAY);
	VSPN_SCL_Reset();
	delay(I2C_DELAY);
	VSPN_SDA_Set();
}

void VSPN_I2C_NoAck(void)
{
	VSPN_SDA_Set();
	VSPN_SCL_Set();
	delay(I2C_DELAY);
	VSPN_SCL_Reset();
	delay(I2C_DELAY);
}

uint8_t VSPN_I2C_TestAck(void)
{
	uint8_t ErrorBit = 0;

	VSPN_SDA_Set();
	delay(I2C_DELAY);
	VSPN_SCL_Set();
	delay(I2C_DELAY);
	if(VSPN_SDA_GetValue() == 1)
		ErrorBit = 1;
	VSPN_SCL_Reset();
	delay(I2C_DELAY);
	return ErrorBit;
}

void VSPN_I2C_Write8Bit(uint8_t wdata)
{
	uint8_t i;
	for(i = 0;i < 8;i++)
	{
		if(wdata & 0x80)
			VSPN_SDA_Set();
		else
			VSPN_SDA_Reset();
		delay(I2C_DELAY);
		VSPN_SCL_Set();
		delay(I2C_DELAY);
		VSPN_SCL_Reset();
		wdata <<= 1;
	}
}

uint8_t VSPN_I2C_Read8Bit(void)
{
	uint8_t i,rec_byte = 0;
	VSPN_SDA_Set();
	delay(I2C_DELAY);
	for(i = 0;i < 8;i++)
	{
		VSPN_SCL_Set();
		delay(I2C_DELAY);
		rec_byte <<= 1;
		if(VSPN_SDA_GetValue() == 1)
			rec_byte |= 0x01;
		VSPN_SCL_Reset();
		delay(I2C_DELAY);
	}
	return rec_byte;
}

