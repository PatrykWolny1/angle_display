/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "freertos.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
osMessageQueueId_t dataQueue;
osMutexId_t uartMutex;
osSemaphoreId_t dmaTxCompleteSemaphore;
/* USER CODE END Variables */
/* Definitions for defaultTask */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */



/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */

/* USER CODE BEGIN Header_StartDefaultTask */

/* USER CODE END Header_StartDefaultTask */

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
void FreeRTOS_Init(void) {
    osKernelInitialize();

	// Create a message queue to pass data between threads
    dataQueue = osMessageQueueNew(10, sizeof(MPU6050_Data), NULL); // Assuming MPU6050_Data is the data structure for MPU6050 readings
    if (dataQueue == NULL) {
        printf("Failed to create data queue\r\n");
        return;
    }

    // Create a mutex for UART access
    uartMutex = osMutexNew(NULL);
    if (uartMutex == NULL) {
        printf("Failed to create UART mutex\r\n");
        return;
    }

    // Create a semaphore for DMA TX completion signaling
    dmaTxCompleteSemaphore = osSemaphoreNew(1, 0, NULL);
    if (dmaTxCompleteSemaphore == NULL) {
        printf("Failed to create DMA TX semaphore\r\n");
        return;
    }

    // Create a thread for reading data from the MPU6050 sensor
    osThreadAttr_t mpu6050TaskAttributes = {
        .name = "MPU6050Task",
        .priority = osPriorityNormal,
        .stack_size = 512 * 5  // Adjust stack size as needed
    };
    if (osThreadNew((osThreadFunc_t)mpu6050_ReadData, NULL, &mpu6050TaskAttributes) == NULL) {
        printf("Failed to create MPU6050 task\r\n");
        return;
    }

    // Create a thread for processing data
    osThreadAttr_t dataProcessingTaskAttributes = {
        .name = "DataProcessingTask",
        .priority = osPriorityNormal,
        .stack_size = 512 * 12  // Adjust stack size as needed
    };
    if (osThreadNew((osThreadFunc_t)DataProcessing, NULL, &dataProcessingTaskAttributes) == NULL) {
        printf("Failed to create Data Processing task\r\n");
        return;
    }

    printf("FreeRTOS initialization complete\r\n");

    osKernelStart();
}
/* USER CODE END Application */

