#include "GPU_Cfg.h"
#include "MCU_GPU_fsmc.h"
#include "tools.h"
#include <stdio.h>

//DDR Byte address: [29:0], Actual DDR Memory 2Gb(128M*16bit):[27:0], The Higher 2bit[29:28] for future use, Now Keep 2'b00;
//FramePage: [29:26], or Actual:{2'b00, [27:26]};
//FrameRegion: 4096*4096Pixel, [25:14] * [13:0] Byte;
//each time access 128bit(16*8bit), so [3:0] should be always 0s;(即每次最少写入数据单位是4个Pixel<128bit=4*32>)
//
//目前DDR 双buffer切换对应的FramePage地址为[29:26]--> 4'h0 or 4'h1, 即4'h0显示时往4'h1写, 4'h1显示时往4'h0写;
//

void pattern_grayscale_buf(UINT16 *ptr_i, UINT16 *ptr_i_Remainder, UINT8 *ptr_RGBValue, UINT8 grayscalenum, UINT8 *ptr_Scale256Remainder, UINT16 Scale256Step, UINT16 Scale256StepPlus1, UINT32 RGBmask, UINT8 InvertRGB) {
	UINT16 k;
	UINT8 RGBValue;

	MCU_GPU__ADDR = MCU_CFG_GPU__DDRBUF_ADDR;

	RGBValue = (UINT8)(((UINT16)(*ptr_RGBValue)) * 0x0ff / ((UINT16)grayscalenum)); //when 64 grayscale, then 53 --> 53*255/63
	if(InvertRGB != 0)
		RGBValue = ~RGBValue;

	for(k=0; k<256; k++) {
		MCU_GPU__DATAH = (UINT16)RGBValue & (RGBmask >> 16);
		MCU_GPU__DATA  = (((UINT16)RGBValue<<8) | (UINT16)RGBValue) & ((UINT16)RGBmask);//(UINT16)RGBValue; //
		
		(*ptr_i)++;
		if(*ptr_Scale256Remainder != 0) {
			if((*ptr_i)%Scale256StepPlus1 == 0) {
				(*ptr_RGBValue)--;
				(*ptr_Scale256Remainder)--;
				*ptr_i_Remainder = *ptr_i;
				RGBValue = (UINT8)(((UINT16)(*ptr_RGBValue)) * 0x0ff / ((UINT16)grayscalenum)); //when 64 grayscale, then 53 --> 53*255/63
				if(InvertRGB != 0)
					RGBValue = ~RGBValue;
			}
		}
		else {
			if((*ptr_i - *ptr_i_Remainder)%Scale256Step == 0) {
				(*ptr_RGBValue)--;
				RGBValue = (UINT8)(((UINT16)(*ptr_RGBValue)) * 0x0ff / ((UINT16)grayscalenum)); //when 64 grayscale, then 53 --> 53*255/63
				if(InvertRGB != 0)
					RGBValue = ~RGBValue;
			}
		}
		if((*ptr_i) == ptr_MIPI_TABLE[gMipiTableIndex]->HACT_WIDTH) //when dual-mipi, break if half filled
			break;
	}
}
void pattern_grayscale_wr_ddr(UINT16 linenum, UINT16 ddr_current_display_region_addr, UINT8 num_in256pixel_eachline) {
	UINT16 value;
	UINT16 res;

	if(ddr_current_display_region_addr == 0) { //process with ddr-byte-addr[26]
		value = (linenum>>2) | 0x0400;
	}
	else {
		value = (linenum>>2) & 0x03ff;
	}
	MCU_GPU__ADDR = MCU_CFG_GPU__DDR_ACCESS_BYTE_ADDR1;
	MCU_GPU__DATA = value;
	value = linenum<<14;
	MCU_GPU__ADDR = MCU_CFG_GPU__DDR_ACCESS_BYTE_ADDR0;
	MCU_GPU__DATA = value | (((UINT16)num_in256pixel_eachline)<<10); //256pixel=256*4byte=1024byte

	MCU_GPU__ADDR = MCU_CFG_GPU__DDR_ACCESS_CTRL_REG_ADDR;
	MCU_GPU__DATA = 0x007f;//start_enable:1, burst length:63, that is 64 of 128bits
		
	//-----wait transfer done
	res = 0x40;
	while(res) {
		res = MCU_GPU__DATA;
		res = res & 0x40;
	}
}

void pattern_WriteLineBuf256Pixel(UINT8 R0, UINT8 G0, UINT8 B0, UINT8 R1, UINT8 G1, UINT8 B1) {
	UINT16 i;
	
	MCU_GPU__ADDR = MCU_CFG_GPU__DDRBUF_ADDR;
	
	for(i=0; i<128; i++) {
		MCU_GPU__DATAH = (UINT16)R0;
		MCU_GPU__DATA  = ((UINT16)G0<<8) | (UINT16)B0;
		MCU_GPU__DATAH = (UINT16)R1;
		MCU_GPU__DATA  = ((UINT16)G1<<8) | (UINT16)B1;
	}
}
void pattern_crosstalk_buf(UINT16 *ptr_i, UINT16 RegionL, UINT16 RegionH, UINT8 Ri, UINT8 Gi, UINT8 Bi, UINT8 Ro, UINT8 Go, UINT8 Bo) {
	UINT16 k;
	
	MCU_GPU__ADDR = MCU_CFG_GPU__DDRBUF_ADDR;
	
	for(k=0; k<256; k++) {
		//if((*ptr_i > (bmp_width_single_or_dual >> 2)) && (*ptr_i < ((bmp_width_single_or_dual >> 2) * 3))) { //black or white
		if((*ptr_i >= RegionL) && (*ptr_i < RegionH)) { //inner region
			MCU_GPU__DATAH = (UINT16)Ri;
			MCU_GPU__DATA  = ((UINT16)Gi<<8) | (UINT16)Bi;
		}
		else { //outline region
			MCU_GPU__DATAH = (UINT16)Ro;
			MCU_GPU__DATA  = ((UINT16)Go<<8) | (UINT16)Bo;
		}

		(*ptr_i)++;
		if((*ptr_i) == ptr_MIPI_TABLE[gMipiTableIndex]->HACT_WIDTH) //when dual-mipi, break if half filled
			break;
	}
}
void pattern_WriteLineOneDot(UINT8 cur_display_region, UINT16 cur_line_ddr_addr, UINT8 num_in256pixel_eachline) {
	UINT8 j;
	UINT16 value;
	UINT16 res;

	
	
	if(cur_display_region == 0) { //process with ddr-byte-addr[26]
		value = (cur_line_ddr_addr>>2) | 0x0400;
	}
	else {
		value = (cur_line_ddr_addr>>2) & 0x03ff;
	}
	MCU_GPU__ADDR = MCU_CFG_GPU__DDR_ACCESS_BYTE_ADDR1;
	MCU_GPU__DATA = value;
	value = cur_line_ddr_addr<<14;
	
	for(j=0; j<num_in256pixel_eachline; j++) {
		MCU_GPU__ADDR = MCU_CFG_GPU__DDR_ACCESS_BYTE_ADDR0;
		MCU_GPU__DATA = value | (((UINT16)j)<<10); //256pixel=256*4byte=1024byte

		MCU_GPU__ADDR = MCU_CFG_GPU__DDR_ACCESS_CTRL_REG_ADDR;
		MCU_GPU__DATA = 0x007f;//start_enable:1, burst length:63, that is 64 of 128bits
			
		//-----wait transfer done
		res = 0x40;
		while(res) {
			res = MCU_GPU__DATA;
			res = res & 0x40;
		}
	}

	if(ptr_MIPI_TABLE[gMipiTableIndex]->DUAL_MIPI_LCD != 0) { //dual mipi
		for(j=8; j<(num_in256pixel_eachline+8); j++) {
			MCU_GPU__ADDR = MCU_CFG_GPU__DDR_ACCESS_BYTE_ADDR0;
			MCU_GPU__DATA = value | (((UINT16)j)<<10); //256pixel=256*4byte=1024byte

			MCU_GPU__ADDR = MCU_CFG_GPU__DDR_ACCESS_CTRL_REG_ADDR;
			MCU_GPU__DATA = 0x007f;//start_enable:1, burst length:63, that is 64 of 128bits
		
			//-----wait transfer done
			res = 0x40;
			while(res) {
				res = MCU_GPU__DATA;
				res = res & 0x40;
			}
		}
	}
}


void op_PatternGrayScaleH(UINT8 InvertRGB, UINT8 GrayScaleNum) {
	UINT8 blk_num_in256Pixel_of_each_line;
	UINT16 ddr_current_display_region_addr;
	UINT16 Scale256Step; //eg: 1080*1920, then Scale256 of 1080(256*4 + 56) need 4 pixel each step, here step = 4;
	UINT16 Scale256StepPlus1;
	UINT8 Scale256Remainder; //eg: 1080*1920, then Scale256 of 1080(256*4 + 56) is 56 as remainder, here remainder = 56;
	UINT16 j;
	UINT16 i;
	UINT16 i_Remainder;
	UINT8 RGBValue;
	UINT8 num_in256pixel_eachline;
	UINT8 grayscale_num;
	
	
	
	//Cancel FIFO Channel of BMP display(FIFO-BUF-DDR), Here is MCU-BUF-DDR,
	MCU_GPU__ADDR = MCU_CFG_GPU__SDIP_BUFFER_CTRL_REG_ADDR;
	MCU_GPU__DATA = 0x0000; //bit[12], 1 mean select SDIP to DDR FIFO channel; 0 mean select SD-MCU-buffer;
	
	
	MCU_GPU__ADDR = MCU_CFG_GPU__DDR_FRAMEREGION_READ_START_ADDR;//read the current display region, [29:26] of DDR-BYTE-ADDRESS
	ddr_current_display_region_addr = MCU_GPU__DATA;
	
	blk_num_in256Pixel_of_each_line = ((ptr_MIPI_TABLE[gMipiTableIndex]->HACT_WIDTH - 1) >> 8) + 1;
	
	grayscale_num = GrayScaleNum;
	if(grayscale_num == 0) //remove 0
		grayscale_num = 0xff;
	
	if(ptr_MIPI_TABLE[gMipiTableIndex]->DUAL_MIPI_LCD != 0) { //dual mipi
		Scale256Step = (ptr_MIPI_TABLE[gMipiTableIndex]->HACT_WIDTH << 1) / (((UINT16)grayscale_num) + 1); //divide 256
		Scale256Remainder = (ptr_MIPI_TABLE[gMipiTableIndex]->HACT_WIDTH << 1) % (((UINT16)grayscale_num) + 1); //remainder
	}
	else {
		Scale256Step = ptr_MIPI_TABLE[gMipiTableIndex]->HACT_WIDTH / (((UINT16)grayscale_num) + 1); //divide 256
		Scale256Remainder = ptr_MIPI_TABLE[gMipiTableIndex]->HACT_WIDTH % (((UINT16)grayscale_num) + 1); //remainder
	}
	
	Scale256StepPlus1 = Scale256Step + 1;
	RGBValue = grayscale_num;
	i=0;
	i_Remainder = 0;
		
	for(num_in256pixel_eachline=0; num_in256pixel_eachline<blk_num_in256Pixel_of_each_line; ) {
		pattern_grayscale_buf(&i, &i_Remainder, &RGBValue, grayscale_num, &Scale256Remainder, Scale256Step, Scale256StepPlus1, 0x00FFFFFF, InvertRGB);
		
		for(j=0; j<ptr_MIPI_TABLE[gMipiTableIndex]->VACT_WIDTH; j++) {
			pattern_grayscale_wr_ddr(j, ddr_current_display_region_addr, num_in256pixel_eachline);
		}
		num_in256pixel_eachline++;
		
		if(ptr_MIPI_TABLE[gMipiTableIndex]->DUAL_MIPI_LCD != 0) { //dual mipi, then blk_num_in256Pixel_of_each_line is only half
			if(num_in256pixel_eachline == blk_num_in256Pixel_of_each_line) {
				if(num_in256pixel_eachline > 8)
					break;
				else {
					num_in256pixel_eachline = 8;
					blk_num_in256Pixel_of_each_line += 8;
				}
			}
		}
	}
	
	//update the figure display region in DDR
	if(ddr_current_display_region_addr == 0) {
		MCU_GPU__ADDR = MCU_CFG_GPU__DDR_FRAMEREGION_READ_START_ADDR;
		MCU_GPU__DATA = 0x01;
	}
	else {
		MCU_GPU__ADDR = MCU_CFG_GPU__DDR_FRAMEREGION_READ_START_ADDR;
		MCU_GPU__DATA = 0x00;
	}
	
	//close pure color mode to BMP display mode, if previous display is Pure-Color-Mode
	{
		MCU_GPU__ADDR = MCU_CFG_GPU__PURECOLOR_ADDR1;
		MCU_GPU__DATA = 0x0000;
	}
}





