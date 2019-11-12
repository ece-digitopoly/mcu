################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/stm32f4xx_it.c \
../src/syscalls.c \
../src/system_stm32f4xx.c 

CPP_SRCS += \
../src/Profile.cpp \
../src/Property.cpp \
../src/Util.cpp \
../src/main.cpp \
../src/play.cpp \
../src/properties.cpp \
../src/raspi.cpp \
../src/rn4020.cpp 

OBJS += \
./src/Profile.o \
./src/Property.o \
./src/Util.o \
./src/main.o \
./src/play.o \
./src/properties.o \
./src/raspi.o \
./src/rn4020.o \
./src/stm32f4xx_it.o \
./src/syscalls.o \
./src/system_stm32f4xx.o 

C_DEPS += \
./src/stm32f4xx_it.d \
./src/syscalls.d \
./src/system_stm32f4xx.d 

CPP_DEPS += \
./src/Profile.d \
./src/Property.d \
./src/Util.d \
./src/main.d \
./src/play.d \
./src/properties.d \
./src/raspi.d \
./src/rn4020.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: MCU G++ Compiler'
	@echo $(PWD)
	arm-none-eabi-g++ -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DSTM32 -DSTM32F4 -DSTM32F407VGTx -DSTM32F407G_DISC1 -DDEBUG -DSTM32F407xx -DUSE_HAL_DRIVER -I"C:/Users/shankak/workspace/dice_test/Utilities/Components/ili9325" -I"C:/Users/shankak/workspace/dice_test/Utilities/Components/s25fl512s" -I"C:/Users/shankak/workspace/dice_test/Utilities/Components/cs43l22" -I"C:/Users/shankak/workspace/dice_test/Utilities/Components/ili9341" -I"C:/Users/shankak/workspace/dice_test/Utilities/Components/ampire480272" -I"C:/Users/shankak/workspace/dice_test/Utilities/Components/n25q512a" -I"C:/Users/shankak/workspace/dice_test/Utilities/Components/s5k5cag" -I"C:/Users/shankak/workspace/dice_test/Utilities/Components/mfxstm32l152" -I"C:/Users/shankak/workspace/dice_test/CMSIS/device" -I"C:/Users/shankak/workspace/dice_test/Utilities/Components/n25q128a" -I"C:/Users/shankak/workspace/dice_test/Utilities/Components/ts3510" -I"C:/Users/shankak/workspace/dice_test/Utilities/Components/st7735" -I"C:/Users/shankak/workspace/dice_test/HAL_Driver/Inc/Legacy" -I"C:/Users/shankak/workspace/dice_test/Utilities/Components/lis302dl" -I"C:/Users/shankak/workspace/dice_test/Utilities/Components/otm8009a" -I"C:/Users/shankak/workspace/dice_test/Utilities/Components/stmpe1600" -I"C:/Users/shankak/workspace/dice_test/Utilities/Components/Common" -I"C:/Users/shankak/workspace/dice_test/Utilities/Components/ov2640" -I"C:/Users/shankak/workspace/dice_test/Utilities/Components/l3gd20" -I"C:/Users/shankak/workspace/dice_test/HAL_Driver/Inc" -I"C:/Users/shankak/workspace/dice_test/Utilities" -I"C:/Users/shankak/workspace/dice_test/Utilities/Components/stmpe811" -I"C:/Users/shankak/workspace/dice_test/Utilities/Components/lis3dsh" -I"C:/Users/shankak/workspace/dice_test/Utilities/Components/wm8994" -I"C:/Users/shankak/workspace/dice_test/Utilities/Components/n25q256a" -I"C:/Users/shankak/workspace/dice_test/inc" -I"C:/Users/shankak/workspace/dice_test/Utilities/Components/ls016b8uy" -I"C:/Users/shankak/workspace/dice_test/Utilities/Components/ft6x06" -I"C:/Users/shankak/workspace/dice_test/Utilities/STM32F4-Discovery" -I"C:/Users/shankak/workspace/dice_test/Utilities/Components/exc7200" -I"C:/Users/shankak/workspace/dice_test/Utilities/Components/st7789h2" -I"C:/Users/shankak/workspace/dice_test/Utilities/Components/ampire640480" -I"C:/Users/shankak/workspace/dice_test/Utilities/Components/lsm303dlhc" -I"C:/Users/shankak/workspace/dice_test/CMSIS/core" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fno-exceptions -fno-rtti -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DSTM32 -DSTM32F4 -DSTM32F407VGTx -DSTM32F407G_DISC1 -DDEBUG -DSTM32F407xx -DUSE_HAL_DRIVER -I"C:/Users/shankak/workspace/dice_test/Utilities/Components/ili9325" -I"C:/Users/shankak/workspace/dice_test/Utilities/Components/s25fl512s" -I"C:/Users/shankak/workspace/dice_test/Utilities/Components/cs43l22" -I"C:/Users/shankak/workspace/dice_test/Utilities/Components/ili9341" -I"C:/Users/shankak/workspace/dice_test/Utilities/Components/ampire480272" -I"C:/Users/shankak/workspace/dice_test/Utilities/Components/n25q512a" -I"C:/Users/shankak/workspace/dice_test/Utilities/Components/s5k5cag" -I"C:/Users/shankak/workspace/dice_test/Utilities/Components/mfxstm32l152" -I"C:/Users/shankak/workspace/dice_test/CMSIS/device" -I"C:/Users/shankak/workspace/dice_test/Utilities/Components/n25q128a" -I"C:/Users/shankak/workspace/dice_test/Utilities/Components/ts3510" -I"C:/Users/shankak/workspace/dice_test/Utilities/Components/st7735" -I"C:/Users/shankak/workspace/dice_test/HAL_Driver/Inc/Legacy" -I"C:/Users/shankak/workspace/dice_test/Utilities/Components/lis302dl" -I"C:/Users/shankak/workspace/dice_test/Utilities/Components/otm8009a" -I"C:/Users/shankak/workspace/dice_test/Utilities/Components/stmpe1600" -I"C:/Users/shankak/workspace/dice_test/Utilities/Components/Common" -I"C:/Users/shankak/workspace/dice_test/Utilities/Components/ov2640" -I"C:/Users/shankak/workspace/dice_test/Utilities/Components/l3gd20" -I"C:/Users/shankak/workspace/dice_test/HAL_Driver/Inc" -I"C:/Users/shankak/workspace/dice_test/Utilities" -I"C:/Users/shankak/workspace/dice_test/Utilities/Components/stmpe811" -I"C:/Users/shankak/workspace/dice_test/Utilities/Components/lis3dsh" -I"C:/Users/shankak/workspace/dice_test/Utilities/Components/wm8994" -I"C:/Users/shankak/workspace/dice_test/Utilities/Components/n25q256a" -I"C:/Users/shankak/workspace/dice_test/inc" -I"C:/Users/shankak/workspace/dice_test/Utilities/Components/ls016b8uy" -I"C:/Users/shankak/workspace/dice_test/Utilities/Components/ft6x06" -I"C:/Users/shankak/workspace/dice_test/Utilities/STM32F4-Discovery" -I"C:/Users/shankak/workspace/dice_test/Utilities/Components/exc7200" -I"C:/Users/shankak/workspace/dice_test/Utilities/Components/st7789h2" -I"C:/Users/shankak/workspace/dice_test/Utilities/Components/ampire640480" -I"C:/Users/shankak/workspace/dice_test/Utilities/Components/lsm303dlhc" -I"C:/Users/shankak/workspace/dice_test/CMSIS/core" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


