
#include "init_functions.h"

void gpio_init(){
    //ENTRADAS
    hal_gpio_mode(BTN1,INPUT);
    hal_gpio_set_pullup(BTN1);

    //SALIDAS
    hal_gpio_mode(LED4,OUTPUT);
}

void adc_init(){
    hal_adc_init();
    hal_adc_config(ADC1_CHANNEL_4);

}

void uart_init(){
    hal_comunicacion_terminal_config(UART_NUM_0,9600,UART_DATA_8_BITS,UART_PARITY_DISABLE,UART_STOP_BITS_1,UART_HW_FLOWCTRL_DISABLE);

}

/*En esta funcion se crean las tareas que en este caso seran 3 para que el programa tenga un mejor fucionamiento*/
esp_err_t create_tasks(void){
    static uint8_t ucParameterToPass;
    TaskHandle_t xHandle = NULL;

    xTaskCreate(vTaskEntradas,                           /*Funcion que va a llamar*/
                "vTaskEntradas",                         /*Nombre de la funcion que va a llamar*/
                STACK_SIZE,                              /*Memoria que asignaremos*/
                 &ucParameterToPass,
                 1,                                      /*prioridad*/
                 &xHandle);

    xTaskCreate(vTaskTerminal,                           /*Funcion que va a llamar*/
                "vTaskTerminal",                         /*Nombre de la funcion que va a llamar*/
                STACK_SIZE,                              /*Memoria que asignaremos*/
                 &ucParameterToPass,
                 1,                                      /*prioridad*/
                 &xHandle);

    xTaskCreate(vTaskAdc,                           /*Funcion que va a llamar*/
                "vTaskAdc",                         /*Nombre de la funcion que va a llamar*/
                STACK_SIZE,                              /*Memoria que asignaremos*/
                 &ucParameterToPass,
                 1,                                      /*prioridad*/
                 &xHandle);
    

    return ESP_OK;
}