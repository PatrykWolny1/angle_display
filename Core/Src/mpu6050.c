/*
 * mpu6050.c
 *
 *  Created on: Dec 20, 2024
 *      Author: patryk
 */

#include "mpu6050.h"
#include "write_printf.h"

void MPU6050_Init(void) {
    uint8_t data[2];

    MPU6050_SoftReset();

    // Wake up the MPU6050 (write 0 to PWR_MGMT_1 register)
    data[0] = 0x6B;  // Register address
    data[1] = 0x00;  // Data to write
    if (HAL_I2C_Master_Transmit(&hi2c1, MPU6050_ADDR, data, 2, HAL_MAX_DELAY) != HAL_OK) {
    	//Error handle
    }

    uint8_t data_config;

    // Set accelerometer range to ±2g
    data_config = 0x00;
    HAL_I2C_Mem_Write(&hi2c1, MPU6050_ADDR, ACCEL_CONFIG, 1, &data_config, 1, HAL_MAX_DELAY);

    // Set gyroscope range to ±250°/s
    data_config = 0x00;
    HAL_I2C_Mem_Write(&hi2c1, MPU6050_ADDR, GYRO_CONFIG, 1, &data_config, 1, HAL_MAX_DELAY);

    // Set sample rate to 125Hz
    data_config = 0x07;
    HAL_I2C_Mem_Write(&hi2c1, MPU6050_ADDR, SMPLRT_DIV, 1, &data_config, 1, HAL_MAX_DELAY);


    uint8_t whoAmI = 0;
    HAL_I2C_Mem_Read(&hi2c1, MPU6050_ADDR, 0x75, 1, &whoAmI, 1, HAL_MAX_DELAY);
    if (whoAmI != 0x68) {
        printf("MPU6050 not detected. WHO_AM_I = 0x%02X\r\n", whoAmI);
    } else {
        printf("MPU6050 detected. WHO_AM_I = 0x%02X\r\n", whoAmI);
    }
}

void MPU6050_ReadAll(int16_t *accelX, int16_t *accelY, int16_t *accelZ,
                     int16_t *gyroX, int16_t *gyroY, int16_t *gyroZ, float *temp) {
    uint8_t buffer[14];

    // Read 14 bytes starting from register 0x3B
    if (HAL_I2C_Mem_Read(&hi2c1, MPU6050_ADDR, 0x3B, I2C_MEMADD_SIZE_8BIT, buffer, 14, HAL_MAX_DELAY) == HAL_OK) {
        *accelX = (int16_t)(buffer[0] << 8 | buffer[1]);
        *accelY = (int16_t)(buffer[2] << 8 | buffer[3]);
        *accelZ = (int16_t)(buffer[4] << 8 | buffer[5]);
        *temp   = (int16_t)(buffer[6] << 8 | buffer[7]);
        *gyroX  = (int16_t)(buffer[8] << 8 | buffer[9]);
        *gyroY  = (int16_t)(buffer[10] << 8 | buffer[11]);
        *gyroZ  = (int16_t)(buffer[12] << 8 | buffer[13]);
    } else {
    	//Error handle
    }
}

void MPU6050_Calibrate(void) {
    int16_t accelOffsets[3], gyroOffsets[3];

    // Calculate offsets
    MPU6050_CalculateOffsets(accelOffsets, gyroOffsets);

    // Write offsets to MPU6050
    MPU6050_WriteOffsets(accelOffsets, gyroOffsets);

    // Optional: Print offsets for debugging
    printf("Accel Offsets: X=%d, Y=%d, Z=%d\r\n", accelOffsets[0], accelOffsets[1], accelOffsets[2]);
    printf("Gyro Offsets: X=%d, Y=%d, Z=%d\r\n", gyroOffsets[0], gyroOffsets[1], gyroOffsets[2]);

    HAL_Delay(2000);
}

void MPU6050_CalculateOffsets(int16_t *accelOffsets, int16_t *gyroOffsets) {
    int32_t accelX_sum = 0, accelY_sum = 0, accelZ_sum = 0;
    int32_t gyroX_sum = 0, gyroY_sum = 0, gyroZ_sum = 0;

    uint8_t rawData[6];
    for (int i = 0; i < 1000; i++) {
        // Read accelerometer data
        HAL_I2C_Mem_Read(&hi2c1, MPU6050_ADDR, ACCEL_XOUT_H, 1, rawData, 6, HAL_MAX_DELAY);
        accelX_sum += (int16_t)((rawData[0] << 8) | rawData[1]);
        accelY_sum += (int16_t)((rawData[2] << 8) | rawData[3]);
        accelZ_sum += (int16_t)((rawData[4] << 8) | rawData[5]);

        // Read gyroscope data
        HAL_I2C_Mem_Read(&hi2c1, MPU6050_ADDR, GYRO_XOUT_H, 1, rawData, 6, HAL_MAX_DELAY);
        gyroX_sum += (int16_t)((rawData[0] << 8) | rawData[1]);
        gyroY_sum += (int16_t)((rawData[2] << 8) | rawData[3]);
        gyroZ_sum += (int16_t)((rawData[4] << 8) | rawData[5]);

        HAL_Delay(2);
    }

    // Calculate average offsets
    accelOffsets[0] = accelX_sum / 1000;
    accelOffsets[1] = accelY_sum / 1000;
    accelOffsets[2] = (accelZ_sum / 1000) - 16384; // Subtract 1g for Z-axis

    gyroOffsets[0] = gyroX_sum / 1000;
    gyroOffsets[1] = gyroY_sum / 1000;
    gyroOffsets[2] = gyroZ_sum / 1000;
}

