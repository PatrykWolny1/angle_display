################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Core/SimpleFOC/common/foc_utils.cpp \
../Core/SimpleFOC/common/lowpass_filter.cpp \
../Core/SimpleFOC/common/pid.cpp \
../Core/SimpleFOC/common/time_utils.cpp 

OBJS += \
./Core/SimpleFOC/common/foc_utils.o \
./Core/SimpleFOC/common/lowpass_filter.o \
./Core/SimpleFOC/common/pid.o \
./Core/SimpleFOC/common/time_utils.o 

CPP_DEPS += \
./Core/SimpleFOC/common/foc_utils.d \
./Core/SimpleFOC/common/lowpass_filter.d \
./Core/SimpleFOC/common/pid.d \
./Core/SimpleFOC/common/time_utils.d 


# Each subdirectory must supply rules for building sources it contributes
Core/SimpleFOC/common/%.o Core/SimpleFOC/common/%.su Core/SimpleFOC/common/%.cyclo: ../Core/SimpleFOC/common/%.cpp Core/SimpleFOC/common/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m3 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -DSTM32_THREAD_SAFE_STRATEGY=4 -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3 -I../Core/ThreadSafe -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-SimpleFOC-2f-common

clean-Core-2f-SimpleFOC-2f-common:
	-$(RM) ./Core/SimpleFOC/common/foc_utils.cyclo ./Core/SimpleFOC/common/foc_utils.d ./Core/SimpleFOC/common/foc_utils.o ./Core/SimpleFOC/common/foc_utils.su ./Core/SimpleFOC/common/lowpass_filter.cyclo ./Core/SimpleFOC/common/lowpass_filter.d ./Core/SimpleFOC/common/lowpass_filter.o ./Core/SimpleFOC/common/lowpass_filter.su ./Core/SimpleFOC/common/pid.cyclo ./Core/SimpleFOC/common/pid.d ./Core/SimpleFOC/common/pid.o ./Core/SimpleFOC/common/pid.su ./Core/SimpleFOC/common/time_utils.cyclo ./Core/SimpleFOC/common/time_utils.d ./Core/SimpleFOC/common/time_utils.o ./Core/SimpleFOC/common/time_utils.su

.PHONY: clean-Core-2f-SimpleFOC-2f-common

