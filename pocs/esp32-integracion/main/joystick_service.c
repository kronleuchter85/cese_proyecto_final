#include <string.h>
#include <stdio.h>
#include <math.h>
#include <inttypes.h>

#include "joystick_service.h"
#include "driver/adc.h"
#include "esp_adc_cal.h"

adc_channel_t channel_x = ADC2_CHANNEL_1;      // GPIO 0
adc_unit_t unit_x = ADC_UNIT_2;               // ADC2
adc_atten_t atten_x = ADC_ATTEN_DB_11;        // Full scale 0-3.9V, precision range 150mV-2450mV

adc_channel_t channel_y = ADC1_CHANNEL_7;      // GPIO 35
adc_unit_t unit_y = ADC_UNIT_1;               // ADC2
adc_atten_t atten_y = ADC_ATTEN_DB_11;        // Full scale 0-3.9V, precision range 150mV-2450mV

static esp_adc_cal_characteristics_t adc1_chars_x;
static esp_adc_cal_characteristics_t adc1_chars_y;


void joystick_transform(float * x , float * y);


void joystick_initialize(){

    ESP_ERROR_CHECK(adc2_config_channel_atten(channel_x, atten_x));
    esp_adc_cal_characterize(unit_x, atten_x, ADC_WIDTH_BIT_12, 0, &adc1_chars_x);

    ESP_ERROR_CHECK(adc1_config_channel_atten(channel_y, atten_y));
    esp_adc_cal_characterize(unit_y, atten_y, ADC_WIDTH_BIT_12, 0, &adc1_chars_y);

}

void joystick_get_reading(float * read_x , float * read_y){
    int adc_reading_x = 0;
    adc2_get_raw((adc2_channel_t)channel_x, ADC_WIDTH_BIT_12, &adc_reading_x);
    int voltage_x = esp_adc_cal_raw_to_voltage(adc_reading_x, &adc1_chars_x);
    
    int adc_reading_y = 0;
    adc_reading_y =  adc1_get_raw((adc1_channel_t)channel_y);
    int voltage_y = esp_adc_cal_raw_to_voltage(adc_reading_y, &adc1_chars_y);
    
    *read_x = voltage_x / 1000;
    *read_y = voltage_y / 1000;

    joystick_transform(read_x , read_y);
}



//
// private functions
//

void joystick_transform(float * x , float * y){
    if(*x == 0.0)
        *x = JOYSTICK_READING_MIN;
    else if(*x == 2.0)
        *x = JOYSTICK_READING_NEUTRAL;
    else if(*x == 3.0)
        *x = JOYSTICK_READING_MAX;

    if(*y == 0.0)
        *y = JOYSTICK_READING_MAX;
    else if(*y == 2.0)
        *y = JOYSTICK_READING_NEUTRAL;
    else if( *y==3.0)
        *y = JOYSTICK_READING_MIN;
}