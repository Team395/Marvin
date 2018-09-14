/*
 * Drivebase.h
 *
 *  Created on: Jan 15, 2018
 *      Author: JARVIS
 */

#ifndef SRC_SYSTEMS_DRIVEBASE_H_
#define SRC_SYSTEMS_DRIVEBASE_H_

#include <ctre/Phoenix.h>
#include <Solenoid.h>
#include <Systems/SystemBase.h>
#include <Systems/NewTalonMap.h>
#include <RobotMap.h>
#include <Systems/DrivebaseEncoderSensors.h>
#include <Systems/DrivebaseGyroSensor.h>

class Drivebase : SystemBase, public frc::PIDOutput {
	// TODO:  Java backport cleanup
#if 0
	WPI_TalonSRX leftMaster{DrivebaseMap::kLeftMaster};
	WPI_TalonSRX leftSlave{DrivebaseMap::kLeftSlave};
	WPI_TalonSRX rightMaster{DrivebaseMap::kRightMaster};
	WPI_TalonSRX rightSlave{DrivebaseMap::kRightSlave};
	std::array<WPI_TalonSRX*, 4> talonIndex {{&leftMaster, &leftSlave, &rightMaster, &rightSlave}};
#endif
	bool highGear{true};
	double minimumPidOutput{0.1};
	NewTalonMap* newTalonMap_;
	friend class DrivebaseEncoderSensors;
	friend class DrivebaseGyroSensor;

public:
	Drivebase(NewTalonMap* newTalonMap);
	virtual ~Drivebase();

	void ArcadeDrive(double, double);
	void tankDrive(double, double);
	void PIDWrite(double);
	void setMinimumPidOutput(double);
	// TODO:  Java backport cleanup
#if 0
	WPI_TalonSRX* getLeftMaster();
	WPI_TalonSRX* getRightMaster();
#endif
};

#endif /* SRC_SYSTEMS_DRIVEBASE_H_ */
