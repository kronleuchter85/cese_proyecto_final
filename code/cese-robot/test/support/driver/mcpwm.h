#ifndef __MOTORS__
#define __MOTORS__

#include "commons.h"
#include "stdint.h"

#define MCPWM_OPR_A     MCPWM_GEN_A         ///< @deprecated
#define MCPWM_OPR_B     MCPWM_GEN_B         ///< @deprecated
#define MCPWM_OPR_MAX   MCPWM_GEN_MAX       ///< @deprecated

typedef enum {
    MCPWM_UNIT_0,   /*!<MCPWM unit0 selected*/
    MCPWM_UNIT_1,   /*!<MCPWM unit1 selected*/
    MCPWM_UNIT_MAX, /*!<Max number of MCPWM units*/
} mcpwm_unit_t;

typedef enum {
    MCPWM_TIMER_0,   /*!<Select MCPWM timer0*/
    MCPWM_TIMER_1,   /*!<Select MCPWM timer1*/
    MCPWM_TIMER_2,   /*!<Select MCPWM timer2*/
    MCPWM_TIMER_MAX, /*!<Max number of timers in a unit*/
} mcpwm_timer_t;

typedef enum {
    MCPWM_DUTY_MODE_0 = 0, /*!<Active high duty, i.e. duty cycle proportional to high time for asymmetric MCPWM*/
    MCPWM_DUTY_MODE_1,     /*!<Active low duty,  i.e. duty cycle proportional to low  time for asymmetric MCPWM, out of phase(inverted) MCPWM*/
    MCPWM_HAL_GENERATOR_MODE_FORCE_LOW,
    MCPWM_HAL_GENERATOR_MODE_FORCE_HIGH,
    MCPWM_DUTY_MODE_MAX,   /*!<Num of duty cycle modes*/
} mcpwm_duty_type_t;

typedef enum {
    MCPWM_FREEZE_COUNTER,   /*!<Counter freeze */
    MCPWM_UP_COUNTER,       /*!<For asymmetric MCPWM*/
    MCPWM_DOWN_COUNTER,     /*!<For asymmetric MCPWM*/
    MCPWM_UP_DOWN_COUNTER,  /*!<For symmetric MCPWM, frequency is half of MCPWM frequency set*/
    MCPWM_COUNTER_MAX,      /*!<Maximum counter mode*/
} mcpwm_counter_type_t;


typedef struct {
    uint32_t frequency;              /*!<Set frequency of MCPWM in Hz*/
    float cmpr_a;                    /*!<Set % duty cycle for operator a(MCPWMXA), i.e for 62.3% duty cycle, duty_a = 62.3*/
    float cmpr_b;                    /*!<Set % duty cycle for operator b(MCPWMXB), i.e for 48% duty cycle, duty_b = 48.0*/
    mcpwm_duty_type_t duty_mode;     /*!<Set type of duty cycle*/
    mcpwm_counter_type_t counter_mode;  /*!<Set  type of MCPWM counter*/
} mcpwm_config_t;

typedef enum {
    MCPWM_GEN_A,   /*!<Select MCPWMXA, where 'X' is operator number*/
    MCPWM_GEN_B,   /*!<Select MCPWMXB, where 'X' is operator number*/
    MCPWM_GEN_MAX, /*!<Num of generators to each operator of MCPWM*/
} mcpwm_generator_t;

typedef enum {
    MCPWM0A = 0,        /*!<PWM0A output pin*/
    MCPWM0B,            /*!<PWM0B output pin*/
    MCPWM1A,            /*!<PWM1A output pin*/
    MCPWM1B,            /*!<PWM1B output pin*/
    MCPWM2A,            /*!<PWM2A output pin*/
    MCPWM2B,            /*!<PWM2B output pin*/
    MCPWM_SYNC_0,       /*!<SYNC0  input pin*/
    MCPWM_SYNC_1,       /*!<SYNC1  input pin*/
    MCPWM_SYNC_2,       /*!<SYNC2  input pin*/
    MCPWM_FAULT_0,      /*!<FAULT0 input pin*/
    MCPWM_FAULT_1,      /*!<FAULT1 input pin*/
    MCPWM_FAULT_2,      /*!<FAULT2 input pin*/
    MCPWM_CAP_0 = 84,   /*!<CAP0   input pin*/
    MCPWM_CAP_1,        /*!<CAP1   input pin*/
    MCPWM_CAP_2,        /*!<CAP2   input pin*/
} mcpwm_io_signals_t;

esp_err_t mcpwm_gpio_init(mcpwm_unit_t mcpwm_num, mcpwm_io_signals_t io_signal, int gpio_num);
esp_err_t mcpwm_init( mcpwm_unit_t mcpwm_num, mcpwm_timer_t timer_num, const mcpwm_config_t  *mcpwm_conf);
esp_err_t mcpwm_set_signal_low(mcpwm_unit_t mcpwm_num, mcpwm_timer_t timer_num, mcpwm_generator_t gen);
esp_err_t mcpwm_set_duty(mcpwm_unit_t mcpwm_num, mcpwm_timer_t timer_num, mcpwm_generator_t gen, float duty);
esp_err_t mcpwm_set_duty_type(mcpwm_unit_t mcpwm_num, mcpwm_timer_t timer_num, mcpwm_generator_t gen, mcpwm_duty_type_t duty_type);


#endif
