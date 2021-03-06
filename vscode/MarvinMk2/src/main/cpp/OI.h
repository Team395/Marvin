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

	bool intakeTriggerPressed;

public:
	frc::XboxController xboxController{OIMap::Xbox::kXboxController};

	OI();
	enum class RequestedClawState {
		kOpen,
		kClose,
		kDoNothing
	};
	enum class ElevatorPreset{
		kHighScale,
		kNormalScale,
		kLowScale,
		kSwitch,
		kBottom,
		kDeploy,
		kNone
	};

	double getDriveLeft();
	double getDriveRight();

	double getIntakeThrottle();
	RequestedClawState getRequestedIntakePosition();

	double getElevatorThrottle();

	ElevatorPreset getElevatorPreset();

	Joystick* getLeftStick();

	bool getTurnButton();
	
	bool getToggleIntakeMode();

	bool getIntakeAutoscore();

	bool getShiftDownHalf();

	bool getShiftDownSeventyFive();

	bool getExtendClimber();
	bool getRetractClimber();
	bool getTiltClimber();
	bool getWinchClimber();
};
