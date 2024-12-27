/*
 * threads.cpp
 *
 *  Created on: Dec 19, 2024
 *      Author: patryk
 */



#include "rtos_threads.h"
#include <stdint.h>
#include <stdio.h>
#include <time.h>
#include <errno.h>
#include <unistd.h> // For getcwd
#include <stdlib.h>  // For malloc/free
#include <string.h>

extern osMessageQueueId_t dataQueue;
extern osMutexId_t uartMutex;
extern osSemaphoreId_t dmaTxCompleteSemaphore;
extern void initialise_monitor_handles(void);

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart) {
    if (huart == &huart2) {
        osSemaphoreRelease(dmaTxCompleteSemaphore);

    }
}

void mpu6050_ReadData(void *argument) {
    MPU6050_Data dataToProcess;

    char buffer[200];

    OLED_Init();
    printf("OLED initialized\r\n");
    MPU6050_Init();
    printf("MPU6050 initialized\r\n");
    printf("MPU6050 calibrating...\r\n");

    //MPU6050_CalibrateInternal(&dataToProcess);
    MPU6050_CalibrateExternal(&dataToProcess);
    printf("MPU6050 calibrated\r\n");
    while (1) {
        // Read sensor data
        MPU6050_ReadAll(&dataToProcess);
        // Format sensor data
        //snprintf(buffer, sizeof(buffer),
        //         "Xa=%6.2f Xg=%6.2f Ya=%6.2f Yg=%6.2f Za=%6.2f Zg=%6.2f\r\n",
        //         dataToProcess.accelX, dataToProcess.gyroX, dataToProcess.accelY,
		//		 dataToProcess.gyroY, dataToProcess.accelZ, dataToProcess.gyroZ);

        // Transmit data over UART
        //if (osMutexAcquire(uartMutex, 100) == osOK) {  // Use timeout to avoid deadlocks
            //if (HAL_UART_Transmit_DMA(&huart2, (uint8_t *)buffer, strlen(buffer)) == HAL_OK) {
            //    if (osSemaphoreAcquire(dmaTxCompleteSemaphore, 100) != osOK) {
            //        printf("UART DMA timeout\r\n");
            //    }
            //} else {
            //    printf("UART DMA transmission failed\r\n");
            //}
            //osMutexRelease(uartMutex);  // Release mutex
        //} else {
            //printf("UART mutex acquire failed\r\n");
        //}

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

    CompFilter *resultsCompFilter;

    KalmanFilter resultKalmanFilterPitch;
    KalmanFilter resultKalmanFilterRoll;
    float kalmanRoll;
    float kalmanPitch;
    double dt;
    char buffer[200];

    errno = 0;
    FILE *filePtr = fopen("/home/patryk/Programming/STM32CubeIDE/STM32_Workspace/camera_stabilizer/Core/Src/measurements.txt", "w");

    if (filePtr == NULL) {
         printf("Error opening file: %s (errno: %d)\n", strerror(errno), errno);
         return 1;
     }


    fprintf(filePtr, "Kalman Pitch|Kalman Roll|Acc Pitch|Acc Roll|Gyro Pitch|Gyro Roll\r\n");

    printf("DataProcessing task started\r\n");


    Kalman_Init(&resultKalmanFilterPitch, 0.001f, 0.003f, 0.03f); // Initialize the Kalman filter with noise parameters
    Kalman_Init(&resultKalmanFilterRoll, 0.005f, 0.001f, 0.004f); // Initialize the Kalman filter with noise parameters
    uint32_t prevTick = osKernelGetTickCount();  // Initialize previous tick

    while (1) {

        // Get data from queue
        if (osMessageQueueGet(dataQueue, &receivedData, NULL, 200) == osOK) {
        	// Record the start time
            SSD1306_DrawString(29, 16, "Pitch", 1); // Label for pitch
            SSD1306_DrawString(69, 16, "Roll", 1); // Label for pitch

            //resultsCompFilter = complementary_filter(&resultsPRY, &receivedData, &prevTick);
//            resultsPRY = computeAnglesAcc(&receivedData);
            resultsPRY = computeAngles(&receivedData, &prevTick);

            // Clear regions where pitch and roll values are displayed
            SSD1306_ClearRegion(29, 28, 40, 8); // Clear the region for pitch value
            SSD1306_ClearRegion(69, 28, 40, 8); // Clear the region for roll value

            dt = computeDT(&prevTick);
            kalmanPitch = Kalman_Update(&resultKalmanFilterPitch, resultsPRY->pitchAcc, receivedData.gyroX, (float)dt);
            kalmanRoll = Kalman_Update(&resultKalmanFilterRoll, resultsPRY->rollAcc, receivedData.gyroY, (float)dt);
             //SSD1306_DrawFloat(29, 28, resultsCompFilter->pitch, 1, 1);
            SSD1306_DrawFloat(29, 28, kalmanPitch, 1, 1);

            //SSD1306_DrawFloat(69, 28, resultsCompFilter->roll, 1, 1);
            SSD1306_DrawFloat(69, 28, kalmanRoll, 1, 1);

            SSD1306_UpdateScreen();


            fprintf(filePtr, "%.2f|%.2f|%.2f|%.2f|%.2f|%.2f\r\n",
            		kalmanPitch, kalmanRoll, resultsPRY->pitchAcc, resultsPRY->rollAcc,
					resultsPRY->pitchGyro, resultsPRY->rollGyro);


//             Format processed data for computeAngles()
//            snprintf(buffer, sizeof(buffer), "Acc | Pitch=%6.2f Roll=%6.2f | Gyro | Pitch=%6.2f Roll=%6.2f"
//            		"Yaw=%6.2f\r\n", resultsPRY->pitchAcc, resultsPRY->rollAcc, resultsPRY->pitchGyro,
//					resultsPRY->rollGyro, resultsPRY->yawGyro);
//
//             Format processed data for filters
//            snprintf(buffer, sizeof(buffer), "CompFilter | Pitch=%6.2f Roll=%6.2f\r\n",
//            		resultsCompFilter->pitch, resultsCompFilter->roll);

            // Transmit processed data over UART
//            if (osMutexAcquire(uartMutex, 100) == osOK) {  // Use timeout to avoid deadlocks
//                if (HAL_UART_Transmit_DMA(&huart2, (uint8_t *)buffer, strlen(buffer)) == HAL_OK) {
//                    if (osSemaphoreAcquire(dmaTxCompleteSemaphore, 100) != osOK) {
//                        printf("UART DMA timeout\r\n");
//                    }
//                } else {
//                    printf("UART DMA transmission failed\r\n");
//                }
//                osMutexRelease(uartMutex);  // Release mutex
//            } else {
//                printf("UART mutex acquire failed\r\n");
//            }
//    		osDelay(2);  // Prevent rapid polling
        } else {
//            printf("Queue is empty\r\n");
        }
    }
}


