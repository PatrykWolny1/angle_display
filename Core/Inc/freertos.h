/*
 * freertos.h
 *
 *  Created on: Dec 20, 2024
 *      Author: patryk
 */

#ifndef INC_FREERTOS_H_
#define INC_FREERTOS_H_
/* USER CODE BEGIN Variables */

#include "rtos_threads.h"

extern osMessageQueueId_t dataQueue;
extern osMutexId_t uartMutex;
extern osSemaphoreId_t dmaTxCompleteSemaphore;

void FreeRTOS_Init(void);

/* USER CODE END Variables */


#endif /* INC_FREERTOS_H_ */
