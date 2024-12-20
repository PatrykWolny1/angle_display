/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
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

#include "freertos.h"

void MX_FREERTOS_Init(void) {
    osKernelInitialize();

//    osThreadAttr_t ledTaskAttr = {
//        .name = "StartLEDTask",
//        .priority = osPriorityAboveNormal,
//        .stack_size = 256
//    };

    osThreadAttr_t defaultTaskAttr = {
        .name = "StartMPU6050ReadWriteUART",
        .priority = osPriorityAboveNormal,
        .stack_size = 512
    };

//    osThreadNew(StartLEDTask, NULL, &ledTaskAttr);
    osThreadNew(StartMPU6050ReadWriteUART, NULL, &defaultTaskAttr);

    osKernelStart();
}

