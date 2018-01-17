/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "OI.h"

#include <WPILib.h>
#include "RobotMap.h"
#include <Joystick.h>

OI::OI(){

}

double OI::GetDriveY(){
	return driveStick.GetY();
}

double OI::GetDriveZ(){
	return driveStick.GetZ();
}

double OI::GetManipulatorY(){
	return manipulatorStick.GetY();
}
