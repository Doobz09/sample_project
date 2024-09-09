#include "bsp.h"


void set_gpio(GPIOS pin,int level){
    
    gpio_set_level(pin,level);
} 


void bsp_gpio_mode(GPIOS gpio, MODE mode){
    if(mode == OUTPUT){
        gpio_reset_pin(gpio);
        gpio_set_direction(gpio,GPIO_MODE_OUTPUT);
    }
    else if(mode == INPUT){
        gpio_reset_pin(gpio);
        gpio_set_direction(gpio,GPIO_MODE_INPUT);
    }
}

bool read_gpio(GPIOS gpio){
    return gpio_get_level(gpio);
}

void bsp_uart_config(int uart_num, int baudrate, int data_bits, int paridad, int stop_bits, int flow_ctrl){
uart_config_t uart_config = {
        .baud_rate = baudrate,                  /*9600 de velocidad de trasmision*/
        .data_bits = data_bits,           /*8 bits*/
        .parity = paridad,           /*paridad desabilitada*/
        .stop_bits = stop_bits,           /*un bit para paro */
        .flow_ctrl = flow_ctrl
    };

    uart_param_config(uart_num, &uart_config); /*el puerto de la uart a usar el el 0 le pasamos la estructura anterior */
    uart_set_pin(uart_num, TXD_PIN, RXD_PIN, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);  /*configuramos los pines */
    uart_driver_install(uart_num, 1024, 0, 0, NULL, 0);   /*le decimos el tamaño del buffer en eeste caso 1024*/
}


void bsp_terminal_init(){
    bsp_uart_config(UART_NUM_0,9600,UART_DATA_8_BITS,UART_PARITY_DISABLE,UART_STOP_BITS_1,UART_HW_FLOWCTRL_DISABLE);
}

void bsp_uart_send(const char *mensaje) {
    // Escribir los bytes a la UART seleccionada
    uart_write_bytes(UART_NUM_0, mensaje, strlen(mensaje));
}

void bsp_led_set_level(bool level){
    gpio_set_level(LED4,level);
}