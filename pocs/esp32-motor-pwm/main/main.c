//
// del tutorial: https://esp32tutorials.com/esp32-dc-motor-l289n-esp-idf/
//

#include <stdio.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_attr.h"

#include "driver/mcpwm.h"
#include "soc/mcpwm_periph.h"


#include "motors_service.h"


#define GPIO_MCPWM0_A_OUT 26   //15 // Set GPIO 15 as PWM0A
#define GPIO_MCPWM0_B_OUT 27   //16 // Set GPIO 16 as PWM0B
#define GPIO_MCPWM1_A_OUT 33   //15 // Set GPIO 15 as PWM0A
#define GPIO_MCPWM1_B_OUT 25   //16 // Set GPIO 16 as PWM0B

float duty_cicle_counter = 30.0;

void motors_task(void *arg) {

  float duty_cicle_counter = 30.0;

  motors_initialize(MCPWM_UNIT_0 , MCPWM_TIMER_0 , GPIO_MCPWM0_A_OUT , GPIO_MCPWM0_B_OUT);
  motors_initialize(MCPWM_UNIT_1 , MCPWM_TIMER_1 , GPIO_MCPWM1_A_OUT , GPIO_MCPWM1_B_OUT);

  while (1){

      if(duty_cicle_counter > 60.0)
        duty_cicle_counter = 30.0;

      printf("---------------------------------------------------\n");
      printf("duty_cycle = %.2f\n" , duty_cicle_counter);
      printf("---------------------------------------------------\n");
      
      printf("MOVING_FORWARD ...\n");
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
  printf("Testing brushed motor...\n");
  xTaskCreate(motors_task, "motors_task", 4096, NULL, 5, NULL);
}