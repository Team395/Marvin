/*
 * DrivebaseGyroSensor.h
 *
 *  Created on: Mar 11, 2018
 *      Author: JARVIS
 */

#ifndef SRC_SYSTEMS_DRIVEBASEGYROSENSOR_H_
#define SRC_SYSTEMS_DRIVEBASEGYROSENSOR_H_

#include <ctre/phoenix/Sensors/PigeonIMU.h>
#include <PIDSource.h>
#include <Systems/SystemBase.h>
#include <RobotMap.h>
#include <Preferences.h>
#include <ctre/Phoenix.h>
#include <Systems/Drivebase.h>

class Drivebase;


class DrivebaseGyroSensor: SystemBase, public frc::PIDSource {
	Drivebase* drivebase;
	PigeonIMU imu;

public:
	//PID Gains for Turn
	double kP { 0.04 };
	double kI { 0.00 };
	double kD { 0.004 };
	frc::Preferences* preferences = frc::Preferences::GetInstance();

	DrivebaseGyroSensor(Drivebase*);
	virtual ~DrivebaseGyroSensor();

	double getAngleZ();
	WPI_TalonSRX* getTalon(Drivebase*, int);

	frc::PIDSourceType GetPIDSourceType();
	double PIDGet();
	void setMinimumPidOutput(double);
};

#endif /* SRC_SYSTEMS_DRIVEBASEGYROSENSOR_H_ */

