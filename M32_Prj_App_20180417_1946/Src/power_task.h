#ifndef __POWER_TASK_H
#define __POWER_TASK_H

#include "user_config.h"


#define AVDDP_mV_H (AVDDP_mV >> 8)
#define AVDDP_mV_L (AVDDP_mV & 0xff)
#define AVDDN_mV_H (AVDDN_mV >> 8)
#define AVDDN_mV_L (AVDDN_mV & 0xff)
#define VCOMP_mV_H (VCOMP_mV >> 8)
#define VCOMP_mV_L (VCOMP_mV & 0xff)
#define VCOMN_mV_H (VCOMN_mV >> 8)
#define VCOMN_mV_L (VCOMN_mV & 0xff)

void Power_Init(void);
void Power_Off(void);
void Power_On(void);



#endif /* __POWER_TASK_H */
