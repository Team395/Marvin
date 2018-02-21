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
	frc::Joystick driveStickLeft{OIMap::LeftStick::kDriveStickLeft};
	frc::Joystick driveStickRight{OIMap::RightStick::kDriveStickRight};
	frc::XboxController xboxController{OIMap::Xbox::kXboxController};

public:
	OI();
	double getDriveLeft();
	double getDriveRight();

	double getIntakeThrottle();
	int getIntakePosition();

	double getElevatorThrottle();
	bool getClawDisable();
	bool getTurnButton();
	int getShiftButtons();
	bool getToggleIntakeMode();

	bool getIntakeAutoscore();
};
