/******************************* 广州天码电子 *********************************
 * 文件名   ：power_ctrl.h        
 * 作者     ：天码电子
 * 版本     ：V02
 * 完成日期 ：2014-05-26
 * 描述     ：各通道電壓或電流設置
 * 函數列表	：	
			  	void PwrCtrlInit(void);
				void PwrVDD1(unsigned int mv);
				void PwrVDD2(unsigned int mv);
				void PwrVDD3(unsigned int mv);
				void PwrVDD4(unsigned int mv);
				void PwrVDD5(unsigned int mv);
				void PwrVDD6(unsigned int mv);
	
				void PwrVDD_5V_ON(void);	  //此通道是SSD2828的電源
				void PwrVDD_5V_OFF(void);
				
				void PwrVLED1(unsigned int ma);
				void PwrVLED2(unsigned int ma);
				void PwrVLED3(unsigned int ma);
				void PwrVLED4(unsigned int ma);
				void PwrVLED5(unsigned int ma);
				void PwrVLED6(unsigned int ma);
				void PwrVLED7(unsigned int ma);
				void PwrVLED8(unsigned int ma);
				void PwrVLED_ON(void);		   //背光通道設置電流後 要調用此函數才是真的通電
				void PwrVLED_OFF(void);

				uint8_t ReadDialSwitch(void);

 * 修改记录 ：|    作者    |   日期    |    版本    |    描述    |	
 				天码电子	2014-05-26      V02		  增加读拨码开关		
*******************************************************************************/

#ifndef _POWER_CTRL_
#define _POWER_CTRL_

#include "stm32f10x.h"

/*
*函数名 : PowerCtrlInit
*描述   : 电源控制初始化
*参数   : 无
*返回   : 无
*/
extern void PwrCtrlInit(void);

/*
*函数名 : PwrVDD1
*描述   : 设置VDD1的电压, 電壓可設置範圍0~5V
*参数   : mv -电压值 单位mV
*返回   : 无
*/
extern void PwrVDD1(unsigned int mv);

/*
*函数名 : PwrVDD2
*描述   : 设置VDD2的电压, 電壓可設置範圍0~5V
*参数   : mv -电压值 单位mV
*返回   : 无
*/
extern void PwrVDD2(unsigned int mv);

/*
*函数名 : PwrVDD3
*描述   : 设置VDD3的电压, 電壓可設置範圍0~10V
*参数   : mv -电压值 单位mV
*返回   : 无
*/
extern void PwrVDD3(unsigned int mv);

/*
*函数名 : PwrVDD4
*描述   : 设置VDD4的电压，電壓可設置範圍0~10V
*参数   : mv -电压值 单位mV
*返回   : 无
*/
extern void PwrVDD4(unsigned int mv);

/*
*函数名 : PwrVDD5
*描述   : 设置VDD5的电压，此通道輸出的是負電壓，電壓可設置範圍0 ~ -10V
*参数   : mv -电压值 单位(-mV),參數是正整型，輸出的是負電壓
*返回   : 无
*/
extern void PwrVDD5(unsigned int mv);

/*
*函数名 : PwrVDD6
*描述   : 设置VDD6的电压，電壓可設置範圍0~10V
*参数   : mv -电压值 单位mV
*返回   : 无
*/
extern void PwrVDD6(unsigned int mv);

/*
*函数名 : PwrVDD5V_ON
*描述   : 开启VDD5V电源，此通道也是SSD2828的電源
*参数   : 无
*返回   : 无
*/
extern void PwrVDD_5V_ON(void);

/*
*函数名 : PwrVDD5V_OFF
*描述   : 关闭VDD5V电源，此通道也是SSD2828的電源
*参数   : 无
*返回   : 无
**/
extern void PwrVDD_5V_OFF(void);

/*
*函数名 : PwrVLED1
*描述   : 设置VLED1背光通道电流，可設置電流範圍0~100mA
*参数   : ma -电流值 单位 mA
*返回   : 无
*/
extern void PwrVLED1(unsigned int ma);

/*
*函数名 : PwrVLED2
*描述   : 设置VLED2背光通道电流，可設置電流範圍0~100mA
*参数   : ma -电流值 单位 mA
*返回   : 无
*/
extern void PwrVLED2(unsigned int ma);

/*
*函数名 : PwrVLED3
*描述   : 设置VLED3背光通道电流，可設置電流範圍0~100mA
*参数   : ma -电流值 单位 mA
*返回   : 无
*/
extern void PwrVLED3(unsigned int ma);

/*
*函数名 : PwrVLED4
*描述   : 设置VLED4背光通道电流，可設置電流範圍0~100mA
*参数   : ma -电流值 单位 mA
*返回   : 无
*/
extern void PwrVLED4(unsigned int ma);

/*
*函数名 : PwrVLED5
*描述   : 设置VLED5背光通道电流，可設置電流範圍0~100mA
*参数   : ma -电流值 单位 mA
*返回   : 无
*/
extern void PwrVLED5(unsigned int ma);

/*
*函数名 : PwrVLED6
*描述   : 设置VLED6背光通道电流，可設置電流範圍0~100mA
*参数   : ma -电流值 单位 mA
*返回   : 无
*/
extern void PwrVLED6(unsigned int ma);

/*
*函数名 : PwrVLED7
*描述   : 设置VLED7背光通道电流，可設置電流範圍0~100mA
*参数   : ma -电流值 单位 mA
*返回   : 无
*/
extern void PwrVLED7(unsigned int ma);

/*
*函数名 : PwrVLED8
*描述   : 设置VLED8背光通道电流，可設置電流範圍0~100mA
*参数   : ma -电流值 单位 mA
*返回   : 无
*/
extern void PwrVLED8(unsigned int ma);

/*
*函数名 : PwrVLED_ON
*描述   : 开启背光电源。背光通道設置電流後要調用此函數纔是真的通電
*参数   : 无
*返回   : 无
*调用   : 外部调用
*/
extern void PwrVLED_ON(void);

/*
*函数名 : PwrVDD5V_OFF
*描述   : 关闭VDD5V电源
*参数   : 无
*返回   : 无
*/
extern void PwrVLED_OFF(void);


////////////////////////////////////拨码开关////////////////////////////////////

#define DSW1_ON 0X01
#define DSW2_ON	0x02
#define DSW3_ON 0x04
#define DSW4_ON 0x08
#define DSW_NULL 0X00

/*
*函数名 : ReadDialSwitch
*描述   : 读拨码开关
*参数   : 无
*返回   : 拨码开关状态，用上面的宏定义
*/
extern uint8_t ReadDialSwitch(void);

#endif

/******************************* 广州天码电子 *********************************/
