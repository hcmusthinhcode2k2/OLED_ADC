#include "SystemTick.h"

#ifdef USE_TICK_32BIT
volatile uint32_t SystemTickCount=0;

static void SystemTick_TmrCallback(void)
{
    SystemTimer_Clear();
    SystemTickCount+=65536;
}

void SystemTick_Init(void)
{
    SystemTickCount=0;
    SystemTimer_SetCallbackFunc(SystemTick_TmrCallback);
}

#endif

bool Tick_Is_Over(tick_timer_t *pTick, tick_t ms) // <editor-fold defaultstate="collapsed" desc="Check timeout">
{
    if(pTick->Over==1)
    {
        pTick->Begin=Tick_Get();
        pTick->TickCount=ms*TICK_PER_MS;
        pTick->Over=0;
    }

    if((tick_t)(Tick_Get()-pTick->Begin)>=pTick->TickCount)
        pTick->Over=1;

    return pTick->Over;
} // </editor-fold>