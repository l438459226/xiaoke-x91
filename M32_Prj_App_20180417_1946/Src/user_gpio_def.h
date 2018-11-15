#ifndef __USER_GPIO_DEF_H
#define __USER_GPIO_DEF_H

#include "stm32f10x_gpio.h"






uint8_t I_LCD240x320_SDO(void);
void O_LCD240x320_SDI(uint8_t value);
void O_LCD240x320_SCK(uint8_t value);
void O_LCD240x320_REST(uint8_t value);
void O_LCD240x320_CS(uint8_t value);

uint8_t I_GPU_StartUpBoot_Done(void);
void O_GPU_StartUpBoot_ResetN(uint8_t value);
void O_M25P80_SPI_CSN(uint8_t value);
void O_M25P80_SPI_CLK(uint8_t value);
void O_M25P80_SPI_MOSI(uint8_t value);
uint8_t I_M25P80_SPI_MISO(void);
void EnableGPU_SPI_FLASH_OutputDriving(void);
void DisableGPU_SPI_FLASH_OutputDriving(void);
void EnableEBindingPin_OutputDriving(uint16_t GPIO_PinX);
void DisableEBindingPin_OutputDriving(uint16_t GPIO_PinX);




void O_SSD2828_RESET(uint8_t value);
void O_SSD2828_SPI_CS(uint8_t value);
void O_SSD2828_SPI_CLK(uint8_t value);
void O_SSD2828_SPI_SDI(uint8_t value);
uint8_t I_SSD2828_SPI_SDO(void);



uint8_t GPG_TP_I2C_SCL(uint8_t value);
uint8_t GPG_TP_I2C_SDA(uint8_t value);



void O_PWR_EN_LCDIOVCC(uint8_t value);
void O_PWR_EN_LCDVCC(uint8_t value);
void O_PWR_EN_MTP(uint8_t value);
void O_PWR_BLK_SET_LEDK5(uint8_t value);
void O_TEST1_TP_RESET(uint8_t value);
void O_PWR_BL_PWM(uint8_t value);



uint8_t I_USER_K1_AUTO(void);
uint8_t I_USER_K2_POWER(void);
uint8_t I_USER_K3_NEXT(void);
uint8_t I_USER_K4_UP(void);
uint8_t I_USER_K5(void);
uint8_t I_USER_K6_MODE(void);



void GPIO_Configuration(void);


#endif /* __USER_GPIO_DEF_H */
