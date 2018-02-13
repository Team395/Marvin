/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once
#include <Joystick.h>
#include <XboxController.h>
#include <RobotMap.h>

class OI {
	frc::Joystick driveStick{OIMap::kDriveStick};
	frc::XboxController xboxController{OIMap::kXboxController};

public:
	OI();
	double getDriveY();
	double getDriveZ();

	double getIntakeThrottle();
	double getIntakePosition();

	bool getClawDisable();
	bool getTurnButton();
};