void MPU6050_WriteOffsets(int16_t *accelOffsets, int16_t *gyroOffsets) {
    uint8_t data[2];
    HAL_StatusTypeDef status;
    uint8_t readBack[2];

    // Write accelerometer offsets
    data[0] = (uint8_t)((accelOffsets[0] >> 8) & 0xFF); // High byte
    data[1] = (uint8_t)(accelOffsets[0] & 0xFF);        // Low byte
    status = HAL_I2C_Mem_Write(&hi2c1, MPU6050_ADDR, XA_OFFS_H, 1, data, 2, HAL_MAX_DELAY);

    if (status != HAL_OK) printf("Error writing Accel X offset\r\n");
    HAL_I2C_Mem_Read(&hi2c1, MPU6050_ADDR, XA_OFFS_H, 1, readBack, 2, HAL_MAX_DELAY);
    int16_t writtenOffset = (int16_t)((readBack[0] << 8) | readBack[1]);
    printf("Accel X Offset Written: %d\r\n", writtenOffset);

    data[0] = (uint8_t)((accelOffsets[1] >> 8) & 0xFF); // High byte
    data[1] = (uint8_t)(accelOffsets[1] & 0xFF);        // Low byte
    status = HAL_I2C_Mem_Write(&hi2c1, MPU6050_ADDR, YA_OFFS_H, 1, data, 2, HAL_MAX_DELAY);

    if (status != HAL_OK) printf("Error writing Accel Y offset\r\n");
    HAL_I2C_Mem_Read(&hi2c1, MPU6050_ADDR, YA_OFFS_H, 1, readBack, 2, HAL_MAX_DELAY);
    writtenOffset = (int16_t)((readBack[0] << 8) | readBack[1]);
    printf("Accel Y Offset Written: %d\r\n", writtenOffset);

    data[0] = (uint8_t)((accelOffsets[2] >> 8) & 0xFF); // High byte
    data[1] = (uint8_t)(accelOffsets[2] & 0xFF);        // Low byte
    status = HAL_I2C_Mem_Write(&hi2c1, MPU6050_ADDR, ZA_OFFS_H, 1, data, 2, HAL_MAX_DELAY);
    if (status != HAL_OK) printf("Error writing Accel Z offset\r\n");
    HAL_I2C_Mem_Read(&hi2c1, MPU6050_ADDR, ZA_OFFS_H, 1, readBack, 2, HAL_MAX_DELAY);
    writtenOffset = (int16_t)((readBack[0] << 8) | readBack[1]);
    printf("Accel Z Offset Written: %d\r\n", writtenOffset);

    // Write gyroscope offsets
    data[0] = (uint8_t)((gyroOffsets[0] >> 8) & 0xFF); // High byte
    data[1] = (uint8_t)(gyroOffsets[0] & 0xFF);        // Low byte
    status = HAL_I2C_Mem_Write(&hi2c1, MPU6050_ADDR, XG_OFFS_USRH, 1, data, 2, HAL_MAX_DELAY);

    if (status != HAL_OK) printf("Error writing Gyro X offset\r\n");
    HAL_I2C_Mem_Read(&hi2c1, MPU6050_ADDR, XG_OFFS_USRH, 1, readBack, 2, HAL_MAX_DELAY);
    writtenOffset = (int16_t)((readBack[0] << 8) | readBack[1]);
    printf("Gyro X Offset Written: %d\r\n", writtenOffset);

    data[0] = (uint8_t)((gyroOffsets[1] >> 8) & 0xFF); // High byte
    data[1] = (uint8_t)(gyroOffsets[1] & 0xFF);        // Low byte
    status = HAL_I2C_Mem_Write(&hi2c1, MPU6050_ADDR, YG_OFFS_USRH, 1, data, 2, HAL_MAX_DELAY);
    if (status != HAL_OK) printf("Error writing Gyro Y offset\r\n");

    HAL_I2C_Mem_Read(&hi2c1, MPU6050_ADDR, YG_OFFS_USRH, 1, readBack, 2, HAL_MAX_DELAY);
    writtenOffset = (int16_t)((readBack[0] << 8) | readBack[1]);
    printf("Gyro Y Offset Written: %d\r\n", writtenOffset);

    data[0] = (uint8_t)((gyroOffsets[2] >> 8) & 0xFF); // High byte
    data[1] = (uint8_t)(gyroOffsets[2] & 0xFF);        // Low byte
    status = HAL_I2C_Mem_Write(&hi2c1, MPU6050_ADDR, ZG_OFFS_USRH, 1, data, 2, HAL_MAX_DELAY);
    if (status != HAL_OK) printf("Error writing Gyro Z offset\r\n");

    HAL_I2C_Mem_Read(&hi2c1, MPU6050_ADDR, ZG_OFFS_USRH, 1, readBack, 2, HAL_MAX_DELAY);
    writtenOffset = (int16_t)((readBack[0] << 8) | readBack[1]);
    printf("Gyro Z Offset Written: %d\r\n", writtenOffset);
}

void MPU6050_SoftReset(void) {
    uint8_t data = 0x80; // DEVICE_RESET bit
    HAL_I2C_Mem_Write(&hi2c1, MPU6050_ADDR, PWR_MGMT_1, 1, &data, 1, HAL_MAX_DELAY);
    HAL_Delay(1000); // Allow time for the reset to complete
}
