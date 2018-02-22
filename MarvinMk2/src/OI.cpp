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

double OI::getElevatorThrottle(){
	double throttle = xboxController.GetRawAxis(OIMap::Xbox::kElevator);
	double deadband = 0.15;
	if(std::abs(throttle) < deadband){
		return 0;
	}
	else{
		return -1 * throttle;
	}
}

double OI::getIntakeThrottle(){
	double throttle = xboxController.GetRawAxis(OIMap::Xbox::kIntakeThrottle);
	double deadband = 0.15;
	if(std::abs(throttle) < deadband){
		return 0;
	}
	else{
		return throttle;
	}
}

int OI::getIntakePosition(){
	if(xboxController.GetRawAxis(OIMap::Xbox::kIntakeClose) > 0.5){
		return 1;
	}
	else if(xboxController.GetRawAxis(OIMap::Xbox::kIntakeOpen) > 0.5){
		return -1;
	}
	else{
		return 0;
	}
}

OI::ElevatorPreset OI::getElevatorPreset(){
	if(xboxController.GetRawButtonPressed(OIMap::Xbox::kHighScalePreset)){
		return ElevatorPreset::kHighScale;
	}
	else if(xboxController.GetRawButtonPressed(OIMap::Xbox::kNormalScalePreset)){
		return ElevatorPreset::kNormalScale;
	}
	else if(xboxController.GetRawButtonPressed(OIMap::Xbox::kLowScalePreset)){
		return ElevatorPreset::kLowScale;
	}
	else if(xboxController.GetRawButtonPressed(OIMap::Xbox::kSwitchPreset)){
		return ElevatorPreset::kSwitch;
	}
	else if(xboxController.GetRawButtonPressed(OIMap::Xbox::kBottomPreset)){
		return ElevatorPreset::kBottom;
	}
	else{
		return ElevatorPreset::kNone;
	}
}
