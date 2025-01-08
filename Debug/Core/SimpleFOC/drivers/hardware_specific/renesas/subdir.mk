################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Core/SimpleFOC/drivers/hardware_specific/renesas/renesas.cpp 

OBJS += \
./Core/SimpleFOC/drivers/hardware_specific/renesas/renesas.o 

CPP_DEPS += \
./Core/SimpleFOC/drivers/hardware_specific/renesas/renesas.d 


# Each subdirectory must supply rules for building sources it contributes
Core/SimpleFOC/drivers/hardware_specific/renesas/%.o Core/SimpleFOC/drivers/hardware_specific/renesas/%.su Core/SimpleFOC/drivers/hardware_specific/renesas/%.cyclo: ../Core/SimpleFOC/drivers/hardware_specific/renesas/%.cpp Core/SimpleFOC/drivers/hardware_specific/renesas/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m3 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -DSTM32_THREAD_SAFE_STRATEGY=4 -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3 -I../Core/ThreadSafe -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-SimpleFOC-2f-drivers-2f-hardware_specific-2f-renesas

clean-Core-2f-SimpleFOC-2f-drivers-2f-hardware_specific-2f-renesas:
	-$(RM) ./Core/SimpleFOC/drivers/hardware_specific/renesas/renesas.cyclo ./Core/SimpleFOC/drivers/hardware_specific/renesas/renesas.d ./Core/SimpleFOC/drivers/hardware_specific/renesas/renesas.o ./Core/SimpleFOC/drivers/hardware_specific/renesas/renesas.su

.PHONY: clean-Core-2f-SimpleFOC-2f-drivers-2f-hardware_specific-2f-renesas

