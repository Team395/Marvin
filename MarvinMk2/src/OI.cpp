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
	// xboxcontroller
#if 0
	if(xboxController.GetRawAxis(OIMap::Xbox::kIntakeClose) > 0.5){
//		return RequestedClawState::kClose;
#else
	// ZD-T
	if(xboxController.GetRawButton(OIMap::Xbox::kIntakeClose)){
			return RequestedClawState::kClose;
#endif
//		return 1;
	}
	// xboxcontroller
#if 0
	else if(xboxController.GetRawAxis(OIMap::Xbox::kIntakeOpen) > 0.5){
		return RequestedClawState::kOpen;
#else
	// ZD-T
	else if(xboxController.GetRawButton(OIMap::Xbox::kIntakeOpen)){
			return RequestedClawState::kOpen;
#endif
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
#if 0
	// xboxcontroller
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
#else
	// ZD-T
	if(xboxController.GetRawButton(1)){
		return ElevatorPreset::kHighScale;
	}
	else if(xboxController.GetRawButton(2)){
		return ElevatorPreset::kNormalScale;
	}
	else if(xboxController.GetRawButton(3)){
		return ElevatorPreset::kLowScale;
	}
	else if(xboxController.GetRawButton(4)){
		return ElevatorPreset::kSwitch;
	}
	else if(xboxController.GetRawButton(11)){
		return ElevatorPreset::kBottom;
	}
	else{
		return ElevatorPreset::kNone;
	}
#endif
}

frc::Joystick* OI::getLeftStick(){
	return &driveStickLeft;
}

bool OI::getTurnButton(){
	return driveStickRight.GetRawButton(2);
}

bool OI::getToggleIntakeMode(){
#if 0
	// xboxcontroller
	return xboxController.GetBackButtonPressed();
#else
	return xboxController.GetRawButtonPressed(9);
#endif
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
#if 0
	// xboxcontroller
	return (angle > 135 && angle < 225) || xboxController.GetBumper(frc::GenericHID::JoystickHand::kLeftHand);
#else
	return (angle > 135 && angle < 225) || xboxController.GetRawButton(5);
#endif
}

bool OI::getWinchClimber(){
#if 0
	//	int angle = xboxController.GetPOV();
	//	return (angle != -1) || xboxController.GetBumper(frc::GenericHID::JoystickHand::kRightHand);
#else
	// True if user pushes right on D-PAD or RB
	int angle = xboxController.GetPOV();
//		return (angle >= 45 || angle <= 135)
#if 0
		return (angle > 45 && angle < 135)
				|| xboxController.GetBumper(frc::GenericHID::JoystickHand::kRightHand);
#else
		return (angle > 45 && angle < 135)
						|| xboxController.GetRawButton(6);
#endif
#endif
}
