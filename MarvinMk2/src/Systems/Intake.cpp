/*
. * Intake.cpp
 *
 *  Created on: Jan 24, 2018
 *      Author: hlewi
 */

#include "Intake.h"

Intake::Intake() : SystemBase("Intake"){

}

Intake::~Intake() {

}

void Intake::driveLeft(double speed){
	leftIntake.Set(speed);
}

void Intake::driveRight(double speed){
	//Scaling factor because different motor on half of the gripper
	rightIntake.Set(speed * 790/860);
}

void Intake::actuateClaw(bool open){
	if(open){
		clawOpen.Set(open);
		clawClose.Set(!open);
	}
	else{
		clawOpen.Set(false);
		clawClose.Set(true);
	}

}

bool Intake::getClawOpen(){
	return clawOpen.Get();
}
bool Intake::getSideBanner(){
	return sideBannerSensor.Get();
}

bool Intake::getBackBanner(){
	return backBannerSensor.Get();
}

void Intake::setState(IntakeState state){
	intakeState = state;
}

IntakeState Intake::getState(){
	return intakeState;
}
