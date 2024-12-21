/*
 * threads.cpp
 *
 *  Created on: Dec 19, 2024
 *      Author: patryk
 */


#include <stdint.h>
#include <stdio.h>
#include "freertos.h"
#include "rtos_threads.h"
#include "write_printf.h"
#include "FreeRTOSConfig.h"

extern osMessageQueueId_t dataQueue;
extern osMutexId_t uartMutex;
extern osSemaphoreId_t dmaTxCompleteSemaphore;

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart) {
    if (huart == &huart2) {
        osSemaphoreRelease(dmaTxCompleteSemaphore);

    }
}

void mpu6050_ReadData(void *argument) {
    float accelX, accelY, accelZ;
    float gyroX, gyroY, gyroZ;
    float temp;

    char buffer[200];

    MPU6050_Init();
    printf("MPU6050 initialized\r\n");

    while (1) {
        // Read sensor data
        MPU6050_ReadAll(&accelX, &accelY, &accelZ, &gyroX, &gyroY, &gyroZ, &temp);
        osDelay(100);

        // Format sensor data
        snprintf(buffer, sizeof(buffer),
                 "Xa=%6.2f Xg=%6.2f Ya=%6.2f Yg=%6.2f Za=%6.2f Zg=%6.2f\r\n",
                 accelX, gyroX, accelY, gyroY, accelZ, gyroZ);

        // Transmit data over UART
        if (osMutexAcquire(uartMutex, 100) == osOK) {  // Use timeout to avoid deadlocks
            if (HAL_UART_Transmit_DMA(&huart2, (uint8_t *)buffer, strlen(buffer)) == HAL_OK) {
                if (osSemaphoreAcquire(dmaTxCompleteSemaphore, 100) != osOK) {
                    printf("UART DMA timeout\r\n");
                }
            } else {
                printf("UART DMA transmission failed\r\n");
            }
            osMutexRelease(uartMutex);  // Release mutex
        } else {
            printf("UART mutex acquire failed\r\n");
        }

        // Send data to the queue
        if (osMessageQueuePut(dataQueue, &accelX, 0, 100) != osOK) {
            printf("Queue is full\r\n");
        }

        osDelay(50);  // Prevent rapid polling
    }
}


void DataProcessing(void *argument) {
    float receivedData;
    char buffer[200];

    printf("DataProcessing task started\r\n");

    while (1) {
        // Get data from queue
        if (osMessageQueueGet(dataQueue, &receivedData, NULL, 100) == osOK) {
            receivedData += 10;

            // Format processed data
            snprintf(buffer, sizeof(buffer), "Processed: %6.2f\r\n", receivedData);

            // Transmit processed data over UART
            if (osMutexAcquire(uartMutex, 100) == osOK) {  // Use timeout to avoid deadlocks
                if (HAL_UART_Transmit_DMA(&huart2, (uint8_t *)buffer, strlen(buffer)) == HAL_OK) {
                    if (osSemaphoreAcquire(dmaTxCompleteSemaphore, 100) != osOK) {
                        printf("UART DMA timeout\r\n");
                    }
                } else {
                    printf("UART DMA transmission failed\r\n");
                }
                osMutexRelease(uartMutex);  // Release mutex
            } else {
                printf("UART mutex acquire failed\r\n");
            }
        } else {
            printf("Queue is empty\r\n");
        }

        osDelay(20);  // Prevent rapid polling
    }
}


