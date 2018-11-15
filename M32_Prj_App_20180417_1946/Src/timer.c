#include "timer.h"
#include "app.h"
#include "misc.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_exti.h"

UINT16 GPIO_KEY_SampleValue;
UINT16 GPIO_KEY_SampleValue_Pre1;
UINT16 GPIO_KEY_SampleValue_Pre2;

extern UINT8 KeyPowerPressed;
extern UINT8 KeyUpPressed;
extern UINT8 KeyDownPressed;
extern UINT8 KeyAutoPressed;
extern UINT8 KeyOTPPressed;

UINT16 GPIO_EBINDINGPIN_SampleValue;
UINT16 GPIO_EBINDINGPIN_SampleValue_Pre1;
UINT16 GPIO_EBINDINGPIN_SampleValue_Pre2;
extern UINT8 EBindingPinTrigger;

#define SEL_KEY_POWER_ONOFF GPIO_Pin_13
#define SEL_KEY_DOWN_NEXT   GPIO_Pin_6
#define SEL_KEY_UP_PRE      GPIO_Pin_14
#define SEL_KEY_AUTO_MANUAL GPIO_Pin_15
#define SEL_KEY_OTP         GPIO_Pin_8

UINT16 Time20msCnt;
//---------------------------------------------------------------------------------------------------

/**
  * @brief  Configure the nested vectored interrupt controller.
  * @param  None
  * @retval None
  */
void NVIC_Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	
	/* Enable the TIM2 global Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel =  TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; //Timer2抢占优先级要最高
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	/* Enable the USART1 global Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel =  USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	/* Enable the TIM3 global Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel =  TIM3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	/* Enable the External GPIO-PD7 global Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}


void Timer2_Configuration(void) { //10ms timer
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	
	/* TIM2 clock enable */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	TIM_DeInit(TIM2); //复位TIM2定时器, 使之进入初始状态
	
	//---((1+TIM_Prescaler)/(72M or 36M))*(1+TIM_Period)
	TIM_TimeBaseStructure.TIM_Period=20-1;  //自动重装载寄存器的值
	TIM_TimeBaseStructure.TIM_Prescaler=(T10MS-1); //时钟预分频数
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;  //采样分频
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
	
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseStructure);
	
	TIM_ClearFlag(TIM2,TIM_FLAG_Update); //清除溢出中断标志
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
	//TIM_Cmd(TIM2,ENABLE); //开启时钟
	
	//
	Time20msCnt = 0;
	//
	GPIO_EBINDINGPIN_SampleValue = 0x4000;
	GPIO_EBINDINGPIN_SampleValue_Pre1 = 0x4000;
	GPIO_EBINDINGPIN_SampleValue_Pre2 = 0x4000;
}
void Timer2_Enable(void) {
	TIM_Cmd(TIM2,ENABLE); //开启时钟
}

void Timer3_Configuration(void) { //100us timer
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	
	/* TIM3 clock enable */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	TIM_DeInit(TIM3); //复位TIM3定时器, 使之进入初始状态
	
	//---((1+TIM_Prescaler)/(72M or 36M))*(1+TIM_Period)
	TIM_TimeBaseStructure.TIM_Period=20-1;  //自动重装载寄存器的值
	TIM_TimeBaseStructure.TIM_Prescaler=(T250US-1); //时钟预分频数
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;  //采样分频
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
	
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);
	
	TIM_ClearFlag(TIM3,TIM_FLAG_Update); //清除溢出中断标志
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);
	
	//
}
void Timer3_Enable(void) {
	TIM_Cmd(TIM3,ENABLE); //开启时钟
}

