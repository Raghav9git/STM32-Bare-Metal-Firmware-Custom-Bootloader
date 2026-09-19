#include "core/timer.h"
#include <libopencm3/stm32/timer.h>  // for timer control
#include <libopencm3/stm32/rcc.h>    // for reset and clock control

// 84_000_000 Hz

#define PRESCALER (84)
#define ARR_VALUE (1000) 

// freq = system_freq / ((prescaler - 1) * (arr - 1))



void timer_setup(void) {
    rcc_periph_clock_enable(RCC_TIM2);    // working with timer 2, enabling the clock for timer 2 

    // High level timer configuration 
    timer_set_mode(TIM2, TIM_CR1_CKD_CK_INT, TIM_CR1_CMS_EDGE, TIM_CR1_DIR_UP);   // setting the mode of timer 2 to count up in edge aligned mode with no clock division

    // setup pwm mode 
    timer_set_oc_mode(TIM2, TIM_OC1, TIM_OCM_PWM1);   // setting the output compare mode of timer 2 channel 1 to PWM mode 1 
    
    // Enabling PWM output and starting the timer 
    timer_enable_counter(TIM2);    // enabling the counter for timer 2 to start counting

    timer_enable_oc_output(TIM2, TIM_OC1);   // enabling the output compare for timer 2 channel 1 to allow the PWM signal to be output on the corresponding pin 

    // Frequency and resolution setup
    timer_set_prescaler(TIM2, PRESCALER);
    timer_set_period(TIM2, ARR_VALUE - 1);    // setting period of timer 2 to arr_value - 1 to achieve the desired frequency of the PWM signal
}


void timer_pwm_set_duty_cycle(float duty_cycle) {
    // duty cycle = (ccr / arr) * 100
    // ccr = arr * (duty_cyclle / 100)

    const float raw_value = (float)ARR_VALUE * (duty_cycle / 100.0f);    
    timer_set_oc_value(TIM2, TIM_OC1, (uint32_t)raw_value);    // setting output capture value for timer 2 channel 1 to achieve the desired duty cycle of the PWM signal

}