#include "ExternalIntWithGPU.h"
#include "stm32f10x_exti.h"
#include "stm32f10x_gpio.h"

UINT8 GPU_Int_Pending;

void EXTI_GPIO_Init(void) {
	EXTI_InitTypeDef EXTI_InitStructure;

	EXTI_ClearITPendingBit(EXTI_Line7);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOD,GPIO_PinSource7);//PD7 为GPIOD的PIN7
	EXTI_InitStructure.EXTI_Line= EXTI_Line7; //PD7, 为:EXTI_Line7
	EXTI_InitStructure.EXTI_Mode= EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger= EXTI_Trigger_Rising;   //中断方式为上升沿
	EXTI_InitStructure.EXTI_LineCmd=ENABLE;
	EXTI_Init(&EXTI_InitStructure);
}  

void EXTI9_5_IRQHandler(void) { //这里为:EXTI9_5 (外部中断号5~9都在这里实现)
	if(EXTI_GetITStatus(EXTI_Line7) != RESET) { //这里为判断相应的中断号是否进入中断, 如果有多个中断的话

		GPU_Int_Pending = 1;

		EXTI_ClearITPendingBit(EXTI_Line7); //清中断
	}
}
