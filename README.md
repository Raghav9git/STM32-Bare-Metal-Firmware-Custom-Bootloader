# STM32 Bare-Metal Firmware & Custom Bootloader

This project is a hands-on study of bare-metal firmware development on an STM32F4 Cortex-M4 microcontroller. It covers the firmware build process, memory layout, startup sequence, peripheral configuration, timer/PWM generation, linker scripts, vector tables, and the basic structure of a custom bootloader.

The project is developed using the ARM GNU toolchain, GNU Make, libopencm3, MSYS2, and VS Code. The firmware is written in C with a small amount of ARM assembly used during the application image construction.

The current stage focuses on understanding and implementing the bootloader-to-application execution flow. Firmware update over a communication interface and firmware authentication are not implemented yet.

## Current Status

### Work in progress.

The current implementation includes:

```text
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
```

Firmware update, UART/USB transfer, firmware validation, and secure firmware authentication are not implemented yet.

The project is written for an STM32F4 Cortex-M4 target.

The current memory configuration used by the linker scripts is:

```text
Flash:
Base address : 0x08000000
Size         : 512 KB
```

The clock configuration used by the application is 84 MHz.

## Memory Layout

The current Flash configuration uses 512 KB of Flash and 96 KB of SRAM.

Flash

```text
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

`0x08008000`

## Development Environment

The project uses the following tools:

```text
ARM GNU Toolchain
GNU Make
MSYS2 UCRT64
libopencm3
GNU GDB
OpenOCD
VS Code
Cortex-Debug
J-Link / ST-Link for debugging
```

### STM32 Hardware

The project uses the **STM32 NUCLEO-F401RE** development board, featuring an STM32F401RE microcontroller with an ARM Cortex-M4 core.

The board integrates an onboard ST-LINK/V2-1 debugger/programmer, so a separate J-Link or external ST-LINK debugger is not required for the current setup.

The board is connected to the laptop using a USB-A-to-Mini-B USB 2.0 data cable plugged into the ST-LINK USB connector (CN1).

### ST-LINK Driver Installation

The ST-LINK USB driver was downloaded from the official STMicroelectronics website:

https://www.st.com/en/development-tools/stsw-link009.html

The downloaded package was extracted, and the `dpinst_amd64` installer was used to install the driver on Windows.

After installation, the board was reconnected to the laptop. Windows Device Manager recognised the device as `ST-LINK Debug` under Universal Serial Bus devices, and its device status confirmed that it was working properly.

### VS Code and MSYS2 Setup

The development environment is configured on Windows using Visual Studio Code and the MSYS2 UCRT64 terminal.

The ARM GNU Toolchain and GNU Make are used to compile the firmware. OpenOCD provides the interface between the development environment and the onboard ST-LINK debugger.

The board is powered through the USB connection, which also provides the programming and debugging interface.

### OpenOCD Installation

OpenOCD was installed through the MSYS2 UCRT64 package manager:

```bash
pacman -S mingw-w64-ucrt-x86_64-openocd
```

The installation was verified using:

```bash
openocd --version
```

The installed version is OpenOCD 0.12.0.

### Verifying the STM32 Connection

With the NUCLEO-F401RE connected to the laptop, the following command was executed in the MSYS2 UCRT64 terminal:

```bash
openocd -f interface/stlink.cfg -f target/stm32f4x.cfg
```

OpenOCD successfully detected the onboard ST-LINK debugger and the STM32 target.

The connection log confirmed:

* ST-LINK V2 detected.
* Target voltage detected.
* ARM Cortex-M4 processor detected.
* GDB server started and listening on port `3333`.

This verifies communication between the laptop, onboard ST-LINK debugger, and STM32 microcontroller.


## libopencm3

The project uses libopencm3 as a low-level hardware abstraction library for STM32 and ARM Cortex-M devices.

It is included as a Git submodule:

`libopencm3/`

The submodule is configured in `.gitmodules`.

The library provides interfaces used by the project for:

```text
Reset and Clock Control
GPIO
SysTick
Timers
Cortex-M system control
Vector table handling
```

## Build

Initialize the libopencm3 submodule:

```bash
git submodule update --init --recursive
```

Build libopencm3:

```bash
cd libopencm3
make
cd ..
```

Build the bootloader:

```bash
cd bootloader
make
cd ..
```

Build the application:

```bash
cd app
make
```

The application build currently requires further verification because a compilation error was encountered while resolving the `scb.h` header include path.

## Future Work

Planned extensions include:

```text
Firmware update over UART/USB
Flash programming from the bootloader
Firmware integrity verification
Firmware authentication and secure boot
Improved boot decision and recovery mechanisms
```

Additional development tasks include:

```text
Resolve the current application compilation error
Complete firmware flashing through ST-LINK and OpenOCD
Configure VS Code debugging
Verify firmware execution on the physical STM32 board
Capture and document GPIO, timer, and PWM hardware results
```

This repository represents the current development stage of the project.
