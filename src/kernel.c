#include "mini_uart.h"
#include "irq.h"
#include "utils.h"
#include "timer.h"
#include "scheduler.h"
#include "string_utils.h"
#include "common.h"


void print(u64 number) {
	char buffer[] = "0000000000000000";
	parse_int(number, buffer, 16);
	uart_send_string(buffer);
	uart_send_string("\n");
}

void kernel_main(void)
{
	uart_init();
	uart_send_string("\n\nRaspberry PI Bare Metal OS Initializing...\n");

	irq_init_vector();
	enable_interrupt_controller();
	enable_irq();
	init_timer();

	while (1);	
}