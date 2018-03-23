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
	return -1 * driveStickLeft.GetY();
}

double OI::getDriveRight(){
	return -1 * driveStickRight.GetY();
}

double OI::getElevatorThrottle(){
	double throttle = xboxController.GetRawAxis(OIMap::Xbox::kElevator);
	double deadband = 0.25;
	if(std::abs(throttle) < deadband){
		return 0;
	}
	else{
		return -1 * throttle;
	}
}

double OI::getIntakeThrottle(){
	double throttle = xboxController.GetRawAxis(OIMap::Xbox::kIntakeThrottle);
	double deadband = 0.25;
	if(std::abs(throttle) < deadband){
		return 0;
	}
	else{
		return -1 * throttle;
	}
}

OI::RequestedClawState OI::getRequestedIntakePosition(){
	if(xboxController.GetRawAxis(OIMap::Xbox::kIntakeClose) > 0.5){
		return RequestedClawState::kClose;

//		return 1;
	}
	else if(xboxController.GetRawAxis(OIMap::Xbox::kIntakeOpen) > 0.5){
		return RequestedClawState::kOpen;
//		return -1;
	}
	else{
		return RequestedClawState::kDoNothing;
//		return 0;
	}
}

OI::ElevatorPreset OI::getElevatorPreset(){
//	if(xboxController.GetRawButtonPressed(OIMap::Xbox::kHighScalePreset)){
//		return ElevatorPreset::kHighScale;
//	}
//	else if(xboxController.GetRawButtonPressed(OIMap::Xbox::kNormalScalePreset)){
//		return ElevatorPreset::kNormalScale;
//	}
//	else if(xboxController.GetRawButtonPressed(OIMap::Xbox::kLowScalePreset)){
//		return ElevatorPreset::kLowScale;
//	}
//	else if(xboxController.GetRawButtonPressed(OIMap::Xbox::kSwitchPreset)){
//		return ElevatorPreset::kSwitch;
//	}
//	else if(xboxController.GetRawButtonPressed(OIMap::Xbox::kBottomPreset)){
//		return ElevatorPreset::kBottom;
//	}
//	else{
//		return ElevatorPreset::kNone;
//	}

	if(xboxController.GetYButton()){
		return ElevatorPreset::kHighScale;
	}
	else if(xboxController.GetBButton()){
		return ElevatorPreset::kNormalScale;
	}
	else if(xboxController.GetAButton()){
		return ElevatorPreset::kLowScale;
	}
	else if(xboxController.GetXButton()){
		return ElevatorPreset::kSwitch;
	}
	else if(xboxController.GetStickButton(frc::GenericHID::JoystickHand::kLeftHand)){
		return ElevatorPreset::kBottom;
	}
	else{
		return ElevatorPreset::kNone;
	}
}

frc::Joystick* OI::getLeftStick(){
	return &driveStickLeft;
}

bool OI::getTurnButton(){
	return driveStickRight.GetRawButton(2);
}

bool OI::getToggleIntakeMode(){
	return xboxController.GetBackButtonPressed();
}

bool OI::getIntakeAutoscore(){
	return xboxController.GetRawButtonPressed(OIMap::Xbox::kAutoScore);
}

bool OI::getShiftDownHalf(){
	return driveStickLeft.GetTrigger();
}

bool OI::getShiftDownSeventyFive(){
	return driveStickRight.GetTrigger();
}

bool OI::getExtendClimber() {
	// True if user pushes up on D-PAD
	int angle = xboxController.GetPOV();
//	return (angle >= 315 || angle <= 45);
	return (angle > 315 && angle <= 360) || (angle >= 0 && angle < 45);
}

bool OI::getRetractClimber() {
	// True if user pushes down on D-PAD or LB
	int angle = xboxController.GetPOV();
//	return (angle >= 135 || angle <= 225) || xboxController.GetBumper(frc::GenericHID::JoystickHand::kLeftHand);
	return (angle > 135 && angle < 225) || xboxController.GetBumper(frc::GenericHID::JoystickHand::kLeftHand);
}

bool OI::getTiltClimber() {
	// True if user pushes left on D-PAD
	int angle = xboxController.GetPOV();
//	return (angle >= 225 || angle <= 315);
	return (angle > 225 && angle < 315);
}

bool OI::getWinchClimber(){
	// True if user pushes right on D-PAD or RB
	int angle = xboxController.GetPOV();
//	return (angle >= 45 || angle <= 135);
	return (angle > 45 && angle < 135) || xboxController.GetBumper(frc::GenericHID::JoystickHand::kRightHand);
}
