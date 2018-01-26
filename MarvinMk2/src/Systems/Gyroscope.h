/*
 * Gyroscope.h
 *
 *  Created on: Jan 16, 2018
 *      Author: JARVIS
 */

#ifndef SRC_SYSTEMS_GYROSCOPE_H_
#define SRC_SYSTEMS_GYROSCOPE_H_
#include <ctre/phoenix/Sensors/PigeonIMU.h>
#include <PIDSource.h>
#include <Systems/SystemBase.h>
#include <RobotMap.h>

using PigeonIMU = ctre::phoenix::sensors::PigeonIMU;

class Gyroscope : SystemBase, public frc::PIDSource {
	PigeonIMU imu{CANMap::kPigeon};

public:
	//PID Gains for Turn
	//TODO: retune loop for degrees
	const double kP{2};
	const double kI{0.00};
	const double kD{0.1};

	Gyroscope();
	virtual ~Gyroscope();

	double getAngleX();

	frc::PIDSourceType GetPIDSourceType();
	double PIDGet();

	PigeonIMU* getIMU();
};

#endif /* SRC_SYSTEMS_GYROSCOPE_H_ */
