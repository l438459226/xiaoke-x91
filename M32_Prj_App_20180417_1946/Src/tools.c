#include "tools.h"

//��ʵ�ʲ���, ���Ż��ȼ�Ϊ3ʱdelayus(1)��������1us
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


//����ʵ�ʲ���, ���Ż��ȼ�Ϊ3ʱdelayms(1)��������1ms, ��delayms(100)ʱʵ��ʱ��Ϊ103ms
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
