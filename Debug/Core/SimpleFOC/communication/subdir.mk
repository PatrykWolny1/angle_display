################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Core/SimpleFOC/communication/Commander.cpp \
../Core/SimpleFOC/communication/SimpleFOCDebug.cpp \
../Core/SimpleFOC/communication/StepDirListener.cpp 

OBJS += \
./Core/SimpleFOC/communication/Commander.o \
./Core/SimpleFOC/communication/SimpleFOCDebug.o \
./Core/SimpleFOC/communication/StepDirListener.o 

CPP_DEPS += \
./Core/SimpleFOC/communication/Commander.d \
./Core/SimpleFOC/communication/SimpleFOCDebug.d \
./Core/SimpleFOC/communication/StepDirListener.d 


# Each subdirectory must supply rules for building sources it contributes
Core/SimpleFOC/communication/%.o Core/SimpleFOC/communication/%.su Core/SimpleFOC/communication/%.cyclo: ../Core/SimpleFOC/communication/%.cpp Core/SimpleFOC/communication/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m3 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -DSTM32_THREAD_SAFE_STRATEGY=4 -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3 -I../Core/ThreadSafe -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-SimpleFOC-2f-communication

clean-Core-2f-SimpleFOC-2f-communication:
	-$(RM) ./Core/SimpleFOC/communication/Commander.cyclo ./Core/SimpleFOC/communication/Commander.d ./Core/SimpleFOC/communication/Commander.o ./Core/SimpleFOC/communication/Commander.su ./Core/SimpleFOC/communication/SimpleFOCDebug.cyclo ./Core/SimpleFOC/communication/SimpleFOCDebug.d ./Core/SimpleFOC/communication/SimpleFOCDebug.o ./Core/SimpleFOC/communication/SimpleFOCDebug.su ./Core/SimpleFOC/communication/StepDirListener.cyclo ./Core/SimpleFOC/communication/StepDirListener.d ./Core/SimpleFOC/communication/StepDirListener.o ./Core/SimpleFOC/communication/StepDirListener.su

.PHONY: clean-Core-2f-SimpleFOC-2f-communication

