/*
 * compute_angles.h
 *
 *  Created on: Dec 22, 2024
 *      Author: patryk
 */
#ifndef _COMPUTE_ANG_H
#define _COMPUTE_ANG_H
#include "mpu6050.h"
#include "math.h"

struct {
    float pitchAcc;
	float rollAcc;
    float pitchGyro;
    float rollGyro;
    float yawGyro;
    float pitchGyroDelta;
    float rollGyroDelta;
    float yawGyroDelta;
} typedef PitchRollYaw;

PitchRollYaw* computeAngles(MPU6050_Data *dataToProcess, uint32_t *prevTick);

#endif
