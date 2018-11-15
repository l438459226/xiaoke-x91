#include "ExternalIntWithGPU.h"
#include "stm32f10x_exti.h"
#include "stm32f10x_gpio.h"

UINT8 GPU_Int_Pending;

void EXTI_GPIO_Init(void) {
	EXTI_InitTypeDef EXTI_InitStructure;

	EXTI_ClearITPendingBit(EXTI_Line7);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOD,GPIO_PinSource7);//PD7 ΪGPIOD��PIN7
	EXTI_InitStructure.EXTI_Line= EXTI_Line7; //PD7, Ϊ:EXTI_Line7
	EXTI_InitStructure.EXTI_Mode= EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger= EXTI_Trigger_Rising;   //�жϷ�ʽΪ������
	EXTI_InitStructure.EXTI_LineCmd=ENABLE;
	EXTI_Init(&EXTI_InitStructure);
}  

void EXTI9_5_IRQHandler(void) { //����Ϊ:EXTI9_5 (�ⲿ�жϺ�5~9��������ʵ��)
	if(EXTI_GetITStatus(EXTI_Line7) != RESET) { //����Ϊ�ж���Ӧ���жϺ��Ƿ�����ж�, ����ж���жϵĻ�

		GPU_Int_Pending = 1;

		EXTI_ClearITPendingBit(EXTI_Line7); //���ж�
	}
}
