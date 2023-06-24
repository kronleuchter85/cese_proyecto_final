#include "unity.h"

#include "measuring_services.h"

#include "mock_dht.h"
#include "mock_bmp280.h"

extern bmp280_params_t params;
extern bmp280_t dev;

void test_measuring_services_init_Success(){
    bmp280_init_default_params_ExpectAndReturn(&params , ESP_OK);
    bmp280_init_desc_ExpectAndReturn(&dev , BMP280_I2C_ADDRESS_0 , 0 , BMP_SDA_GPIO , BMP_SCL_GPIO , ESP_OK);
    bmp280_init_ExpectAndReturn(&dev , &params , ESP_OK);
    int8_t innitializationResult = measuring_services_init();
    TEST_ASSERT_EQUAL(0,innitializationResult);
}

void test_measuring_services_init_Error(){
    bmp280_init_default_params_ExpectAndReturn(&params , ESP_OK);
    bmp280_init_desc_ExpectAndReturn(&dev , BMP280_I2C_ADDRESS_0 , 0 , BMP_SDA_GPIO , BMP_SCL_GPIO , ESP_FAIL);
    int8_t innitializationResult = measuring_services_init();
    TEST_ASSERT_EQUAL(-1,innitializationResult);
}

void test_get_measures_temperature_and_humidity_successfully(){
    int16_t temperature = 0;
    int16_t humidity = 0;
    gpio_num_t dht_gpio = 2;
    dht_sensor_type_t sensor_type = DHT_TYPE_DHT11;
    int16_t expected_temperature = 5;
    int16_t expected_humidity = 4;
    dht_read_data_ExpectAndReturn(sensor_type ,dht_gpio , &humidity , &temperature, ESP_OK);
    dht_read_data_ReturnThruPtr_humidity(&expected_humidity);
    dht_read_data_ReturnThruPtr_temperature(&expected_temperature);
    measuring_service_get_temperature_and_humidity(&humidity , &temperature);
    TEST_ASSERT_EQUAL(expected_temperature , temperature);
    TEST_ASSERT_EQUAL(expected_humidity , humidity);
}

void test_get_measures_temperature_and_humidity_with_errors(){
    int16_t temperature = 0;
    int16_t humidity = 0;
    gpio_num_t dht_gpio = 2;
    dht_sensor_type_t sensor_type = DHT_TYPE_DHT11;
    int16_t read_temperature = 5;
    int16_t read_humidity = 4;
    
    //
    // como se espera que la lectura sea erronea el flujo de ejecucion deberia cambiar 
    //
    dht_read_data_ExpectAndReturn(sensor_type ,dht_gpio , &humidity , &temperature, ESP_FAIL);
    dht_read_data_ReturnThruPtr_humidity(&read_temperature);
    dht_read_data_ReturnThruPtr_temperature(&read_humidity);
    measuring_service_get_temperature_and_humidity(&humidity , &temperature);
    
    //
    // al cambiar el flujo de ejecucion se obtiene que los valores leidos son -1 
    //
    TEST_ASSERT_EQUAL(-1 , temperature);
    TEST_ASSERT_EQUAL(-1 , humidity);
}


void test_get_measures_pressure_Success(){
    float pressure =0;
    float temperature =0;
    float humidity =0;
    float expected_pressure = 3;
    float expected_temperature = 5;
    float expected_humidity = 4;
    bmp280_read_float_ExpectAndReturn(&dev , &temperature , &pressure , &humidity, ESP_OK);
    bmp280_read_float_ReturnThruPtr_temperature(&expected_temperature);
    bmp280_read_float_ReturnThruPtr_pressure(&expected_pressure);
    bmp280_read_float_ReturnThruPtr_humidity(&expected_humidity);
    measuring_service_get_pressure(&pressure ,  &temperature , &humidity );
    TEST_ASSERT_EQUAL(expected_temperature , temperature);
    TEST_ASSERT_EQUAL(expected_humidity , humidity);
    TEST_ASSERT_EQUAL(expected_pressure , pressure);
}

void test_get_measures_pressure_Error(){
    float pressure =0;
    float temperature =0;
    float humidity =0;
    float expected_pressure = -1;
    float expected_temperature = -1;
    float expected_humidity = -1;
    float read_pressure = 3;
    float read_temperature = 5;
    float read_humidity = 4;
    bmp280_read_float_ExpectAndReturn(&dev , &temperature , &pressure , &humidity,ESP_FAIL);
    bmp280_read_float_ReturnThruPtr_temperature(&read_temperature);
    bmp280_read_float_ReturnThruPtr_pressure(&read_pressure);
    bmp280_read_float_ReturnThruPtr_humidity(&read_humidity);
    measuring_service_get_pressure(&pressure ,  &temperature , &humidity );
    TEST_ASSERT_EQUAL(expected_temperature , temperature);
    TEST_ASSERT_EQUAL(expected_humidity , humidity);
    TEST_ASSERT_EQUAL(expected_pressure , pressure);

}

