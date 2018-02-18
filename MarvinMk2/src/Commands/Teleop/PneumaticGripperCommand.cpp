/*
 * PneumaticGripperCommand.cpp
 *
 *  Created on: Jan 26, 2018
 *      Author: JARVIS
 */

#include <Commands/PneumaticGripperCommand.h>
#include <SmartDashboard/Smartdashboard.h>
#include <iostream>

PneumaticGripperCommand::PneumaticGripperCommand(Intake* intake, OI* oi) : CommandBase("PneumaticgripperCommand"), intake{intake}, oi{oi}{

}

PneumaticGripperCommand::~PneumaticGripperCommand() {

}

void PneumaticGripperCommand::init(){
	CommandBase::init();
}

void PneumaticGripperCommand::update(){
	//What mode in
	int actuate = (oi->getIntakePosition());
	double throttle= oi->getIntakeThrottle();

	if(intake->getState() == IntakeState::automatic && actuate != 0){
		intake->setState(IntakeState::manual);
	}
	else if(intake->getState() == IntakeState::manual && actuate == 1 && intake->getClawOpen()){
		intake->setState(IntakeState::automatic);
	}

	//Claw Position
	if(intake->getState() == IntakeState::automatic){
		if(!(intake->getSideBanner() || intake->getBackBanner())){
			intake->actuateClaw(false);
		}
		else{
			intake->actuateClaw(true);
		}

	}
	else{
		switch(actuate){
			case 1:
				intake->actuateClaw(true);
				break;

			case -1:
				intake->actuateClaw(false);
				break;

			case 0:
				break;
		}
	}

	//Wheel Speed
	if(intake->getState() == IntakeState::automatic){
		if(!(intake->getSideBanner() || intake->getBackBanner())){
			intake->driveLeft(throttle);
			intake->driveRight(throttle);
		}
		else if(intake->getSideBanner() && !intake->getBackBanner()){
			intake->driveLeft(-1);
			intake->driveRight(-1);
		}
		else if(intake->getBackBanner()){
			intake->driveLeft(0);
			intake->driveRight(0);
		}
	}
	else{
		intake->driveLeft(throttle);
		intake->driveRight(throttle);
	}
}

void PneumaticGripperCommand::finish(){
	CommandBase::finish();
}
