#ifndef __PLL_FREQ_DEF_H
#define __PLL_FREQ_DEF_H

#include "user_config.h"

typedef struct {
	UINT8 M;
	UINT8 N;
	UINT8 C;
} pPLL_FACTOR;

//--- PLL output Frequency = (((100MHz / PLL_FACTOR_N) * PLL_FACTOR_M) / PLL_FACTOR_C);
extern const pPLL_FACTOR gPLL_FACTOR_Table[401];

#endif /* __PLL_FREQ_DEF_H */
