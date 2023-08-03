#include <stdio.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_attr.h"

#include "driver/mcpwm.h"
#include "soc/mcpwm_periph.h"

#define GPIO_DIR_1 26//15 // Set GPIO 15 as PWM0A
#define GPIO_DIR_2 27//16 // Set GPIO 16 as PWM0B

int buttonState = 0;


/**
 * @brief Configure MCPWM module for brushed dc motor
 */
static void motor_example_2(void *arg)
{

  gpio_set_direction(GPIO_DIR_1, GPIO_MODE_OUTPUT);
  gpio_set_direction(GPIO_DIR_2, GPIO_MODE_OUTPUT);

  while (1)
  {


      gpio_set_level(GPIO_DIR_1,1);
      gpio_set_level(GPIO_DIR_2,0);
      vTaskDelay(2000 / portTICK_RATE_MS);

      gpio_set_level(GPIO_DIR_1,0);
      gpio_set_level(GPIO_DIR_2,0);
      vTaskDelay(2000 / portTICK_RATE_MS);
     
      gpio_set_level(GPIO_DIR_1,0);
      gpio_set_level(GPIO_DIR_2,1);
      vTaskDelay(2000 / portTICK_RATE_MS);


      gpio_set_level(GPIO_DIR_1,0);
      gpio_set_level(GPIO_DIR_2,0);
      vTaskDelay(2000 / portTICK_RATE_MS);


  }
}

void app_main(void)
{
  printf("Testing brushed motor...\n");
  xTaskCreate(motor_example_2, "motor_example_2", 4096, NULL, 5, NULL);
}