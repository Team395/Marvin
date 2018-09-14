/*
 * Elevator.cpp
 *
 *  Created on: Jan 15, 2018
 *      Author: JARVIS
 */

#include "Elevator.h"
#include <SmartDashboard/SmartDashboard.h>

Elevator::Elevator() : SystemBase("elevator"), driveUpLastCommand(false) {
	winchOneController.SetSensorPhase(false);
	winchOneController.SetInverted(false);
	winchTwoController.SetInverted(false);
	winchTwoController.Follow(winchOneController);
}

Elevator::~Elevator() {

}

bool Elevator::topPressed(){
	return ElevatorMap::kTopInverted
			? !topLimit.Get()
			: topLimit.Get();
}

bool Elevator::bottomPressed(){
	return ElevatorMap::kBottomInverted
			? !bottomLimit.Get()
			: bottomLimit.Get();
}

double Elevator::getOffset(){
	return percentOutputOffset;
}

void Elevator::setOffset(double offset){
	percentOutputOffset = offset;
}

double Elevator::PIDGet(){
	double currentSensorPositionTicks = winchOneController.GetSelectedSensorPosition(0);
	double pidGet = currentSensorPositionTicks * inchesPerTick;
	frc::SmartDashboard::PutNumber("PIDGet", pidGet);
	currentPosition = currentSensorPositionTicks;
	return pidGet;
}

void Elevator::PIDWrite(double throttle){
	double pidWrite = throttle + percentOutputOffset;
//	frc::SmartDashboard::PutNumber("PIDWrite", pidWrite);
//	frc::SmartDashboard::PutNumber("PID O", percentOutputOffset);
//	double minimum = currentPosition > ElevatorPresets::kSwitchHeight
//			? minimumAcceptableOutputAboveSwitchHeight
//			: minimumAcceptableOutputBelowSwitchHeight;
	double minimum = -.1;
//	double minimum = 0;
	pidWrite = pidWrite > minimum ? pidWrite : minimum;
	winchOneController.Set(ControlMode::PercentOutput, pidWrite);
}

void Elevator::homeEncoder(){
	winchOneController.SetSelectedSensorPosition(0, 0, 0);
}

void Elevator::driveWinch(double throttle){
	winchOneController.Set(ControlMode::PercentOutput, 0);
}
