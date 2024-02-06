#include <string.h>
#include <stdio.h>
#include <math.h>
#include <inttypes.h>
#include "esp_log.h"
#include "joystick_service.h"
#include "driver/adc.h"
#include "esp_adc_cal.h"


// GPIO 34 (ADC1)
static adc_channel_t channel_x =  ADC1_CHANNEL_6;      
static adc_unit_t unit_x = ADC_UNIT_1;               
static adc_atten_t atten_x = ADC_ATTEN_DB_11;        

// GPIO 0 (ADC2)
// static adc_channel_t channel_x = ADC2_CHANNEL_1;      
// static adc_unit_t unit_x = ADC_UNIT_2;               
// static adc_atten_t atten_x = ADC_ATTEN_DB_11;        

// GPIO 35 (ADC1)
static adc_channel_t channel_y = ADC1_CHANNEL_7;      
static adc_unit_t unit_y = ADC_UNIT_1;               
static adc_atten_t atten_y = ADC_ATTEN_DB_11;        

// GPIO 12 (ADC2)
// adc_channel_t channel_x = ADC2_CHANNEL_5;      
// adc_unit_t unit_x = ADC_UNIT_2;               
// adc_atten_t atten_x = ADC_ATTEN_DB_11; 

// GPIO 14 (ADC2)
// adc_channel_t channel_x = ADC2_CHANNEL_5;      
// adc_unit_t unit_x = ADC_UNIT_2;               
// adc_atten_t atten_x = ADC_ATTEN_DB_11; 

static esp_adc_cal_characteristics_t adc1_chars_x;
static esp_adc_cal_characteristics_t adc1_chars_y;

static const adc_bits_width_t WIDTH = ADC_WIDTH_BIT_11;

void joystick_transform(float * x , float * y);


void joystick_initialize(){

    // usando ADC 1
    adc1_config_width(WIDTH);
    ESP_ERROR_CHECK(adc1_config_channel_atten(channel_x, atten_x));
    esp_adc_cal_characterize(unit_x, atten_x, WIDTH, 0, &adc1_chars_x);
    ESP_ERROR_CHECK(adc1_config_channel_atten(channel_y, atten_y));
    esp_adc_cal_characterize(unit_y, atten_y, WIDTH, 0, &adc1_chars_y);

    // usando ADC 2
    // ESP_ERROR_CHECK(adc2_config_channel_atten(channel_x, atten_x));
    // esp_adc_cal_characterize(unit_x, atten_x, WIDTH, 0, &adc1_chars_x);
    // ESP_ERROR_CHECK(adc2_config_channel_atten(channel_y, atten_y));
    // esp_adc_cal_characterize(unit_y, atten_y, WIDTH, 0, &adc1_chars_y);


    // usando ADC 1 y ADC 2
    // ESP_ERROR_CHECK(adc2_config_channel_atten(channel_x, atten_x));
    // esp_adc_cal_characterize(unit_x, atten_x, WIDTH, 0, &adc1_chars_x);
    // ESP_ERROR_CHECK(adc1_config_channel_atten(channel_y, atten_y));
    // esp_adc_cal_characterize(unit_y, atten_y, WIDTH, 0, &adc1_chars_y);


}

void joystick_get_reading(float * read_x , float * read_y){
    int adc_reading_x = 0;
    int adc_reading_y = 0;

    // adc2_get_raw((adc2_channel_t)channel_x, ADC_WIDTH_BIT_12, &adc_reading_x);
    adc_reading_x =  adc1_get_raw((adc1_channel_t)channel_x);
    int voltage_x = esp_adc_cal_raw_to_voltage(adc_reading_x, &adc1_chars_x);
    
    adc_reading_y =  adc1_get_raw((adc1_channel_t)channel_y);
    int voltage_y = esp_adc_cal_raw_to_voltage(adc_reading_y, &adc1_chars_y);

    int normalized_x = adc_reading_x / 900;
    int normalized_y = adc_reading_y / 900;

    // ESP_LOGI("POC Joystick - Reading", " (%d , %d) ", adc_reading_x , adc_reading_y);
    // ESP_LOGI("POC Joystick - Reading", " (%d , %d) ", normalized_x , normalized_y);
    // *read_x = voltage_x / 1000;
    // *read_y = voltage_y / 1000;

    *read_x = (float) normalized_x;
    *read_y = (float) normalized_y;

    joystick_transform(read_x , read_y);


    ESP_LOGI("POC Joystick - Reading", " (%f , %f) ", *read_x , *read_y);
}


//
// private functions
//

void joystick_transform(float * x , float * y){
    if(*x == 0.0)
        *x = READING_MIN;
    else if(*x == 1.0)
        *x = READING_NEUTRAL;
    else if(*x == 2.0)
        *x = READING_MAX;

    if(*y == 2.0)
        *y = READING_MAX;
    else if(*y == 1.0)
        *y = READING_NEUTRAL;
    else if( *y==0.0)
        *y = READING_MIN;
}