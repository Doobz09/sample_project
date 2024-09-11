#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h> 
#include "../hal/hal.h"


char mensaje[100];
char state[100];

void gpio_init();
void adc_init();
void uart_init();


void app_main(void)
{
    gpio_init();
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
                hal_led_set_level(1);
                adc_on = true;
                
            }
                
            else{
                 hal_led_set_level(0);
                 adc_on=false;
                 hal_uart_send("No_Disponible\n");

            }

        }

        if(adc_on){
            value_adc = hal_read_adc(ADC1_CHANNEL_4);
            sprintf(state, "Valor ADC: %d\n",value_adc);
            hal_uart_send(state);
            
        }
       
       vTaskDelay(100/ portTICK_PERIOD_MS);
              
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