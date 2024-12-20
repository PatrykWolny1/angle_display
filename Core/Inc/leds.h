/*
 * leds.h
 *
 *  Created on: Dec 19, 2024
 *      Author: patryk
 */

#ifndef INC_LEDS_H_
#define INC_LEDS_H_

#include "main.h"
#include "cmsis_os.h"
#include "usart.h"
#include "dma.h"
#include "mpu6050.h"

//void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart);
//void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart);
void StartLEDTask(void *argument);
void StartMPU6050ReadWriteUART(void *argument);

#endif /* INC_LEDS_H_ */
