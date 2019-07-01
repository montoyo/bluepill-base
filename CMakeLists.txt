cmake_minimum_required(VERSION 3.8)

# Project name goes here
project(bluepill-base C ASM)

# Add files to SOURCE_FILES
include_directories(${CMAKE_SOURCE_DIR}/include)
set(SOURCE_FILES include/core_cm3.h include/stm32f10x.h include/system_stm32f10x.h src/core_cm3.c src/system_stm32f10x.c src/main.c startup.s)
set(LINK_SCRIPT ${CMAKE_SOURCE_DIR}/stm32f.ld)

# Compiler settings
set(CMAKE_ASM_COMPILER arm-none-eabi-gcc)
set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_SYSTEM_PROCESSOR arm)
set(CMAKE_AR arm-none-eabi-ar)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -T ${LINK_SCRIPT}")
set(CMAKE_C_FLAGS "-ffreestanding -nostdlib -mthumb -mcpu=cortex-m3")
set(CMAKE_C_IMPLICIT_LINK_LIBRARIES "")
set(CMAKE_C_IMPLICIT_LINK_DIRECTORIES "")
set_target_properties(${TARGET_NAME} PROPERTIES LINK_DEPENDS ${LINK_SCRIPT})

add_executable(${PROJECT_NAME}.elf ${SOURCE_FILES})
add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD COMMAND arm-none-eabi-objcopy -O binary ${PROJECT_NAME}.elf ${PROJECT_NAME}.bin)

