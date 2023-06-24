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

void app_main(void)
{
    ESP_ERROR_CHECK( nvs_flash_init() );
    ESP_ERROR_CHECK(esp_event_loop_create_default());

    xTaskCreate(&measuring_task, "measuring_task", 4096, NULL, 5, NULL);
}
