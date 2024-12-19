/*
 * leds.cpp
 *
 *  Created on: Dec 19, 2024
 *      Author: patryk
 */

#include "cmsis_os.h"
#include "stm32f1xx_hal.h"
#include "leds.h"
#include "usart.h"

uint8_t message[] = "Hello, UART!\r\n";
uint8_t rxBuffer[10];

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
    if (huart->Instance == USART2) {
        // Handle received data in rxBuffer
        HAL_UART_Transmit(&huart2, rxBuffer, sizeof(rxBuffer), HAL_MAX_DELAY);
    }
}

void StartLEDTask(void *argument) {
    while (1) {
        HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5); // Toggle LED
        osDelay(100); // Delay for 500ms
        uint8_t rxBuffer[10];
        HAL_UART_Transmit(&huart2, message, sizeof(message) - 1, HAL_MAX_DELAY); // Send message
        HAL_UART_Receive_IT(&huart2, rxBuffer, sizeof(rxBuffer));
    }
}

void StartDefaultTask(void *argument) {
    while (1) {
        HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_0); // Toggle another LED
        osDelay(1000); // Delay for 1 second
    }
}

