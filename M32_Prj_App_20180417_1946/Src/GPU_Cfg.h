#ifndef __GPU_CFG_H
#define __GPU_CFG_H

#include "BasicDataType.h"
#include "user_config.h"
#include "stm32f10x.h"

//------------------------------------------------------------------------------
#define MCU_CFG_GPU__GPU_DATE_TIME_ADDR0   	(0x0000)
#define MCU_CFG_GPU__GPU_DATE_TIME_ADDR1   	(0x0100)
#define MCU_CFG_GPU__GPU_VERSION_ADDR0     	(0x0200)
#define MCU_CFG_GPU__GPU_VERSION_ADDR1     	(0x0300)

#define MCU_CFG_GPU__DDR_FRAMEREGION_READ_START_ADDR   	(0x0400) /* {12'h0, ???}, 4bit<[29:26] or {2'b00, [27:26]} of DDR-ByteAddr>, FramePage */
#define MCU_CFG_GPU__DDR_ACCESS_BYTE_ADDR0 				(0x0500) /* [15:0] */
#define MCU_CFG_GPU__DDR_ACCESS_BYTE_ADDR1 				(0x0600) /* {32bitAccessDDRWithMask_Enable, Access_W0_R1_Sel, [29:16]} */
#define MCU_CFG_GPU__DDR_ACCESS_CTRL_REG_ADDR 			(0x0700) /* {6'h20,Vld1,Vld0, DDR_Ready, {Access-Start-Trig, burst-length[5:0]}} */
#define MCU_CFG_GPU__PARAM_VACT_ADDR 		(0x0800) /* {InvDE, InvVS, InvHS, VACT[12:0]} */
#define MCU_CFG_GPU__PARAM_HACT_ADDR 		(0x0900) /* {2'h0, ResetLcdLogic, HACT[12:0]} */
#define MCU_CFG_GPU__PARAM_VSW_ADDR 		(0x0A00) /* {ChannelTwoSame, ChannelSwap, DualMipi_EO_nLR, VSW[12:0]} */
#define MCU_CFG_GPU__PARAM_VBP_ADDR 		(0x0B00) /* {3'h0, VBP[12:0]} */
#define MCU_CFG_GPU__PARAM_VFP_ADDR 		(0x0C00) /* {3'h0, VFP[12:0]} */
#define MCU_CFG_GPU__PARAM_HSW_ADDR 		(0x0D00) /* {3'h0, HSW[12:0]} */
#define MCU_CFG_GPU__PARAM_HBP_ADDR 		(0x0E00) /* {3'h0, HBP[12:0]} */
#define MCU_CFG_GPU__PARAM_HFP_ADDR 		(0x0F00) /* {3'h0, HFP[12:0]} */
#define MCU_CFG_GPU__PURECOLOR_ADDR0 		(0x1000) /* {G[7:0], B[7:0]} */
#define MCU_CFG_GPU__PURECOLOR_ADDR1 		(0x1100) /* {7'h0, PureColorEnable, R[7:0]} */

//#define MCU_CFG_GPU__PLL_DATA_ADDR0 		(0x1200)
//#define MCU_CFG_GPU__PLL_DATA_ADDR1 		(0x1300)
//#define MCU_CFG_GPU__PLL_DATA_ADDR2 		(0x1400)
//#define MCU_CFG_GPU__PLL_DATA_ADDR3 		(0x1500)
//#define MCU_CFG_GPU__PLL_DATA_ADDR4 		(0x1600)
//#define MCU_CFG_GPU__PLL_DATA_ADDR5 		(0x1700)
//#define MCU_CFG_GPU__PLL_DATA_ADDR6 		(0x1800)
//#define MCU_CFG_GPU__PLL_CTRL_ADDR 		(0x1900)

