/*
 * compute_angles.c
 *
 *  Created on: Dec 22, 2024
 *      Author: patryk
 */

#include "compute_angles.h"
#include "mpu6050.h"

PitchRollYaw resultsPRY;

double computeDT(uint32_t *prevTick) {
    uint32_t currTick = osKernelGetTickCount();  // Get current tick
    uint32_t tickFreq = osKernelGetTickFreq();  // Get tick frequency (e.g., 1000 Hz)

    double dt = (double)(currTick - *prevTick) / tickFreq;  // Convert ticks to seconds
    *prevTick = currTick;  // Update previous tick for the next call

    return dt;  // Return time difference in seconds
}

float radiansToDegrees(float radians) {
    return radians * (180.0f / M_PI);
}

void complementary_filter(MPU6050_Data *dataToProcess) {

}

PitchRollYaw* computeAngles(MPU6050_Data *dataToProcess, uint32_t *prevTick) {
	resultsPRY.pitchAcc = atan2(dataToProcess->accelY, sqrt(pow(dataToProcess->accelX,2)+pow(dataToProcess->accelZ,2)));
	resultsPRY.rollAcc = atan2(dataToProcess->accelX, sqrt(pow(dataToProcess->accelY,2)+pow(dataToProcess->accelZ,2)));

    resultsPRY.pitchAcc = radiansToDegrees(resultsPRY.pitchAcc);
    resultsPRY.rollAcc = radiansToDegrees(resultsPRY.rollAcc);

    double dt = computeDT(prevTick);
    printf("%.2f\r\n", dt);

    resultsPRY.pitchGyroDelta = dataToProcess->gyroX * dt;
    resultsPRY.rollGyroDelta = dataToProcess->gyroY * dt;
    resultsPRY.yawGyroDelta = dataToProcess->gyroZ * dt;

    resultsPRY.pitchGyro += resultsPRY.pitchGyroDelta;
    resultsPRY.rollGyro += resultsPRY.rollGyroDelta;
    resultsPRY.yawGyro += resultsPRY.yawGyroDelta;

    return &resultsPRY;
}
