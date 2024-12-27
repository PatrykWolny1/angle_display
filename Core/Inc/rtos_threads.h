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
#include "cmsis_os2.h"
#include "usart.h"
#include "dma.h"
#include "mpu6050.h"
#include "oled.h"
#include "queue.h"
#include "freertos.h"
#include "compute_angles.h"
#include "write_printf.h"
#include <stdint.h>
#include <stdio.h>
#include <time.h>
#include <errno.h>
#include <unistd.h> // For getcwd
#include <stdlib.h>  // For malloc/free


void mpu6050_ReadData(void *argument);
void DataProcessing(void *argument);

#endif /* INC_RTOS_THREADS_H_ */