void op_PatternGrayScaleV(UINT8 InvertRGB, UINT8 GrayScaleNum) {
	UINT8 blk_num_in256Pixel_of_each_line;
	UINT8 ddr_current_display_region_addr;
	UINT16 Scale256Step; //eg: 1080*1920, then Scale256 of 1080(256*4 + 56) need 4 pixel each step, here step = 4;
	UINT16 Scale256StepPlus1;
	UINT8 Scale256Remainder; //eg: 1080*1920, then Scale256 of 1080(256*4 + 56) is 56 as remainder, here remainder = 56;
	UINT16 j;
	UINT8 RGBValue;
	UINT16 line_num;
	UINT8 k;
	UINT8 grayscale_num;
	UINT8 grayscale_value;
	
	
	//Cancel FIFO Channel of BMP display(FIFO-BUF-DDR), Here is MCU-BUF-DDR,
	MCU_GPU__ADDR = MCU_CFG_GPU__SDIP_BUFFER_CTRL_REG_ADDR;
	MCU_GPU__DATA = 0x0000; //bit[12], 1 mean select SDIP to DDR FIFO channel; 0 mean select SD-MCU-buffer;
	
	
	MCU_GPU__ADDR = MCU_CFG_GPU__DDR_FRAMEREGION_READ_START_ADDR;//read the current display region, [29:26] of DDR-BYTE-ADDRESS
	ddr_current_display_region_addr = MCU_GPU__DATA;
	
	
	blk_num_in256Pixel_of_each_line = ((ptr_MIPI_TABLE[gMipiTableIndex]->HACT_WIDTH - 1) >> 8) + 1;
	grayscale_num = GrayScaleNum;
	if(grayscale_num == 0) //remove 0
		grayscale_num = 0xff;
	
	Scale256Step = ptr_MIPI_TABLE[gMipiTableIndex]->VACT_WIDTH / (((UINT16)grayscale_num) + 1); //divide 256
	Scale256Remainder = ptr_MIPI_TABLE[gMipiTableIndex]->VACT_WIDTH % (((UINT16)grayscale_num) + 1); //remainder
	
	Scale256StepPlus1 = Scale256Step + 1;
	grayscale_value = grayscale_num;
	
	line_num = 0;
	for(k=0; k<Scale256Remainder; k++) {
		RGBValue = (UINT8)(((UINT16)grayscale_value) * 0x0ff / ((UINT16)grayscale_num)); //when 64 grayscale, then 53 --> 53*255/63
	  if(InvertRGB != 0)
			RGBValue = ~RGBValue;
		pattern_WriteLineBuf256Pixel(RGBValue, RGBValue, RGBValue, RGBValue, RGBValue, RGBValue);
		for(j=line_num; j<(Scale256StepPlus1+line_num); j++) {
			pattern_WriteLineOneDot(ddr_current_display_region_addr, j, blk_num_in256Pixel_of_each_line);
		}
		grayscale_value--;
		line_num += Scale256StepPlus1;
	}
	while(line_num < ptr_MIPI_TABLE[gMipiTableIndex]->VACT_WIDTH) {
		RGBValue = (UINT8)(((UINT16)grayscale_value) * 0x0ff / ((UINT16)grayscale_num)); //when 64 grayscale, then 53 --> 53*255/63
	  if(InvertRGB != 0)
			RGBValue = ~RGBValue;
		pattern_WriteLineBuf256Pixel(RGBValue, RGBValue, RGBValue, RGBValue, RGBValue, RGBValue);
		for(j=line_num; j<(Scale256Step+line_num); j++) {
			pattern_WriteLineOneDot(ddr_current_display_region_addr, j, blk_num_in256Pixel_of_each_line);
		}
		grayscale_value--;
		line_num += Scale256Step;
	}
	
	//update the figure display region in DDR
	if(ddr_current_display_region_addr == 0) {
		MCU_GPU__ADDR = MCU_CFG_GPU__DDR_FRAMEREGION_READ_START_ADDR;
		MCU_GPU__DATA = 0x01;
	}
	else {
		MCU_GPU__ADDR = MCU_CFG_GPU__DDR_FRAMEREGION_READ_START_ADDR;
		MCU_GPU__DATA = 0x00;
	}
	
	//close pure color mode to BMP display mode, if previous display is Pure-Color-Mode
	{
		MCU_GPU__ADDR = MCU_CFG_GPU__PURECOLOR_ADDR1;
		MCU_GPU__DATA = 0x0000;
	}
}



void op_Pattern4ColorBarGrayScaleV(UINT8 InvertRGB, UINT8 GrayScaleNum) {
	UINT8 blk_num_in256Pixel_of_each_line;
	UINT8 ddr_current_display_region_addr;
	UINT16 Scale256Step; //eg: 1080*1920, then Scale256 of 1080(256*4 + 56) need 4 pixel each step, here step = 4;
	UINT16 Scale256StepPlus1;
	UINT8 Scale256Remainder; //eg: 1080*1920, then Scale256 of 1080(256*4 + 56) is 56 as remainder, here remainder = 56;
	UINT8 Scale256Remainder_prev;
	UINT16 j;
	UINT16 i;
	UINT16 i_Remainder;
	UINT16 i_prev;
	UINT8 RGBValue;
	UINT8 RGBValue_prev;
	UINT8 num_in256pixel_eachline;
	UINT8 grayscale_num;
	
	//Cancel FIFO Channel of BMP display(FIFO-BUF-DDR), Here is MCU-BUF-DDR,
	MCU_GPU__ADDR = MCU_CFG_GPU__SDIP_BUFFER_CTRL_REG_ADDR;
	MCU_GPU__DATA = 0x0000; //bit[12], 1 mean select SDIP to DDR FIFO channel; 0 mean select SD-MCU-buffer;
	
	
	MCU_GPU__ADDR = MCU_CFG_GPU__DDR_FRAMEREGION_READ_START_ADDR;//read the current display region, [29:26] of DDR-BYTE-ADDRESS
	ddr_current_display_region_addr = MCU_GPU__DATA;
	
	
	blk_num_in256Pixel_of_each_line = ((ptr_MIPI_TABLE[gMipiTableIndex]->HACT_WIDTH - 1) >> 8) + 1;


	grayscale_num = GrayScaleNum;
	if(grayscale_num == 0) //remove 0
		grayscale_num = 0xff;
	
	if(ptr_MIPI_TABLE[gMipiTableIndex]->DUAL_MIPI_LCD != 0) { //dual mipi
		Scale256Step = (ptr_MIPI_TABLE[gMipiTableIndex]->HACT_WIDTH << 1) / (((UINT16)grayscale_num) + 1); //divide 256
		Scale256Remainder = (ptr_MIPI_TABLE[gMipiTableIndex]->HACT_WIDTH << 1) % (((UINT16)grayscale_num) + 1); //remainder
	}
	else {
		Scale256Step = ptr_MIPI_TABLE[gMipiTableIndex]->HACT_WIDTH / (((UINT16)grayscale_num) + 1); //divide 256
		Scale256Remainder = ptr_MIPI_TABLE[gMipiTableIndex]->HACT_WIDTH % (((UINT16)grayscale_num) + 1); //remainder
	}

	Scale256StepPlus1 = Scale256Step + 1;
	RGBValue = grayscale_num;
	i=0;
	i_Remainder = 0;
	
	for(num_in256pixel_eachline=0; num_in256pixel_eachline<blk_num_in256Pixel_of_each_line; ) {
		RGBValue_prev = RGBValue;
		i_prev = i;
		Scale256Remainder_prev = Scale256Remainder;
		
		pattern_grayscale_buf(&i, &i_Remainder, &RGBValue, grayscale_num, &Scale256Remainder, Scale256Step, Scale256StepPlus1, 0x00FF0000, InvertRGB);
		for(j=0; j<(ptr_MIPI_TABLE[gMipiTableIndex]->VACT_WIDTH>>2); j++) {
			pattern_grayscale_wr_ddr(j, ddr_current_display_region_addr, num_in256pixel_eachline);
		}
		
		RGBValue = RGBValue_prev;
		i = i_prev;
		Scale256Remainder = Scale256Remainder_prev;
		pattern_grayscale_buf(&i, &i_Remainder, &RGBValue, grayscale_num, &Scale256Remainder, Scale256Step, Scale256StepPlus1, 0x0000FF00, InvertRGB);
		for(; j<(ptr_MIPI_TABLE[gMipiTableIndex]->VACT_WIDTH>>1); j++) {
			pattern_grayscale_wr_ddr(j, ddr_current_display_region_addr, num_in256pixel_eachline);
		}
		
		RGBValue = RGBValue_prev;
		i = i_prev;
		Scale256Remainder = Scale256Remainder_prev;
		pattern_grayscale_buf(&i, &i_Remainder, &RGBValue, grayscale_num, &Scale256Remainder, Scale256Step, Scale256StepPlus1, 0x000000FF, InvertRGB);
		for(; j<((ptr_MIPI_TABLE[gMipiTableIndex]->VACT_WIDTH>>2)*3); j++) {
			pattern_grayscale_wr_ddr(j, ddr_current_display_region_addr, num_in256pixel_eachline);
		}
		
		RGBValue = RGBValue_prev;
		i = i_prev;
		Scale256Remainder = Scale256Remainder_prev;
		pattern_grayscale_buf(&i, &i_Remainder, &RGBValue, grayscale_num, &Scale256Remainder, Scale256Step, Scale256StepPlus1, 0x00FFFFFF, InvertRGB);
		for(; j<ptr_MIPI_TABLE[gMipiTableIndex]->VACT_WIDTH; j++) {
			pattern_grayscale_wr_ddr(j, ddr_current_display_region_addr, num_in256pixel_eachline);
		}
		
		num_in256pixel_eachline++;
		if(ptr_MIPI_TABLE[gMipiTableIndex]->DUAL_MIPI_LCD != 0) { //dual mipi, then blk_num_in256Pixel_of_each_line is just half
			if(num_in256pixel_eachline == blk_num_in256Pixel_of_each_line) {
				if(num_in256pixel_eachline > 4)
					break;
				else {
					num_in256pixel_eachline = 4;
					blk_num_in256Pixel_of_each_line += 4;
				}
			}
		}
	}
	
	//update the figure display region in DDR
	if(ddr_current_display_region_addr == 0) {
		MCU_GPU__ADDR = MCU_CFG_GPU__DDR_FRAMEREGION_READ_START_ADDR;
		MCU_GPU__DATA = 0x01;
	}
	else {
		MCU_GPU__ADDR = MCU_CFG_GPU__DDR_FRAMEREGION_READ_START_ADDR;
		MCU_GPU__DATA = 0x00;
	}
	
	//close pure color mode to BMP display mode, if previous display is Pure-Color-Mode
	{
		MCU_GPU__ADDR = MCU_CFG_GPU__PURECOLOR_ADDR1;
		MCU_GPU__DATA = 0x0000;
	}
}


