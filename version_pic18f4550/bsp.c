
#include <18f4550.h>
#include <usb_bootloader.h> // Necesario por el bootloader
#use delay(clock=20M)
#fuses HS,NOWDT,NOPROTECT,NOLVP
#include <select_version.c>
#include <lcd.c>


#define OUTPUT 0x00
#define INPUt 0xFF

#define HIGH 1
#define LOW 0
#define BTN1 PIN_B0

#define LED0 PIN_D0
#define LED1 PIN_D1
#define LED2 PIN_D2
#define LED3 PIN_D3
#define LED4 PIN_D4
#define LED5 PIN_D5
#define LED6 PIN_D6
#define LED7 PIN_D7

#define CHANNEL_0   0
#define CHANNEL_1   1
#define CHANNEL_2   2
#define CHANNEL_3   3
#define CHANNEL_4   4
#define CHANNEL_5   5
#define CHANNEL_6   6
#define CHANNEL_7   7
#define CHANNEL_8   8
#define CHANNEL_9   9
#define CHANNEL_10  10
#define CHANNEL_11  11
#define CHANNEL_12  12


enum pines{
   D0,D1,D2,D3,D4,D5,D6,D7,
   B0,B1,B2,B3,B4,B5,B6,B7,
   C0,C1,C2,C3,C4,C5,C6,C7,
};


#ifdef ESP32
void hal_gpio_mode(int gpio, int mode){
    if(mode == OUTPUT){
        gpio_reset_pin(gpio);
        gpio_set_direction(gpio,GPIO_MODE_OUTPUT);
    }
    else if(mode == INPUT){
        gpio_reset_pin(gpio);
        gpio_set_direction(gpio,GPIO_MODE_INPUT);
    }
}
void hal_led_set_level(int gpio,bool state){
    gpio_set_level(gpio,state);
}
bool hal_btn_read(int gpio){

    return gpio_get_level(gpio);
}
void hal_gpio_set_pullup(int gpio){
     gpio_set_pull_mode(gpio,GPIO_PULLUP_ONLY);
}

void hal_comunicacion_terminal_config(int uart_num, int baudrate, int data_bits, int paridad, int stop_bits, int flow_ctrl){
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
void hal_terminal_send(const char *mensaje){

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



#endif



#ifdef PIC18
void hal_gpio_mode(int pin, int mode){

   if(pin>=D0 && pin<=D7){
      set_tris_d(mode);
   }
   if(pin>=B0 && pin<=B7){
   set_tris_b(mode);
   }
   if(pin==BTN1){
      set_tris_b(mode);
   }
   
   
}
void hal_led_set_level(int puerto,int state){
   if(state==1)
      output_high(puerto);
   else if(state==0)
      output_low(puerto);
}

int hal_btn_read(int btn){
 if(btn==PIN_B0){
  return INPUT_STATE(PIN_B0);
 }

}


void hal_comunicacion_terminal_config(){
   lcd_init();
}

void hal_terminal_send(char* mensaje){
   lcd_putc("\f");  // Comando para limpiar la pantalla LCD
   lcd_gotoxy(1,1);
   printf(lcd_putc,mensaje);
  
}

void hal_adc_config(int canal,int puerto){
   setup_adc_ports(puerto);
   setup_adc(ADC_CLOCK_INTERNAL);
   set_adc_channel(canal);
}

int8 hal_read_adc(int channel){
   set_adc_channel(channel);
   return read_adc();

}




#endif



