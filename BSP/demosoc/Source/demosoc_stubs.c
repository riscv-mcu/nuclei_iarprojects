#include "nuclei_demosoc.h"

int putchar(int ch)
{
    if (ch == '\n') {
        uart_write(SOC_DEBUG_UART, '\r');
    }
    uart_write(SOC_DEBUG_UART, ch);

    return ch;
}
