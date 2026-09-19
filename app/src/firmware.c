// This code will tell the processor to tell the gpio to turn led pin on and off in a loop

#include <libopencm3/stm32/rcc.h>    // for clock control, rcc = reset and clok control 
#include <libopencm3/stm32/gpio.h>   // for gpio control 
#include <libopencm3/stm32/cm3/scb.h>  // 

#include <core/system.h>             // for system setup and systick timer control
#include <core/timer.h>              // for timer setup and pwm control

#define BOOTLOADER_SIZE (0x8000U)

#define LED_PORT (GPIOA)
#define LED_PIN (GPIO5)

static void vector_setup(void) {
    SCB_VTOR = BOOTLOADER_SIZE;
}


/* static void gpio_setup(void) {
    rcc_periph_clock_enable(RCC_GPIOA);                            // turning on all, off by default clk peripherals 
    gpio_mode_setup(LED_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, LED_PIN);    // setting up GPIO pin 5 of port A as an output pin with no pull-up or pull-down resistors
} */

// for pwm 
static void gpio_setup(void) {
    rcc_periph_clock_enable(RCC_GPIOA);                            // turning on all, off by default clk peripherals 
    gpio_mode_setup(LED_PORT, GPIO_MODE_AF, GPIO_PUPD_NONE, LED_PIN);    
    gpio_set_af(LED_PORT, GPIO_AF1, LED_PIN);                      // setting up GPIO pin 5 of port A as an alternate function pin with no pull-up or pull-down resistors and assigning it to alternate function 1 (AF1) for timer 2 channel 1 output

}


int main (void) {
    vetor_setup();
    system_setup();
    gpio_setup();
    timer_setup();        // setup timer 2 to generate a PWM signal on gpio pin 5 of port A with a freq 1 khz and a duty cycle of 50%

        
   uint64_t start_time = system_get_ticks();  // start time is set to the current value of the ticks variable 
   float duty_cycle = 0.0f;                   // duty cycle is set to 0% initially 

   timer_pwm_set_duty_cycle(duty_cycle);        // setting the duty cycle of the PWM signal to 0% initially

    /* while (1) {                                     // represents infinite loop to keep the program running , keep the cpu running as long it is on
        if (system_get_ticks() - start_time >= 100) {     // check if 1000 milliseconds (1 second) have passed since the last time the LED was toggled
            gpio_toggle(LED_PORT, LED_PIN);
            start_time = system_get_ticks();                // update the start time to the current value of the ticks variable
        } */

// for pwm manipulation 

while (1) {                                     // represents infinite loop to keep the program running , keep the cpu running as long it is on
        if (system_get_ticks() - start_time >= 10) {     
            duty_cycle += 1.0f;                 // increment the duty cycle by 1% every 10 milliseconds
            if (duty_cycle > 100.0f) {          
                duty_cycle = 0.0f;              // reset the duty cycle to 0% when it reaches 100%
            }
            timer_pwm_set_duty_cycle(duty_cycle);        // setting the duty cycle of the PWM signal to the updated value
                    
        } 

        

    }

    // Never return
    return 0;
}