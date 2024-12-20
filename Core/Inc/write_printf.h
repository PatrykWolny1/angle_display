/*
 * write_printf.h
 *
 *  Created on: Dec 20, 2024
 *      Author: patryk
 */

#ifndef INC_WRITE_PRINTF_H_
#define INC_WRITE_PRINTF_H_

#include "usart.h" // Include the generated USART configuration

int _write(int file, char *data, int len) {
    HAL_UART_Transmit(&huart2, (uint8_t *)data, len, HAL_MAX_DELAY);
    return len;
}


#endif /* INC_WRITE_PRINTF_H_ */
