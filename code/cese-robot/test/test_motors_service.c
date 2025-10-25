#include "unity.h"

#include "mock_mcpwm.h"
#include "motors_service.h"

#include "commons.h"


void test_motors_service_initialize_MCPWM_UNIT_0(){

    mcpwm_unit_t unit_to_use = MCPWM_UNIT_0;
    mcpwm_timer_t timer_to_use = MCPWM_TIMER_0;
    int gpio_pin_A = 26;
    int gpio_pin_b = 27;

    mcpwm_gpio_init_ExpectAndReturn(unit_to_use, MCPWM0A, gpio_pin_A,ESP_OK);
    mcpwm_gpio_init_ExpectAndReturn(unit_to_use, MCPWM0B, gpio_pin_b,ESP_OK);

    mcpwm_config_t pwm_config;
    pwm_config.frequency = 1000; // frequency = 500Hz,
    pwm_config.cmpr_a = 0;       // duty cycle of PWMxA = 0
    pwm_config.cmpr_b = 0;       // duty cycle of PWMxb = 0
    pwm_config.counter_mode = MCPWM_UP_COUNTER;
    pwm_config.duty_mode = MCPWM_DUTY_MODE_0;
    mcpwm_init_ExpectAndReturn(unit_to_use, timer_to_use, &pwm_config,ESP_OK);

    motors_initialize(unit_to_use , timer_to_use , gpio_pin_A , gpio_pin_b);
}

void test_motors_service_initialize_MCPWM_UNIT_1(){
    mcpwm_unit_t unit_to_use = MCPWM_UNIT_1;
    mcpwm_timer_t timer_to_use = MCPWM_TIMER_0;
    int gpio_pin_A = 26;
    int gpio_pin_b = 27;

    mcpwm_gpio_init_ExpectAndReturn(unit_to_use, MCPWM1A, gpio_pin_A,ESP_OK);
    mcpwm_gpio_init_ExpectAndReturn(unit_to_use, MCPWM1B, gpio_pin_b,ESP_OK);

    mcpwm_config_t pwm_config;
    pwm_config.frequency = 1000; // frequency = 500Hz,
    pwm_config.cmpr_a = 0;       // duty cycle of PWMxA = 0
    pwm_config.cmpr_b = 0;       // duty cycle of PWMxb = 0
    pwm_config.counter_mode = MCPWM_UP_COUNTER;
    pwm_config.duty_mode = MCPWM_DUTY_MODE_0;
    mcpwm_init_ExpectAndReturn(unit_to_use, timer_to_use, &pwm_config,ESP_OK);


    motors_initialize(unit_to_use , timer_to_use , gpio_pin_A , gpio_pin_b);
}

void test_motors_service_motors_forward(){
    mcpwm_unit_t mcpwm_num = MCPWM_UNIT_0; 
    mcpwm_timer_t timer_num = MCPWM_TIMER_0; 
    float duty_cycle = 30;

    mcpwm_set_signal_low_ExpectAndReturn(mcpwm_num, timer_num, MCPWM_OPR_B , ESP_OK);
    mcpwm_set_duty_ExpectAndReturn(mcpwm_num, timer_num, MCPWM_OPR_A, duty_cycle, ESP_OK);
    mcpwm_set_duty_type_ExpectAndReturn(mcpwm_num, timer_num, MCPWM_OPR_A, MCPWM_DUTY_MODE_0, ESP_OK);

    motors_forward( mcpwm_num,  timer_num,  duty_cycle);
    
}
void test_motors_service_motors_backward(){
    mcpwm_unit_t mcpwm_num = MCPWM_UNIT_0; 
    mcpwm_timer_t timer_num = MCPWM_TIMER_0; 
    float duty_cycle = 30;

    mcpwm_set_signal_low_ExpectAndReturn(mcpwm_num, timer_num, MCPWM_OPR_A , ESP_OK);
    mcpwm_set_duty_ExpectAndReturn(mcpwm_num, timer_num, MCPWM_OPR_B, duty_cycle, ESP_OK);
    mcpwm_set_duty_type_ExpectAndReturn(mcpwm_num, timer_num, MCPWM_OPR_B, MCPWM_DUTY_MODE_0, ESP_OK);

    motors_backward( mcpwm_num,  timer_num,  duty_cycle);
}

void test_motors_service_motors_stop(){
    mcpwm_unit_t mcpwm_num = MCPWM_UNIT_0; 
    mcpwm_timer_t timer_num = MCPWM_TIMER_0; 
    float duty_cycle = 30;

    mcpwm_set_signal_low_ExpectAndReturn(mcpwm_num, timer_num, MCPWM_OPR_A , ESP_OK);
    mcpwm_set_signal_low_ExpectAndReturn(mcpwm_num, timer_num, MCPWM_OPR_B , ESP_OK);

    motors_stop( mcpwm_num,  timer_num);
}