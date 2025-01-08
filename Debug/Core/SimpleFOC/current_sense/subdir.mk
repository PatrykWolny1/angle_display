################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Core/SimpleFOC/current_sense/GenericCurrentSense.cpp \
../Core/SimpleFOC/current_sense/InlineCurrentSense.cpp \
../Core/SimpleFOC/current_sense/LowsideCurrentSense.cpp 

OBJS += \
./Core/SimpleFOC/current_sense/GenericCurrentSense.o \
./Core/SimpleFOC/current_sense/InlineCurrentSense.o \
./Core/SimpleFOC/current_sense/LowsideCurrentSense.o 

CPP_DEPS += \
./Core/SimpleFOC/current_sense/GenericCurrentSense.d \
./Core/SimpleFOC/current_sense/InlineCurrentSense.d \
./Core/SimpleFOC/current_sense/LowsideCurrentSense.d 


# Each subdirectory must supply rules for building sources it contributes
Core/SimpleFOC/current_sense/%.o Core/SimpleFOC/current_sense/%.su Core/SimpleFOC/current_sense/%.cyclo: ../Core/SimpleFOC/current_sense/%.cpp Core/SimpleFOC/current_sense/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m3 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -DSTM32_THREAD_SAFE_STRATEGY=4 -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3 -I../Core/ThreadSafe -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-SimpleFOC-2f-current_sense

clean-Core-2f-SimpleFOC-2f-current_sense:
	-$(RM) ./Core/SimpleFOC/current_sense/GenericCurrentSense.cyclo ./Core/SimpleFOC/current_sense/GenericCurrentSense.d ./Core/SimpleFOC/current_sense/GenericCurrentSense.o ./Core/SimpleFOC/current_sense/GenericCurrentSense.su ./Core/SimpleFOC/current_sense/InlineCurrentSense.cyclo ./Core/SimpleFOC/current_sense/InlineCurrentSense.d ./Core/SimpleFOC/current_sense/InlineCurrentSense.o ./Core/SimpleFOC/current_sense/InlineCurrentSense.su ./Core/SimpleFOC/current_sense/LowsideCurrentSense.cyclo ./Core/SimpleFOC/current_sense/LowsideCurrentSense.d ./Core/SimpleFOC/current_sense/LowsideCurrentSense.o ./Core/SimpleFOC/current_sense/LowsideCurrentSense.su

.PHONY: clean-Core-2f-SimpleFOC-2f-current_sense

