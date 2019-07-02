# bluepill-base
Minimal CMake project for bluepill (STM32F10xx) development. Works with CLion on both Windows & Linux.

## Basic setup
### Required tools
* On Linux: install the cmake, arm-none-eabi-binutils, arm-none-eabi-gcc and arm-none-eabi-newlib packages
* On Windows:
    - You will need MinGW, which can be found [here](https://sourceforge.net/projects/mingw-w64/)
    - Install the ARM GCC toolchain, which can be found [here](https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm/downloads)
    - If you're not going to use CLion, you will also need [CMake](https://cmake.org/download/#latest)
    - Otherwise, if you're going to use CLion, don't forget to add MinGW as a toolchain

### Setting up the CLion project
* Launch CLion, and create a new project by importing `CMakeLists.txt`
* Go to File \> Settings \> Build, Execution, Deployment \> CMake and in "CMake Options" put `-DCMAKE_TOOLCHAIN_FILE=./arm-toolchain.cmake`
* Close the settings window
* Open the CMake window by clicking "CMake" at the bottom
* Hit the reload button on the top-left of the CMake window
* If you are on Windows, you're probably seeing errors and need to change the toolchain bin path. To do so, hit the CMake Cache File button (the one with the file and cog icon on the top-left). Look for the `ARM_GCC_BIN_DIR:PATH=/usr/bin` line and replace the path by the path to the bin folder where you installed arm-none-eabi-gcc. Then, hit the reload button again. Errors should be gone.
* For launch configuration, check out the "CLion Flash & Run configuration" section

### Wiring to the Arduino's serial to USB
The bluepill does not come with a serial to USB IC. You can either buy an FTDI chip or, if you have
an Arduino Uno around, you can use it like this:

* Remove the ATmega328P IC from the Arduino board
* Wire the bluepill's A10 pin (PA10 = RX1) to the Arduino's pin 0 (RX)
* Wire the bluepill's A9 pin (PA9 = TX1) to the Arduino's pin 1 (TX)
* Wire one of the bluepill's 3.3 pin to the Arduino's 3.3V pin
* Wire one of the bluepill's G pin to one of the Arduino's GND pin 

### Flashing via serial

* Compile [bluepill-flash](https://github.com/montoyo/bluepill-flash) or, if you're using Windows, download a compiled executable from [here](https://github.com/montoyo/bluepill-flash/releases)
* On the bluepill board, move the BOOT0 jumper to 1 and the BOOT1 jumper to 0
* Connect the FTDI/Arduino to your computer
* (**TODO: explain how to find the correct serial port**)
* (**TODO: explain how grant access to the serial port on linux**)
* Hit the reset button
* Run `path/to/bluepill-flash -d {SERIAL_PORT} write path/to/{PROJECT_NAME}.bin start` (don't forget to replace the values between brackets)
* (If it does not work, try to reset the bluepill and run bluepill-flash again)

### CLion Flash & Run configuration
This section explains how to configure CLion to do exactly what is done in the "Flashing via serial" section whenever the
"Run" button is clicked:

* On the upper right, expand the launch configuration list, and choose "Edit Configurations"
* Change the executable by the bluepill-flash executable
* Set the program arguments to "-d {SERIAL_PORT} write {PROJECT_NAME}.bin start" (don't forget to replace the values between brackets)
* Set the working directory to the cmake-build-debug directory
* Hit OK, and you're good to go!

## License
Most of the files in this project are copyright STMicroelectronics. The pinout diagram (Datasheets/Pinout.pdf)
was made by Rasmus Friis Kjeldsen (http://reblag.dk/stm32) and is licensed CC BY-SA. I don't care what you do
with my files (src/main.c as well as the CMakeLists.txt).
