# bluepill-base
Minimal CMake project for bluepill (STM32F10xx) development. Works with CLion on both Windows & Linux.

## Basic setup
### Required tools
* On Linux: install the arm-none-eabi-binutils, arm-none-eabi-gcc and arm-none-eabi-newlib packages
* On Windows: install the ARM GCC toolchain which can be found [here](https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm/downloads)

### Setting up the CMake project
**TODO: Windows: explain how to configure the toolchain root**

Simply change the name of the project in CMakeLists.txt (replace bluepill-base by whatever you want in the `project(...)` statement).
Add source and header files to the `SOURCE_FILES` list. Then, either import the CMakeLists.txt in CLion or build the project using

```
cmake .
make
```

The output bin file will `${PROJECT_NAME}.bin`.

### Wiring to the Arduino's serial to USB
The bluepill does not come with a serial to USB IC. You can either buy an FTDI chip or, if you have
an Arduino Uno around, you can use it like this:

* Remove the ATmega328P IC from the Arduino board
* Wire the bluepill's A10 pin (PA10 = RX1) to the Arduino's pin 0 (RX)
* Wire the bluepill's A9 pin (PA9 = TX1) to the Arduino's pin 1 (TX)
* Wire one of the bluepill's 3.3 pin to the Arduino's 3.3V pin
* Wire one of the bluepill's G pin to one of the Arduino's GND pin 

### Flashing via serial

* Compile [bluepill-flash](https://github.com/montoyo/bluepill-flash)
* On the bluepill board, move the BOOT0 jumper to 1 and the BOOT1 jumper to 0
* Connect the FTDI/Arduino to your computer
* (**TODO: explain how to find the correct serial port**)
* (**TODO: explain how grant access to the serial port on linux**)
* Hit the reset button
* Run `path/to/bluepill-flash -d /dev/ttyACM0 write path/to/bluepill-base.bin start`
* (If it does not work, try to reset the bluepill and run bluepill-flash again)

### CLion "Flash & run" configuration
TODO

## License
Most of the files in this project are copyright STMicroelectronics. The pinout diagram (Datasheets/Pinout.pdf)
was made by Rasmus Friis Kjeldsen (http://reblag.dk/stm32) and is licensed CC BY-SA. I don't care what you do
with my files (src/main.c as well as the CMakeLists.txt).
