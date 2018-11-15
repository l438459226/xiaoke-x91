#ifndef _GPU_SPI_FLASH_PROTOCOL_H_
#define _GPU_SPI_FLASH_PROTOCOL_H_

// 主板和上位机的通信协议
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


#define CMD_SET_BAUDRATE				0x8C			// 设置波特率

#define MAX_PIC_DOWN_SIZE				4096			// 下载片单次最大支持的尺寸
#define MAX_PIC_UP_SIZE					512				// 上传图片音效最大支持的尺寸

#define CMD_GPU_SPI_FLASH_PROGRAM_EXIT	0x8F			// GPU SPI Flash 退出编程模式
#define CMD_GPU_SPI_FLASH_SECTOR_ERASE	0x90			// GPU SPI Flash Sector 擦除操作
#define CMD_PIC_DOWN_GET_INDEX			0x91			// 图片下载读顺序信息
#define CMD_GPU_SPI_FLASH_PAGE_PROGRAM	0x98			// GPU SPI Flash Page 写数据
#define CMD_PIC_DOWN_READ_DATA			0x99			// 图片下载读数据

#define CMD_NOP							0xA0			// 无操作，用于查找设备
#define CMD_SET_SPEED					0xA8			// 设置ISP速度
#define CMD_ENTER_PRG_MODE				0xB0			// 进入编程模式
#define CMD_EXIT_PRG_MODE				0xB1			// 退出编程模式
#define CMD_READ_ID						0xB2			// 读芯片ID

#define CMD_CHIP_ERASE					0xB4			// 整片擦除
#define CMD_SECTOR_ERASE				0xB5			// 扇区擦除
#define CMD_PRG_PAGE					0xB8			// 页编程
#define CMD_READ_PAGE					0xB9			// 页读取
#define CMD_PRG_LOCK					0xBA			// 编程锁定位
#define CMD_READ_LOCK					0xBB			// 读取锁定位

#define CMD_STM32_PRG_ENABLE			0xC0			// STM32编程使能
#define CMD_STM32_PRG_IO_CTRL			0xC2			// STM32编程IO控制

#define BITMASK_ISP_STM32_BOOT0			0x02			// BOOT0引脚
#define BITMASK_ISP_STM32_nRST			0x01			// nRST引脚

#define CMD_STM32_PRG_COM				0xC4			// STM32编程UART通信

#define CMD_GET_VERSION					0xD0			// 读取版本号
#define CMD_PWR_COM						0xD8			// 电源板通信

#define CMD_PRINTF_CTRL					0xE0			// printf 开关控制


#define  Err_OK							0				// 没有错误

#define  Err_ComPort					0x8000			// 串口号错误
#define  Err_ComOpen					0x8001			// 无法打开串口

#define  Err_NoDevice					0x8002			// 没有发现设备

#define  Err_Transefer					0x8003			// 通信错误
#define  Err_CheckSum					0x8004			// CheckSum错误
#define  Err_Setup						0x8005			// 指令头错误
#define	 Err_Index						0x8006			// 顺序号错误
#define  Err_Token						0x8007			// 令牌错误
#define  Err_MsgLen						0x8008			// 信息长度
#define  Err_CmdCode					0x8009			// 指令码错误
#define  Err_MsgEnd						0x800A			// 帧尾
#define  Err_SubTransefer				0x8103			// 下位机通信发生异常
#define  Err_McuReturn					0x8F00			// MCU返回的错误码

#define	 MAX_FILE_LEN					0x10000			// 最大文件长度

#define	 GPU_SPI_FLASH_PAGE_SIZE		0x100 	/* M25P80 Page大小为256Byte */


#define INDEX_CPU_LOGIC					0x00
#define INDEX_CPU_FW					0x01
#define INDEX_GPU						0x02
#define INDEX_POWER						0x03
#define INDEX_EX_MCU					0x04
#define INDEX_FLICKER					0x05
#define INDEX_TG_DISPLAY				0x06



#endif

