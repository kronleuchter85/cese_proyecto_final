#include <string.h>
#include <stdio.h>
#include <time.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "esp_system.h"
#include "esp_event.h"
#include "esp_log.h"
#include "nvs_flash.h"

#include "measuring_services.h"
#include "motors_service.h"


// 
// Motors configuration
// 
#define GPIO_MCPWM0_A_OUT 26   
#define GPIO_MCPWM0_B_OUT 27   
#define GPIO_MCPWM1_A_OUT 33   
#define GPIO_MCPWM1_B_OUT 25   


static const char *TAG = "temp_collector";

static void measuring_task(void *pvParameters) {
    
    if(measuring_services_init() != MEASURING_INITIALIZATION_SUCCESS)
        return;

    int16_t temperature = 0;
    int16_t humidity = 0;

    float temp2 , hum2, pressure;


    while(1) {

        if (measuring_service_get_temperature_and_humidity( &humidity, &temperature) == MEASURING_READING_SUCCESS) {
            ESP_LOGI(TAG,"Humidity: %d%% Temp: %dC\n", humidity / 10, temperature / 10);
            
        } else {
            ESP_LOGE(TAG,"Could not read data from sensor\n");
        }

        if (measuring_service_get_pressure( &pressure,  &temp2, &hum2) != MEASURING_READING_SUCCESS) {
            ESP_LOGI(TAG, "Temperature/pressure reading failed\n");
        } else {
            ESP_LOGI(TAG, "Pressure: %.2f Pa, Temperature: %.2f C", pressure, temp2);
        }    

        for(int countdown = 10; countdown >= 0; countdown--) {
            ESP_LOGI(TAG, "%d... ", countdown);
            vTaskDelay(1000 / portTICK_PERIOD_MS);
        }
        ESP_LOGI(TAG, "Starting again!");
    }
}



static void motors_task(void *arg) {

    float duty_cicle_counter = 30.0;

    motors_initialize(MCPWM_UNIT_0 , MCPWM_TIMER_0 , GPIO_MCPWM0_A_OUT , GPIO_MCPWM0_B_OUT);
    motors_initialize(MCPWM_UNIT_1 , MCPWM_TIMER_1 , GPIO_MCPWM1_A_OUT , GPIO_MCPWM1_B_OUT);

    while (1){

        if(duty_cicle_counter > 60.0)
        duty_cicle_counter = 30.0;

        printf("---------------------------------------------------\n");
        printf("duty_cycle = %.2f\n" , duty_cicle_counter);
        printf("---------------------------------------------------\n");
        
        printf("Forward ...\n");
        motors_forward(MCPWM_UNIT_0, MCPWM_TIMER_0, duty_cicle_counter);
        motors_forward(MCPWM_UNIT_1, MCPWM_TIMER_1, duty_cicle_counter);
        vTaskDelay(5000 / portTICK_RATE_MS);

        printf("Stop ...\n");
        motors_stop(MCPWM_UNIT_0, MCPWM_TIMER_0);
        motors_stop(MCPWM_UNIT_1, MCPWM_TIMER_1);
        vTaskDelay(2000 / portTICK_RATE_MS);
        
        printf("Backward ...\n");
        motors_backward(MCPWM_UNIT_0, MCPWM_TIMER_0, duty_cicle_counter);
        motors_backward(MCPWM_UNIT_1, MCPWM_TIMER_1, duty_cicle_counter);
        vTaskDelay(5000 / portTICK_RATE_MS);
        
        printf("Stop ...\n");
        motors_stop(MCPWM_UNIT_0, MCPWM_TIMER_0);
        motors_stop(MCPWM_UNIT_1, MCPWM_TIMER_1);
        vTaskDelay(2000 / portTICK_RATE_MS);
        
        duty_cicle_counter = duty_cicle_counter + 10.0;

        vTaskDelay(500 / portTICK_RATE_MS);
    }
}



void app_main(void)
{
    ESP_ERROR_CHECK( nvs_flash_init() );
    ESP_ERROR_CHECK(esp_event_loop_create_default());

    xTaskCreate(&motors_task, "motors_task", 4096, NULL, 5, NULL);
}
