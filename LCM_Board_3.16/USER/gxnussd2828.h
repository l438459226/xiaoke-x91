
#ifndef _GXNUSSD2828_H_
#define _GXNUSSD2828_H_

#include "systick.h"

extern unsigned int Dsi_LANE;
extern unsigned int Dsi_mbps;//mbps
extern unsigned int Lcd_PCLK;
extern unsigned int Lcd_fps;

void SSD_LANE(u8 lane,u16 clock);
void SSD_MODE(u8 vido_mode,u8 mode);
void print_panelinfo(void);

#endif

