#include "unity.h"

// #include "motors_service.h"

#include "mock_dht.h"
#include "mock_bmp280.h"
#include "mock_adc_service.h"
// #include "mock_esp_log.h"
#include "commons.h"

extern bmp280_params_t params;
extern bmp280_t dev;



void test_motors_service_initialize_Success(){
    // bmp280_init_default_params_ExpectAndReturn(&params , ESP_OK);
    // bmp280_init_desc_ExpectAndReturn(&dev , BMP280_I2C_ADDRESS_0 , 0 , 18 , 19 , ESP_OK);
    // bmp280_init_ExpectAndReturn(&dev , &params , ESP_OK);
    // int8_t innitializationResult = measuring_services_init();
    // TEST_ASSERT_EQUAL(0,innitializationResult);
}


void test_motors_service_initialize_Error(){

}



void test_motors_service_motors_backward(){
    
}

void test_motors_service_motors_stop(){

}