/*
 * write_printf.c
 *
 *  Created on: Dec 21, 2024
 *      Author: patryk
 */

#include "write_printf.h"
extern UART_HandleTypeDef huart2;

int _write(int file, char *data, int len) {
        HAL_UART_Transmit(&huart2, (uint8_t *)data, len, HAL_MAX_DELAY);
    return len;
}
