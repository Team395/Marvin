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
	return xboxController.GetRawAxis(OIMap::Xbox::kElevator);
}

double OI::getIntakeThrottle(){
	if(xboxController.GetRawAxis(OIMap::Xbox::kIntakeIn) > 0 && xboxController.GetRawAxis(OIMap::Xbox::kIntakeOut) == 0){
		return xboxController.GetRawAxis(OIMap::Xbox::kIntakeIn);
	}
	else if(xboxController.GetRawAxis(OIMap::Xbox::kIntakeOut) > 0 && xboxController.GetRawAxis(OIMap::Xbox::kIntakeIn) == 0){
		return -xboxController.GetRawAxis(OIMap::Xbox::kIntakeOut);
	}
	else{
		return 0;
	}
}

double OI::getIntakePosition(){
	/*if(xboxController.GetRawButton(OIMap::kIntakeIn) && xboxController.GetRawButton(OIMap::kIntakeOut)){
		return 0;
	}
	else */if(xboxController.GetRawButton(OIMap::Xbox::kIntakeOpen)){
		return 1;
	}
	else if(xboxController.GetRawButton(OIMap::Xbox::kIntakeClose)){
		return -1;
	}
	else{
		return 0;
	}
}

bool OI::getClawDisable(){
	return xboxController.GetRawButton(OIMap::Xbox::kClawRelease);
}

int OI::getShiftButtons(){
	bool low = driveStickRight.GetTriggerPressed();
	bool high = driveStickLeft.GetTriggerPressed();
	if(low == high) return 0;
	else if(high) return 1;
	else if(low) return -1;
	else return 0;
}
