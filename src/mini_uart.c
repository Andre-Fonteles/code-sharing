#include "gpio.h"
#include "utils.h"
#include "peripherals/aux.h"
#include "mini_uart.h"

#define TXD 14
#define RXD 15

void uart_init(void)
{
    gpio_pin_set_func(TXD, GFAlt5);
    gpio_pin_set_func(RXD, GFAlt5);

    gpio_pin_pull_enable(TXD, PUDOff);
    gpio_pin_pull_enable(RXD, PUDOff);

    REGS_AUX->enables = 1;
    REGS_AUX->mu_control = 0;
    REGS_AUX->mu_ier = 0b1101; // Enable UART receive interrupt
    REGS_AUX->mu_lcr = 3;
    REGS_AUX->mu_mcr = 0;
    REGS_AUX->mu_baud_rate = 541; // = 115200 @ 500 Mhz
    REGS_AUX->mu_control = 3;
}

void uart_send(char c)
{
    // Loop (pool) until the device is ready to send the data.
    while (!(REGS_AUX->mu_lsr & 0x20)); // Bit 5 tells if the transmiter is empty (the UART is ready write)

    REGS_AUX->mu_io = c;
}

void uart_send_string(char *str)
{
    while (*str)
    {
        if (*str == '\n')
        {
            uart_send('\r');
        }

        uart_send(*str);
        str++;
    }
}