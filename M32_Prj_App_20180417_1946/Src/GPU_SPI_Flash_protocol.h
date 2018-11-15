#ifndef _GPU_SPI_FLASH_PROTOCOL_H_
#define _GPU_SPI_FLASH_PROTOCOL_H_

// �������λ����ͨ��Э��
#define MESSAGE_START_INDEX				0x00
#define SEQUENCE_NUM_INDEX				0x01
#define MESSAGE_SIZE_HIGH_INDEX			0x02
#define MESSAGE_SIZE_LOW_INDEX			0x03
#define TOKE_INEXE						0x04
#define MESSAGE_BODY_INDEX				0x05
#define CHECK_SUM						0x00

#define MESSAGE_START_VAL				0x1B
#define TOKE_VAL						0x0E

#define PROTOCOL_GPU_SPI_FLASH 			0x00 			// GPU_SPI_Flash
#define PROTOCOL_USER    			  	0x01 			// User(Extension in ExtMCU32)


#define CMD_SET_BAUDRATE				0x8C			// ���ò�����

#define MAX_PIC_DOWN_SIZE				4096			// ����Ƭ�������֧�ֵĳߴ�
#define MAX_PIC_UP_SIZE					512				// �ϴ�ͼƬ��Ч���֧�ֵĳߴ�

#define CMD_GPU_SPI_FLASH_PROGRAM_EXIT	0x8F			// GPU SPI Flash �˳����ģʽ
#define CMD_GPU_SPI_FLASH_SECTOR_ERASE	0x90			// GPU SPI Flash Sector ��������
#define CMD_PIC_DOWN_GET_INDEX			0x91			// ͼƬ���ض�˳����Ϣ
#define CMD_GPU_SPI_FLASH_PAGE_PROGRAM	0x98			// GPU SPI Flash Page д����
#define CMD_PIC_DOWN_READ_DATA			0x99			// ͼƬ���ض�����

#define CMD_NOP							0xA0			// �޲��������ڲ����豸
#define CMD_SET_SPEED					0xA8			// ����ISP�ٶ�
#define CMD_ENTER_PRG_MODE				0xB0			// ������ģʽ
#define CMD_EXIT_PRG_MODE				0xB1			// �˳����ģʽ
#define CMD_READ_ID						0xB2			// ��оƬID

#define CMD_CHIP_ERASE					0xB4			// ��Ƭ����
#define CMD_SECTOR_ERASE				0xB5			// ��������
#define CMD_PRG_PAGE					0xB8			// ҳ���
#define CMD_READ_PAGE					0xB9			// ҳ��ȡ
#define CMD_PRG_LOCK					0xBA			// �������λ
#define CMD_READ_LOCK					0xBB			// ��ȡ����λ

#define CMD_STM32_PRG_ENABLE			0xC0			// STM32���ʹ��
#define CMD_STM32_PRG_IO_CTRL			0xC2			// STM32���IO����

#define BITMASK_ISP_STM32_BOOT0			0x02			// BOOT0����
#define BITMASK_ISP_STM32_nRST			0x01			// nRST����

#define CMD_STM32_PRG_COM				0xC4			// STM32���UARTͨ��

#define CMD_GET_VERSION					0xD0			// ��ȡ�汾��
#define CMD_PWR_COM						0xD8			// ��Դ��ͨ��

#define CMD_PRINTF_CTRL					0xE0			// printf ���ؿ���


#define  Err_OK							0				// û�д���

#define  Err_ComPort					0x8000			// ���ںŴ���
#define  Err_ComOpen					0x8001			// �޷��򿪴���

#define  Err_NoDevice					0x8002			// û�з����豸

#define  Err_Transefer					0x8003			// ͨ�Ŵ���
#define  Err_CheckSum					0x8004			// CheckSum����
#define  Err_Setup						0x8005			// ָ��ͷ����
#define	 Err_Index						0x8006			// ˳��Ŵ���
#define  Err_Token						0x8007			// ���ƴ���
#define  Err_MsgLen						0x8008			// ��Ϣ����
#define  Err_CmdCode					0x8009			// ָ�������
#define  Err_MsgEnd						0x800A			// ֡β
#define  Err_SubTransefer				0x8103			// ��λ��ͨ�ŷ����쳣
#define  Err_McuReturn					0x8F00			// MCU���صĴ�����

#define	 MAX_FILE_LEN					0x10000			// ����ļ�����

#define	 GPU_SPI_FLASH_PAGE_SIZE		0x100 	/* M25P80 Page��СΪ256Byte */


#define INDEX_CPU_LOGIC					0x00
#define INDEX_CPU_FW					0x01
#define INDEX_GPU						0x02
#define INDEX_POWER						0x03
#define INDEX_EX_MCU					0x04
#define INDEX_FLICKER					0x05
#define INDEX_TG_DISPLAY				0x06



#endif

