/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

namespace OIMap{
	const int kDriveStick = 0;
	const int kManipulatorStick = 1;
	const int kTurnButton = 1;
};

namespace DrivebaseMap{
	const int kLeft1 = 2;
	const int kLeft2 = 3;
	const int kRight1 = 0;
	const int kRight2 = 1;
};

namespace ElevatorMap{
	const int kWinchInverted = 0;
	const int kLimitTop = 0;
	const int kLimitBottom = 1;
	const int kTopInverted = 0;
	const int kBottomInverted = 0;
};

namespace CANMap{
	const int kWinch = 0;
	const int kPigeon = 1;
}

/**
 * The RobotMap is a mapping from the ports sensors and actuators are wired into
 * to a variable name. This provides flexibility changing wiring, makes checking
 * the wiring easier and significantly reduces the number of magic numbers
 * floating around.
 */

// For example to map the left and right motors, you could define the
// following variables to use with your drivetrain subsystem.
// constexpr int kLeftMotor = 1;
// constexpr int kRightMotor = 2;

// If you are using multiple modules, make sure to define both the port
// number and the module. For example you with a rangefinder:
// constexpr int kRangeFinderPort = 1;
// constexpr int kRangeFinderModule = 1;
