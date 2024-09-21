#include "unity.h"

#include <string.h>
#include "wifi_service.h"
#include "mock_esp_wifi.h"
#include "commons.h"


void test_wifi_service_init_access_point(){

    esp_netif_create_default_wifi_ap_Expect();

    wifi_init_config_t cfg;
    WIFI_INIT_CONFIG_DEFAULT_ExpectAndReturn(cfg);

    esp_wifi_init_ExpectAndReturn(&cfg , ESP_OK);
    ESP_ERROR_CHECK_Expect(ESP_OK);
    
    esp_event_handler_instance_register_IgnoreAndReturn( ESP_OK);
    ESP_ERROR_CHECK_Expect(ESP_OK);
    
    esp_wifi_set_mode_ExpectAndReturn(WIFI_MODE_AP , ESP_OK);
    ESP_ERROR_CHECK_Expect(ESP_OK);


    wifi_config_t wifi_config = {
        .ap = {
            .ssid = EXAMPLE_ESP_WIFI_SSID,
            .ssid_len = strlen(EXAMPLE_ESP_WIFI_SSID),
            .channel = EXAMPLE_ESP_WIFI_CHANNEL,
            .password = EXAMPLE_ESP_WIFI_PASS,
            .max_connection = EXAMPLE_MAX_STA_CONN,
            .authmode = WIFI_AUTH_WPA_WPA2_PSK
        },
    };
    esp_wifi_set_config_ExpectAndReturn(WIFI_IF_AP, &wifi_config , ESP_OK);
    ESP_ERROR_CHECK_Expect(ESP_OK);
    esp_wifi_start_ExpectAndReturn(ESP_OK);
    ESP_ERROR_CHECK_Expect(ESP_OK);
    wifi_service_init_access_point();
}


void test_wifi_event_handler_WIFI_EVENT_AP_STADISCONNECTED(){

    int arg1;
    esp_event_base_t event_base;
    int32_t event_id = WIFI_EVENT_AP_STADISCONNECTED;
    wifi_event_ap_stadisconnected_t data = { 
        .mac = {0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC}, 
        .aid = 1, 
        .is_mesh_child = false 
    };

    wifi_event_handler(&arg1, event_base , event_id, &data );
}

void test_wifi_event_handler_WIFI_EVENT_AP_STACONNECTED(){

    int arg1;
    esp_event_base_t event_base;
    int32_t event_id = WIFI_EVENT_AP_STACONNECTED;
    wifi_event_ap_staconnected_t sta_connected = { 
        .mac = {0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC}, 
        .aid = 1, 
        .is_mesh_child = false 
    };

    wifi_event_handler(&arg1, event_base , event_id, &sta_connected );
}

void test_wifi_event_handler_no_valid_event_id(){

    int arg1;
    esp_event_base_t event_base;
    int32_t event_id;
    char * data = "data";

    wifi_event_handler(&arg1, event_base , event_id, data );
}