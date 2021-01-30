#include "peripherals/timer.h"
#include "peripherals/irq.h"
#include "peripherals/aux.h"
#include "mini_uart.h"
#include "string_utils.h"
#include "scheduler.h"

const u32 interval_1 = CLOCKHZ;
u32 currrent_value_1 = 0;

void init_timer(void)
{
    // Set the next timer interrupt
    currrent_value_1 = REGS_TIMER->counter_low;
    currrent_value_1 += interval_1;
    REGS_TIMER->compare[1] = currrent_value_1;
}

void handle_timer_1(void)
{
    // Set the next timer interrupt
    currrent_value_1 += interval_1;
    REGS_TIMER->compare[1] = currrent_value_1;
    REGS_TIMER->control_status |= SYS_TIMER_IRQ_1;
    
    timer_tick();
}