void pattern_h_grayscale_buf(UINT16 *ptr_i, UINT8 RGBValue, UINT16 bmp_width_single_or_dual) {
	UINT16 k;
	
	MCU_GPU__ADDR = MCU_CFG_GPU__DDRBUF_ADDR;
	
	for(k=0; k<256; k++) {
		if(*ptr_i < (bmp_width_single_or_dual>>2)) {
			MCU_GPU__DATAH = (UINT16)RGBValue; //(UINT16)R;
			MCU_GPU__DATA  = 0x0000; //((UINT16)G<<8) | (UINT16)B;
		}
		else if(*ptr_i < (bmp_width_single_or_dual>>1)) {
			MCU_GPU__DATAH = 0x0000; //(UINT16)R;
			MCU_GPU__DATA  = ((UINT16)RGBValue)<<8; //((UINT16)G<<8) | (UINT16)B;
		}
		else if(*ptr_i < ((bmp_width_single_or_dual>>2)*3)) {
			MCU_GPU__DATAH = 0x0000; //(UINT16)R;
			MCU_GPU__DATA  = ((UINT16)RGBValue); //((UINT16)G<<8) | (UINT16)B;
		}
		else {
			MCU_GPU__DATAH = (UINT16)RGBValue; //(UINT16)R;
			MCU_GPU__DATA  = (((UINT16)RGBValue<<8) | (UINT16)RGBValue); //((UINT16)G<<8) | (UINT16)B;
		}
		(*ptr_i)++;
		if((*ptr_i) == ptr_MIPI_TABLE[gMipiTableIndex]->HACT_WIDTH) //when dual-mipi, break if half filled
			break;
	}
}

void op_Pattern4ColorBarGrayScaleH(UINT8 InvertRGB, UINT8 GrayScaleNum) {
	UINT8 blk_num_in256Pixel_of_each_line;
	UINT8 ddr_current_display_region_addr;
	UINT16 Scale256Step; //eg: 1080*1920, then Scale256 of 1080(256*4 + 56) need 4 pixel each step, here step = 4;
	UINT16 Scale256StepPlus1;
	UINT8 Scale256Remainder; //eg: 1080*1920, then Scale256 of 1080(256*4 + 56) is 56 as remainder, here remainder = 56;
	UINT16 j;
	UINT16 i;
	UINT16 i_prev;
	UINT8 RGBValue;
	UINT16 line_num;
	UINT8 k;
	UINT8 num_in256pixel_eachline;
	UINT16 bmp_width_single_or_dual;
	UINT8 grayscale_num;
	UINT8 grayscale_value;
	
	//Cancel FIFO Channel of BMP display(FIFO-BUF-DDR), Here is MCU-BUF-DDR,
	MCU_GPU__ADDR = MCU_CFG_GPU__SDIP_BUFFER_CTRL_REG_ADDR;
	MCU_GPU__DATA = 0x0000; //bit[12], 1 mean select SDIP to DDR FIFO channel; 0 mean select SD-MCU-buffer;
	
	
	MCU_GPU__ADDR = MCU_CFG_GPU__DDR_FRAMEREGION_READ_START_ADDR;//read the current display region, [29:26] of DDR-BYTE-ADDRESS
	ddr_current_display_region_addr = MCU_GPU__DATA;
	
	
	blk_num_in256Pixel_of_each_line = ((ptr_MIPI_TABLE[gMipiTableIndex]->HACT_WIDTH - 1) >> 8) + 1;

	bmp_width_single_or_dual = (ptr_MIPI_TABLE[gMipiTableIndex]->DUAL_MIPI_LCD != 0) ? (ptr_MIPI_TABLE[gMipiTableIndex]->HACT_WIDTH<<1) : ptr_MIPI_TABLE[gMipiTableIndex]->HACT_WIDTH;
	
	
	grayscale_num = GrayScaleNum;
	if(grayscale_num == 0) //remove 0
		grayscale_num = 0xff;

	Scale256Step = ptr_MIPI_TABLE[gMipiTableIndex]->VACT_WIDTH / (((UINT16)grayscale_num) + 1); //divide 256
	Scale256Remainder = ptr_MIPI_TABLE[gMipiTableIndex]->VACT_WIDTH % (((UINT16)grayscale_num) + 1); //remainder
	
	Scale256StepPlus1 = Scale256Step + 1;
	i=0;
	
	for(num_in256pixel_eachline=0; num_in256pixel_eachline<blk_num_in256Pixel_of_each_line; ) {
		line_num = 0;
		i_prev = i;
		grayscale_value = grayscale_num;
		
		for(k=0; k<Scale256Remainder; k++) {
			i = i_prev;
			RGBValue = (UINT8)(((UINT16)grayscale_value) * 0x0ff / ((UINT16)grayscale_num)); //when 64 grayscale, then 53 --> 53*255/63
			if(InvertRGB != 0)
				RGBValue = ~RGBValue;
			pattern_h_grayscale_buf(&i, RGBValue, bmp_width_single_or_dual);
			for(j=line_num; j<(Scale256StepPlus1+line_num); j++) {
				pattern_grayscale_wr_ddr(j, ddr_current_display_region_addr, num_in256pixel_eachline);
			}
			grayscale_value--;
			line_num += Scale256StepPlus1;
		}
		
		while(line_num < ptr_MIPI_TABLE[gMipiTableIndex]->VACT_WIDTH) {
			i = i_prev;
			RGBValue = (UINT8)(((UINT16)grayscale_value) * 0x0ff / ((UINT16)grayscale_num)); //when 64 grayscale, then 53 --> 53*255/63
			if(InvertRGB != 0)
				RGBValue = ~RGBValue;
			pattern_h_grayscale_buf(&i, RGBValue, bmp_width_single_or_dual);
			for(j=line_num; j<(Scale256Step+line_num); j++) {
				pattern_grayscale_wr_ddr(j, ddr_current_display_region_addr, num_in256pixel_eachline);
			}
			grayscale_value--;
			line_num += Scale256Step;
		}
		
		num_in256pixel_eachline++;
		if(ptr_MIPI_TABLE[gMipiTableIndex]->DUAL_MIPI_LCD != 0) { //dual mipi, then blk_num_in256Pixel_of_each_line is just half
			if(num_in256pixel_eachline == blk_num_in256Pixel_of_each_line) {
				if(num_in256pixel_eachline > 4)
					break;
				else {
					num_in256pixel_eachline = 4;
					blk_num_in256Pixel_of_each_line += 4;
				}
			}
		}
	}
	
	//update the figure display region in DDR
	if(ddr_current_display_region_addr == 0) {
		MCU_GPU__ADDR = MCU_CFG_GPU__DDR_FRAMEREGION_READ_START_ADDR;
		MCU_GPU__DATA = 0x01;
	}
	else {
		MCU_GPU__ADDR = MCU_CFG_GPU__DDR_FRAMEREGION_READ_START_ADDR;
		MCU_GPU__DATA = 0x00;
	}
	
	//close pure color mode to BMP display mode, if previous display is Pure-Color-Mode
	{
		MCU_GPU__ADDR = MCU_CFG_GPU__PURECOLOR_ADDR1;
		MCU_GPU__DATA = 0x0000;
	}
}


