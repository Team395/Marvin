/*
 * DrivebaseSensors.h
 *
 *  Created on: Jan 16, 2018
 *      Author: JARVIS
 */

#ifndef SRC_SYSTEMS_DRIVEBASESENSORS_H_
#define SRC_SYSTEMS_DRIVEBASESENSORS_H_
#include <ctre/phoenix/Sensors/PigeonIMU.h>
#include <PIDSource.h>
#include <Systems/SystemBase.h>
#include <Systems/Elevator.h>

#include <RobotMap.h>
#include <Preferences.h>
#include <ctre/Phoenix.h>

using PigeonIMU = ctre::phoenix::sensors::PigeonIMU;

class Elevator;

class DrivebaseSensors : SystemBase, public frc::PIDSource {
	friend Elevator;
	PigeonIMU imu;
	WPI_TalonSRX* getGyroTalon(Elevator*);
public:
	//PID Gains for Turn
	//TODO: retune loop for degrees
	double kP{-0.03};
	double kI{0.00};
	double kD{0};

//	frc::Preferences* preferences = Preferences::GetInstance();

	DrivebaseSensors(Elevator* elevator);
	virtual ~DrivebaseSensors();

	double getAngleZ();

	frc::PIDSourceType GetPIDSourceType();
	double PIDGet();

	PigeonIMU* getIMU();
};

#endif /* SRC_SYSTEMS_DRIVEBASESENSORS_H_ */
