#include "i2c.h"
#include <stdint.h>
#include <stdio.h>

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
#define SMPLRT_DIV 0x19
#define PWR_MGMT_1 0x6B

void MPU6050_Init(void);

void MPU6050_ReadAll(int16_t *accelX, int16_t *accelY, int16_t *accelZ,
		int16_t *gyroX, int16_t *gyroY, int16_t *gyroZ, float *temp);

void MPU6050_Calibrate(void);

void MPU6050_CalculateOffsets(int16_t *accelOffsets, int16_t *gyroOffsets);

void MPU6050_WriteOffsets(int16_t *accelOffsets, int16_t *gyroOffsets);

void MPU6050_SoftReset(void);
