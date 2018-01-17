/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "SetWristSetpoint.h"

#include "../Robot.h"

SetWristSetpoint::SetWristSetpoint(double setpoint)
    : frc::Command("SetWristSetpoint") {
	m_setpoint = setpoint;
	Requires(&Robot::wrist);
}

// Called just before this Command runs the first time
void SetWristSetpoint::Initialize() {
	Robot::wrist.SetSetpoint(m_setpoint);
	Robot::wrist.Enable();
}

// Make this return true when this Command no longer needs to run execute()
bool SetWristSetpoint::IsFinished() {
	return Robot::wrist.OnTarget();
}
