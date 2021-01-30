#include "scheduler.h"
#include "string_utils.h"
#include "mini_uart.h"

int var = 1;
int *p_var = &(var);      // Current task being executed

void timer_tick(void)
{
    char buff[] = "0000000000000000";

    parse_int(*p_var, buff, 16);
    uart_send_string("*p_var: ");
    uart_send_string(buff);
    uart_send_string("\n");

    parse_int(var, buff, 16);
    uart_send_string("var: ");
    uart_send_string(buff);
    uart_send_string("\n");

    if(p_var == &var) {
        uart_send_string("equal: true");
    } else {
        uart_send_string("equal: false");
    }
}