void op_PatternFlickerColumnInversion(UINT8 R1, UINT8 G1, UINT8 B1, UINT8 R0, UINT8 G0, UINT8 B0) {
	UINT8 blk_num_in256Pixel_of_each_line;
	UINT8 ddr_current_display_region_addr;
	UINT16 i;
	
	//Cancel FIFO Channel of BMP display(FIFO-BUF-DDR), Here is MCU-BUF-DDR,
	MCU_GPU__ADDR = MCU_CFG_GPU__SDIP_BUFFER_CTRL_REG_ADDR;
	MCU_GPU__DATA = 0x0000; //bit[12], 1 mean select SDIP to DDR FIFO channel; 0 mean select SD-MCU-buffer;
	
	
	MCU_GPU__ADDR = MCU_CFG_GPU__DDR_FRAMEREGION_READ_START_ADDR;//read the current display region, [29:26] of DDR-BYTE-ADDRESS
	ddr_current_display_region_addr = MCU_GPU__DATA;
	
	
	blk_num_in256Pixel_of_each_line = ((ptr_MIPI_TABLE[gMipiTableIndex]->HACT_WIDTH - 1) >> 8) + 1; //dual mipi will be processed in pattern_WriteLineOneDot()

	pattern_WriteLineBuf256Pixel(R1, G1, B1, R0, G0, B0);
	for(i=0; i<ptr_MIPI_TABLE[gMipiTableIndex]->VACT_WIDTH; i++) {
		pattern_WriteLineOneDot(ddr_current_display_region_addr, i, blk_num_in256Pixel_of_each_line);
	}
	
	//update the figure display region in DDR
	if(ddr_current_display_region_addr == 0) {
		MCU_GPU__ADDR = MCU_CFG_GPU__DDR_FRAMEREGION_READ_START_ADDR;
		MCU_GPU__DATA = 0x01;
	}
	else {
		MCU_GPU__ADDR = MCU_CFG_GPU__DDR_FRAMEREGION_READ_START_ADDR;
		MCU_GPU__DATA = 0x00;
	}
	
	//close pure color mode to BMP display mode, if previous display is Pure-Color-Mode
	{
		MCU_GPU__ADDR = MCU_CFG_GPU__PURECOLOR_ADDR1;
		MCU_GPU__DATA = 0x0000;
	}
}

void op_PatternFlickerOneDot(UINT8 R1, UINT8 G1, UINT8 B1, UINT8 R0, UINT8 G0, UINT8 B0) {
	UINT8 blk_num_in256Pixel_of_each_line;
	UINT8 ddr_current_display_region_addr;
	UINT16 i;
	
	
	//Cancel FIFO Channel of BMP display(FIFO-BUF-DDR), Here is MCU-BUF-DDR,
	MCU_GPU__ADDR = MCU_CFG_GPU__SDIP_BUFFER_CTRL_REG_ADDR;
	MCU_GPU__DATA = 0x0000; //bit[12], 1 mean select SDIP to DDR FIFO channel; 0 mean select SD-MCU-buffer;
	
	
	MCU_GPU__ADDR = MCU_CFG_GPU__DDR_FRAMEREGION_READ_START_ADDR;//read the current display region, [29:26] of DDR-BYTE-ADDRESS
	ddr_current_display_region_addr = MCU_GPU__DATA;
	
	
	blk_num_in256Pixel_of_each_line = ((ptr_MIPI_TABLE[gMipiTableIndex]->HACT_WIDTH - 1) >> 8) + 1; //dual mipi will be processed in pattern_WriteLineOneDot()

	
	pattern_WriteLineBuf256Pixel(R1, G1, B1, R0, G0, B0);
	for(i=0; i<ptr_MIPI_TABLE[gMipiTableIndex]->VACT_WIDTH; i+=2) {
		pattern_WriteLineOneDot(ddr_current_display_region_addr, i, blk_num_in256Pixel_of_each_line);
	}
	
	pattern_WriteLineBuf256Pixel(R0, G0, B0, R1, G1, B1);
	for(i=1; i<ptr_MIPI_TABLE[gMipiTableIndex]->VACT_WIDTH; i+=2) {
		pattern_WriteLineOneDot(ddr_current_display_region_addr, i, blk_num_in256Pixel_of_each_line);
	}
	
	
	//update the figure display region in DDR
	if(ddr_current_display_region_addr == 0) {
		MCU_GPU__ADDR = MCU_CFG_GPU__DDR_FRAMEREGION_READ_START_ADDR;
		MCU_GPU__DATA = 0x01;
	}
	else {
		MCU_GPU__ADDR = MCU_CFG_GPU__DDR_FRAMEREGION_READ_START_ADDR;
		MCU_GPU__DATA = 0x00;
	}
	
	//close pure color mode to BMP display mode, if previous display is Pure-Color-Mode
	{
		MCU_GPU__ADDR = MCU_CFG_GPU__PURECOLOR_ADDR1;
		MCU_GPU__DATA = 0x0000;
	}
}

void op_PatternPureColorThroughDDR(UINT8 R, UINT8 G, UINT8 B) {
	UINT8 blk_num_in256Pixel_of_each_line;
	UINT8 ddr_current_display_region_addr;
	UINT16 i;
	
	//Cancel FIFO Channel of BMP display(FIFO-BUF-DDR), Here is MCU-BUF-DDR,
	MCU_GPU__ADDR = MCU_CFG_GPU__SDIP_BUFFER_CTRL_REG_ADDR;
	MCU_GPU__DATA = 0x0000; //bit[12], 1 mean select SDIP to DDR FIFO channel; 0 mean select SD-MCU-buffer;
	
	
	MCU_GPU__ADDR = MCU_CFG_GPU__DDR_FRAMEREGION_READ_START_ADDR;//read the current display region, [29:26] of DDR-BYTE-ADDRESS
	ddr_current_display_region_addr = MCU_GPU__DATA;
	
	
	blk_num_in256Pixel_of_each_line = ((ptr_MIPI_TABLE[gMipiTableIndex]->HACT_WIDTH - 1) >> 8) + 1; //dual mipi will be processed in pattern_WriteLineOneDot()

	pattern_WriteLineBuf256Pixel(R, G, B, R, G, B);
	for(i=0; i<ptr_MIPI_TABLE[gMipiTableIndex]->VACT_WIDTH; i++) {
		pattern_WriteLineOneDot(ddr_current_display_region_addr, i, blk_num_in256Pixel_of_each_line);
	}
	
	//update the figure display region in DDR
	if(ddr_current_display_region_addr == 0) {
		MCU_GPU__ADDR = MCU_CFG_GPU__DDR_FRAMEREGION_READ_START_ADDR;
		MCU_GPU__DATA = 0x01;
	}
	else {
		MCU_GPU__ADDR = MCU_CFG_GPU__DDR_FRAMEREGION_READ_START_ADDR;
		MCU_GPU__DATA = 0x00;
	}
	
	//close pure color mode to BMP display mode, if previous display is Pure-Color-Mode
	{
		MCU_GPU__ADDR = MCU_CFG_GPU__PURECOLOR_ADDR1;
		MCU_GPU__DATA = 0x0000;
	}
}

