/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

namespace OIMap{
	namespace Xbox{
		constexpr int kXboxController = 2;
		constexpr int kElevator = 1;
		constexpr int kIntakeThrottle = 5;
		constexpr int kIntakeOpen = 2;
		constexpr int kIntakeClose = 3;

		constexpr int kHighScalePreset = 4;
		constexpr int kNormalScalePreset = 2;
		constexpr int kLowScalePreset = 1;
		constexpr int kSwitchPreset = 3;
		constexpr int kBottomPreset = 9 ;

		constexpr int kAutoScore = 10;
	}

	namespace LeftStick{
		constexpr int kDriveStickLeft = 0;
		constexpr int kTurnButton = 1; //On left stick
	}

	namespace RightStick{
		constexpr int kDriveStickRight = 1;
	}
};

namespace DrivebaseMap{
	constexpr int kLeftMaster = 1;
	constexpr int kLeftSlave = 2;
	constexpr int kRightMaster = 3;
	constexpr int kRightSlave = 4;
};

namespace ElevatorMap{
	constexpr int kWinchInverted = 1;
	constexpr int kLimitTop = 0;
	constexpr int kLimitBottom = 1;
	constexpr int kTopInverted = 1;
	constexpr int kBottomInverted = 1;
	constexpr int kWinch = 5;
};

namespace IntakeMap{
	constexpr int kGripperOpen = 0;
	constexpr int kGripperClose = 1;
	constexpr int kIntakeLeft = 0;
	constexpr int kIntakeRight = 1;
	constexpr int kBackBanner = 2;
}

namespace ClimberMap{
	constexpr int kWinch = 0;
	constexpr int kTelescope = 1;
	constexpr int kTilt = 2;
};

//Maps out gadgeteer ports on talons
namespace TalonMap{
	constexpr int kLeftEncoder = 1;
	constexpr int kRightEncoder = 3;
	constexpr int kPigeon = 4;
}
