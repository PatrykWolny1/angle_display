/*
 * leds.h
 *
 *  Created on: Dec 19, 2024
 *      Author: patryk
 */

#ifndef LEDS_H_
#define LEDS_H_

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);
void StartLEDTask(void *argument);
void StartDefaultTask(void *argument);

#endif /* INC_LEDS_H_ */