#define MCU_CFG_GPU__GPIO_Output_ADDR0 		(0x1A00) /* [15:8] is mask of [7:0], bit[i] will be success written when bit[i+8]==1; */
#define MCU_CFG_GPU__GPIO_Output_ADDR1 		(0x1B00)

#define MCU_CFG_GPU__GPIO_Input_ADDR0 		(0x1C00)


#define MCU_CFG_GPU__DDRBUF_ADDR 			(0x1F00) //256*32 buffer, each 32bit:{8'h00<Reserved>, R[7:0], G[7:0], B[7:0]}


//SD Controller Register region address
#define MCU_CFG_GPU__SDIP_ARG01_REG_ADDR       (0x2000)
#define MCU_CFG_GPU__SDIP_ARG23_REG_ADDR       (0x2100)
#define MCU_CFG_GPU__SDIP_COMMAND_REG_ADDR     (0x2200)
#define MCU_CFG_GPU__SDIP_BLK_CNT_REG_ADDR     (0x2400)
#define MCU_CFG_GPU__SDIP_BYTE_CNT_REG_ADDR    (0x2600)
#define MCU_CFG_GPU__SDIP_CTRL_REG_ADDR        (0x2800)
#define MCU_CFG_GPU__SDIP_CONFIG_REG_ADDR      (0x2A00)
#define MCU_CFG_GPU__SDIP_INTR_ENABLE_REG_ADDR (0x2C00)
#define MCU_CFG_GPU__SDIP_STATUS_REG_ADDR      (0x2E00)
#define MCU_CFG_GPU__SDIP_RSPNS01_REG_ADDR     (0x3000)
#define MCU_CFG_GPU__SDIP_RSPNS23_REG_ADDR     (0x3100)
#define MCU_CFG_GPU__SDIP_RSPNS45_REG_ADDR     (0x3200)
#define MCU_CFG_GPU__SDIP_RSPNS67_REG_ADDR     (0x3300)
#define MCU_CFG_GPU__SDIP_RSPNS89_REG_ADDR     (0x3400)
#define MCU_CFG_GPU__SDIP_RSPNSAB_REG_ADDR     (0x3500)
#define MCU_CFG_GPU__SDIP_RSPNSCD_REG_ADDR     (0x3600)
#define MCU_CFG_GPU__SDIP_RSPNSE_REG_ADDR      (0x3700)
#define MCU_CFG_GPU__SDIP_BUFFER_DATA_REG_ADDR (0x4000) /* Buffer-Size:4096*16, 读或写之前先指定起始地址, 然后陆续读/写即可(GPU内部地址会自动递加) */
#define MCU_CFG_GPU__SDIP_BUFFER_CTRL_REG_ADDR (0x4100) /* {3'h0<Reserved>, MCU_SPIP2DDR_FIFO_channel_sel, [11:0]<BUF_sdmcu_addr_start>} */

#define MCU_CFG_GPU__SDIP_FIFO_RESET_ADDR      (0x4200) /* {14'h0<Reserved>, SD_BMP_LineOrderReverse<1 mean reverse>, ResetFIFO<HighActive>} */

#define MCU_CFG_GPU__CONNECTION_CHECK_ADDR     (0x4300) /* {16'hA5C3} */

#define MCU_CFG_GPU__BINDINGDATA_ADDR0         (0x4500)
#define MCU_CFG_GPU__BINDINGDATA_ADDR1         (0x4600)
#define MCU_CFG_GPU__BINDINGDATA_ADDR2         (0x4700)
#define MCU_CFG_GPU__BINDINGDATA_ADDR3         (0x4800)
#define MCU_CFG_GPU__BINDINGDATA_ADDR4         (0x4900)

