
#include "adc.h"

#ifdef ESP32
//funciones adc
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