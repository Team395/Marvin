/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/
#include <Joystick.h>

#include <RobotMap.h>

#include "OI.h"

OI::OI(){

}

double OI::getDriveLeft(){
	return driveStickLeft.GetY();
}

double OI::getDriveRight(){
	return driveStickRight.GetY();
}

bool OI::getTurnButton(){
	return driveStickLeft.GetRawButton(OIMap::LeftStick::kTurnButton);
}

double OI::getElevatorThrottle(){
	if(xboxController.GetRawAxis(OIMap::Xbox::kElevatorUp) > 0 && xboxController.GetRawAxis(OIMap::Xbox::kElevatorDown) == 0){
		return xboxController.GetRawAxis(OIMap::Xbox::kElevatorUp);
	}
	else if(xboxController.GetRawAxis(OIMap::Xbox::kElevatorDown) > 0
			&& xboxController.GetRawAxis(OIMap::Xbox::kElevatorUp) == 0){
		return -xboxController.GetRawAxis(OIMap::Xbox::kElevatorDown);
	}
	else{
		return 0;
	}
}

double OI::getIntakeThrottle(){
	/*if(xboxController.GetRawButton(OIMap::kIntakeIn) && xboxController.GetRawButton(OIMap::kIntakeOut)){
		return 0;
	}
	else */if(xboxController.GetRawButton(OIMap::Xbox::kIntakeIn)){
		return 1;
	}
	else if(xboxController.GetRawButton(OIMap::Xbox::kIntakeOut)){
		return -1;
	}
	else{
		return 0;
	}
}

bool OI::getClawDisable(){
	return xboxController.GetRawButton(OIMap::Xbox::kClawRelease);
}

bool OI::getShiftButton(){
	return driveStickRight.GetRawButton(OIMap::RightStick::kShiftButton);
}