void op_Pattern8ColorBarV_BBRGWCYM(void) {
	UINT8 blk_num_in256Pixel_of_each_line;
	UINT8 ddr_current_display_region_addr;
	UINT16 ColorBar8Step; //eg: 1080*1920, then ColorBar8 of 1920(8*240) need 240 pixel each step, here step = 240;
	UINT16 i;
	UINT16 line_num;
	UINT8 k;
	
	
	//Cancel FIFO Channel of BMP display(FIFO-BUF-DDR), Here is MCU-BUF-DDR,
	MCU_GPU__ADDR = MCU_CFG_GPU__SDIP_BUFFER_CTRL_REG_ADDR;
	MCU_GPU__DATA = 0x0000; //bit[12], 1 mean select SDIP to DDR FIFO channel; 0 mean select SD-MCU-buffer;
	
	
	MCU_GPU__ADDR = MCU_CFG_GPU__DDR_FRAMEREGION_READ_START_ADDR;//read the current display region, [29:26] of DDR-BYTE-ADDRESS
	ddr_current_display_region_addr = MCU_GPU__DATA;
	
	
	blk_num_in256Pixel_of_each_line = ((ptr_MIPI_TABLE[gMipiTableIndex]->HACT_WIDTH - 1) >> 8) + 1; //dual mipi will be processed in pattern_WriteLineOneDot()
	
	ColorBar8Step = ptr_MIPI_TABLE[gMipiTableIndex]->VACT_WIDTH >> 3; //divide 8
	
	k = 0;
	line_num = 0;
	while(line_num < ptr_MIPI_TABLE[gMipiTableIndex]->VACT_WIDTH) {
		if(k == 0)
			pattern_WriteLineBuf256Pixel(0x00, 0x00, 0x00, 0x00, 0x00, 0x00); //Black
		else if(k == 1)
			pattern_WriteLineBuf256Pixel(0x00, 0x00, 0xff, 0x00, 0x00, 0xff); //Blue
		else if(k == 2)
			pattern_WriteLineBuf256Pixel(0xff, 0x00, 0x00, 0xff, 0x00, 0x00); //Red
		else if(k == 3)
			pattern_WriteLineBuf256Pixel(0x00, 0xff, 0x00, 0x00, 0xff, 0x00); //Green
		else if(k == 4)
			pattern_WriteLineBuf256Pixel(0xff, 0xff, 0xff, 0xff, 0xff, 0xff); //White
		else if(k == 5)
			pattern_WriteLineBuf256Pixel(0x00, 0xff, 0xff, 0x00, 0xff, 0xff); //C
		else if(k == 6)
			pattern_WriteLineBuf256Pixel(0xff, 0xff, 0x00, 0xff, 0xff, 0x00); //Yellow
		else
			pattern_WriteLineBuf256Pixel(0xff, 0x00, 0xff, 0xff, 0x00, 0xff); //M
		
		for(i=line_num; i<(ColorBar8Step+line_num); i++) {
			pattern_WriteLineOneDot(ddr_current_display_region_addr, i, blk_num_in256Pixel_of_each_line);
		}
		line_num += ColorBar8Step;
		k++;
	}
	
	//update the figure display region in DDR
	if(ddr_current_display_region_addr == 0) {
		MCU_GPU__ADDR = MCU_CFG_GPU__DDR_FRAMEREGION_READ_START_ADDR;
		MCU_GPU__DATA = 0x01;
	}
	else {
		MCU_GPU__ADDR = MCU_CFG_GPU__DDR_FRAMEREGION_READ_START_ADDR;
		MCU_GPU__DATA = 0x00;
	}
	
	//close pure color mode to BMP display mode, if previous display is Pure-Color-Mode
	{
		MCU_GPU__ADDR = MCU_CFG_GPU__PURECOLOR_ADDR1;
		MCU_GPU__DATA = 0x0000;
	}
}
void pattern_h_8colorbar_buf(UINT16 *ptr_i, UINT16 ColorBar8Step) {
	UINT16 k;
	
	MCU_GPU__ADDR = MCU_CFG_GPU__DDRBUF_ADDR;
	
	for(k=0; k<256; k++) {
		if(*ptr_i < ColorBar8Step) {
			MCU_GPU__DATAH = 0x0000; //(UINT16)R;
			MCU_GPU__DATA  = 0x0000; //((UINT16)G<<8) | (UINT16)B;
		}
		else if(*ptr_i < (ColorBar8Step << 1)) {
			MCU_GPU__DATAH = 0x0000; //(UINT16)R;
			MCU_GPU__DATA  = 0x00ff; //((UINT16)G<<8) | (UINT16)B;
		}
		else if(*ptr_i < (ColorBar8Step * 3)) {
			MCU_GPU__DATAH = 0x00ff; //(UINT16)R;
			MCU_GPU__DATA  = 0x0000; //((UINT16)G<<8) | (UINT16)B;
		}
		else if(*ptr_i < (ColorBar8Step << 2)) {
			MCU_GPU__DATAH = 0x0000; //(UINT16)R;
			MCU_GPU__DATA  = 0xff00; //((UINT16)G<<8) | (UINT16)B;
		}
		else if(*ptr_i < (ColorBar8Step * 5)) {
			MCU_GPU__DATAH = 0x00ff; //(UINT16)R;
			MCU_GPU__DATA  = 0xffff; //((UINT16)G<<8) | (UINT16)B;
		}
		else if(*ptr_i < (ColorBar8Step * 6)) {
			MCU_GPU__DATAH = 0x0000; //(UINT16)R;
			MCU_GPU__DATA  = 0xffff; //((UINT16)G<<8) | (UINT16)B;
		}
		else if(*ptr_i < (ColorBar8Step * 7)) {
			MCU_GPU__DATAH = 0x00ff; //(UINT16)R;
			MCU_GPU__DATA  = 0xff00; //((UINT16)G<<8) | (UINT16)B;
		}
		else {
			MCU_GPU__DATAH = 0x00ff; //(UINT16)R;
			MCU_GPU__DATA  = 0x00ff; //((UINT16)G<<8) | (UINT16)B;
		}
		(*ptr_i)++;
		if((*ptr_i) == ptr_MIPI_TABLE[gMipiTableIndex]->HACT_WIDTH) //when dual-mipi, break if half filled
			break;
	}
}
void op_Pattern8ColorBarH_BBRGWCYM(void) {
	UINT8 blk_num_in256Pixel_of_each_line;
	UINT8 ddr_current_display_region_addr;
	UINT16 ColorBar8Step; //eg: 1080*1920, then ColorBar8Step of 1080(8*135) need 135 pixel each step, here step = 135;
	UINT16 j;
	UINT16 i;
	UINT8 num_in256pixel_eachline;
	
	//Cancel FIFO Channel of BMP display(FIFO-BUF-DDR), Here is MCU-BUF-DDR,
	MCU_GPU__ADDR = MCU_CFG_GPU__SDIP_BUFFER_CTRL_REG_ADDR;
	MCU_GPU__DATA = 0x0000; //bit[12], 1 mean select SDIP to DDR FIFO channel; 0 mean select SD-MCU-buffer;
	
	
	MCU_GPU__ADDR = MCU_CFG_GPU__DDR_FRAMEREGION_READ_START_ADDR;//read the current display region, [29:26] of DDR-BYTE-ADDRESS
	ddr_current_display_region_addr = MCU_GPU__DATA;
	
	
	blk_num_in256Pixel_of_each_line = ((ptr_MIPI_TABLE[gMipiTableIndex]->HACT_WIDTH - 1) >> 8) + 1; //dual mipi will be processed in pattern_WriteLineOneDot()
	
	ColorBar8Step = (ptr_MIPI_TABLE[gMipiTableIndex]->DUAL_MIPI_LCD != 0) ? (ptr_MIPI_TABLE[gMipiTableIndex]->HACT_WIDTH >> 2) : (ptr_MIPI_TABLE[gMipiTableIndex]->HACT_WIDTH >> 3);
	
	i=0;
	for(num_in256pixel_eachline=0; num_in256pixel_eachline<blk_num_in256Pixel_of_each_line; ) {
		pattern_h_8colorbar_buf(&i, ColorBar8Step);
		for(j=0; j<ptr_MIPI_TABLE[gMipiTableIndex]->VACT_WIDTH; j++) {
			pattern_grayscale_wr_ddr(j, ddr_current_display_region_addr, num_in256pixel_eachline);
		}
		
		num_in256pixel_eachline++;
		if(ptr_MIPI_TABLE[gMipiTableIndex]->DUAL_MIPI_LCD != 0) { //dual mipi, then blk_num_in256Pixel_of_each_line is just half
			if(num_in256pixel_eachline == blk_num_in256Pixel_of_each_line) {
				if(num_in256pixel_eachline > 4)
					break;
				else {
					num_in256pixel_eachline = 4;
					blk_num_in256Pixel_of_each_line += 4;
				}
			}
		}
	}

	//update the figure display region in DDR
	if(ddr_current_display_region_addr == 0) {
		MCU_GPU__ADDR = MCU_CFG_GPU__DDR_FRAMEREGION_READ_START_ADDR;
		MCU_GPU__DATA = 0x01;
	}
	else {
		MCU_GPU__ADDR = MCU_CFG_GPU__DDR_FRAMEREGION_READ_START_ADDR;
		MCU_GPU__DATA = 0x00;
	}
	
	//close pure color mode to BMP display mode, if previous display is Pure-Color-Mode
	{
		MCU_GPU__ADDR = MCU_CFG_GPU__PURECOLOR_ADDR1;
		MCU_GPU__DATA = 0x0000;
	}
}

void op_PatternCrosstalk_BlackWhite(UINT8 BlackOrNot) { //1: black, 0: white
	UINT8 blk_num_in256Pixel_of_each_line;
	UINT8 ddr_current_display_region_addr;
	UINT16 j;
	UINT16 i;
	UINT8 num_in256pixel_eachline;
	UINT16 bmp_width_single_or_dual;
	UINT8 RGBValue;
	UINT16 RegionL, RegionH;
	
	//Cancel FIFO Channel of BMP display(FIFO-BUF-DDR), Here is MCU-BUF-DDR,
	MCU_GPU__ADDR = MCU_CFG_GPU__SDIP_BUFFER_CTRL_REG_ADDR;
	MCU_GPU__DATA = 0x0000; //bit[12], 1 mean select SDIP to DDR FIFO channel; 0 mean select SD-MCU-buffer;
	
	
	MCU_GPU__ADDR = MCU_CFG_GPU__DDR_FRAMEREGION_READ_START_ADDR;//read the current display region, [29:26] of DDR-BYTE-ADDRESS
	ddr_current_display_region_addr = MCU_GPU__DATA;
	
	
	blk_num_in256Pixel_of_each_line = ((ptr_MIPI_TABLE[gMipiTableIndex]->HACT_WIDTH - 1) >> 8) + 1; //dual mipi will be processed in pattern_WriteLineOneDot()
	
	bmp_width_single_or_dual = (ptr_MIPI_TABLE[gMipiTableIndex]->DUAL_MIPI_LCD != 0) ? (ptr_MIPI_TABLE[gMipiTableIndex]->HACT_WIDTH<<1) : ptr_MIPI_TABLE[gMipiTableIndex]->HACT_WIDTH;
	RGBValue = BlackOrNot ? 0x00 : 0xff;
	RegionL = bmp_width_single_or_dual >> 2;
	RegionH = (bmp_width_single_or_dual >> 2) * 3;
	
	pattern_WriteLineBuf256Pixel(0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f);
	for(j=0; j<(ptr_MIPI_TABLE[gMipiTableIndex]->VACT_WIDTH >> 2); j++) {
		pattern_WriteLineOneDot(ddr_current_display_region_addr, j, blk_num_in256Pixel_of_each_line);
	}
	for(j=((ptr_MIPI_TABLE[gMipiTableIndex]->VACT_WIDTH >> 2)) * 3; j<ptr_MIPI_TABLE[gMipiTableIndex]->VACT_WIDTH; j++) {
		pattern_WriteLineOneDot(ddr_current_display_region_addr, j, blk_num_in256Pixel_of_each_line);
	}
	
	i=0;
	for(num_in256pixel_eachline=0; num_in256pixel_eachline<blk_num_in256Pixel_of_each_line; ) {
		pattern_crosstalk_buf(&i, RegionL, RegionH, RGBValue, RGBValue, RGBValue, 0x7f, 0x7f, 0x7f);
		for(j=(ptr_MIPI_TABLE[gMipiTableIndex]->VACT_WIDTH >> 2); j<(((ptr_MIPI_TABLE[gMipiTableIndex]->VACT_WIDTH >> 2)) * 3); j++) {
			pattern_grayscale_wr_ddr(j, ddr_current_display_region_addr, num_in256pixel_eachline);
		}
		
		num_in256pixel_eachline++;
		if(ptr_MIPI_TABLE[gMipiTableIndex]->DUAL_MIPI_LCD != 0) { //dual mipi, then blk_num_in256Pixel_of_each_line is just half
			if(num_in256pixel_eachline == blk_num_in256Pixel_of_each_line) {
				if(num_in256pixel_eachline > 4)
					break;
				else {
					num_in256pixel_eachline = 4;
					blk_num_in256Pixel_of_each_line += 4;
				}
			}
		}
	}
	
	//update the figure display region in DDR
	if(ddr_current_display_region_addr == 0) {
		MCU_GPU__ADDR = MCU_CFG_GPU__DDR_FRAMEREGION_READ_START_ADDR;
		MCU_GPU__DATA = 0x01;
	}
	else {
		MCU_GPU__ADDR = MCU_CFG_GPU__DDR_FRAMEREGION_READ_START_ADDR;
		MCU_GPU__DATA = 0x00;
	}
	
	//close pure color mode to BMP display mode, if previous display is Pure-Color-Mode
	{
		MCU_GPU__ADDR = MCU_CFG_GPU__PURECOLOR_ADDR1;
		MCU_GPU__DATA = 0x0000;
	}
}

