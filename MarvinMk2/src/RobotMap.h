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
		constexpr int kIntakeIn = 3;
		constexpr int kIntakeOut = 2;
		constexpr int kIntakeOpen = 5;
		constexpr int kIntakeClose = 6;
		constexpr int kClawRelease = 1;
	}

	namespace LeftStick{
		constexpr int kDriveStickLeft = 0;
		constexpr int kTurnButton = 1; //On left stick
	}

	namespace RightStick{
		constexpr int kDriveStickRight = 1;
		constexpr int kShiftButton = 1;
	}
};

namespace DrivebaseMap{
	constexpr int kLeftMaster = 1;
	constexpr int kLeftSlave = 2;
	constexpr int kRightMaster = 3;
	constexpr int kRightSlave = 4;
	constexpr int kLowGear = 3; //Should be extended
	constexpr int kHighGear = 2; //Should be retracted
};

namespace ElevatorMap{
	constexpr int kWinchInverted = 0;
	constexpr int kLimitTop = 0;
	constexpr int kLimitBottom = 1;
	constexpr int kTopInverted = 0;
	constexpr int kBottomInverted = 0;
	constexpr int kWinch = 5;
};

namespace IntakeMap{
	constexpr int kSolenoidOpen = 0;
	constexpr int kSolenoidClose = 1;
	constexpr int kIntakeLeft = 0;
	const int kIntakeLeftInverted = false ? -1 : 1;
	constexpr int kIntakeRight = 1;
	const int kIntakeRightInverted = false ? -1 : 1;
}

//Maps out gadgeteer ports on talons
namespace TalonMap{
	constexpr int kLeftEncoder = 1;
	constexpr int kRightEncoder = 3;
	constexpr int kPigeon = 2;
}
