################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Core/SimpleFOC/current_sense/hardware_specific/stm32/stm32f4/stm32f4_hal.cpp \
../Core/SimpleFOC/current_sense/hardware_specific/stm32/stm32f4/stm32f4_mcu.cpp \
../Core/SimpleFOC/current_sense/hardware_specific/stm32/stm32f4/stm32f4_utils.cpp 

OBJS += \
./Core/SimpleFOC/current_sense/hardware_specific/stm32/stm32f4/stm32f4_hal.o \
./Core/SimpleFOC/current_sense/hardware_specific/stm32/stm32f4/stm32f4_mcu.o \
./Core/SimpleFOC/current_sense/hardware_specific/stm32/stm32f4/stm32f4_utils.o 

CPP_DEPS += \
./Core/SimpleFOC/current_sense/hardware_specific/stm32/stm32f4/stm32f4_hal.d \
./Core/SimpleFOC/current_sense/hardware_specific/stm32/stm32f4/stm32f4_mcu.d \
./Core/SimpleFOC/current_sense/hardware_specific/stm32/stm32f4/stm32f4_utils.d 


# Each subdirectory must supply rules for building sources it contributes
Core/SimpleFOC/current_sense/hardware_specific/stm32/stm32f4/%.o Core/SimpleFOC/current_sense/hardware_specific/stm32/stm32f4/%.su Core/SimpleFOC/current_sense/hardware_specific/stm32/stm32f4/%.cyclo: ../Core/SimpleFOC/current_sense/hardware_specific/stm32/stm32f4/%.cpp Core/SimpleFOC/current_sense/hardware_specific/stm32/stm32f4/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m3 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -DSTM32_THREAD_SAFE_STRATEGY=4 -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3 -I../Core/ThreadSafe -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-SimpleFOC-2f-current_sense-2f-hardware_specific-2f-stm32-2f-stm32f4

clean-Core-2f-SimpleFOC-2f-current_sense-2f-hardware_specific-2f-stm32-2f-stm32f4:
	-$(RM) ./Core/SimpleFOC/current_sense/hardware_specific/stm32/stm32f4/stm32f4_hal.cyclo ./Core/SimpleFOC/current_sense/hardware_specific/stm32/stm32f4/stm32f4_hal.d ./Core/SimpleFOC/current_sense/hardware_specific/stm32/stm32f4/stm32f4_hal.o ./Core/SimpleFOC/current_sense/hardware_specific/stm32/stm32f4/stm32f4_hal.su ./Core/SimpleFOC/current_sense/hardware_specific/stm32/stm32f4/stm32f4_mcu.cyclo ./Core/SimpleFOC/current_sense/hardware_specific/stm32/stm32f4/stm32f4_mcu.d ./Core/SimpleFOC/current_sense/hardware_specific/stm32/stm32f4/stm32f4_mcu.o ./Core/SimpleFOC/current_sense/hardware_specific/stm32/stm32f4/stm32f4_mcu.su ./Core/SimpleFOC/current_sense/hardware_specific/stm32/stm32f4/stm32f4_utils.cyclo ./Core/SimpleFOC/current_sense/hardware_specific/stm32/stm32f4/stm32f4_utils.d ./Core/SimpleFOC/current_sense/hardware_specific/stm32/stm32f4/stm32f4_utils.o ./Core/SimpleFOC/current_sense/hardware_specific/stm32/stm32f4/stm32f4_utils.su

.PHONY: clean-Core-2f-SimpleFOC-2f-current_sense-2f-hardware_specific-2f-stm32-2f-stm32f4

