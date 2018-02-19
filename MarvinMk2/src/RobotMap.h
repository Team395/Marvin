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
		constexpr int kClawRelease = 1;
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
	constexpr int kLeftMaster = 5;
	constexpr int kLeftSlave = 2;
	constexpr int kRightMaster = 3;
	constexpr int kRightSlave = 1;
};

namespace ElevatorMap{
	constexpr int kWinchInverted = 1;
	constexpr int kLimitTop = 0;
	constexpr int kLimitBottom = 1;
	constexpr int kTopInverted = 0;
	constexpr int kBottomInverted = 0;
	constexpr int kWinch = 4;
};

namespace IntakeMap{
	constexpr int kGripperOpen = 1;
	constexpr int kGripperClose = 0;
	constexpr int kIntakeLeft = 0;
	constexpr int kIntakeRight = 1;
	constexpr int kBackBanner = 9;
}

//Maps out gadgeteer ports on talons
namespace TalonMap{
	constexpr int kLeftEncoder = 1;
	constexpr int kRightEncoder = 3;
	constexpr int kPigeon = 2;
}
