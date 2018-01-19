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
#include <Talon.h>
#include <PIDOutput.h>

#include "../RobotMap.h"

class Drivebase : public frc::PIDOutput {
	frc::Talon left1{DrivebaseMap::kLeft1};
	frc::Talon left2{DrivebaseMap::kLeft2};
	frc::Talon right1{DrivebaseMap::kRight1};
	frc::Talon right2{DrivebaseMap::kRight2};

	frc::SpeedControllerGroup leftSpeedControllers{left1, left2};
	frc::SpeedControllerGroup rightSpeedControllers{right1, right2};

	frc::DifferentialDrive differentialDrive{leftSpeedControllers, rightSpeedControllers};

public:
	Drivebase();

	void ArcadeDrive(double, double);
	void PIDWrite(double);

	virtual ~Drivebase();
};

#endif /* SRC_SYSTEMS_DRIVEBASE_H_ */
