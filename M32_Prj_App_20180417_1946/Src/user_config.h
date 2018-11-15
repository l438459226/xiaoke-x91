#ifndef __USER_CONFIG_H
#define __USER_CONFIG_H

#include "BasicDataType.h"

//--- MCU�̼�����汾��Ϣ, ���һ��bitΪ1��ʾMCU32, Ϊ0��ʾMCU8; ----------------------------------------------------------
#define EXTMCU_VERSION (0x80DD001) //--- 32bit

//--- �ⲿLCD�ӿڰ����� ------------------------------------------------------------
// 1: ��ʾ�����˫MIPIת�Ӱ�; 
// 2: ��ʾ�����˫MIPIת�Ӱ�����ϼ������µ�й�ŵ�·��ת�Ӱ�; 
// 3: ��ʾeDP��ת�Ӱ�; 
// 4: �µ�Dual-CommandModeת�Ӱ�
#define LCD_DAUGHTER_BOARD_TYPE  (4)


typedef struct {
	UINT8 bLCDName[29]; //���ڼ�¼��MIPI-LCD�ķֱ���
	UINT8 bICName[29]; //���ڼ�¼��MIPI-LCD�ķֱ���
	UINT8 DUAL_MIPI_LCD; 			//--- ������LCD�Ƿ�Ϊ˫MIPI��(��MIPI��ʱ����������·��ͬ�ĵ�MIPI�ź���ͬʱ����������)
	UINT8 DUAL_MIPI_CHANNEL_SWAP; 	//--- ��˫MIPI��������ͨ����������Ҫ����һ��, 0��������, 1������
	UINT8 ODD_EVEN_nLEFT_RIGHT;     //---  ������˫MIPI��������ͨ��ģʽ������żͨ��ģʽ, 0��ʾ����ͨ��(Left-Right Division), 1��ʾ��żͨ��(Odd-Even Division)
	UINT16 PCLK_Freq; 	//PCLK Frequecy, 4~400������, ��λMHz
	UINT8 LANE_CNT;	// 4:4Lane, 8:8Lane, Others Reserved
	UINT8 V_DE;		// 1:DE �ߵ�ƽ��Ч, 0:DE �͵�ƽ��Ч
	UINT8 V_VS;		// 1:VS �ߵ�ƽ��Ч, 0:VS �͵�ƽ��Ч
	UINT8 V_HS; 	// 1:HS �ߵ�ƽ��Ч, 0:HS �͵�ƽ��Ч
	UINT8 Display_Mode; 	// ��ʾģʽ 0:Non burst mode with sync pulses  1:Non burst mode with sync events 2:Burst mode 3:Command mode
	UINT16 HACT_WIDTH;	//���
	UINT16 VACT_WIDTH;	//�߶�
	UINT16 HFP_WIDTH;	//��ǰ��
	UINT16 HBP_WIDTH;	//����
	UINT16 HSW_WIDTH;	//��ͬ��
	UINT16 VFP_WIDTH;	//��ǰ��
	UINT16 VBP_WIDTH;	//�ߺ��
	UINT16 VSW_WIDTH; 	//��ͬ��
	UINT16 VSP_mV;
	UINT16 VSN_mV;
	UINT16 VGH_mV;
	UINT16 VGL_mV;
	UINT16 SIZE_OF_SHOW_MODE; 	//��ʾ���ܻ������
	UINT8  PicIndex1;
	UINT8  PicIndex2;
	void (*ptr_Initial_LCM)(void); //����ָ��, ָ���Ӧ�ĳ�ʼ������
} pMIPI_Para_Table;

extern const pMIPI_Para_Table *ptr_MIPI_TABLE[];
extern unsigned char MIPI_TABLE_LAST_INDEX;
extern UINT8 gMipiTableIndex;






#endif /* __USER_CONFIG_H */
