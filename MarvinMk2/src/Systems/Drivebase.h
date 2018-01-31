/*
 * Drivebase.h
 *
 *  Created on: Jan 15, 2018
 *      Author: JARVIS
 */

#ifndef SRC_SYSTEMS_DRIVEBASE_H_
#define SRC_SYSTEMS_DRIVEBASE_H_

#include <SpeedControllerGroup.h>
#include <Drive/DifferentialDrive.h>
#include <ctre/Phoenix.h>
#include <PIDOutput.h>

#include <Systems/SystemBase.h>
#include <RobotMap.h>

class Drivebase : SystemBase, public frc::PIDOutput {
	WPI_TalonSRX leftMaster{DrivebaseMap::kLeftMaster};
	WPI_TalonSRX leftSlave{DrivebaseMap::kLeftSlave};
	WPI_TalonSRX rightMaster{DrivebaseMap::kRightMaster};
	WPI_TalonSRX rightSlave{DrivebaseMap::kRightSlave};

	double minimumPidOutput{0.05};
public:
	Drivebase();

	void ArcadeDrive(double, double);
	void tankDrive(double, double);
	void PIDWrite(double);
	void setMinimumPidOutput(double);

	virtual ~Drivebase();
};

#endif /* SRC_SYSTEMS_DRIVEBASE_H_ */
