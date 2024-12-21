/*
 * threads.h
 *
 *  Created on: Dec 19, 2024
 *      Author: patryk
 */

#ifndef INC_RTOS_THREADS_H_
#define INC_RTOS_THREADS_H_

#include "main.h"
#include "cmsis_os.h"
#include "usart.h"
#include "dma.h"
#include "mpu6050.h"
#include "queue.h"

void mpu6050_ReadData(void *argument);
void DataProcessing(void *argument);

#endif /* INC_RTOS_THREADS_H_ */