#define MCU_CFG_GPU__COMMANDMODE_R_DATAL       (0x4A00) /* ReadOnly, [15:0] */
#define MCU_CFG_GPU__COMMANDMODE_R_DATAH       (0x4B00) /* ReadOnly, {8'h00, [23:16]} */
#define MCU_CFG_GPU__COMMANDMODE_W_DATA        (0x4C00) /* WriteOnly, [15:0], the [23:16] is contained in Addr[7:0] */
#define MCU_CFG_GPU__COMMANDMODE_CONTROL       (0x4D00) /* W/R, {8'h0, LINERD_ENABLE, RGB0_BGR1_ORDER, GPU_WholeFrame<Auto Cleared after set to 1>, GPU_RectanglePureColor<Auto Cleared after set to 1>, CM_ReadReq, WRX, RDX, DCX} */
#define MCU_CFG_GPU__COMMANDMODE_RECT_PIXELNUM (0x4E00) /* WriteOnly, [15:0], the [21:16] is contained in Addr[5:0] */
#define MCU_CFG_GPU__COMMANDMODE_ENABLE        (0x4F00) /* WriteOnly, {15'h0, CommandModeSelect}, default:0, 0 mean VideoMode, 1 mean CommandMode */


//CommandMode defines
#define CM_GPU_CONTROL__LINERD_ENABLE_1       (0x8080) //4 Pixels based, the data(multiply of 4 pixels, from DDR) read should be in the same line;
#define CM_GPU_CONTROL__LINERD_ENABLE_0       (0x8000)
#define CM_GPU_CONTROL__RGB0_BGR1_ORDER_1     (0x4040)
#define CM_GPU_CONTROL__RGB0_BGR1_ORDER_0     (0x4000)
#define CM_GPU_CONTROL__WHOLEFRAME_1          (0x2020) //<Auto Cleared after set to 1>
#define CM_GPU_CONTROL__WHOLEFRAME_0          (0x2000)
#define CM_GPU_CONTROL__RECTANGLEPURECOLOR_1  (0x1010) //<Auto Cleared after set to 1>
#define CM_GPU_CONTROL__READREQ_1             (0x0808)
#define CM_GPU_CONTROL__READREQ_0             (0x0800)
#define CM_GPU_CONTROL__WRX_1                 (0x0404)
#define CM_GPU_CONTROL__WRX_0                 (0x0400)
#define CM_GPU_CONTROL__RDX_1                 (0x0202)
#define CM_GPU_CONTROL__RDX_0                 (0x0200)
#define CM_GPU_CONTROL__DCX_1                 (0x0101)
#define CM_GPU_CONTROL__DCX_0                 (0x0100)


//------------------------------------------------------------------------------
//function declaration
UINT32 Get_GPU_DateTime(void);
UINT32 Get_GPU_Version(void);

UINT8 GPU_Connection_Check(void);
UINT8 GPU_LogicWorkStatus(void);

void Gpu_DisplayCfg(void);

void Lcd_ShowPureColor(UINT8 pure_R, UINT8 pure_G, UINT8 pure_B);




void O_PWR_EN_VSN(UINT8 Val); 			// bit0 ---MCU_CFG_GPU__GPIO_Output_ADDR0
void O_PWR_EN_VSP(UINT8 Val); 			// bit1
void O_PWR_BL_EN(UINT8 Val); 			// bit2
void O_PWR_BLK_SET_GPA23(UINT8 Val); 	// bit3
void O_PWR_BLK_SET_GPA24(UINT8 Val); 	// bit4
void O_PWR_BLK_SET_GPE14(UINT8 Val); 	// bit5
void O_PWR_BLK_SET_GPE15(UINT8 Val); 	// bit6
void O_PWR_BLK_SET_GPM0(UINT8 Val); 	// bit7
void O_EN_RES(UINT8 Val); 			// bit0 ---MCU_CFG_GPU__GPIO_Output_ADDR1
void O_LCM_TP_RES(UINT8 Val); 		// bit1




UINT8 I_LCM_INT(void);




