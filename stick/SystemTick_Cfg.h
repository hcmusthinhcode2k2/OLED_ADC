#ifndef SYSTEMTICK_CFG_H
#define	SYSTEMTICK_CFG_H

#include "tmr1.h"

#define TICK_PER_MS         31
#define TICK_PER_SEC        31250
#define USE_TICK_32BIT

#define SystemTimer_Get()   TMR1_Counter16BitGet()
#define SystemTimer_SetCallbackFunc(x) TMR1_SetInterruptHandler(x)
#define SystemTimer_Clear() TMR1_Counter16BitSet(0)
#endif