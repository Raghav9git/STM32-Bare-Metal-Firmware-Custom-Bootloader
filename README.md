# STM32 Bare-Metal Firmware & Custom Bootloader

This project is a hands-on study of bare-metal firmware development on an STM32F4 Cortex-M4 microcontroller. It covers the firmware build process, memory layout, startup sequence, peripheral configuration, timer/PWM generation, linker scripts, vector tables, and the basic structure of a custom bootloader.

The project is developed using the ARM GNU toolchain, GNU Make, libopencm3, MSYS2, and VS Code. The firmware is written in C with a small amount of ARM assembly used during the application image construction.

The current stage focuses on understanding and implementing the bootloader-to-application execution flow. Firmware update over a communication interface and firmware authentication are not implemented yet.

## Current Status

### Work in progress.

The current implementation includes:

Bare-metal STM32F4 firmware
Custom bootloader and application separation
32 KB bootloader memory region
Custom linker scripts
Bootloader binary generation and padding
Bootloader inclusion in the application image
Application reset-vector lookup
Bootloader-to-application jump
Cortex-M vector table handling
RCC and clock configuration
SysTick-based timing
GPIO alternate-function configuration
TIM2 configuration
PWM generation with variable duty cycle

Firmware update, UART/USB transfer, firmware validation, and secure firmware authentication are not implemented yet.

The project is written for an STM32F4 Cortex-M4 target.

The current memory configuration used by the linker scripts is:

Flash:
Base address : 0x08000000
Size         : 512 KB
The clock configuration used by the application is 84 MHz.

## Memory Layout

The current Flash configuration uses 512 KB of Flash and 96 KB of SRAM.

Flash
```
0x08000000
+---------------------------+
| Bootloader                |
| 32 KB                     |
+---------------------------+
0x08008000
| Main Application          |
|                           |
| Remaining Flash           |
+---------------------------+
```
The application therefore starts at:

0x08008000

## Development Environment

The project uses the following tools:

ARM GNU Toolchain
GNU Make
MSYS2 UCRT64
libopencm3
GNU GDB
OpenOCD
VS Code
Cortex-Debug
J-Link / ST-Link for debugging

libopencm3

The project uses libopencm3 as a low-level hardware abstraction library for STM32 and ARM Cortex-M devices.

It is included as a Git submodule:

## libopencm3/

The submodule is configured in .gitmodules.

The library provides interfaces used by the project for:

Reset and Clock Control
GPIO
SysTick
Timers
Cortex-M system control
Vector table handling

## Build

Initialize the libopencm3 submodule:

git submodule update --init --recursive

Build libopencm3:

cd libopencm3
make
cd ..

Build the bootloader:

cd bootloader
make
cd ..

Build the application:

cd app
make

## Future Work

Planned extensions include:

Firmware update over UART/USB
Flash programming from the bootloader
Firmware integrity verification
Firmware authentication and secure boot
Improved boot decision and recovery mechanisms

This repository represents the current development stage of the project.

