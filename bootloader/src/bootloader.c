#include "common-defines.h"
#include <libopencm3/stm32/memorymap.h>

#define BOOTLOADER_SIZE (0x8000U)   // 32 KB bootloader size 
#define MAIN_APP_START_ADDRESS (FLASH_BASE + BOOTLOADER_SIZE)   // main application start address is set to the base address of the flash memory + size of the bootloader 

// now the pointer is at locatioon 0x0800_8000, which is the start of main firmware of flash memory 

const uint8_t data[0x8000] = {0};       // defining a constant array of 32 KB size, initialized to zero, this is used to fill the bootloader section of the flash memory with zeros, effectively erasing any previous data in that section   

static void jump_to_main(void) {            
    typedef void (*void_fn)(void);    // defining a function pointer type that points to a function that takes no arguments and retunrns void, this is used to call reset handler of main application 


    uint32_t* reset_vector_entry = (uint32_t*)(MAIN_APP_START_ADDRESS + 4U);    // reset vector is set to or pointed to the address of main application start address
    // why 4U - because each entry in the IVT is 4 bytes long, and reset vector is the second entry because 1st entry is the initial stack pointer value, which is located at start (0x0800_8000) and reset vector is at (0x0800_8004), 4 bytes after

    uint32_t* reset_vector = (uint32_t*)(*reset_vector_entry);    // dereferencing the reset vector entry to get the actual address of the reset handler of the main application
    // dereferening helps to access or modify the data stored at the memory location pointed by the pointer 

    void_fn jump_fn = (void_fn)reset_vector;     // casting the reset vector 

    jump_fn();           // 

}




int main (void) {
    // Defines an un-optimizable loop where an 8-bit counter 'i' (max 255) can never reach 0x8000, creating an infinite loop.
    // Due to 'volatile' and the code bloat of this endless loop, the compiled text size overflows the small bootloader ROM boundary.
    // gives the error = bootloader.elf section `.text' will not fit in region `rom'
    /*
    volatile uint8_t x = 0;
    for (uint8_t i = 0; i < 0x8000; i++) {
        x =+ data[i];
    }
    */




    jump_to_main();   
    
    

    // Never return 
    return 0;
}