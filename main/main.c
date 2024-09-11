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
esp_err_t create_tasks(void);                   /*DECLARACION DE LA FUNCION QUE CREARA LAS 3 TAREAS QUE INVOCARAN LAS FUNCIONES DE ARRIBA DECLARADAS*/

int count_btn=0;
bool sistema_on = false;

void app_main(void)
{
    gpio_init();
    adc_init();
    uart_init();

    int count_btn=0;
    bool adc_on = false;
    int value_adc = 0;
    create_tasks();

 
    while (1)
    {
        if(sistema_on==true){
            hal_led_set_level(1);
            value_adc = hal_read_adc(ADC1_CHANNEL_4);
            sprintf(state, "Valor ADC: %d\n",value_adc);
            hal_uart_send(state);
        }
        else{
            hal_led_set_level(0);
        }

       /* if(adc_on){
            value_adc = hal_read_adc(ADC1_CHANNEL_4);
            sprintf(state, "Valor ADC: %d\n",value_adc);
            hal_uart_send(state);
            
        }*/
       
      // vTaskDelay(100/ portTICK_PERIOD_MS);
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

    

    return ESP_OK;
}

/*tarea #1*/

void vTaskEntradas(void* pvParameters){

    while(1){
        if(hal_btn_read(BTN1)==0){
            while(hal_btn_read(BTN1)==0);
            count_btn++;
            if((count_btn & 1)==1){
               // hal_led_set_level(1);
                //adc_on = true;
                sistema_on=true;
                
            }
                
            else{
                sistema_on=false;
                 //hal_led_set_level(0);
                 //adc_on=false;
                 //hal_uart_send("No_Disponible\n");

            }

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