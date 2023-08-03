#include <string.h>
#include <stdio.h>
#include <math.h>
#include <inttypes.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_event.h"
#include "esp_log.h"
#include "nvs_flash.h"

#include "joystick_service.h"


void joystick_task(void * args){

    joystick_initialize();

    while (1) {

        float normalized_x ;
        float normalized_y ;

        joystick_get_reading(&normalized_x , &normalized_y);

        ESP_LOGI("POC Joystick", " (%.2f , %.2f) ", normalized_x , normalized_y);

        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void app_main(void){

    ESP_ERROR_CHECK( nvs_flash_init() );
    ESP_ERROR_CHECK(esp_event_loop_create_default());

    xTaskCreate(&joystick_task, "joystick_task", 4096, NULL, 5, NULL);
}
