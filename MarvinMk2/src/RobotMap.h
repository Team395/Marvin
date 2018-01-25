/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

namespace OIMap{
	constexpr int kDriveStick = 0;
	constexpr int kManipulatorStick = 1;
	constexpr int kTurnButton = 1;
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
	constexpr int kIntakeLeft = 4;
	constexpr bool kIntakeLeftInverted = false;
	constexpr int kIntakeRight = 5;
	constexpr bool kIntakeRightInverted = false;
}

namespace CANMap{
	constexpr int kWinch = 0;
	constexpr int kPigeon = 1;
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
