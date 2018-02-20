/*
 * Elevator.cpp
 *
 *  Created on: Jan 15, 2018
 *      Author: JARVIS
 */

#include "Elevator.h"
#include <SmartDashboard/SmartDashboard.h>

Elevator::Elevator() : SystemBase("elevator"), driveUpLastCommand(false) {
	winchController.SetInverted(ElevatorMap::kWinchInverted);
	winchController.SetSensorPhase(false);
	winchController.SetInverted(false);
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
	double pidGet = winchController.GetSelectedSensorPosition(0) * inchesPerTick;
	frc::SmartDashboard::PutNumber("PIDGet", pidGet);
	return pidGet;
}

void Elevator::PIDWrite(double throttle){
	double pidWrite = throttle + percentOutputOffset;
	frc::SmartDashboard::PutNumber("PIDWrite", pidWrite);
	frc::SmartDashboard::PutNumber("PID O", percentOutputOffset);
	pidWrite = pidWrite > minimumAcceptableOutput ? pidWrite : minimumAcceptableOutput;
	winchController.Set(ControlMode::PercentOutput, pidWrite);
}

void Elevator::homeEncoder(){
	winchController.SetSelectedSensorPosition(0, 0, 0);
}
