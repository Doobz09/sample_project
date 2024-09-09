#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h> 
#include "../hal/hal.h"




char mensaje[100];


void app_main(void)
{
    hal_gpio_mode(LED4,OUTPUT);
    hal_uart_config(UART_NUM_0,9600,UART_DATA_8_BITS,UART_PARITY_DISABLE,UART_STOP_BITS_1,UART_HW_FLOWCTRL_DISABLE);
    
       
    hal_led_set_level(0);
        
    while (1)
    {


       vTaskDelay(500 / portTICK_PERIOD_MS);
       hal_uart_send("LED:ENCENDIDO\n");
       hal_led_set_level(1);
       vTaskDelay(500 / portTICK_PERIOD_MS);
       hal_uart_send("LED:APAGADO\n");
       hal_led_set_level(0);
    
    }
    
}
