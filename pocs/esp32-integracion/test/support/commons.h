#ifndef __COMMONS_H__
#define __COMMONS_H__

#include "stdlib.h"
#include "stdio.h"
typedef int gpio_num_t;

typedef enum{
        ESP_OK , ESP_FAIL
} esp_err_t;


// #define ESP_LOGI( tag, format, ... ) printf(format , __VA_OPT__(,) __VA_ARGS__)
#define ESP_LOGI(tag, format, ...) printf(format, ##__VA_ARGS__)


#endif
