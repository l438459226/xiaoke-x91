#include "tools.h"

//经实际测量, 当优化等级为3时delayus(1)基本等于1us
void delayus(unsigned int t) {
	short int ValRx;
	while(t--)
	{
//		__asm{
//			MOV R2, #24  // 1 cycle
//			loop:
//			SUB R2, R2, 1 // 1 cycle
//			CMP R2, #0    // 1 cycle
//			BNE loop        // 1 + P
//		}
		__asm{
			MOV ValRx, #7  // 1 cycle
			loop:
			SUB ValRx, ValRx, 1 // 1 cycle
			CMP ValRx, #0    // 1 cycle
			BNE loop        // 1 + P
		}
	}
}


//经过实际测量, 当优化等级为3时delayms(1)基本等于1ms, 测delayms(100)时实际时间为103ms
void delayms(unsigned int t)
{
	int ValRx;
	while(t--)
	{
		__asm{
			MOV ValRx, #8200  // 1 cycle
			loop:
			SUB ValRx, ValRx, 1 // 1 cycle
			CMP ValRx, #0    // 1 cycle
			BNE loop        // 1 + P
		}
	}
}
