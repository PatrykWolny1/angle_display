/*
 * threads.cpp
 *
 *  Created on: Dec 19, 2024
 *      Author: patryk
 */



#include "rtos_threads.h"

extern osMessageQueueId_t dataQueue;
extern osMutexId_t uartMutex;
extern osSemaphoreId_t dmaTxCompleteSemaphore;

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart) {
    if (huart == &huart2) {
        osSemaphoreRelease(dmaTxCompleteSemaphore);

    }
}

void mpu6050_ReadData(void *argument) {
    MPU6050_Data dataToProcess;

    char buffer[200];


    MPU6050_Init();
//    MPU6050_CalibrateInternal(&dataToProcess);
    MPU6050_CalibrateExternal(&dataToProcess);
    printf("MPU6050 initialized\r\n");

    while (1) {
        // Read sensor data
        MPU6050_ReadAll(&dataToProcess);

        // Format sensor data
//        snprintf(buffer, sizeof(buffer),
//                 "Xa=%6.2f Xg=%6.2f Ya=%6.2f Yg=%6.2f Za=%6.2f Zg=%6.2f\r\n",
//                 dataToProcess.accelX, dataToProcess.gyroX, dataToProcess.accelY,
//				 dataToProcess.gyroY, dataToProcess.accelZ, dataToProcess.gyroZ);

        // Transmit data over UART
        if (osMutexAcquire(uartMutex, 100) == osOK) {  // Use timeout to avoid deadlocks
//            if (HAL_UART_Transmit_DMA(&huart2, (uint8_t *)buffer, strlen(buffer)) == HAL_OK) {
//                if (osSemaphoreAcquire(dmaTxCompleteSemaphore, 100) != osOK) {
//                    printf("UART DMA timeout\r\n");
//                }
//            } else {
//                printf("UART DMA transmission failed\r\n");
//            }
            osMutexRelease(uartMutex);  // Release mutex
        } else {
            printf("UART mutex acquire failed\r\n");
        }

        // Send data to the queue
        if (osMessageQueuePut(dataQueue, &dataToProcess, 0, 200) != osOK) {
            printf("Queue is full\r\n");
        }

        osDelay(2);  // Prevent rapid polling
    }
}


void DataProcessing(void *argument) {
    MPU6050_Data receivedData;
    PitchRollYaw *resultsPRY;


    char buffer[200];

    printf("DataProcessing task started\r\n");

    uint32_t prevTick = osKernelGetTickCount();  // Initialize previous tick

    while (1) {

        // Get data from queue
        if (osMessageQueueGet(dataQueue, &receivedData, NULL, 200) == osOK) {
        	// Record the start time

            resultsPRY = computeAngles(&receivedData, &prevTick);

            // Format processed data
            snprintf(buffer, sizeof(buffer), "Acc | Pitch=%6.2f Roll=%6.2f | Gyro | Pitch=%6.2f Roll=%6.2f"
            		"Yaw=%6.2f\r\n", resultsPRY->pitchAcc, resultsPRY->rollAcc, resultsPRY->pitchGyro,
					resultsPRY->rollGyro, resultsPRY->yawGyro);

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
    		osDelay(20);  // Prevent rapid polling
        } else {
//            printf("Queue is empty\r\n");
        }
    }
}


