#include "gpio.h"

#ifdef ESP32
//GPIOS
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

#endif
//PIC 18F4550
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
#endif