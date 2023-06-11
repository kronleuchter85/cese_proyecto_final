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


adc_channel_t channel_x = ADC2_CHANNEL_1;      // GPIO 0
adc_unit_t unit_x = ADC_UNIT_2;               // ADC2
adc_atten_t atten_x = ADC_ATTEN_DB_11;        // Full scale 0-3.9V, precision range 150mV-2450mV


adc_channel_t channel_y = ADC1_CHANNEL_7;      // GPIO 35
adc_unit_t unit_y = ADC_UNIT_1;               // ADC2
adc_atten_t atten_y = ADC_ATTEN_DB_11;        // Full scale 0-3.9V, precision range 150mV-2450mV

static esp_adc_cal_characteristics_t adc1_chars_x;
static esp_adc_cal_characteristics_t adc1_chars_y;

static const char *TAG = "POC Joystick";

float MAX_Y = 0.0;
float MIN_Y = 3.0;
float MAX_X = 3.0;
float MIN_X = 0.0;
float REST_X_Y = 2.0;

void dc_motors_stop(float normalized_x , float normalized_y){
    ESP_LOGI(TAG, " STOP (%.2f , %.2f) ", normalized_x , normalized_y);
}
void dc_motors_move_forward(float normalized_x , float normalized_y){
    ESP_LOGI(TAG, " MOVE_FORWARD (%.2f , %.2f) ", normalized_x , normalized_y);
}
void dc_motors_move_backward(float normalized_x , float normalized_y){
    ESP_LOGI(TAG, " MOVE_BACKWAWRD (%.2f , %.2f) ", normalized_x , normalized_y);
}
void dc_motors_rotate_left(float normalized_x , float normalized_y){
    ESP_LOGI(TAG, " ROTATE_LEFT (%.2f , %.2f) ", normalized_x , normalized_y);
}
void dc_motors_rotate_right(float normalized_x , float normalized_y){
    ESP_LOGI(TAG, " ROTATE_RIGHT (%.2f , %.2f) ", normalized_x , normalized_y);
}

typedef enum  {
    REST,
    MOVE_FORWARD,
    MOVE_BACKWAWRD,
    ROTATE_RIGHT,
    ROTATE_LEFT
} MOTION_STATUS;

MOTION_STATUS current_status =  REST;

MOTION_STATUS evaluate_control(float x , float y){
   
        // se permanece at rest
        if(x == REST_X_Y && y == REST_X_Y){
            return REST;
        }

        // baja X -> rotar a la izquierda
        //
        else if(x == MIN_X && y == REST_X_Y){
            return ROTATE_LEFT;
        }
        
        // sube X -> rotar a la derecha
        //
        else if(x == MAX_X && y == REST_X_Y){
            return ROTATE_RIGHT;
        }
        
        // sube Y -> hacia adelante
        //
        else if(y == MAX_Y && x == REST_X_Y){
            return MOVE_FORWARD;
        }
        
        // baja Y -> hacia atras
        //
        else if(y == MIN_Y && x == REST_X_Y){
            return MOVE_BACKWAWRD;
        }
        
        // Si (x != REST_X_Y && y != REST_X_Y) -> accion indefinida
        //
        else
            
            return REST;
}

void evaluate_state(float normalized_x , float normalized_y){

    MOTION_STATUS new_status = evaluate_control(normalized_x,normalized_y);

    switch(current_status){

        case REST:
            
            dc_motors_stop(normalized_x,normalized_y);

            if(new_status != current_status ){
                current_status = new_status;
            }
            break;

        case MOVE_FORWARD:

            dc_motors_move_forward(normalized_x,normalized_y);

            break;

        case MOVE_BACKWAWRD:

            dc_motors_move_backward(normalized_x,normalized_y);

            break;
        
        case ROTATE_LEFT:

            dc_motors_rotate_left(normalized_x,normalized_y);

            break;
        
        case ROTATE_RIGHT:
            
            dc_motors_rotate_right(normalized_x,normalized_y);
            
            break;
        
        default:
            break;
    }

    if(new_status != current_status ){
        current_status = REST;
    }

}


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
        
        // ESP_LOGI(TAG, " (%i , %i) ", adc_reading_x , adc_reading_y);
        // ESP_LOGI(TAG, " (%i , %i) ", voltage_x , voltage_y);
        
        float normalized_x = voltage_x / 1000;
        float normalized_y = voltage_y / 1000;

        //ESP_LOGI(TAG, " (%.2f , %.2f) ", normalized_x , normalized_y);

        evaluate_state(normalized_x , normalized_y);

        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }

}
