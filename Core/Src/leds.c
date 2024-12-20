/*
 * leds.cpp
 *
 *  Created on: Dec 19, 2024
 *      Author: patryk
 */


#include "leds.h"
#include <stdio.h>
#include <stdint.h>

uint8_t txBuffer[] = "Hello, UART!\r\n";
uint8_t rxBuffer[14];
int16_t accelX, accelY, accelZ;
int16_t gyroX, gyroY, gyroZ;
float temp;
char buffer[200];





//void StartLEDTask(void *argument) {
//
//    while (1) {
//
////        osDelay(50); // Delay for 500ms
//    }
//}



void StartMPU6050ReadWriteUART(void *argument) {
    MPU6050_Init();
	MPU6050_Calibrate();

	while(1) {
//        HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5); // Toggle LED

		MPU6050_ReadAll(&accelX, &accelY, &accelZ, &gyroX, &gyroY, &gyroZ, &temp);

		snprintf(buffer, sizeof(buffer), "Accel: X=%d, Y=%d, Z=%d, Temp=%.2f, Gyro: X=%d, Y=%d, Z=%d\r\n",
				 accelX, accelY, accelZ, temp, gyroX, gyroY, gyroZ);
		HAL_UART_Transmit_DMA(&huart2, (uint8_t *)buffer, strlen(buffer));
		HAL_Delay(50);

	}
}

