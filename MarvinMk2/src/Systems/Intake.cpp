/*
. * Intake.cpp
 *
 *  Created on: Jan 24, 2018
 *      Author: hlewi
 */

#include "Intake.h"

Intake::Intake() : SystemBase("Intake"){
	leftIntake.SetInverted(false);
	rightIntake.SetInverted(false);
}

Intake::~Intake() {

}

void Intake::driveLeft(double speed){
	leftIntake.Set(speed);
}

void Intake::driveRight(double speed){
	rightIntake.Set(speed);
}

void Intake::setClawOpen(bool open){
	//leftGripperOpen and leftGripperClose are flipped
	leftGripperOpen.Set(!open);
	leftGripperClose.Set(open);
	rightGripperOpen.Set(!open);
	rightGripperClose.Set(open);

	setGripperState(open ? GripperState::open : GripperState::close);
}

bool Intake::getClawOpen(){
	return !leftGripperOpen.Get();
}

bool Intake::getBackBanner(){
	return !backBannerSensor.Get();
}

void Intake::setState(IntakeState state){
	intakeState = state;
}

IntakeState Intake::getState(){
	return intakeState;
}

void Intake::setGripperState(GripperState state){
	gripperState = state;
}

GripperState Intake::getGripperState(){
	return gripperState;
}
