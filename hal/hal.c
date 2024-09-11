
#include "hal.h"



#ifdef ESP32
//GPIOS
void hal_gpio_mode(GPIOS gpio, MODE mode){
    if(mode == OUTPUT){
        gpio_reset_pin(gpio);
        gpio_set_direction(gpio,GPIO_MODE_OUTPUT);
    }
    else if(mode == INPUT){
        gpio_reset_pin(gpio);
        gpio_set_direction(gpio,GPIO_MODE_INPUT);
    }
}
void hal_led_set_level(bool state){
    gpio_set_level(LED4,state);
}
bool hal_btn_read(GPIOS gpio){

    return gpio_get_level(gpio);
}
void hal_gpio_set_pullup(GPIOS gpio){
     gpio_set_pull_mode(gpio,GPIO_PULLUP_ONLY);
}

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


void hal_adc_init(){

    /*CONFIGURAMOS el ADC USAMOS EL CANAL 4  */
    /*RESOLUCION DE 12 BITS MAXIMO VALOR 4095 ATENUACION 11 PARA TENER UN VALOR DE 3.3 EN VOLTAJE*/
    //adc1_config_channel_atten(ADC1_CHANNEL_0, ADC_ATTEN_DB_11);/*pinVp*/
    
    adc1_config_width(ADC_WIDTH_BIT_12);


}
void hal_adc_config(int chanel){
    adc1_config_channel_atten(chanel, ADC_ATTEN_DB_11);/*PIN32*/
}

int hal_read_adc(int channel){
    return adc1_get_raw(channel);
}


#else
//aqui iran las funciones para el pic18f4550 o arduino
#endif




