/*
 * Elevator.cpp
 *
 *  Created on: Jan 15, 2018
 *      Author: JARVIS
 */

#include "Elevator.h"
#include <SmartDashboard/SmartDashboard.h>

Elevator::Elevator(NewTalonMap* newTalonMap)
    : SystemBase("elevator"),
	  newTalonMap_(newTalonMap),
	  driveUpLastCommand(false)
{
#if 0
	winchOneController.SetSensorPhase(false);
	winchOneController.SetInverted(false);
	winchTwoController.SetInverted(false);
	winchTwoController.Follow(winchOneController);
#else
	newTalonMap_->getTalonByID(TalonMap::kWinchEncoder)->SetSensorPhase(true);
	newTalonMap_->getTalonByID(ElevatorMap::kWinchOne)->SetInverted(true);
#endif
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
#if 0
	double currentSensorPositionTicks = winchOneController.GetSelectedSensorPosition(0);
#else
	double currentSensorPositionTicks = newTalonMap_->getTalonByID(TalonMap::kWinchEncoder)->GetSelectedSensorPosition(0);
#endif
	double pidGet = currentSensorPositionTicks * inchesPerTick;
	frc::SmartDashboard::PutNumber("PIDGet", pidGet);
	currentPosition = currentSensorPositionTicks;
	return pidGet;
}

void Elevator::PIDWrite(double throttle){
	double pidWrite = throttle + percentOutputOffset;
	frc::SmartDashboard::PutNumber("PIDWrite", pidWrite);
//	frc::SmartDashboard::PutNumber("PID O", percentOutputOffset);
//	double minimum = currentPosition > ElevatorPresets::kSwitchHeight
//			? minimumAcceptableOutputAboveSwitchHeight
//			: minimumAcceptableOutputBelowSwitchHeight;
	double minimum = -.1;
//	double minimum = 0;
	pidWrite = pidWrite > minimum ? pidWrite : minimum;
	// TODO:  Java backport cleanup
#if 0
	winchOneController.Set(ControlMode::PercentOutput, pidWrite);
#else
	newTalonMap_->getTalonByID(ElevatorMap::kWinchOne)->Set(ControlMode::PercentOutput, pidWrite);
#endif
}

void Elevator::homeEncoder(){
	// TODO:  Java backport cleanup
#if 0
	winchOneController.SetSelectedSensorPosition(0, 0, 0);
#else
	newTalonMap_->getTalonByID(TalonMap::kWinchEncoder)->SetSelectedSensorPosition(0, 0, 0);
#endif
}

void Elevator::driveWinch(double throttle){
	// TODO:  Java backport cleanup
#if 0
	winchOneController.Set(ControlMode::PercentOutput, 0);
#else
	newTalonMap_->getTalonByID(ElevatorMap::kWinchOne)->Set(ControlMode::PercentOutput, 0);
#endif
}