void pattern_checker_buf(UINT16 *ptr_i, UINT16 *checker_cnt, UINT16 checker_step, UINT16 checker_step_plus1, UINT16 checker_remainder, UINT8 R0, UINT8 G0, UINT8 B0, UINT8 R1, UINT8 G1, UINT8 B1) {
	UINT16 k;
	
	
	MCU_GPU__ADDR = MCU_CFG_GPU__DDRBUF_ADDR;
	
	
	
	for(k=0; k<256; k++) {
		if(((*checker_cnt) & 0x01) == 0) { //black or white
			MCU_GPU__DATAH = (UINT16)R0;
			MCU_GPU__DATA  = ((UINT16)G0<<8) | (UINT16)B0;
		}
		else {
			MCU_GPU__DATAH = (UINT16)R1;
			MCU_GPU__DATA  = ((UINT16)G1<<8) | (UINT16)B1;
		}

		(*ptr_i)++;
		if((*checker_cnt) < checker_remainder) {
			if(((*ptr_i) % checker_step_plus1) == 0)
				(*checker_cnt)++;
		}
		else {
			if(((*ptr_i - checker_remainder) % checker_step) == 0)
				(*checker_cnt)++;
		}
		if((*ptr_i) == ptr_MIPI_TABLE[gMipiTableIndex]->HACT_WIDTH) //when dual-mipi, break if half filled
			break;
	}
}
void op_PatternChecker_BlackWhite(UINT8 BlackOrNot, UINT8 CheckerHNum, UINT8 CheckerVNum) { //1: black, 0: white
	UINT8 blk_num_in256Pixel_of_each_line;
	UINT8 ddr_current_display_region_addr;
	UINT16 j,k;
	UINT16 i;
	UINT16 i_prev;
	UINT8 num_in256pixel_eachline;
	UINT16 bmp_width_single_or_dual;
	UINT8 RGBValue0;
	UINT8 RGBValue1;
	UINT16 CheckerHStep;
	UINT16 CheckerHStepPlus1;
	UINT16 CheckerHRemainder;
	UINT16 CheckerVStep;
	UINT16 CheckerVStepPlus1;
	UINT16 CheckerVRemainder;
	UINT16 CheckerHCnt;
	UINT16 CheckerHCnt_prev;
	UINT16 line_num;
	UINT8 checker_h_num, checker_v_num;
	
	//Cancel FIFO Channel of BMP display(FIFO-BUF-DDR), Here is MCU-BUF-DDR,
	MCU_GPU__ADDR = MCU_CFG_GPU__SDIP_BUFFER_CTRL_REG_ADDR;
	MCU_GPU__DATA = 0x0000; //bit[12], 1 mean select SDIP to DDR FIFO channel; 0 mean select SD-MCU-buffer;
	
	
	MCU_GPU__ADDR = MCU_CFG_GPU__DDR_FRAMEREGION_READ_START_ADDR;//read the current display region, [29:26] of DDR-BYTE-ADDRESS
	ddr_current_display_region_addr = MCU_GPU__DATA;
	
	
	blk_num_in256Pixel_of_each_line = ((ptr_MIPI_TABLE[gMipiTableIndex]->HACT_WIDTH - 1) >> 8) + 1; //dual mipi will be processed in pattern_WriteLineOneDot()
	
	bmp_width_single_or_dual = (ptr_MIPI_TABLE[gMipiTableIndex]->DUAL_MIPI_LCD != 0) ? (ptr_MIPI_TABLE[gMipiTableIndex]->HACT_WIDTH<<1) : ptr_MIPI_TABLE[gMipiTableIndex]->HACT_WIDTH;
	
	checker_h_num = CheckerHNum;
	CheckerHStep = bmp_width_single_or_dual / ((UINT16)checker_h_num);
	CheckerHRemainder = bmp_width_single_or_dual % ((UINT16)checker_h_num);
	CheckerHStepPlus1 = CheckerHStep + 1;
	
	checker_v_num = CheckerVNum;
	CheckerVStep = (ptr_MIPI_TABLE[gMipiTableIndex]->VACT_WIDTH) / ((UINT16)checker_v_num);
	CheckerVRemainder = (ptr_MIPI_TABLE[gMipiTableIndex]->VACT_WIDTH) % ((UINT16)checker_v_num);
	CheckerVStepPlus1 = CheckerVStep + 1;
	
	RGBValue0 = BlackOrNot ? 0x00 : 0xff;
	RGBValue1 = BlackOrNot ? 0xff : 0x00;
	
	i = 0;
	CheckerHCnt = 0;
	for(num_in256pixel_eachline=0; num_in256pixel_eachline<blk_num_in256Pixel_of_each_line; ) {
		//first even lines of checker
		i_prev = i;
		CheckerHCnt_prev = CheckerHCnt;
		pattern_checker_buf(&i, &CheckerHCnt, CheckerHStep, CheckerHStepPlus1, CheckerHRemainder, RGBValue0, RGBValue0, RGBValue0, RGBValue1, RGBValue1, RGBValue1);
		
		line_num = 0;
		k = CheckerVRemainder;
		while(k > 0) {
			for(j=line_num; j<(line_num + CheckerVStepPlus1); j++) {
				pattern_grayscale_wr_ddr(j, ddr_current_display_region_addr, num_in256pixel_eachline);
				//pattern_grayscale_wr_ddr(j, 1, num_in256pixel_eachline);
			}
			line_num += CheckerVStepPlus1;
			k--;
			if(k != 0) {
				line_num += CheckerVStepPlus1;
				k--;
			}
			else {
				line_num += CheckerVStep;
			}
		}
		while(line_num < ptr_MIPI_TABLE[gMipiTableIndex]->VACT_WIDTH) {
			for(j=line_num; j<(line_num + CheckerVStep); j++) {
				pattern_grayscale_wr_ddr(j, ddr_current_display_region_addr, num_in256pixel_eachline);
				//pattern_grayscale_wr_ddr(j, 1, num_in256pixel_eachline);
			}
			line_num += (CheckerVStep << 1);
		}
		
		//second odd lines of checker
		i = i_prev;
		CheckerHCnt = CheckerHCnt_prev;
		pattern_checker_buf(&i, &CheckerHCnt, CheckerHStep, CheckerHStepPlus1, CheckerHRemainder, RGBValue1, RGBValue1, RGBValue1, RGBValue0, RGBValue0, RGBValue0);
		
		k = CheckerVRemainder;
		if(k != 0) {
			line_num = CheckerVStepPlus1;
			k--;
		}
		else
			line_num = CheckerVStep;
		while(k > 0) {
			for(j=line_num; j<(line_num + CheckerVStepPlus1); j++) {
				pattern_grayscale_wr_ddr(j, ddr_current_display_region_addr, num_in256pixel_eachline);
				//pattern_grayscale_wr_ddr(j, 1, num_in256pixel_eachline);
			}
			line_num += CheckerVStepPlus1;
			k--;
			if(k != 0) {
				line_num += CheckerVStepPlus1;
				k--;
			}
			else {
				line_num += CheckerVStep;
			}
		}
		while(line_num < ptr_MIPI_TABLE[gMipiTableIndex]->VACT_WIDTH) {
			for(j=line_num; j<(line_num + CheckerVStep); j++) {
				pattern_grayscale_wr_ddr(j, ddr_current_display_region_addr, num_in256pixel_eachline);
				//pattern_grayscale_wr_ddr(j, 1, num_in256pixel_eachline);
			}
			line_num += (CheckerVStep << 1);
		}
		
		num_in256pixel_eachline++;
		if(ptr_MIPI_TABLE[gMipiTableIndex]->DUAL_MIPI_LCD != 0) { //dual mipi, then blk_num_in256Pixel_of_each_line is just half
			if(num_in256pixel_eachline == blk_num_in256Pixel_of_each_line) {
				if(num_in256pixel_eachline > 4)
					break;
				else {
					num_in256pixel_eachline = 4;
					blk_num_in256Pixel_of_each_line += 4;
				}
			}
		}
	}
	
	//update the figure display region in DDR
	if(ddr_current_display_region_addr == 0) {
		MCU_GPU__ADDR = MCU_CFG_GPU__DDR_FRAMEREGION_READ_START_ADDR;
		MCU_GPU__DATA = 0x01;
	}
	else {
		MCU_GPU__ADDR = MCU_CFG_GPU__DDR_FRAMEREGION_READ_START_ADDR;
		MCU_GPU__DATA = 0x00;
	}
	
	//close pure color mode to BMP display mode, if previous display is Pure-Color-Mode
	{
		MCU_GPU__ADDR = MCU_CFG_GPU__PURECOLOR_ADDR1;
		MCU_GPU__DATA = 0x0000;
	}
}

void op_PatternColorOutline(UINT8 par_R, UINT8 par_G, UINT8 par_B) {
	UINT8 blk_num_in256Pixel_of_each_line;
	UINT8 ddr_current_display_region_addr;
	UINT16 j;
	UINT16 i;
	UINT8 num_in256pixel_eachline;
	UINT16 bmp_width_single_or_dual;
	UINT8 Outline_R, Outline_G, Outline_B;
	UINT16 RegionL, RegionH;
	
	
	//Cancel FIFO Channel of BMP display(FIFO-BUF-DDR), Here is MCU-BUF-DDR,
	MCU_GPU__ADDR = MCU_CFG_GPU__SDIP_BUFFER_CTRL_REG_ADDR;
	MCU_GPU__DATA = 0x0000; //bit[12], 1 mean select SDIP to DDR FIFO channel; 0 mean select SD-MCU-buffer;
	
	
	MCU_GPU__ADDR = MCU_CFG_GPU__DDR_FRAMEREGION_READ_START_ADDR;//read the current display region, [29:26] of DDR-BYTE-ADDRESS
	ddr_current_display_region_addr = MCU_GPU__DATA;
	
	blk_num_in256Pixel_of_each_line = ((ptr_MIPI_TABLE[gMipiTableIndex]->HACT_WIDTH - 1) >> 8) + 1;
	bmp_width_single_or_dual = (ptr_MIPI_TABLE[gMipiTableIndex]->DUAL_MIPI_LCD != 0) ? (ptr_MIPI_TABLE[gMipiTableIndex]->HACT_WIDTH<<1) : ptr_MIPI_TABLE[gMipiTableIndex]->HACT_WIDTH;

	RegionL = 1;
	RegionH = bmp_width_single_or_dual - 1;
	{
		Outline_R = par_R;
		Outline_G = par_G;
		Outline_B = par_B;
	}
	
	pattern_WriteLineBuf256Pixel(Outline_R, Outline_G, Outline_B, Outline_R, Outline_G, Outline_B);
	pattern_WriteLineOneDot(ddr_current_display_region_addr, 0, blk_num_in256Pixel_of_each_line);
	pattern_WriteLineOneDot(ddr_current_display_region_addr, (ptr_MIPI_TABLE[gMipiTableIndex]->VACT_WIDTH - 1), blk_num_in256Pixel_of_each_line);
	
	i=0;
	for(num_in256pixel_eachline=0; num_in256pixel_eachline<blk_num_in256Pixel_of_each_line; ) {
		pattern_crosstalk_buf(&i, RegionL, RegionH, 0x00, 0x00, 0x00, Outline_R, Outline_G, Outline_B);
		for(j=1; j<(ptr_MIPI_TABLE[gMipiTableIndex]->VACT_WIDTH - 1); j++) {
			pattern_grayscale_wr_ddr(j, ddr_current_display_region_addr, num_in256pixel_eachline);
		}
		
		num_in256pixel_eachline++;
		if(ptr_MIPI_TABLE[gMipiTableIndex]->DUAL_MIPI_LCD != 0) { //dual mipi, then blk_num_in256Pixel_of_each_line is just half
			if(num_in256pixel_eachline == blk_num_in256Pixel_of_each_line) {
				if(num_in256pixel_eachline > 8)
					break;
				else {
					num_in256pixel_eachline = 8;
					blk_num_in256Pixel_of_each_line += 8;
				}
			}
		}
	}
	
	//update the figure display region in DDR
	if(ddr_current_display_region_addr == 0) {
		MCU_GPU__ADDR = MCU_CFG_GPU__DDR_FRAMEREGION_READ_START_ADDR;
		MCU_GPU__DATA = 0x01;
	}
	else {
		MCU_GPU__ADDR = MCU_CFG_GPU__DDR_FRAMEREGION_READ_START_ADDR;
		MCU_GPU__DATA = 0x00;
	}
	
	//close pure color mode to BMP display mode, if previous display is Pure-Color-Mode
	{
		MCU_GPU__ADDR = MCU_CFG_GPU__PURECOLOR_ADDR1;
		MCU_GPU__DATA = 0x0000;
	}
}