//--- Pattern function ---
void op_PatternGrayScaleH(UINT8 InvertRGB, UINT8 GrayScaleNum);
void op_PatternGrayScaleV(UINT8 InvertRGB, UINT8 GrayScaleNum);
void op_Pattern4ColorBarGrayScaleH(UINT8 InvertRGB, UINT8 GrayScaleNum);
void op_Pattern4ColorBarGrayScaleV(UINT8 InvertRGB, UINT8 GrayScaleNum);
void op_PatternFlickerOneDot(UINT8 R1, UINT8 G1, UINT8 B1, UINT8 R0, UINT8 G0, UINT8 B0);
void op_PatternFlickerColumnInversion(UINT8 R1, UINT8 G1, UINT8 B1, UINT8 R0, UINT8 G0, UINT8 B0);
void op_PatternPureColorThroughDDR(UINT8 R, UINT8 G, UINT8 B);
void op_Pattern8ColorBarH_BBRGWCYM(void);
void op_Pattern8ColorBarV_BBRGWCYM(void);
void op_PatternCrosstalk_BlackWhite(UINT8 BlackOrNot);
void op_PatternChecker_BlackWhite(UINT8 BlackOrNot, UINT8 CheckerHNum, UINT8 CheckerVNum);
void op_PatternColorOutline(UINT8 par_R, UINT8 par_G, UINT8 par_B);

void TestDrawPixelDotLine(void);
void TestCommandModeDrawRectangleFromDDR(void);

void op_PatternShow16x16DotArray(UINT16 LineIndex, UINT16 ColumnIndexStart, UINT8 *DotArray, UINT8 F_R,UINT8 F_G,UINT8 F_B, UINT8 B_R,UINT8 B_G, UINT8 B_B);


//CommandMode Register
void CommandMode_Init(void);
void CommandMode_Read(UINT32 Cmd, UINT32 *RData, INT16 RdCnt);
void CommandMode_Write(UINT32 Cmd, UINT32 *WData, INT16 WrCnt);
void CommandMode_GPUWholeFrame_FastWrite(UINT32 Cmd);
void CommandMode_GPURectanglePureColor_FastWrite(UINT32 PureColorRGB, UINT32 PixelTotalNumberInRegion, UINT32 Cmd);
void CommandMode_GPURectangleReadOutFromDDR(UINT32 Cmd, UINT16 ddr_current_display_region_addr, UINT16 LinePixel_RowAddrStart, UINT16 Row_Num, UINT16 LinePixel_ColumnAddrStart, UINT16 ColumnPixel_Num);

//--- SDIP ---
extern UINT16 RCA;
extern UINT16 CardCapacityStatus;

void SD_IP_Config_Init(void);
UINT8 SD_IP_Wait_Cmd_Done(void);
void SD_IP_Wait_Data_Done(void);
void SD_IP_Wait_Clock_Change_Done(void);
UINT8 SD_IP_Send_Cmd_Non_Data(UINT8 index, UINT32 arg);
UINT8 SD_IP_Send_Cmd_Has_Data(UINT8 index, UINT32 arg, UINT8 RWFlag, UINT16 BLK_CNT, UINT16 BYTE_CNT);
UINT8 SD_IP_Card_Init(void);
UINT8 SD_ReadDisk(UINT8 *buf, UINT32 sector, UINT8 cnt);
UINT8 SD_WriteDisk(UINT8 *buf, UINT32 sector, UINT8 cnt);
UINT8 SD_ReadDisk_to_FIFO(UINT32 sector, UINT16 cnt);

//--- FAT32 Sys ---
typedef struct { //ShortFileName(SFN:8+3)
	UINT32 FileSize; //32-bit DWORD holding this file's size in bytes.
	UINT32 FileFstClus; //this entry's first cluster number.
}FAT32_BMP_ENTRY;

void ExtractBPB_Param(void);
//void FindBMP_Entry(FAT32_BMP_ENTRY *ptrBMPEntry);
void FindALLBMP_Entry(void);
void DisplayBMP(UINT16 Num);



#endif /* __GPU_CFG_H */
