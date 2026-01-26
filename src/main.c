#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/uart.h"

#define UART_ID uart1
#define BAUD_RATE 31250   // MIDI baudrate
#define UART_TX_PIN 4
#define UART_RX_PIN 5

int main() {
    stdio_init_all();

    uart_init(UART_ID, BAUD_RATE);

    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);

    uart_set_format(UART_ID, 8, 1, UART_PARITY_NONE);
    uart_set_fifo_enabled(UART_ID, false);

    while (true) {

        if (uart_is_readable(UART_ID)) {
            uint8_t byte = uart_getc(UART_ID);

		if (byte == 0xF8)
		{
			continue;
		}
            printf("RX: 0x%02X\n", byte);
        }
    }
}


