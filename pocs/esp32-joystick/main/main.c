#include <string.h>
#include <stdio.h>
#include <math.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_event.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "driver/adc.h"
#include "esp_adc_cal.h"
#include <inttypes.h>

#define PIN_ANALOG_IN   4           // A10, ADC2_CHANNEL_0

#define DEFAULT_VREF    1100        //Default vref
#define NO_OF_SAMPLES   64          //Multisampling


adc_channel_t channel_x = ADC2_CHANNEL_1;      // ADC1:GPIO36, ADC2:GPIO4
adc_unit_t unit_x = ADC_UNIT_2;               // ADC2
adc_atten_t atten_x = ADC_ATTEN_DB_11;        // Full scale 0-3.9V, precision range 150mV-2450mV


adc_channel_t channel_y = ADC1_CHANNEL_7;      // ADC1:GPIO36, ADC2:GPIO4
adc_unit_t unit_y = ADC_UNIT_1;               // ADC2
adc_atten_t atten_y = ADC_ATTEN_DB_11;        // Full scale 0-3.9V, precision range 150mV-2450mV

static esp_adc_cal_characteristics_t adc1_chars_x;
static esp_adc_cal_characteristics_t adc1_chars_y;

static const char *TAG = "POC Joystick";


void app_main(void)
{

    ESP_ERROR_CHECK(adc2_config_channel_atten(channel_x, atten_x));
    esp_adc_cal_characterize(unit_x, atten_x, ADC_WIDTH_BIT_12, 0, &adc1_chars_x);

    ESP_ERROR_CHECK(adc1_config_channel_atten(channel_y, atten_y));
    esp_adc_cal_characterize(unit_y, atten_y, ADC_WIDTH_BIT_12, 0, &adc1_chars_y);

    while (1) 
    {

        int adc_reading_x = 0;
        adc2_get_raw((adc2_channel_t)channel_x, ADC_WIDTH_BIT_12, &adc_reading_x);
        int voltage_x = esp_adc_cal_raw_to_voltage(adc_reading_x, &adc1_chars_x);
        
        int adc_reading_y = 0;
        adc_reading_y =  adc1_get_raw((adc1_channel_t)channel_y);
        int voltage_y = esp_adc_cal_raw_to_voltage(adc_reading_y, &adc1_chars_y);

        float normalized_x = voltage_x / 1000;
        float normalized_y = voltage_y / 1000;

        ESP_LOGI(TAG, " (%.2f , %.2f) ", normalized_x , normalized_y);

        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }

}
