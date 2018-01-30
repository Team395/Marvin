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

double OI::getDriveY(){
	return driveStick.GetY();
}

double OI::getDriveZ(){
	return driveStick.GetZ();
}

bool OI::getTurnButton(){
	return driveStick.GetRawButton(OIMap::kTurnButton);
}

double OI::getElevatorThrottle(){
	if(xboxController.GetRawAxis(OIMap::kElevatorUp) > 0 && xboxController.GetRawAxis(OIMap::kElevatorDown) == 0){
		return xboxController.GetRawAxis(OIMap::kElevatorUp);
	}
	else if(xboxController.GetRawAxis(OIMap::kElevatorDown) > 0 && xboxController.GetRawAxis(OIMap::kElevatorUp) == 0){
		return -xboxController.GetRawAxis(OIMap::kElevatorDown);
	}
	else{
		return 0;
	}
}

double OI::getIntakeThrottle(){
	/*if(xboxController.GetRawButton(OIMap::kIntakeIn) && xboxController.GetRawButton(OIMap::kIntakeOut)){
		return 0;
	}
	else */if(xboxController.GetRawButton(OIMap::kIntakeIn)){
		return 1;
	}
	else if(xboxController.GetRawButton(OIMap::kIntakeOut)){
		return -1;
	}
	else{
		return 0;
	}
}

bool OI::getClawDisable(){
	return xboxController.GetRawButton(OIMap::kClawRelease);
}
