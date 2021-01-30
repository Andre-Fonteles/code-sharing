#include "utils.h"
#include "entry.h"
#include "peripherals/irq.h"
#include "peripherals/aux.h"
#include "mini_uart.h"
#include "string_utils.h"
#include "timer.h"

void handle_invalid_entry_message(u32 type, u64 esr, u64 address) {
    uart_send_string("ERROR CAUGHT: \n");
}

void enable_interrupt_controller(void) {
    REGS_IRQ->irq0_enable_0 = SYS_TIMER_IRQ_1;
}

void handle_irq(void) {
    u32 irq;

    irq = REGS_IRQ->irq0_pending_0;

    while(irq) {
        if(irq & SYS_TIMER_IRQ_1) {
            irq &= ~SYS_TIMER_IRQ_1;
            handle_timer_1();
        }
    }

}