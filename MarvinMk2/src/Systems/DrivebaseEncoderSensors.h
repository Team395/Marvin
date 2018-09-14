/*
 * DrivebaseEncoderSensors.h
 *
 *  Created on: Jan 16, 2018
 *      Author: JARVIS
 */

#ifndef SRC_SYSTEMS_DRIVEBASEENCODERSENSORS_H_
#define SRC_SYSTEMS_DRIVEBASEENCODERSENSORS_H_


#include <PIDSource.h>
#include <Systems/SystemBase.h>
#include <Systems/Elevator.h>
#include <RobotMap.h>
#include <Preferences.h>
#include <ctre/Phoenix.h>
#include <Systems/Drivebase.h>
#include <Systems/NewTalonMap.h>

using PigeonIMU = ctre::phoenix::sensors::PigeonIMU;
class Drivebase;

class DrivebaseEncoderSensors : SystemBase, public frc::PIDSource {
	Drivebase* drivebase;
	NewTalonMap* newTalonMap_;
	//  TODO:  Java backport cleanup
#if 0
	WPI_TalonSRX* leftEncoderTalon;
	WPI_TalonSRX* rightEncoderTalon;
#endif

public:
	//PID Gains for Turn
	double kP{0.04};
	double kI{0.00};
	double kD{0.004};
	frc::Preferences* preferences = frc::Preferences::GetInstance();

	DrivebaseEncoderSensors(Drivebase*,NewTalonMap*);
	virtual ~DrivebaseEncoderSensors();

	frc::PIDSourceType GetPIDSourceType();
	double PIDGet();
	double getAveragedEncoderPositions();


	double convertToNativeUnits(double feet);
	const double PI  =3.141592653589793238463;
	const double INCHES_PER_FOOT = 12;
	const double WHEEL_DIAMETER_INCHES = 4;
	const double UNITS_PER_ROTATION = 4096;

	WPI_TalonSRX* getTalon(Drivebase*, int);

	enum class returnType{
		kDisplacement,
		kVelocity
	};
	double getLeftEncoder(returnType);
	double getRightEncoder(returnType);

	void setMinimumPidOutput(double);
	void resetEncoderSensors();
};

#endif /* SRC_SYSTEMS_DRIVEBASEENCODERSENSORS_H_ */
