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
#include "joystick_service.h"
#include "robot_position_state.h"
#include "measuring_state.h"

// UDP server headers
#include <sys/param.h>
#include "esp_wifi.h"
#include "esp_netif.h"
#include "protocol_examples_common.h"
#include "lwip/err.h"
#include "lwip/sockets.h"
#include "lwip/sys.h"
#include <lwip/netdb.h>
#include <bmp280.h>
#include "adc_service.h"
#include "display_service.h"


// 
// Motors configuration
// 

// left
#define GPIO_MCPWM0_A_OUT 26   
#define GPIO_MCPWM0_B_OUT 27   

// right
#define GPIO_MCPWM1_A_OUT 33   
#define GPIO_MCPWM1_B_OUT 25   


// UDP server conf
#define PORT 3333

static const char *payload = "Temp: 24.5 - Hum: 44 - Luz: 66 - Pres: 720";
static const char *payload2 = "%0.1f %0.1f %0.1f %0.1f";
// static const char *payload2 = "Temp: %0.1f - Hum: %0.1f - Luz: %0.1f - Pres: %0.1f";

static const char *TAG = "temp_collector";


//
// ---------------------------------------------------------------------------------------------------------
// Display
// ---------------------------------------------------------------------------------------------------------
//
static void display_task(void * args){

    display_service_init();

    char first_line[20];
    char second_line[20];

    while (true) {

        measuring_state_t state = measuring_state_get();

        sprintf(first_line, "Temp: %.1f C", state.temperature);
        sprintf(second_line, "Hume: %.1f %%", state.humidity);

        display_service_print(first_line , second_line);
        vTaskDelay(3000 / portTICK_RATE_MS);

        sprintf(first_line, "Pres: %.1f hPa", state.pressure);
        sprintf(second_line, "Lumi: %.1f %%", state.light);
        
        display_service_print(first_line , second_line);
        vTaskDelay(3000 / portTICK_RATE_MS);
    }
}

