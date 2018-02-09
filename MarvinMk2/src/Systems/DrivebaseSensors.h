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
#include <Systems/Drivebase.h>

using PigeonIMU = ctre::phoenix::sensors::PigeonIMU;
class Drivebase;

class DrivebaseSensors : SystemBase, public frc::PIDSource {
	Drivebase* drivebase;
	PigeonIMU imu;
	//Talon encoders only exposed through encoder object, these are pointers
	WPI_TalonSRX* leftEncoderTalon;
	WPI_TalonSRX* rightEncoderTalon;

public:
	//PID Gains for Turn
	//TODO: retune loop for degrees
	double kP{-0.03};
	double kI{0.00};
	double kD{0};

//	frc::Preferences* preferences = Preferences::GetInstance();

	DrivebaseSensors(Drivebase*);
	virtual ~DrivebaseSensors();
	double getAngleZ();
	frc::PIDSourceType GetPIDSourceType();
	double PIDGet();

	WPI_TalonSRX* getTalon(Drivebase*, int);
};

#endif /* SRC_SYSTEMS_DRIVEBASESENSORS_H_ */
