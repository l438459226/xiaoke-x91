#include "user_config.h"
#include "lcd_cfg.h"

//CommandMode��PCLK_Freq��ֵ���ܳ���SSD2828 PLLʱ�ӵ�1/8, ����SSD2828�ᴦ������
const pMIPI_Para_Table PARA_MIPI_MOTOCM_1080x1920_A = {
	"Moto_1080x1920_CommandM ", //UINT8 bLCDName[30];
	"XXXX   ", //UINT8 bICName[30];
	0, 		//UINT8 DUAL_MIPI_LCD; 			//--- ������LCD�Ƿ�Ϊ˫MIPI��(��MIPI��ʱ����������·��ͬ�ĵ�MIPI�ź���ͬʱ����������)
	0, 		//UINT8 DUAL_MIPI_CHANNEL_SWAP; //--- ��˫MIPI��������ͨ����������Ҫ����һ��, 0��������, 1������
	0, 		//UINT8 ODD_EVEN_nLEFT_RIGHT;   //---  ������˫MIPI��������ͨ��ģʽ������żͨ��ģʽ, 0��ʾ����ͨ��(Left-Right Division), 1��ʾ��żͨ��(Odd-Even Division)
	100, 	//UINT16 PCLK_Freq; //PCLK Frequecy, 4~400������, ��λMHz
	4, 		//UINT8 LANE_CNT;	// 1:1Lane, 2:2Lane, 4:4Lane, Others Reserved
	1, 		//UINT8 V_DE;		// 1:DE �ߵ�ƽ��Ч, 0:DE �͵�ƽ��Ч
	0, 		//UINT8 V_VS;		// 1:VS �ߵ�ƽ��Ч, 0:VS �͵�ƽ��Ч
	0, 		//UINT8 V_HS; 		// 1:HS �ߵ�ƽ��Ч, 0:HS �͵�ƽ��Ч
	
	3,   //UINT8 Display_Mode; // ��ʾģʽ 0:Non burst mode with sync pulses  1:Non burst mode with sync events 2:Burst mode 3:Command mode

	1080, 	//UINT16 HACT_WIDTH;//���
	1920, 	//UINT16 VACT_WIDTH;//�߶�
	180, 	//UINT16 HFP_WIDTH;	//��ǰ��
	180, 	//UINT16 HBP_WIDTH;	//����
	120, 	//UINT16 HSW_WIDTH;	//��ͬ��
	10, 	//UINT16 VFP_WIDTH;	//��ǰ��
	10, 		//UINT16 VBP_WIDTH;	//�ߺ��
	6, 		//UINT16 VSW_WIDTH; //��ͬ��
	
	5500, 		//UINT16 VSP_mV;
	5500, 		//UINT16 VSN_mV;
	0, 		//UINT16 VGH_mV;
	0, 		//UINT16 VGL_mV;
	34, 	//UINT16 SIZE_OF_SHOW_MODE; 	//��ʾ���ܻ������
	1, 		//UINT8  PicIndex1;
	2, 		//UINT8  PicIndex2;
	Initial_LCM_1080x1920_OppoR9_Oled
};



const pMIPI_Para_Table PARA_MIPI_TIANJI2_1080x1920_A = {
	"TianJi2_1080x1920_VideoM ", //UINT8 bLCDName[30];
	"XXXX   ", //UINT8 bICName[30];
	0, 		//UINT8 DUAL_MIPI_LCD; 			//--- ������LCD�Ƿ�Ϊ˫MIPI��(��MIPI��ʱ����������·��ͬ�ĵ�MIPI�ź���ͬʱ����������)
	0, 		//UINT8 DUAL_MIPI_CHANNEL_SWAP; //--- ��˫MIPI��������ͨ����������Ҫ����һ��, 0��������, 1������
	0, 		//UINT8 ODD_EVEN_nLEFT_RIGHT;   //---  ������˫MIPI��������ͨ��ģʽ������żͨ��ģʽ, 0��ʾ����ͨ��(Left-Right Division), 1��ʾ��żͨ��(Odd-Even Division)
	133, 	//UINT16 PCLK_Freq; //PCLK Frequecy, 4~400������, ��λMHz
	4, 		//UINT8 LANE_CNT;	// 1:1Lane, 2:2Lane, 4:4Lane, Others Reserved
	1, 		//UINT8 V_DE;		// 1:DE �ߵ�ƽ��Ч, 0:DE �͵�ƽ��Ч
	0, 		//UINT8 V_VS;		// 1:VS �ߵ�ƽ��Ч, 0:VS �͵�ƽ��Ч
	0, 		//UINT8 V_HS; 		// 1:HS �ߵ�ƽ��Ч, 0:HS �͵�ƽ��Ч
	
	0,   //UINT8 Display_Mode; // ��ʾģʽ 0:Non burst mode with sync pulses  1:Non burst mode with sync events 2:Burst mode 3:Command mode

	1080, 	//UINT16 HACT_WIDTH;//���
	1920, 	//UINT16 VACT_WIDTH;//�߶�
	20, 	//UINT16 HFP_WIDTH;	//��ǰ��
	22, 	//UINT16 HBP_WIDTH;	//����
	10, 	//UINT16 HSW_WIDTH;	//��ͬ��
	20, 	//UINT16 VFP_WIDTH;	//��ǰ��
	1, 		//UINT16 VBP_WIDTH;	//�ߺ��
	6, 		//UINT16 VSW_WIDTH; //��ͬ��
	
	5500, 		//UINT16 VSP_mV;
	5500, 		//UINT16 VSN_mV;
	0, 		//UINT16 VGH_mV;
	0, 		//UINT16 VGL_mV;
	34, 	//UINT16 SIZE_OF_SHOW_MODE; 	//��ʾ���ܻ������
	1, 		//UINT8  PicIndex1;
	2, 		//UINT8  PicIndex2;
	Initial_LCM_1080x1920_TianJi2
};


//-----------------------------------------------------------------------------------
// ���������ñ����, ����һ��MIPI����".c"�ļ�֮��, Ҫ�Ѷ�Ӧ�Ľṹ�峣���ӵ���ָ��������(�ӵ�ʱ����Բ����Ⱥ�˳��)
const pMIPI_Para_Table *ptr_MIPI_TABLE[] = {
	&PARA_MIPI_MOTOCM_1080x1920_A
	//&PARA_MIPI_TIANJI2_1080x1920_A
};
unsigned char MIPI_TABLE_LAST_INDEX = ((sizeof(ptr_MIPI_TABLE)/sizeof(const pMIPI_Para_Table *)) - 1); //�Զ�����ptr_EDP_TABLE���ж�Ӧ�������õĸ���



