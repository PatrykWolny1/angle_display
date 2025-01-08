################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Core/SimpleFOC/drivers/BLDCDriver3PWM.cpp \
../Core/SimpleFOC/drivers/BLDCDriver6PWM.cpp \
../Core/SimpleFOC/drivers/StepperDriver2PWM.cpp \
../Core/SimpleFOC/drivers/StepperDriver4PWM.cpp 

OBJS += \
./Core/SimpleFOC/drivers/BLDCDriver3PWM.o \
./Core/SimpleFOC/drivers/BLDCDriver6PWM.o \
./Core/SimpleFOC/drivers/StepperDriver2PWM.o \
./Core/SimpleFOC/drivers/StepperDriver4PWM.o 

CPP_DEPS += \
./Core/SimpleFOC/drivers/BLDCDriver3PWM.d \
./Core/SimpleFOC/drivers/BLDCDriver6PWM.d \
./Core/SimpleFOC/drivers/StepperDriver2PWM.d \
./Core/SimpleFOC/drivers/StepperDriver4PWM.d 


# Each subdirectory must supply rules for building sources it contributes
Core/SimpleFOC/drivers/%.o Core/SimpleFOC/drivers/%.su Core/SimpleFOC/drivers/%.cyclo: ../Core/SimpleFOC/drivers/%.cpp Core/SimpleFOC/drivers/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m3 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -DSTM32_THREAD_SAFE_STRATEGY=4 -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3 -I../Core/ThreadSafe -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-SimpleFOC-2f-drivers

clean-Core-2f-SimpleFOC-2f-drivers:
	-$(RM) ./Core/SimpleFOC/drivers/BLDCDriver3PWM.cyclo ./Core/SimpleFOC/drivers/BLDCDriver3PWM.d ./Core/SimpleFOC/drivers/BLDCDriver3PWM.o ./Core/SimpleFOC/drivers/BLDCDriver3PWM.su ./Core/SimpleFOC/drivers/BLDCDriver6PWM.cyclo ./Core/SimpleFOC/drivers/BLDCDriver6PWM.d ./Core/SimpleFOC/drivers/BLDCDriver6PWM.o ./Core/SimpleFOC/drivers/BLDCDriver6PWM.su ./Core/SimpleFOC/drivers/StepperDriver2PWM.cyclo ./Core/SimpleFOC/drivers/StepperDriver2PWM.d ./Core/SimpleFOC/drivers/StepperDriver2PWM.o ./Core/SimpleFOC/drivers/StepperDriver2PWM.su ./Core/SimpleFOC/drivers/StepperDriver4PWM.cyclo ./Core/SimpleFOC/drivers/StepperDriver4PWM.d ./Core/SimpleFOC/drivers/StepperDriver4PWM.o ./Core/SimpleFOC/drivers/StepperDriver4PWM.su

.PHONY: clean-Core-2f-SimpleFOC-2f-drivers

