/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

//TODO Recheck All

namespace OIMap{
	namespace Xbox{
		constexpr int kXboxController = 2;
		constexpr int kElevator = 1;
#if 1
		constexpr int kIntakeThrottle = 5; // axis - xboxcontroller
		constexpr int kIntakeOpen = 2; // axis - xboxcontroller
		constexpr int kIntakeClose = 3; // axis - xboxcontroller
#else
		constexpr int kIntakeThrottle = 3; // axis - ZD-T
		constexpr int kIntakeOpen = 7; // button - ZD-T
		constexpr int kIntakeClose = 8; // button - ZD-T
#endif
		constexpr int kHighScalePreset = 4;
		constexpr int kNormalScalePreset = 2;
		constexpr int kLowScalePreset = 1;
		constexpr int kSwitchPreset = 3;
		constexpr int kBottomPreset = 9 ;

#if 1
		constexpr int kAutoScore = 10;
#else
		constexpr int kAutoScore = 12;
#endif
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
//	constexpr int kWinchOneInverted = 1; //TODO check
//	constexpr int kWinchTwoInverted = 1;
	constexpr int kLimitTop = 7;
	constexpr int kLimitBottom = 5;
	constexpr int kTopInverted = 1;
	constexpr int kBottomInverted = 1;
	constexpr int kWinchOne = 5;
	constexpr int kWinchTwo = 6; //TODO flash talon
};

namespace IntakeMap{
	constexpr int kGripperOpen = 1; //Check
	constexpr int kGripperClose = 0; //Check
	constexpr int kIntakeLeft = 0;
	constexpr int kIntakeRight = 1;
	constexpr int kBackBanner = 9;
	constexpr int kReleaseServo = 9;
}

namespace ClimberMap{
	constexpr int kWinch = 4;
	constexpr int kTelescope = 3;
};

//Maps out gadgeteer ports on talons
// Equivalent to SensorMap in Java code
namespace TalonMap{
	constexpr int kLeftEncoder = 2;
	constexpr int kRightEncoder = 3;
	constexpr int kPigeon = 5;
	constexpr int kWinchEncoder = 1;
}


namespace ChooserMap{
	constexpr int kLeft = 3;
	constexpr int kRight = 2;
	constexpr int kSwitch = 1;
	constexpr int kScale = 0;
}
