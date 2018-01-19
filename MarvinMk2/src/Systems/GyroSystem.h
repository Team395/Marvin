/*
 * GyroSystem.h
 *
 *  Created on: Jan 16, 2018
 *      Author: JARVIS
 */

#ifndef SRC_SYSTEMS_GYROSYSTEM_H_
#define SRC_SYSTEMS_GYROSYSTEM_H_
#include "../Libraries/ADIS16448_IMU.h"

#include <PIDSource.h>

class GyroSystem : public frc::PIDSource {
	ADIS16448_IMU imu{};

public:
	//PID Gains for Turn
	const double kP{2};
	const double kI{0.00};
	const double kD{0.1};

	GyroSystem();
	virtual ~GyroSystem();

	double getAngleX();

	frc::PIDSourceType GetPIDSourceType();
	double PIDGet();

	ADIS16448_IMU* getIMU();
};

#endif /* SRC_SYSTEMS_GYROSYSTEM_H_ */
