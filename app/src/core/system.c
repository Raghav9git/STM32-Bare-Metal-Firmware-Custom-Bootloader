#include <core/system.h>
#include <libopencm3/cm3/systick.h>  // for systick timer control, systick is a timer that can be used to generate periodic interrupts 
#include <libopencm3/cm3/vector.h>   // for vector table control, vector table is a table that contains the addresses of the interrupt service routines (ISRs) for the different interrupts that can occur in the system
#include <libopencm3/stm32/rcc.h>    // for clock control, rcc = reset and clok control 

static volatile uint64_t  ticks = 0;  // 64 bit is used instead of 32 bit to avoid overflow, as 32 bit will overflow after 49 days, while 64 bit will overflow after 584 billion years, which is more than enough for our counting needs. 

void sys_tick_handler(void) {
    ticks++;  // increment the ticks variable every time the systick interrupt occurs, this will be used to keep track of the number of milliseconds that have passed since the program started running
}

static void rcc_setup(void) {
    rcc_clock_setup_pll(&rcc_hsi_configs[RCC_CLOCK_3V3_84MHZ]);    // setting up clk to 84 MHz using hsi - high speed internal oscillator 
}

static void systick_setup(void) {
    systick_set_frequency(SYSTICK_FREQ , CPU_FREQ);              // setting up systick timer to generate interrupts at a frequency of 1000 Hz (1 ms interval) based on the CPU frequency of 84 MHz
    systick_counter_enable();
    systick_interrupt_enable();

}


uint64_t system_get_ticks(void) {
    return ticks;  // return the current value of the ticks variable, which represents the number of milliseconds that have passed since the program started running
}

void system_setup(void) {
    rcc_setup();          // setting up the rcc to use the hsi as the clock source and set the clock frequency to 84 MHz   
    systick_setup();      //setting up the systick timer to generate interrupts at a frequency of 1000 Hz (1 ms interval) based on the CPU frequency of 84 MHz

}


