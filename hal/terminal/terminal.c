
#include "terminal.h"

#ifdef ESP32
//--------------
void hal_uart_config(int uart_num, int baudrate, int data_bits, int paridad, int stop_bits, int flow_ctrl){
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
void hal_uart_send(const char *mensaje){

    uart_write_bytes(UART_NUM_0, mensaje, strlen(mensaje));
}

#endif


#ifdef PIC18

void hal_adc_config(int canal,int puerto){
   setup_adc_ports(puerto);
   setup_adc(ADC_CLOCK_INTERNAL);
   set_adc_channel(canal);
}

int8 hal_read_adc(int channel){
   set_adc_channel(channel);
   return read_adc();

}
#endif
