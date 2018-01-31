/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

namespace OIMap{
	constexpr int kDriveStickLeft = 0;
	constexpr int kDriveStickRight = 1;
	constexpr int kXboxController = 2;
	constexpr int kTurnButton = 1;
	constexpr int kElevatorUp = 3;
	constexpr int kElevatorDown = 2;
	constexpr int kIntakeIn = 6;
	constexpr int kIntakeOut = 5;
	constexpr int kClawRelease = 1;
};

namespace DrivebaseMap{
	constexpr int kLeft1 = 2;
	constexpr int kLeft2 = 3;
	constexpr int kRight1 = 0;
	constexpr int kRight2 = 1;
};

namespace ElevatorMap{
	constexpr int kWinchInverted = 0;
	constexpr int kLimitTop = 0;
	constexpr int kLimitBottom = 1;
	constexpr int kTopInverted = 0;
	constexpr int kBottomInverted = 0;
};

namespace IntakeMap{
	constexpr int kSolenoidOpen = 0;
	constexpr int kSolenoidClose = 1;
	/*constexpr int kIntakeLeft = 4;
	constexpr bool kIntakeLeftInverted = false;
	constexpr int kIntakeRight = 5;
	constexpr bool kIntakeRightInverted = false;
	*/
}

namespace CANMap{
	constexpr int kWinch = 0;
	constexpr int kPigeon = 0;
}
