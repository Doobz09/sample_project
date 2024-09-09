#ifndef _HAL_H_
#define _HAL_H_
#define ESP32
#include "../bsp/bsp.h"
#if !defined(ESP32) && !defined(PIC18)
    #error "Debe definirse la macro ESP32 o PIC18 para compilar correctamente."
#endif
void hal_gpio_mode(GPIOS gpio, MODE mode);
void hal_led_set_level(bool state);

//funciones uart
void hal_uart_config(int uart_num, int baudrate, int data_bits, int paridad, int stop_bits, int flow_ctrl);
void hal_uart_send(const char *mensaje);


#endif