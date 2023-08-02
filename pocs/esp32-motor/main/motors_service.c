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

#define GPIO_PWM0A_OUT 26   //15 // Set GPIO 15 as PWM0A
#define GPIO_PWM0B_OUT 27   //16 // Set GPIO 16 as PWM0B

float duty_cicle_counter = 30.0;

static void mcpwm_example_gpio_initialize(mcpwm_unit_t unit_to_use , mcpwm_timer_t timer_to_use , int gpio_pin_A , int gpio_pin_b){

  // 1. mcpwm gpio initialization
  printf("initializing mcpwm gpio...\n");
  mcpwm_gpio_init(unit_to_use, MCPWM0A, gpio_pin_A);
  mcpwm_gpio_init(unit_to_use, MCPWM0B, gpio_pin_b);

  // 2. initial mcpwm configuration
  printf("Configuring Initial Parameters of mcpwm...\n");
  mcpwm_config_t pwm_config;
  pwm_config.frequency = 1000; // frequency = 500Hz,
  pwm_config.cmpr_a = 0;       // duty cycle of PWMxA = 0
  pwm_config.cmpr_b = 0;       // duty cycle of PWMxb = 0
  pwm_config.counter_mode = MCPWM_UP_COUNTER;
  pwm_config.duty_mode = MCPWM_DUTY_MODE_0;
  mcpwm_init(unit_to_use, timer_to_use, &pwm_config); // Configure PWM0A & PWM0B with above settings
}

static void brushed_motor_forward(mcpwm_unit_t mcpwm_num, mcpwm_timer_t timer_num, float duty_cycle)
{
  mcpwm_set_signal_low(mcpwm_num, timer_num, MCPWM_OPR_B);
  mcpwm_set_duty(mcpwm_num, timer_num, MCPWM_OPR_A, duty_cycle);
  mcpwm_set_duty_type(mcpwm_num, timer_num, MCPWM_OPR_A, MCPWM_DUTY_MODE_0); // call this each time, if operator was previously in low/high state
}

static void brushed_motor_backward(mcpwm_unit_t mcpwm_num, mcpwm_timer_t timer_num, float duty_cycle)
{
  mcpwm_set_signal_low(mcpwm_num, timer_num, MCPWM_OPR_A);
  mcpwm_set_duty(mcpwm_num, timer_num, MCPWM_OPR_B, duty_cycle);
  mcpwm_set_duty_type(mcpwm_num, timer_num, MCPWM_OPR_B, MCPWM_DUTY_MODE_0); // call this each time, if operator was previously in low/high state
}

static void brushed_motor_stop(mcpwm_unit_t mcpwm_num, mcpwm_timer_t timer_num)
{
  mcpwm_set_signal_low(mcpwm_num, timer_num, MCPWM_OPR_A);
  mcpwm_set_signal_low(mcpwm_num, timer_num, MCPWM_OPR_B);
}

static void mcpwm_example_brushed_motor_control(void *arg)
{
  mcpwm_example_gpio_initialize(MCPWM_UNIT_0 , MCPWM_TIMER_0 , GPIO_PWM0A_OUT , GPIO_PWM0B_OUT);

  while (1){

    if(duty_cicle_counter > 60.0)
      duty_cicle_counter = 30.0;

    printf("---------------------------------------------------\n");
    printf("duty_cycle = %.2f\n" , duty_cicle_counter);
    printf("---------------------------------------------------\n");
    printf("Forward ...\n");
    brushed_motor_forward(MCPWM_UNIT_0, MCPWM_TIMER_0, duty_cicle_counter);
    vTaskDelay(5000 / portTICK_RATE_MS);

    printf("Stop ...\n");
    brushed_motor_stop(MCPWM_UNIT_0, MCPWM_TIMER_0);
    vTaskDelay(2000 / portTICK_RATE_MS);
    
    printf("Backward ...\n");
    brushed_motor_backward(MCPWM_UNIT_0, MCPWM_TIMER_0, duty_cicle_counter);
    vTaskDelay(5000 / portTICK_RATE_MS);
    
    printf("Stop ...\n");
    brushed_motor_stop(MCPWM_UNIT_0, MCPWM_TIMER_0);
    vTaskDelay(2000 / portTICK_RATE_MS);
    
    duty_cicle_counter = duty_cicle_counter + 10.0;

    vTaskDelay(500 / portTICK_RATE_MS);
  }
}

void app_main(void)
{
  printf("Testing brushed motor...\n");
  xTaskCreate(mcpwm_example_brushed_motor_control, "mcpwm_example_brushed_motor_control", 4096, NULL, 5, NULL);
}