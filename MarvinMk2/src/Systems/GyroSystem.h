/*
 * GyroSystem.h
 *
 *  Created on: Jan 16, 2018
 *      Author: JARVIS
 */

#ifndef SRC_SYSTEMS_GYROSYSTEM_H_
#define SRC_SYSTEMS_GYROSYSTEM_H_
#include "../Libraries/ADIS16448_IMU.h"

class GyroSystem {
	ADIS16448_IMU imu{};

public:
	GyroSystem();
	virtual ~GyroSystem();

	ADIS16448_IMU* getIMU();
};

#endif /* SRC_SYSTEMS_GYROSYSTEM_H_ */
