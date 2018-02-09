/*
 * Drivebase.h
 *
 *  Created on: Jan 15, 2018
 *      Author: JARVIS
 */

#ifndef SRC_SYSTEMS_DRIVEBASE_H_
#define SRC_SYSTEMS_DRIVEBASE_H_

#include <Systems/DrivebaseSensors.h>
#include <ctre/Phoenix.h>
#include <Solenoid.h>
#include <Systems/SystemBase.h>
#include <RobotMap.h>
#include <Systems/DrivebaseSensors.h>

class Drivebase : SystemBase, public frc::PIDOutput {
	WPI_TalonSRX leftMaster{DrivebaseMap::kLeftMaster};
	WPI_TalonSRX leftSlave{DrivebaseMap::kLeftSlave};
	WPI_TalonSRX rightMaster{DrivebaseMap::kRightMaster};
	WPI_TalonSRX rightSlave{DrivebaseMap::kRightSlave};
	std::array<WPI_TalonSRX*, 4> talonIndex {{&leftMaster, &leftSlave, &rightMaster, &rightSlave}};

	Solenoid lowGearSolenoid{DrivebaseMap::kLowGear};
	Solenoid highGearSolenoid{DrivebaseMap::kHighGear};
	bool highGear{true};
	double minimumPidOutput{0.05};
	friend class DrivebaseSensors;

public:
	Drivebase();
	virtual ~Drivebase();

	void ArcadeDrive(double, double);
	void tankDrive(double, double);
	void PIDWrite(double);
	void setMinimumPidOutput(double);
	void shiftHighGear(bool);
	bool isHighGear();
};

#endif /* SRC_SYSTEMS_DRIVEBASE_H_ */
