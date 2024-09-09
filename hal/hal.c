
#include "hal.h"



#ifdef ESP32
void hal_gpio_mode(GPIOS gpio, MODE mode){
    bsp_gpio_mode(gpio,mode);
}
void hal_led_set_level(bool state){
    bsp_led_set_level(state);
}
void hal_uart_config(int uart_num, int baudrate, int data_bits, int paridad, int stop_bits, int flow_ctrl){
    bsp_uart_config(UART_NUM_0,9600,UART_DATA_8_BITS,UART_PARITY_DISABLE,UART_STOP_BITS_1,UART_HW_FLOWCTRL_DISABLE);
}
void hal_uart_send(const char *mensaje){
    bsp_uart_send(mensaje);
}
#else
//aqui iran las funciones para el pic18f4550 o arduino
#endif




