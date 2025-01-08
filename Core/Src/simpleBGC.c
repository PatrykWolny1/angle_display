/*
 * simpleBGC.c
 *
 *  Created on: Jan 8, 2025
 *      Author: patryk
 */

#include "simpleBGC.h"

// UART handle declaration (from STM32CubeMX)
extern UART_HandleTypeDef huart1;  // Ensure huart1 is configured in CubeMX

void setup() {
    // Initialize SimpleFOC serial communication
    SimpleFOCDebug::enable(&huart1);
    HAL_UART_Transmit(&huart1, (uint8_t *)"UART Ready\r\n", 12, HAL_MAX_DELAY);
}

void loop() {
    uint8_t rx_buffer[1];  // Buffer for received data
    uint8_t tx_buffer[20]; // Buffer for transmitting data

    // Wait to receive data
    if (HAL_UART_Receive(&huart1, rx_buffer, 1, HAL_MAX_DELAY) == HAL_OK) {
        // Echo received data
        sprintf((char *)tx_buffer, "Received: %c\r\n", rx_buffer[0]);
        HAL_UART_Transmit(&huart1, tx_buffer, strlen((char *)tx_buffer), HAL_MAX_DELAY);
    }
}
