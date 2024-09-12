#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h> 
#include "../bsp/bsp.h"


char mensaje[100];
char state[100];

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
            hal_led_set_level(LED4,1);
        }
        else{
            hal_led_set_level(LED4,0);
           
        }
      vTaskDelay(pdMS_TO_TICKS(100));
              
    }

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
                hal_terminal_send("No Disponible\n");
            }
        }
        
        vTaskDelay(pdMS_TO_TICKS(50));
    }

}

void vTaskTerminal(void* pvParameters){
    while(1){
    if(sistema_on==true){
        sprintf(state, "Valor ADC: %d\n",value_adc);
        hal_terminal_send(state);
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
