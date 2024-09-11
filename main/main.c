#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h> 
#include "../hal/hal.h"


char mensaje[100];
char state[100];

void gpio_init();
void adc_init();
void uart_init();


#define STACK_SIZE 1024
void vTaskEntradas(void* pvParameters); 
void vTaskTerminal(void* pvParameters); 
void vTaskAdc(void* pvParameters); 
esp_err_t create_tasks(void);                   /*DECLARACION DE LA FUNCION QUE CREARA LAS 3 TAREAS QUE INVOCARAN LAS FUNCIONES DE ARRIBA DECLARADAS*/

int count_btn=0;
bool sistema_on = false;
int value_adc = 0;

void app_main(void)
{
    gpio_init();
    adc_init();
    uart_init();
    create_tasks();

 
    while (1)
    {
        if(sistema_on==true){
            hal_led_set_level(1);
        }
        else{
            hal_led_set_level(0);
        }
      vTaskDelay(pdMS_TO_TICKS(100));
              
    }

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

/*tarea #1*/

void vTaskEntradas(void* pvParameters){

    while(1){
        if(hal_btn_read(BTN1)==0){
            while(hal_btn_read(BTN1)==0);
            count_btn++;
            if((count_btn & 1)==1){
                sistema_on=true;  
            }
                
            else{
                sistema_on=false;
            }
        }
        
        vTaskDelay(pdMS_TO_TICKS(50));
    }

}

void vTaskTerminal(void* pvParameters){
    while(1){
    if(sistema_on==true){
        sprintf(state, "Valor ADC: %d\n",value_adc);
        hal_uart_send(state);
    }
    vTaskDelay(pdMS_TO_TICKS(50));
    }

}

void vTaskAdc(void* pvParameters){
    while(1){
    if(sistema_on==true){
        value_adc = hal_read_adc(ADC1_CHANNEL_4);
    }
    vTaskDelay(pdMS_TO_TICKS(50));
    }

}

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
    hal_uart_config(UART_NUM_0,9600,UART_DATA_8_BITS,UART_PARITY_DISABLE,UART_STOP_BITS_1,UART_HW_FLOWCTRL_DISABLE);

}