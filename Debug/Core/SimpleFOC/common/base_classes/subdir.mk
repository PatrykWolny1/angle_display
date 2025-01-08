################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Core/SimpleFOC/common/base_classes/CurrentSense.cpp \
../Core/SimpleFOC/common/base_classes/FOCMotor.cpp \
../Core/SimpleFOC/common/base_classes/Sensor.cpp 

OBJS += \
./Core/SimpleFOC/common/base_classes/CurrentSense.o \
./Core/SimpleFOC/common/base_classes/FOCMotor.o \
./Core/SimpleFOC/common/base_classes/Sensor.o 

CPP_DEPS += \
./Core/SimpleFOC/common/base_classes/CurrentSense.d \
./Core/SimpleFOC/common/base_classes/FOCMotor.d \
./Core/SimpleFOC/common/base_classes/Sensor.d 


# Each subdirectory must supply rules for building sources it contributes
Core/SimpleFOC/common/base_classes/%.o Core/SimpleFOC/common/base_classes/%.su Core/SimpleFOC/common/base_classes/%.cyclo: ../Core/SimpleFOC/common/base_classes/%.cpp Core/SimpleFOC/common/base_classes/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m3 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -DSTM32_THREAD_SAFE_STRATEGY=4 -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3 -I../Core/ThreadSafe -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-SimpleFOC-2f-common-2f-base_classes

clean-Core-2f-SimpleFOC-2f-common-2f-base_classes:
	-$(RM) ./Core/SimpleFOC/common/base_classes/CurrentSense.cyclo ./Core/SimpleFOC/common/base_classes/CurrentSense.d ./Core/SimpleFOC/common/base_classes/CurrentSense.o ./Core/SimpleFOC/common/base_classes/CurrentSense.su ./Core/SimpleFOC/common/base_classes/FOCMotor.cyclo ./Core/SimpleFOC/common/base_classes/FOCMotor.d ./Core/SimpleFOC/common/base_classes/FOCMotor.o ./Core/SimpleFOC/common/base_classes/FOCMotor.su ./Core/SimpleFOC/common/base_classes/Sensor.cyclo ./Core/SimpleFOC/common/base_classes/Sensor.d ./Core/SimpleFOC/common/base_classes/Sensor.o ./Core/SimpleFOC/common/base_classes/Sensor.su

.PHONY: clean-Core-2f-SimpleFOC-2f-common-2f-base_classes

