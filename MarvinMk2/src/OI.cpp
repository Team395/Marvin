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

double OI::getIntakeThrottle(){
	if(xboxController.GetRawAxis(OIMap::kIntakeIn) > 0 && xboxController.GetRawAxis(OIMap::kIntakeOut) == 0){
		return xboxController.GetRawAxis(OIMap::kIntakeIn);
	}
	else if(xboxController.GetRawAxis(OIMap::kIntakeOut) > 0 && xboxController.GetRawAxis(OIMap::kIntakeIn) == 0){
		return -xboxController.GetRawAxis(OIMap::kIntakeOut);
	}
	else{
		return 0;
	}
}

double OI::getIntakePosition(){
	/*if(xboxController.GetRawButton(OIMap::kIntakeIn) && xboxController.GetRawButton(OIMap::kIntakeOut)){
		return 0;
	}
	else */if(xboxController.GetRawButton(OIMap::kIntakeOpen)){
		return 1;
	}
	else if(xboxController.GetRawButton(OIMap::kIntakeClose)){
		return -1;
	}
	else{
		return 0;
	}
}

bool OI::getClawDisable(){
	return xboxController.GetRawButton(OIMap::kClawRelease);
}
