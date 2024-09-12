#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h> 
#include "../bsp/bsp.h"



char mensaje[100];
char state[100];


void app_main(void)
{
    gpio_init();//iniciamos los gpios
    adc_init();
    uart_init();

    int count_btn=0;
    bool adc_on = false;
    int value_adc = 0;
 
    while (1)
    {
        if(hal_btn_read(BTN1)==0){
            while(hal_btn_read(BTN1)==0);
            count_btn++;
            if((count_btn & 1)==1){
                hal_led_set_level(LED4,1);
                adc_on = true;
                
            }
                
            else{
                 hal_led_set_level(LED4,0);
                 adc_on=false;
                 hal_terminal_send("No_Disponible\n");
            }
        }
        if(adc_on){
            value_adc = hal_read_adc(ADC1_CHANNEL_4);
            sprintf(state, "Valor ADC: %d\n",value_adc);
            hal_terminal_send(state);
            
        }
       
       vTaskDelay(100/ portTICK_PERIOD_MS);
              
    }

    
}

