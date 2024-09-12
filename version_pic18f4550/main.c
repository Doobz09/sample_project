#include <bsp.c>

void gpio_init();
void adc_init();
void uart_init();
char mensaje[]; 



void main()
{
    gpio_init();
    adc_init();
    uart_init();
   
   
   int count_btn=0;
   int adc_on = false;
   int value_adc = 0;
   
   while(true){
   
      if(hal_btn_read(BTN1)==0){
            while(hal_btn_read(BTN1)==0);
            count_btn++;
            if((count_btn & 1)==1){
                hal_led_set_level(LED3,1);
                adc_on = true;
                
            }
                
            else{
                 hal_led_set_level(LED3,0);
                 adc_on=false;
                 sprintf(mensaje,"NO DISPONIBLE");
                 hal_terminal_send(mensaje);

            }

        }
        
        if(adc_on){
            value_adc = hal_read_adc(CHANNEL_0);
            sprintf(mensaje, "Valor ADC: %u\n",value_adc);
            hal_terminal_send(mensaje);
            
        }
   
   
   
      delay_ms(50);
     
   }

}







void gpio_init(){
    //ENTRADAS
    hal_gpio_mode(BTN1,INPUT);

    //SALIDAS
    hal_gpio_mode(LED3,OUTPUT);
    hal_led_set_level(LED3,LOW);
}
void adc_init(){
   // hal_adc_init();
    hal_adc_config(CHANNEL_0,AN0);

}

void uart_init(){
    hal_comunicacion_terminal_config();
}
