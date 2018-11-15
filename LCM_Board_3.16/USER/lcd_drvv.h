

#ifndef _LCD_DRV_H_
#define _LCD_DRV_H_

//#include "stm32f10x.h"
//#include "sys.h"


#define DCLK_FALLING_EDGE 0	 //lcd在DCLK的下降沿锁存数据
#define DCLK_RISING_EDGE  1	 //lcd在DCLK的上升沿锁存数据
#define HSYNC_ACTIVE_LOW  0  //hsync脉冲低电平有效
#define HSYNC_ACTIVE_HIGH 1  //hsync脉冲高电平有效
#define VSYNC_ACTIVE_LOW  0  //vsync脉冲低电平有效
#define VSYNC_ACTIVE_HIGH 1  //vsync脉冲高电平有效
#define DE_ACTIVE_LOW     1  //DE低电平有效
#define DE_ACTIVE_HIGH    0  //DE高电平有效

#define u16 unsigned short
#define u8 unsigned char

typedef struct vidinfo {

	
	u16	width;	/* Width of display area in millimeters */
	u16	height;	/* Height of display area in millimeters */
	u8 fps;
	u16 pclk;
	u8 pixel;
	/* LCD configuration register */
	u8	hsync;		/* Horizontal Sync polarity */
	u8	hbp;		/* Vertical Sync polarity */
	u8	hfp;		/* Data polarity */
	u8	vsync;	/* Bits per pixel, 0 = 1, 1 = 2, 2 = 4, 3 = 8 */
	u8	vbp;
	u8	vfp;
	
	u8 dsi_lane;
	u16 dsi_mbps;
	
} vidinfo_t;
vidinfo_t panel_info;

												 
															 
																					 
													 

#endif 