//
// ---------------------------------------------------------------------------------------------------------
// Measuring
// ---------------------------------------------------------------------------------------------------------
//
static void measuring_task(void *pvParameters) {

    // dht11
    int16_t temperature = 0;
    int16_t humidity = 0;
    
    //bmp280
    float temp2 , hum2, pressure;
    
    // photoresistor
    int light_reading = 0;
    int voltage = 0;
    int ligh_level = 0;

    if(measuring_services_init() != MEASURING_INITIALIZATION_SUCCESS)
        return;

    while(1) {

        if (measuring_service_get_temperature_and_humidity( &humidity, &temperature) == MEASURING_READING_SUCCESS) {
            measuring_state_set_humidity(humidity/10);
            measuring_state_set_temperature(temperature/ 10);
        } else {
            ESP_LOGE(TAG,"Could not read data from sensor\n");
        }

        if (measuring_service_get_pressure( &pressure,  &temp2, &hum2) != MEASURING_READING_SUCCESS) {
            ESP_LOGI(TAG, "Temperature/pressure reading failed\n");
        } else {

            measuring_state_set_pressure(pressure/100);
        }    

        if (measuring_service_get_light_level( &light_reading, &voltage , &ligh_level) != MEASURING_READING_SUCCESS) {
            ESP_LOGI(TAG, "Light reading failed\n");
        } else {
            measuring_state_set_light((float)ligh_level);
        }    

        ESP_LOGI(TAG, "BMP280_Pressure: %.2f Pa, BMP280_Temperature: %.2f C, DHT11_Temperature: %d C, DHT11_Humidity: %d %%, Light: %d %%"
            , pressure, temp2, temperature , humidity , ligh_level);

        measuring_state_t state = measuring_state_get();
        
        ESP_LOGI(TAG, "Pressure: %.2f Pa, Temperature: %.2f C, Humidity: %.2f %%, Light: %.2f %%"
            , state.pressure, state.temperature, state.humidity , state.light);

        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}


//
// ---------------------------------------------------------------------------------------------------------
// Joystick
// ---------------------------------------------------------------------------------------------------------
//
static void joystick_task(void * args){

    // joystick_initialize();

    int reading_x ;
    int reading_y ;

    while (1) {

        joystick_get_reading(&reading_x , &reading_y);

        robot_position_t action = robot_position_state_get_action_by_coordinates(reading_x , reading_y);

        robot_position_state_update(action);

        ESP_LOGI("POC Joystick - Reading", " (%d , %d) ", reading_x , reading_y);

        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}

//
// ---------------------------------------------------------------------------------------------------------
// Motors
// ---------------------------------------------------------------------------------------------------------
//
static void motors_task(void *arg) {

    float duty_cicle_counter = 40.0;

    motors_initialize(MCPWM_UNIT_0 , MCPWM_TIMER_0 , GPIO_MCPWM0_A_OUT , GPIO_MCPWM0_B_OUT);
    motors_initialize(MCPWM_UNIT_1 , MCPWM_TIMER_1 , GPIO_MCPWM1_A_OUT , GPIO_MCPWM1_B_OUT);
    
    bool at_rest = false;
    
    while (1){

        if(duty_cicle_counter > 60.0)
            duty_cicle_counter = 40.0;

        // printf("---------------------------------------------------\n");
        // printf("duty_cycle = %.2f\n" , duty_cicle_counter);
        // printf("---------------------------------------------------\n");
        
        robot_position_t state = robot_position_state_get();
        
        switch (state)
        {
            case MOVING_FORWARD:
                // printf("MOVING_FORWARD ...\n");
                motors_forward(MCPWM_UNIT_0, MCPWM_TIMER_0, duty_cicle_counter);
                motors_forward(MCPWM_UNIT_1, MCPWM_TIMER_1, duty_cicle_counter);
                at_rest = false;
                break;
            case MOVING_BACKWARD:
                // printf("MOVING_BACKWARD ...\n");
                motors_backward(MCPWM_UNIT_0, MCPWM_TIMER_0, duty_cicle_counter);
                motors_backward(MCPWM_UNIT_1, MCPWM_TIMER_1, duty_cicle_counter);
                at_rest = false;
                break;
            case ROTATE_LEFT:
                // printf("ROTATE_LEFT ...\n");
                motors_forward(MCPWM_UNIT_0, MCPWM_TIMER_0, duty_cicle_counter);
                motors_backward(MCPWM_UNIT_1, MCPWM_TIMER_1, duty_cicle_counter);
                at_rest = false;
                break;
            case ROTATE_RIGHT:
                // printf("ROTATE_RIGHT ...\n");
                motors_backward(MCPWM_UNIT_0, MCPWM_TIMER_0, duty_cicle_counter);
                motors_forward(MCPWM_UNIT_1, MCPWM_TIMER_1, duty_cicle_counter);
                at_rest = false;
                break;
            default:
                // printf("default ...\n");
                if(!at_rest){
                    motors_stop(MCPWM_UNIT_0, MCPWM_TIMER_0);
                    motors_stop(MCPWM_UNIT_1, MCPWM_TIMER_1);
                }
                at_rest = true;
                break;
        }

        // duty_cicle_counter = duty_cicle_counter + 10.0;

        vTaskDelay(100 / portTICK_RATE_MS);
    }
}

//
// ---------------------------------------------------------------------------------------------------------
// UDP Server
// ---------------------------------------------------------------------------------------------------------
//

static void udp_server_task(void * pvParameters){
    bool logging = (bool)pvParameters;

    char body[256];

    char rx_buffer[128];
    char addr_str[128];
    int addr_family = AF_INET;
    int ip_protocol = 0;
    struct sockaddr_in6 dest_addr;

    while (1) {

        struct sockaddr_in *dest_addr_ip4 = (struct sockaddr_in *)&dest_addr;
        dest_addr_ip4->sin_addr.s_addr = htonl(INADDR_ANY);
        dest_addr_ip4->sin_family = AF_INET;
        dest_addr_ip4->sin_port = htons(PORT);
        ip_protocol = IPPROTO_IP;

        int sock = socket(addr_family, SOCK_DGRAM, ip_protocol);
        if (sock < 0) {
            ESP_LOGE(TAG, "Unable to create socket: errno %d", errno);
            break;
        }
        ESP_LOGI(TAG, "Socket created");


        // Set timeout
        struct timeval timeout;
        timeout.tv_sec = 10; 
        timeout.tv_usec = 0;
        setsockopt (sock, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof timeout);

        int err = bind(sock, (struct sockaddr *)&dest_addr, sizeof(dest_addr));
        if (err < 0) {
            ESP_LOGE(TAG, "Socket unable to bind: errno %d", errno);
        }
        ESP_LOGI(TAG, "Socket bound, port %d", PORT);

        struct sockaddr_storage source_addr; // Large enough for both IPv4 or IPv6
        socklen_t socklen = sizeof(source_addr);


        while (1) {
            int len = recvfrom(sock, rx_buffer, sizeof(rx_buffer) - 1, 0, (struct sockaddr *)&source_addr, &socklen);
            if (len < 0) {
                ESP_LOGE(TAG, "recvfrom failed: errno %d", errno);
                // break;
            }
            // Data received
            else {

                // procesamos el comando recibido

                if (source_addr.ss_family == PF_INET) {
                    inet_ntoa_r(((struct sockaddr_in *)&source_addr)->sin_addr, addr_str, sizeof(addr_str) - 1);
                } 

                rx_buffer[len] = 0;
                ESP_LOGI(TAG, "Received %d bytes from %s:%d - [%s]", len, addr_str , PORT , rx_buffer);
                
                //
                // actualizamos el estado del robot
                //
                robot_position_t action = robot_position_state_get_action_by_name(rx_buffer);
                robot_position_state_update(action);

            }

            measuring_state_t state = measuring_state_get();

            sprintf(body, payload2, state.temperature  , state.humidity , state.light , state.pressure );
            ESP_LOGI(TAG, "Sending status %s", body);

            int err = sendto(sock, body, strlen(body), 0, (struct sockaddr *)&source_addr, sizeof(source_addr));
            if (err < 0) {
                ESP_LOGE(TAG, "Error occurred during sending: errno %d", errno);
                break;
            }

            vTaskDelay(100 / portTICK_PERIOD_MS);

        }

        if (sock != -1) {
            ESP_LOGE(TAG, "Shutting down socket and restarting...");
            shutdown(sock, 0);
            close(sock);
        }
    }
    vTaskDelete(NULL);
}


void app_main(void){

    ESP_ERROR_CHECK( nvs_flash_init() );
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    
    // UDP server - wifi init
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(example_connect());

    // I2C init
    //
    ESP_ERROR_CHECK(i2cdev_init());
    
    adc_service_initialize();



    //
    // task del motor
    //
    xTaskCreate(motors_task, "motors_task", 4096, (void*)true , 5, NULL);

    //
    // task del joystick
    //
    // xTaskCreate(joystick_task, "joystick_task", 4096, (void*)true , 5, NULL);

    //
    // task UDP server
    //
    xTaskCreate(udp_server_task, "udp_server", 4096, (void*)true , 5, NULL);
    
    //
    // measuring task
    //
    xTaskCreate(measuring_task, "measuring_task", 4096, (void*)true , 5, NULL);
    

    //
    // display task
    //
    // xTaskCreate(display_task, "display_task", 4096, (void*)true , 5, NULL);

}
