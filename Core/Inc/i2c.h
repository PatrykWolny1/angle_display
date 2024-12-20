/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    i2c.h
  * @brief   This file contains all the function prototypes for
  *          the i2c.c file
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
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __I2C_H__
#define __I2C_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */
#include "cmsis_os.h"

/* USER CODE END Includes */

extern I2C_HandleTypeDef hi2c1;

/* USER CODE BEGIN Private defines */
extern osMutexId_t i2cMutex;

/* USER CODE END Private defines */

void MX_I2C1_Init(void);

/* USER CODE BEGIN Prototypes */
HAL_StatusTypeDef SafeHAL_I2C_Mem_Read(I2C_HandleTypeDef *hi2c, uint16_t DevAddress,
                                       uint16_t MemAddress, uint16_t MemAddSize,
                                       uint8_t *pData, uint16_t Size, uint32_t Timeout);

HAL_StatusTypeDef SafeHAL_I2C_Mem_Write(I2C_HandleTypeDef *hi2c, uint16_t DevAddress,
                                        uint16_t MemAddress, uint16_t MemAddSize,
                                        uint8_t *pData, uint16_t Size, uint32_t Timeout);
/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __I2C_H__ */

