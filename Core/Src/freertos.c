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
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartDefaultTask */

/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartDefaultTask */
}

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

