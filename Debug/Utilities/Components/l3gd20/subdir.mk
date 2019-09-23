################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Utilities/Components/l3gd20/l3gd20.c 

OBJS += \
./Utilities/Components/l3gd20/l3gd20.o 

C_DEPS += \
./Utilities/Components/l3gd20/l3gd20.d 


# Each subdirectory must supply rules for building sources it contributes
Utilities/Components/l3gd20/%.o: ../Utilities/Components/l3gd20/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DSTM32 -DSTM32F4 -DSTM32F407VGTx -DSTM32F407G_DISC1 -DDEBUG -DSTM32F407xx -DUSE_HAL_DRIVER -I"U:/personal/SystemWorkbench2.7/digitopoly/Utilities/Components/ili9325" -I"U:/personal/SystemWorkbench2.7/digitopoly/Utilities/Components/s25fl512s" -I"U:/personal/SystemWorkbench2.7/digitopoly/Utilities/Components/cs43l22" -I"U:/personal/SystemWorkbench2.7/digitopoly/Utilities/Components/ili9341" -I"U:/personal/SystemWorkbench2.7/digitopoly/Utilities/Components/ampire480272" -I"U:/personal/SystemWorkbench2.7/digitopoly/Utilities/Components/n25q512a" -I"U:/personal/SystemWorkbench2.7/digitopoly/Utilities/Components/s5k5cag" -I"U:/personal/SystemWorkbench2.7/digitopoly/Utilities/Components/mfxstm32l152" -I"U:/personal/SystemWorkbench2.7/digitopoly/CMSIS/device" -I"U:/personal/SystemWorkbench2.7/digitopoly/Utilities/Components/n25q128a" -I"U:/personal/SystemWorkbench2.7/digitopoly/Utilities/Components/ts3510" -I"U:/personal/SystemWorkbench2.7/digitopoly/Utilities/Components/st7735" -I"U:/personal/SystemWorkbench2.7/digitopoly/HAL_Driver/Inc/Legacy" -I"U:/personal/SystemWorkbench2.7/digitopoly/Utilities/Components/lis302dl" -I"U:/personal/SystemWorkbench2.7/digitopoly/Utilities/Components/otm8009a" -I"U:/personal/SystemWorkbench2.7/digitopoly/Utilities/Components/stmpe1600" -I"U:/personal/SystemWorkbench2.7/digitopoly/Utilities/Components/Common" -I"U:/personal/SystemWorkbench2.7/digitopoly/Utilities/Components/ov2640" -I"U:/personal/SystemWorkbench2.7/digitopoly/Utilities/Components/l3gd20" -I"U:/personal/SystemWorkbench2.7/digitopoly/HAL_Driver/Inc" -I"U:/personal/SystemWorkbench2.7/digitopoly/Utilities" -I"U:/personal/SystemWorkbench2.7/digitopoly/Utilities/Components/stmpe811" -I"U:/personal/SystemWorkbench2.7/digitopoly/Utilities/Components/lis3dsh" -I"U:/personal/SystemWorkbench2.7/digitopoly/Utilities/Components/wm8994" -I"U:/personal/SystemWorkbench2.7/digitopoly/Utilities/Components/n25q256a" -I"U:/personal/SystemWorkbench2.7/digitopoly/inc" -I"U:/personal/SystemWorkbench2.7/digitopoly/Utilities/Components/ls016b8uy" -I"U:/personal/SystemWorkbench2.7/digitopoly/Utilities/Components/ft6x06" -I"U:/personal/SystemWorkbench2.7/digitopoly/Utilities/STM32F4-Discovery" -I"U:/personal/SystemWorkbench2.7/digitopoly/Utilities/Components/exc7200" -I"U:/personal/SystemWorkbench2.7/digitopoly/Utilities/Components/st7789h2" -I"U:/personal/SystemWorkbench2.7/digitopoly/Utilities/Components/ampire640480" -I"U:/personal/SystemWorkbench2.7/digitopoly/Utilities/Components/lsm303dlhc" -I"U:/personal/SystemWorkbench2.7/digitopoly/CMSIS/core" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


