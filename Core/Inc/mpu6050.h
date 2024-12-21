#include <stdint.h>
#include <stdio.h>
#include "i2c.h"

#define MPU6050_ADDR 0x68 << 1  // I2C address (shifted for HAL)
#define ACCEL_XOUT_H 0x3B
#define GYRO_XOUT_H 0x43
#define XA_OFFS_H 0x06
#define YA_OFFS_H 0x08
#define ZA_OFFS_H 0x0A
#define XG_OFFS_USRH 0x13
#define YG_OFFS_USRH 0x15
#define ZG_OFFS_USRH 0x17
#define ACCEL_CONFIG 0x1C
#define GYRO_CONFIG 0x1B
#define SMPRT_DIV 0x19
#define PWR_MGMT_1 0x6B
#define CONFIG 0x1A
#define FIFO_EN 0x23
#define USER_CTRL 0x6A

void MPU6050_Init(void);

void MPU6050_ReadAll(float *accelX_g, float *accelY_g, float *accelZ_g,
                     float *gyroX_s, float *gyroY_s, float *gyroZ_s, float *temp_c);

void MPU6050_CalibrateInternal(void);

void MPU6050_CalculateOffsets(int16_t *accelOffsets, int16_t *gyroOffsets);

void MPU6050_WriteOffsets(int16_t *accelOffsets, int16_t *gyroOffsets);

void MPU6050_SoftReset(void);
