#include "measuring_services.h"
#include <string.h>
#include <stdio.h>
#include "dht.h"
#include "bmp280.h"

#define DHT_GPIO 2
#define BMP_SDA_GPIO 18
#define BMP_SCL_GPIO 19

//
// DHT11 consts
//

static const gpio_num_t dht_gpio = DHT_GPIO;
static const dht_sensor_type_t sensor_type = DHT_TYPE_DHT11;

//
// BMP280
//
bmp280_params_t params;
bmp280_t dev;

t_measuring_status measuring_services_init(void){

    //
    // inicializacion de modulos
    //

    if(bmp280_init_default_params(&params) != ESP_OK){
        return MEASURING_INITIALIZATION_ERROR;
    }

    memset(&dev, 0, sizeof(bmp280_t));
    if(bmp280_init_desc(&dev, BMP280_I2C_ADDRESS_0, 0, BMP_SDA_GPIO, BMP_SCL_GPIO) != ESP_OK ){
        return MEASURING_INITIALIZATION_ERROR;
    }
    if(bmp280_init(&dev, &params)!= ESP_OK){
        return MEASURING_INITIALIZATION_ERROR;
    }

    return MEASURING_INITIALIZATION_SUCCESS;
}


t_measuring_status measuring_service_get_temperature_and_humidity(int16_t * h, int16_t * t){

    int16_t temperature = 0;
    int16_t humidity = 0;

    if(dht_read_data(sensor_type, dht_gpio, &humidity, &temperature) == ESP_OK){
        *h = humidity;
        *t = temperature;

        return MEASURING_READING_SUCCESS;
    }else{
        *h = -1;
        *t = -1;

        return MEASURING_READING_ERROR;
    }
}

t_measuring_status measuring_service_get_pressure( float * p,float * t,float * h){

    float pressure =0, temperature =0, humidity =0;

    if(bmp280_read_float(&dev, &temperature, &pressure, &humidity) == ESP_OK){
        *h = humidity;
        *t = temperature;
        *p = pressure;
        return MEASURING_READING_SUCCESS;
    }else{
        *h = -1;
        *t = -1;
        *p = -1;
        return MEASURING_READING_ERROR;
    }
}

