/*
 * freertos.h
 *
 *  Created on: Dec 20, 2024
 *      Author: patryk
 */

#ifndef INC_FREERTOS_H_
#define INC_FREERTOS_H_

#include "main.h"
#include "cmsis_os.h"
#include "rtos_threads.h"

extern osMessageQueueId_t dataQueue;
extern osMutexId_t uartMutex;
extern osSemaphoreId_t dmaTxCompleteSemaphore;

void MX_FREERTOS_Init(void);

#endif /* INC_FREERTOS_H_ */