void TIM2_IRQHandler(void) {
	if(TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) { //检测是否发生溢出更新事件
		TIM_ClearITPendingBit(TIM2 , TIM_FLAG_Update); //清除TIM2的中断待处理位
		
		if(Time20msCnt) //分出20ms出来
			Time20msCnt = 0;
		else
			Time20msCnt = 1;
		
		// user code --- KeyButton
		if(Time20msCnt) { //每隔20ms采样一次
			GPIO_KEY_SampleValue_Pre2 = GPIO_KEY_SampleValue_Pre1;
			GPIO_KEY_SampleValue_Pre1 = GPIO_KEY_SampleValue;
			GPIO_KEY_SampleValue = (((uint16_t)GPIOA->IDR) & GPIO_Pin_8) | (((uint16_t)GPIOC->IDR) & (GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15)); //GPIO_ReadInputData(GPIOC) & 0x01f;
			if(((GPIO_KEY_SampleValue&SEL_KEY_POWER_ONOFF) == 0) && ((GPIO_KEY_SampleValue_Pre1&SEL_KEY_POWER_ONOFF) == 0) && ((GPIO_KEY_SampleValue_Pre2&SEL_KEY_POWER_ONOFF) != 0))
				KeyPowerPressed = 1;
			if(((GPIO_KEY_SampleValue&SEL_KEY_DOWN_NEXT) == 0) && ((GPIO_KEY_SampleValue_Pre1&SEL_KEY_DOWN_NEXT) == 0) && ((GPIO_KEY_SampleValue_Pre2&SEL_KEY_DOWN_NEXT) != 0))
				KeyDownPressed = 1;
			if(((GPIO_KEY_SampleValue&SEL_KEY_UP_PRE) == 0) && ((GPIO_KEY_SampleValue_Pre1&SEL_KEY_UP_PRE) == 0) && ((GPIO_KEY_SampleValue_Pre2&SEL_KEY_UP_PRE) != 0))
				KeyUpPressed = 1;
			if(((GPIO_KEY_SampleValue&SEL_KEY_AUTO_MANUAL) == 0) && ((GPIO_KEY_SampleValue_Pre1&SEL_KEY_AUTO_MANUAL) == 0) && ((GPIO_KEY_SampleValue_Pre2&SEL_KEY_AUTO_MANUAL) != 0))
		  		KeyAutoPressed = 1;
			if(((GPIO_KEY_SampleValue&SEL_KEY_OTP) == 0) && ((GPIO_KEY_SampleValue_Pre1&SEL_KEY_OTP) == 0) && ((GPIO_KEY_SampleValue_Pre2&SEL_KEY_OTP) != 0))
		  		KeyOTPPressed = 1;
		}
		
		// Encrypt Binding Pin Input capture, 这里需要使用10ms来采样
		GPIO_EBINDINGPIN_SampleValue_Pre2 = GPIO_EBINDINGPIN_SampleValue_Pre1;
		GPIO_EBINDINGPIN_SampleValue_Pre1 = GPIO_EBINDINGPIN_SampleValue;
		GPIO_EBINDINGPIN_SampleValue = (((uint16_t)GPIOA->IDR) & (GPIO_Pin_13 | GPIO_Pin_14));
		if((GPIO_EBINDINGPIN_SampleValue == 0x0000) && (GPIO_EBINDINGPIN_SampleValue_Pre1 == 0x0000) && (GPIO_EBINDINGPIN_SampleValue_Pre2 == 0x6000)) //连续两次确认值已经改变
			EBindingPinTrigger = 1;
	}
}

void TIM3_IRQHandler(void) {
	if(TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) { //检测是否发生溢出更新事件
		TIM_ClearITPendingBit(TIM3 , TIM_FLAG_Update); //清除TIM2的中断待处理位
		
		// user code --- KeyButton
		
	}
}


//使用GPIO_PB0即TIM8_CH2N做PWM输出引脚
void TIM8_PWM_Configuration(UINT16 PwmFreqArr/*PWM频率=72MHz/(PwmFreqArr+1)*/, UINT8 PwmDuty/*占空比[0~100]*/) { //PwmDuty指高电平所占比率
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	
	/* TIM8 clock enable */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);
	
	if(PwmDuty > 100)
		PwmDuty = 100; //超过100认为是100占空比
	
	//---((1+TIM_Prescaler)/(72M or 36M))*(1+TIM_Period)
	TIM_TimeBaseStructure.TIM_Period = PwmFreqArr;    //设置自动重装载周期值, PWM频率=72MHz/(PwmFreqArr+1)
	TIM_TimeBaseStructure.TIM_Prescaler = 0;  //设置预分频值为0
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM8,&TIM_TimeBaseStructure);
	
	
	//TIM8_CH2N
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //使用模式2
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable; //使用的是CH2N通道
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Disable;  //关闭CH2通道, 不然会影响PC7对应的CH2通道
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //OCx输出极性设置
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_Low; //OCxN输出极性设置, 由于CH2关闭, 所以这里极性与实际相反
	TIM_OCInitStructure.TIM_Pulse = ((UINT32)PwmDuty)*(1+PwmFreqArr)/100;  //占空比
	TIM_OC2Init(TIM8,&TIM_OCInitStructure);
	TIM_OC2PreloadConfig(TIM8,TIM_OCPreload_Enable); //TIM_8---->通道2N[PB0]
	
	
	TIM_Cmd(TIM8,ENABLE);               
	TIM_CtrlPWMOutputs(TIM8, ENABLE); //设置TIM8的PWM输出为使能
}