//---画点
void pattern_DrawPixelDot_Color(UINT8 R, UINT8 G, UINT8 B) {//写入Buffer, 把这里单独列出来是因为画线时只需要写一次Buffer表示线的颜色即可, 可以节省画线的时间
	UINT8 i;
	
	MCU_GPU__ADDR = MCU_CFG_GPU__DDRBUF_ADDR;
	for(i=0; i<4; i++) { //依然要写128Bit(4*32bit)
		MCU_GPU__DATAH = (UINT16)R;
		MCU_GPU__DATA  = ((UINT16)G<<8) | (UINT16)B;
	}
}
void pattern_DrawPixelDot_ToDDR(UINT16 ddr_current_display_region_addr, UINT16 RowAddr, UINT16 ColumnAddr) { //告诉GPU执行搬运操作, 将Buffer中的数据搬运到DDR相应区域
	UINT16 value;
	UINT16 res;
	
	if(ddr_current_display_region_addr == 0) { //process with ddr-byte-addr[26], 写到当前显示的Frame区域
		value = (RowAddr>>2) & 0x03ff;
	}
	else {
		value = (RowAddr>>2) | 0x0400;
	}
	MCU_GPU__ADDR = MCU_CFG_GPU__DDR_ACCESS_BYTE_ADDR1;
	MCU_GPU__DATA = value | 0x8000; //最高1bit为1表示按pixel(32bit)去写DDR(通过MASK来实现), 每次传输完(bit[5]:start_enable由1变0后)会自动清零
	value = RowAddr<<14;
	MCU_GPU__ADDR = MCU_CFG_GPU__DDR_ACCESS_BYTE_ADDR0;
	MCU_GPU__DATA = value | (ColumnAddr<<2); //[13:0]-->[13:2](Column,4095Max) [1:0](Pixel,32bit), GPU会自动根据[3:2]做mask处理

	value = 0; //Each Pixel=32bit, 128bit=4Pixel
	MCU_GPU__ADDR = MCU_CFG_GPU__DDR_ACCESS_CTRL_REG_ADDR;
	MCU_GPU__DATA = (value&0x3f) | 0x0040; //0x007f;//start_enable:1, burst length:63, that is 64 of 128bits
		
	//-----wait transfer done
	res = 0x40;
	while(res) {
		res = MCU_GPU__DATA;
		res = res & 0x40;
	}
}
void TestDrawPixelDotLine(void) {
	UINT16 ddr_current_display_region_addr;
	UINT16 i,j;
	
	//Cancel FIFO Channel of BMP display(FIFO-BUF-DDR), Here is MCU-BUF-DDR,
	MCU_GPU__ADDR = MCU_CFG_GPU__SDIP_BUFFER_CTRL_REG_ADDR;
	MCU_GPU__DATA = 0x0000; //bit[12], 1 mean select SDIP to DDR FIFO channel; 0 mean select SD-MCU-buffer;
	
	
	MCU_GPU__ADDR = MCU_CFG_GPU__DDR_FRAMEREGION_READ_START_ADDR;//read the current display region, [29:26] of DDR-BYTE-ADDRESS
	ddr_current_display_region_addr = MCU_GPU__DATA;
	
	pattern_DrawPixelDot_Color(0xAF, 0x7F, 0x3F);
	
	for(i=0; i<1920; i++) {
		j = (i*1080 + 960)/1920;
		pattern_DrawPixelDot_ToDDR(ddr_current_display_region_addr, i, j);
	}
	
	
	pattern_DrawPixelDot_Color(0x3F, 0xAF, 0x7F);
	for(i=0; i<1920; i++) {
		j = 1080 - (i*1080 + 960)/1920;
		pattern_DrawPixelDot_ToDDR(ddr_current_display_region_addr, i, j);
	}
}
void TestCommandModeDrawRectangleFromDDR(void) {
	UINT16 ddr_current_display_region_addr;
	UINT16 i,j;
	UINT16 RowNum,RowNum1;
	UINT32 TmpData;
	UINT32 TmpD[2];
	
	MCU_GPU__ADDR = MCU_CFG_GPU__DDR_FRAMEREGION_READ_START_ADDR;//read the current display region, [29:26] of DDR-BYTE-ADDRESS
	ddr_current_display_region_addr = MCU_GPU__DATA;
	
	//最开始DCS命令直接发送128x128大小的矩形框, 然后估计是2828芯片缓冲buffer不够出现了溢出还是别的原因(因为用逻辑分析仪抓取核心板出去的RGB数据信号是正确的), 最终显示到屏端的数据有丢失或异常;
	//所以后面改用2行一次, 128大小就发64次DCS命令(2A+2B+2C), 然后测试发现是OK的;
	for(RowNum=0; RowNum<128; RowNum+=2) { //每次写1行这边测试有问题, 所以就按写2行来测试的
		RowNum1 = RowNum + 1;
		{
			//---------------------------------------------------
			TmpData = 0x0001;
			CommandMode_Write( 0xC0, &TmpData, 1);

			//2A与2B, Restart from (0,0) "origin of coordinates"
			//2A命令, set column address
			TmpData = 0x0743;
			CommandMode_Write( 0xB7, &TmpData, 1);
			TmpData = 0x0005;
			CommandMode_Write( 0xBC, &TmpData, 1);
			TmpData = 0x0000;
			CommandMode_Write( 0xBD, &TmpData, 1);
			TmpD[0] = 0x00002A;
			TmpD[1] = 0x007F00;
			CommandMode_Write( 0xBF, TmpD, 2);
			
			//2B命令, set page address
			TmpData = 0x0743;
			CommandMode_Write( 0xB7, &TmpData, 1);
			TmpData = 0x0005;
			CommandMode_Write( 0xBC, &TmpData, 1);
			TmpData = 0x0000;
			CommandMode_Write( 0xBD, &TmpData, 1);
			TmpD[0] = 0x00002B | (RowNum<<16);
			TmpD[1] = (RowNum1<<8)&0x00FF00;
			CommandMode_Write( 0xBF, TmpD, 2);
			
			
			//声明接下来GPU要写的数据块的大小
			TmpData = 0x0743;
			CommandMode_Write( 0xB7, &TmpData, 1);
			TmpData = 0x0300; //128 * 3 * 2; //each pixel 3 bytes
			CommandMode_Write( 0xBC, &TmpData, 1);
			TmpData = 0x0000; //0x0000;
			CommandMode_Write( 0xBD, &TmpData, 1);
			CommandMode_Write( 0xBF, &TmpData, 0);
		}
		
		CommandMode_GPURectangleReadOutFromDDR(0x2C, ddr_current_display_region_addr, RowNum, 2, 0, 128);
	}
//	CommandMode_GPURectanglePureColor_FastWrite(0x00F07030, 256*256, 0x2C);
	
	
	
//	for(j=0; j<1080; j+=4) {
//		i = (j*1920)/1080;
//		RowNum = (j+4)*1920/1080 - i;
//		if(i+RowNum > 1919)
//			RowNum = 1919 - i + 1;
//		
//		{
//			//---------------------------------------------------
////			TmpData = 0x0001;
////			CommandMode_Write( 0xC0, &TmpData, 1);

//			//2A与2B, Restart from (0,0) "origin of coordinates"
//			//2A命令, set column address
//			TmpData = 0x0743;
//			CommandMode_Write( 0xB7, &TmpData, 1);
//			TmpData = 0x0005;
//			CommandMode_Write( 0xBC, &TmpData, 1);
//			TmpData = 0x0000;
//			CommandMode_Write( 0xBD, &TmpData, 1);
//			TmpData = (UINT32)j;
//			TmpD[0] = 0x00002A | ((TmpData) & 0x00FF00) | ((TmpData << 16) & 0xFF0000);
//			TmpData = (UINT32)(j + 3);
//			TmpD[1] = ((TmpData >> 8) & 0x0000FF) | ((TmpData << 8) & 0x00FF00);
//			CommandMode_Write( 0xBF, TmpD, 2);
//			
//			//2B命令, set page address
//			TmpData = 0x0743;
//			CommandMode_Write( 0xB7, &TmpData, 1);
//			TmpData = 0x0005;
//			CommandMode_Write( 0xBC, &TmpData, 1);
//			TmpData = 0x0000;
//			CommandMode_Write( 0xBD, &TmpData, 1);
//			TmpData = (UINT32)i;
//			TmpD[0] = 0x00002B | ((TmpData) & 0x00FF00) | ((TmpData << 16) & 0xFF0000);
//			TmpData = (UINT32)(i + RowNum - 1);
//			TmpD[1] = ((TmpData >> 8) & 0x0000FF) | ((TmpData << 8) & 0x00FF00);
//			CommandMode_Write( 0xBF, TmpD, 2);
//			
//			
//			//声明接下来GPU要写的数据块的大小
//			TmpData = 0x0743;
//			CommandMode_Write( 0xB7, &TmpData, 1);
//			TmpData = RowNum * 4 * 3; //each pixel 3 bytes
//			CommandMode_Write( 0xBC, &TmpData, 1);
//			TmpData = 0x0000;
//			CommandMode_Write( 0xBD, &TmpData, 1);
//			CommandMode_Write( 0xBF, &TmpData, 0);
//		}
//		
//		CommandMode_GPURectangleReadOutFromDDR(0x2C, ddr_current_display_region_addr, i, RowNum, j, 4);
//	}
	
//	for(j=0; j<1080; j+=4) {
//		i = 1920 - (j+4)*1920/1080;
//		RowNum = 1920 - j*1920/1080 - i;
//		if(i+RowNum > 1919)
//			RowNum = 1919 - i + 1;
//		
//		{
//			//---------------------------------------------------
//			TmpData = 0x0001;
//			CommandMode_Write( 0xC0, &TmpData, 1);

//			//2A与2B, Restart from (0,0) "origin of coordinates"
//			//2A命令, set column address
//			TmpData = 0x0743;
//			CommandMode_Write( 0xB7, &TmpData, 1);
//			TmpData = 0x0005;
//			CommandMode_Write( 0xBC, &TmpData, 1);
//			TmpData = 0x0000;
//			CommandMode_Write( 0xBD, &TmpData, 1);
//			TmpData = (UINT32)j;
//			TmpD[0] = 0x00002A | ((TmpData) & 0x00FF00) | ((TmpData << 16) & 0xFF0000);
//			TmpData = (UINT32)(j + 3);
//			TmpD[1] = ((TmpData >> 8) & 0x0000FF) | ((TmpData << 8) & 0x00FF00);
//			CommandMode_Write( 0xBF, TmpD, 2);
//			
//			//2B命令, set page address
//			TmpData = 0x0743;
//			CommandMode_Write( 0xB7, &TmpData, 1);
//			TmpData = 0x0005;
//			CommandMode_Write( 0xBC, &TmpData, 1);
//			TmpData = 0x0000;
//			CommandMode_Write( 0xBD, &TmpData, 1);
//			TmpData = (UINT32)i;
//			TmpD[0] = 0x00002B | ((TmpData) & 0x00FF00) | ((TmpData << 16) & 0xFF0000);
//			TmpData = (UINT32)(i + RowNum - 1);
//			TmpD[1] = ((TmpData >> 8) & 0x0000FF) | ((TmpData << 8) & 0x00FF00);
//			CommandMode_Write( 0xBF, TmpD, 2);
//			
//			
//			//声明接下来GPU要写的数据块的大小
//			TmpData = 0x0743;
//			CommandMode_Write( 0xB7, &TmpData, 1);
//			TmpData = RowNum * 4 * 3; //each pixel 3 bytes
//			CommandMode_Write( 0xBC, &TmpData, 1);
//			TmpData = 0x0000;
//			CommandMode_Write( 0xBD, &TmpData, 1);
//			CommandMode_Write( 0xBF, &TmpData, 0);
//		}
//		
//		CommandMode_GPURectangleReadOutFromDDR(0x2C, ddr_current_display_region_addr, i, RowNum, j, 4);
//	}
}

