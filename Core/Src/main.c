/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "main.h"
#include "cmsis_os.h"
#include "dma.h"
#include "spi.h"
#include "usart.h"
#include "gpio.h"
#include "i2c.h"
#include "tim.h"
#include "write_printf.h"
#include <string.h>
#include <stdio.h>
#include "stm32f1xx_hal.h"


/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
// Define the PWM duty cycle
#define PWM_MIN_DUTY_CYCLE 20  // Minimum duty cycle (20%)
#define PWM_MAX_DUTY_CYCLE 100 // Maximum duty cycle (100%)
#define PWM_START_DUTY_CYCLE 50 // Start with 50% duty cycle
#define COMMUTATION_STEPS 6     // 6-step commutation for BLDC motor
#define DELAY_BETWEEN_STEPS 10  // Delay in ms between commutation steps

// Function to initialize the motor driver
// Commutation table for trapezoidal control (6 steps)
const uint8_t commutation_table[COMMUTATION_STEPS][6] = {
    {1, 0, 1, 0, 0, 0},  // Step 1
    {1, 0, 0, 0, 1, 0},  // Step 2
    {0, 0, 0, 0, 1, 1},  // Step 3
    {0, 1, 0, 0, 0, 1},  // Step 4
    {0, 1, 1, 0, 0, 0},  // Step 5
    {1, 0, 0, 1, 0, 0}   // Step 6
};
void Motor_Init(void)
{
    // Ensure the driver is enabled
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_SET); // Set VIO/NSTDBY high
}

// Function to start the motor
void Motor_Start(void)
{
    // Start PWM on all channels
    HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);  // UH
    HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);  // UL
    HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);  // VH
    HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_4);  // VL
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);  // WH
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);  // WL
}

// Function to stop the motor
void Motor_Stop(void)
{
    // Stop PWM on all channels
    HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_1);  // UH
    HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_2);  // UL
    HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_3);  // VH
    HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_4);  // VL
    HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_1);  // WH
    HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_2);  // WL
}

// Function to set the current phase based on the commutation table
void Set_Phase(uint8_t step, uint8_t duty_cycle)
{
    // Set PWM duty cycle for each phase based on the commutation table
    __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, commutation_table[step][0] ? duty_cycle : 0); // UH
    __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, commutation_table[step][1] ? duty_cycle : 0); // UL
    __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, commutation_table[step][2] ? duty_cycle : 0); // VH
    __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_4, commutation_table[step][3] ? duty_cycle : 0); // VL
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, commutation_table[step][4] ? duty_cycle : 0); // WH
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, commutation_table[step][5] ? duty_cycle : 0); // WL
}

//void Full_Rotation(void)
//{
//    uint16_t total_steps = COMMUTATION_STEPS * POLE_PAIRS;  // Calculate total steps
//    uint16_t step = 0;
//
//    for (uint16_t i = 0; i < total_steps; i++)
//    {
//        // Set the current commutation phase
//        Set_Phase(step);
//
//        // Move to the next step
//        step = (step + 1) % COMMUTATION_STEPS;
//
//        // Delay between steps (adjust for speed control)
//        HAL_Delay(DELAY_BETWEEN_STEPS);
//    }
//}

int main(void) {
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_I2C1_Init();
    MX_SPI2_Init();
	HAL_SPI_MspInit(&hspi2);
    MX_USART3_UART_Init();
    MX_USART2_UART_Init();
    MX_DMA_Init();
    MX_TIM2_Init();
	MX_TIM3_Init();
    // Initialize the motor driver
    Motor_Init();

    // Start the motor
    Motor_Start();

    // Execute a full mechanical rotation
//    Full_Rotation();

    // Stop the motor after rotation
//    Motor_Stop();

    // Main loop
    uint8_t step = 0;
    while (1)
    {
		// Set the current commutation phase with 50% duty cycle
		Set_Phase(step, 50);

		// Move to the next step
		step = (step + 1) % COMMUTATION_STEPS;
		// Delay between steps (adjust for motor speed)
		HAL_Delay(10);
    }
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI_DIV2;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL16;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
/* USER CODE END 4 */

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM1 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM1) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
