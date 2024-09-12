#ifndef _INIT_FUNCTIONS_H_
#define _INIT_FUNCTIONS_H_
#include "../bsp/bsp.h"

#define STACK_SIZE 1024
void vTaskEntradas(void* pvParameters); 
void vTaskTerminal(void* pvParameters); 
void vTaskAdc(void* pvParameters); 
esp_err_t create_tasks(void);      

void gpio_init();
void adc_init();
void uart_init();


#endif