//---写点阵字
void pattern_DotArrayEachLine_wr_ddr(UINT16 ddr_current_display_region_addr, UINT16 LineIndex, UINT16 ColumnIndexStart, UINT8 DotCnt, UINT8 *DotArray, UINT8 F_R,UINT8 F_G,UINT8 F_B, UINT8 B_R,UINT8 B_G, UINT8 B_B) { //点阵字的每一行
	UINT16 value;
	UINT16 res;
	UINT8 kk;
	UINT8 DotArrayIndex;

	{ //写入Buffer
		MCU_GPU__ADDR = MCU_CFG_GPU__DDRBUF_ADDR;
	
		for(kk=0; kk<DotCnt; kk++) {
			DotArrayIndex = kk >> 3;
			
			if((DotArray[DotArrayIndex] << (kk & 0x07)) & 0x80) {
				MCU_GPU__DATAH = (UINT16)F_R;
				MCU_GPU__DATA  = ((UINT16)F_G<<8) | (UINT16)F_B;
			}
			else {
				MCU_GPU__DATAH = (UINT16)B_R;
				MCU_GPU__DATA  = ((UINT16)B_G<<8) | (UINT16)B_B;
			}
		}
	}
	
	{ //告诉GPU执行搬运操作, 将Buffer中的数据搬运到DDR相应区域
		if(ddr_current_display_region_addr == 0) { //process with ddr-byte-addr[26], 写到当前显示的Frame区域
			value = (LineIndex>>2) & 0x03ff;
		}
		else {
			value = (LineIndex>>2) | 0x0400;
		}
		MCU_GPU__ADDR = MCU_CFG_GPU__DDR_ACCESS_BYTE_ADDR1;
		MCU_GPU__DATA = value;
		value = LineIndex<<14;
		MCU_GPU__ADDR = MCU_CFG_GPU__DDR_ACCESS_BYTE_ADDR0;
		MCU_GPU__DATA = value | (ColumnIndexStart<<2); //[13:0]-->[13:2](Column,4095Max) [1:0](Pixel,32bit), GPU会自动将[3:2]做全0处理

		value = (DotCnt>>2) - 1; //Each Pixel=32bit, 128bit=4Pixel
		MCU_GPU__ADDR = MCU_CFG_GPU__DDR_ACCESS_CTRL_REG_ADDR;
		MCU_GPU__DATA = (value&0x3f) | 0x0040; //0x007f;//start_enable:1, burst length:63, that is 64 of 128bits
			
		//-----wait transfer done
		res = 0x40;
		while(res) {
			res = MCU_GPU__DATA;
			res = res & 0x40;
		}
	}
}
void op_PatternShow16x16DotArray(UINT16 LineIndex, UINT16 ColumnIndexStart, UINT8 *DotArray, UINT8 F_R,UINT8 F_G,UINT8 F_B, UINT8 B_R,UINT8 B_G, UINT8 B_B) {
	UINT16 ddr_current_display_region_addr;
	UINT16 i;
	UINT8 *pDotArray;
	
	//Cancel FIFO Channel of BMP display(FIFO-BUF-DDR), Here is MCU-BUF-DDR,
	MCU_GPU__ADDR = MCU_CFG_GPU__SDIP_BUFFER_CTRL_REG_ADDR;
	MCU_GPU__DATA = 0x0000; //bit[12], 1 mean select SDIP to DDR FIFO channel; 0 mean select SD-MCU-buffer;
	
	
	MCU_GPU__ADDR = MCU_CFG_GPU__DDR_FRAMEREGION_READ_START_ADDR;//read the current display region, [29:26] of DDR-BYTE-ADDRESS
	ddr_current_display_region_addr = MCU_GPU__DATA;
	
	pDotArray = DotArray;
	for(i=0; i<16; i++) { //16行
		pattern_DotArrayEachLine_wr_ddr(ddr_current_display_region_addr, LineIndex, ColumnIndexStart, 16, pDotArray, F_R, F_G, F_B,  B_R, B_G, B_B); //点阵字的每一行, 16个点
		LineIndex ++;
		pDotArray+=2; //每行16个点即2个Byte
	}
	
	
	//close pure color mode to BMP display mode, if previous display is Pure-Color-Mode
	{
		MCU_GPU__ADDR = MCU_CFG_GPU__PURECOLOR_ADDR1;
		MCU_GPU__DATA = 0x0000;
	}
}
void op_PatternShow8x16DotArray(UINT16 LineIndex, UINT16 ColumnIndexStart, UINT8 *DotArray, UINT8 F_R,UINT8 F_G,UINT8 F_B, UINT8 B_R,UINT8 B_G, UINT8 B_B) {
	UINT8 ddr_current_display_region_addr;
	UINT16 i;
	UINT8 *pDotArray;
	
	//Cancel FIFO Channel of BMP display(FIFO-BUF-DDR), Here is MCU-BUF-DDR,
	MCU_GPU__ADDR = MCU_CFG_GPU__SDIP_BUFFER_CTRL_REG_ADDR;
	MCU_GPU__DATA = 0x0000; //bit[12], 1 mean select SDIP to DDR FIFO channel; 0 mean select SD-MCU-buffer;
	
	
	MCU_GPU__ADDR = MCU_CFG_GPU__DDR_FRAMEREGION_READ_START_ADDR;//read the current display region, [29:26] of DDR-BYTE-ADDRESS
	ddr_current_display_region_addr = MCU_GPU__DATA;
	
	pDotArray = DotArray;
	for(i=0; i<16; i++) { //16行
		pattern_DotArrayEachLine_wr_ddr(ddr_current_display_region_addr, LineIndex, ColumnIndexStart, 8, pDotArray, F_R, F_G, F_B,  B_R, B_G, B_B); //点阵字的每一行, 8个点
		LineIndex ++;
		pDotArray+=1; //每行8个点即1个Byte
	}
	
	
	//close pure color mode to BMP display mode, if previous display is Pure-Color-Mode
	{
		MCU_GPU__ADDR = MCU_CFG_GPU__PURECOLOR_ADDR1;
		MCU_GPU__DATA = 0x0000;
	}
}


////国(0) 家(1), 16x16
//UINT8 DotArrayC[2][32] = {
//	{0x00,0x00,0x7F,0xFC, 0x40,0x04,0x40,0x04,  0x5F,0xF4,0x41,0x04, 0x41,0x04,0x4F,0xE4,
//	 0x41,0x04,0x41,0x44, 0x41,0x24,0x5F,0xF4,  0x40,0x04,0x40,0x04, 0x7F,0xFC,0x40,0x04},/*"国",0*/

//	{0x02,0x00,0x01,0x00, 0x7F,0xFE,0x40,0x02,  0x80,0x04,0x7F,0xFC, 0x02,0x00,0x0D,0x08,
//	 0x71,0x90,0x02,0xA0, 0x0C,0xC0,0x71,0xA0,  0x06,0x98,0x18,0x86, 0xE2,0x80,0x01,0x00},/*"家",1*/
//};
//void ShowChar(void) {
//	
//	op_PatternShow16x16DotArray(960, 400, DotArrayC[0], 0xFF,0x00,0xFF, 0x00,0xFF,0x00);
//	op_PatternShow16x16DotArray(960, 416, DotArrayC[1], 0xFF,0x00,0xFF, 0x00,0xFF,0x00);
//}


// A(0) B(1) C(2) D(3), 8x16
UINT8 DotArrayE[4][16] = {
	{0x00,0x00,0x00,0x10,0x10,0x18,0x28,0x28,0x24,0x3C,0x44,0x42,0x42,0xE7,0x00,0x00},/*"A",0*/
	{0x00,0x00,0x00,0xF8,0x44,0x44,0x44,0x78,0x44,0x42,0x42,0x42,0x44,0xF8,0x00,0x00},/*"B",1*/
	{0x00,0x00,0x00,0x3E,0x42,0x42,0x80,0x80,0x80,0x80,0x80,0x42,0x44,0x38,0x00,0x00},/*"C",2*/
	{0x00,0x00,0x00,0xF8,0x44,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x44,0xF8,0x00,0x00},/*"D",3*/
};
void ShowChar(void) {
	op_PatternShow8x16DotArray(960, 400, DotArrayE[0], 0xFF,0x00,0xFF, 0x00,0xFF,0x00);
	op_PatternShow8x16DotArray(960, 408, DotArrayE[1], 0xFF,0x00,0xFF, 0x00,0xFF,0x00);
	op_PatternShow8x16DotArray(960, 416, DotArrayE[2], 0xFF,0x00,0xFF, 0x00,0xFF,0x00);
	op_PatternShow8x16DotArray(960, 424, DotArrayE[3], 0xFF,0x00,0xFF, 0x00,0xFF,0x00);
}
