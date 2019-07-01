set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_VERSION 1)
set(CMAKE_SYSTEM_PROCESSOR arm)

# Compiler path
set(ARM_GCC_BIN_DIR "/usr/bin" CACHE PATH "Directory that contains arm-none-eabi-gcc")

if(WIN32)
    # We need this otherwise CMake refuses to use our compiler
    set(ARM_GCC_POSTFIX ".exe")
else()
    set(ARM_GCC_POSTFIX "")
endif()

set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")
set(CMAKE_C_COMPILER "${ARM_GCC_BIN_DIR}/arm-none-eabi-gcc${ARM_GCC_POSTFIX}")
set(CMAKE_ASM_COMPILER "${ARM_GCC_BIN_DIR}/arm-none-eabi-gcc${ARM_GCC_POSTFIX}")
set(CMAKE_AR "${ARM_GCC_BIN_DIR}/arm-none-eabi-ar${ARM_GCC_POSTFIX}")
