#ifndef SYSTEMTICK_H
#define SYSTEMTICK_H

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
#include "SystemTick_Cfg.h"

#ifndef TICK_PER_MS
#define TICK_PER_MS                         1
#endif

#ifndef TICK_PER_SEC
#define TICK_PER_SEC                        1024
#endif

#ifdef USE_TICK_32BIT

#ifndef SystemTimer_SetCallbackFunc
#error "Please define SystemTimer_SetCallbackFunc"
#endif

#define tick_t uint32_t

extern volatile uint32_t SystemTickCount;

void SystemTick_Init(void);

#define Tick_Get()                          ((tick_t)(SystemTickCount+SystemTimer_Get()))

#else
#define tick_t uint16_t

#define SystemTick_Init()

#ifndef Tick_Get
#define Tick_Get()                          SystemTimer_Get()
#endif

#endif

typedef struct {
    bool Over;
    tick_t Begin;
    tick_t TickCount;
} tick_timer_t;

#define Tick_Reset(cxt)                     cxt.Over=1
#define Tick_Timer_Reset(cxt)               cxt.Over=1

#ifndef __delay_ms
#define __delay_ms(ms) do{tick_t __thisTk=Tick_Get(); \
        while(Tick_Dif_Ms(Tick_Get(), __thisTk)<ms);}while(0)
#endif

bool Tick_Is_Over(tick_timer_t *pTick, tick_t ms);

#define Tick_Dif(tk1, tk2)                  ((tk1)-(tk2))

#ifdef TICK_PER_US
#define Tick_Dif_Us(tk1, tk2)               (((tk1)-(tk2))/TICK_PER_US)
#endif

#define Tick_Dif_Ms(tk1, tk2)               (((tk1)-(tk2))/TICK_PER_MS)
#define Tick_Dif_Sec(tk1, tk2)              (((tk1)-(tk2))/TICK_PER_SEC)
#define Tick_Is_Over_Ms(pTick, ms)          Tick_Is_Over(pTick, ms)
#define Tick_Is_Over_Sec(pTick, sec)        Tick_Is_Over(pTick, 1000UL*(sec))

#define Tick_Timer_Read()                   Tick_Get()
#define Tick_Timer_Is_Over_Ms(pTick, ms)    Tick_Is_Over(&pTick, ms)
#define Tick_Timer_Is_Over_Sec(pTick, sec)  Tick_Is_Over(&pTick, 1000UL*(sec))

#endif