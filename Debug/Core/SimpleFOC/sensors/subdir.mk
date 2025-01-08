################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Core/SimpleFOC/sensors/Encoder.cpp \
../Core/SimpleFOC/sensors/GenericSensor.cpp \
../Core/SimpleFOC/sensors/HallSensor.cpp \
../Core/SimpleFOC/sensors/MagneticSensorAnalog.cpp \
../Core/SimpleFOC/sensors/MagneticSensorI2C.cpp \
../Core/SimpleFOC/sensors/MagneticSensorPWM.cpp \
../Core/SimpleFOC/sensors/MagneticSensorSPI.cpp 

OBJS += \
./Core/SimpleFOC/sensors/Encoder.o \
./Core/SimpleFOC/sensors/GenericSensor.o \
./Core/SimpleFOC/sensors/HallSensor.o \
./Core/SimpleFOC/sensors/MagneticSensorAnalog.o \
./Core/SimpleFOC/sensors/MagneticSensorI2C.o \
./Core/SimpleFOC/sensors/MagneticSensorPWM.o \
./Core/SimpleFOC/sensors/MagneticSensorSPI.o 

CPP_DEPS += \
./Core/SimpleFOC/sensors/Encoder.d \
./Core/SimpleFOC/sensors/GenericSensor.d \
./Core/SimpleFOC/sensors/HallSensor.d \
./Core/SimpleFOC/sensors/MagneticSensorAnalog.d \
./Core/SimpleFOC/sensors/MagneticSensorI2C.d \
./Core/SimpleFOC/sensors/MagneticSensorPWM.d \
./Core/SimpleFOC/sensors/MagneticSensorSPI.d 


# Each subdirectory must supply rules for building sources it contributes
Core/SimpleFOC/sensors/%.o Core/SimpleFOC/sensors/%.su Core/SimpleFOC/sensors/%.cyclo: ../Core/SimpleFOC/sensors/%.cpp Core/SimpleFOC/sensors/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m3 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -DSTM32_THREAD_SAFE_STRATEGY=4 -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3 -I../Core/ThreadSafe -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-SimpleFOC-2f-sensors

clean-Core-2f-SimpleFOC-2f-sensors:
	-$(RM) ./Core/SimpleFOC/sensors/Encoder.cyclo ./Core/SimpleFOC/sensors/Encoder.d ./Core/SimpleFOC/sensors/Encoder.o ./Core/SimpleFOC/sensors/Encoder.su ./Core/SimpleFOC/sensors/GenericSensor.cyclo ./Core/SimpleFOC/sensors/GenericSensor.d ./Core/SimpleFOC/sensors/GenericSensor.o ./Core/SimpleFOC/sensors/GenericSensor.su ./Core/SimpleFOC/sensors/HallSensor.cyclo ./Core/SimpleFOC/sensors/HallSensor.d ./Core/SimpleFOC/sensors/HallSensor.o ./Core/SimpleFOC/sensors/HallSensor.su ./Core/SimpleFOC/sensors/MagneticSensorAnalog.cyclo ./Core/SimpleFOC/sensors/MagneticSensorAnalog.d ./Core/SimpleFOC/sensors/MagneticSensorAnalog.o ./Core/SimpleFOC/sensors/MagneticSensorAnalog.su ./Core/SimpleFOC/sensors/MagneticSensorI2C.cyclo ./Core/SimpleFOC/sensors/MagneticSensorI2C.d ./Core/SimpleFOC/sensors/MagneticSensorI2C.o ./Core/SimpleFOC/sensors/MagneticSensorI2C.su ./Core/SimpleFOC/sensors/MagneticSensorPWM.cyclo ./Core/SimpleFOC/sensors/MagneticSensorPWM.d ./Core/SimpleFOC/sensors/MagneticSensorPWM.o ./Core/SimpleFOC/sensors/MagneticSensorPWM.su ./Core/SimpleFOC/sensors/MagneticSensorSPI.cyclo ./Core/SimpleFOC/sensors/MagneticSensorSPI.d ./Core/SimpleFOC/sensors/MagneticSensorSPI.o ./Core/SimpleFOC/sensors/MagneticSensorSPI.su

.PHONY: clean-Core-2f-SimpleFOC-2f-sensors

