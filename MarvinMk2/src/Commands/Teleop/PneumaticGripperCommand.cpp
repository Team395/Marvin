/*
 * PneumaticGripperCommand.cpp
 *
 *  Created on: Jan 26, 2018
 *      Author: JARVIS
 */

#include <Commands/Teleop/PneumaticGripperCommand.h>
#include <SmartDashboard/Smartdashboard.h>
#include <iostream>

PneumaticGripperCommand::PneumaticGripperCommand(Intake* intake, OI* oi) : CommandBase("PneumaticgripperCommand"), intake{intake}, oi{oi}{

}

PneumaticGripperCommand::~PneumaticGripperCommand() {

}

void PneumaticGripperCommand::updateAutomatic(double throttle){
	//Wheel Speed
	if(!intake->getBackBanner()){
		intake->driveLeft(throttle);
		intake->driveRight(throttle);
		cubeInIntake = false;
		bannerSensorTripped = false;
	}
	else{
		if(!cubeInIntake){
			if(!bannerSensorTripped){
				bannerSensorTripped = true;
				timerStartedTime = Timer::GetFPGATimestamp();
			}
			intake->driveLeft(-1);
			intake->driveRight(-1);
			if(Timer::GetFPGATimestamp() - timerStartedTime > intakeTime){
				cubeInIntake = true;
			}
		}
		else{
			intake->driveLeft(0);
			intake->driveRight(0);
		}
	}

	//Claw Position
	if(intake->getBackBanner()){
		intake->setClawOpen(false);
	}
	else{
		intake->setClawOpen(true);
	}
}

void PneumaticGripperCommand::updateManual(int actuate, double throttle){
	switch(actuate){
		case 1:
			intake->setClawOpen(true);
			break;

		case -1:
			intake->setClawOpen(false);
			break;

		case 0:
			break;
	}

	intake->driveLeft(throttle);
	intake->driveRight(throttle);
}

void PneumaticGripperCommand::updateAutoscore(){
	if(!scoreTimerStarted){
		timerStartedTime = Timer::GetFPGATimestamp();
		scoreTimerStarted = true;
	}
	intake->driveLeft(1);
	intake->driveRight(1);
	if(Timer::GetFPGATimestamp() - timerStartedTime > scoreTime){
		intake->setClawOpen(true);
		intake->driveLeft(0);
		intake->driveRight(0);
		intake->setState(IntakeState::automatic);
		scoreTimerStarted = false;
		cubeInIntake = false;
		bannerSensorTripped = false;
	}
}

void PneumaticGripperCommand::init(){
	CommandBase::init();
}

void PneumaticGripperCommand::update(){
	//Read in inputs
	int actuate = oi->getIntakePosition();
	double throttle= oi->getIntakeThrottle();
	bool autoscore = oi->getIntakeAutoscore();

	if(oi->getToggleIntakeMode()){
		if(intake->getState() == IntakeState::automatic) intake->setState(IntakeState::manual);
		else if(intake->getState() == IntakeState::manual) intake->setState(IntakeState::automatic);
	}
	else if(intake->getState() == IntakeState::automatic && actuate != 0){
		intake->setState(IntakeState::manual);
	}
	else if(intake->getState() == IntakeState::manual && actuate == 1 && intake->getClawOpen()){
		intake->setState(IntakeState::automatic);
	}
	if(autoscore){
		intake->setState(IntakeState::autoscore);
	}

	//Update based on mode
	if(intake->getState() == IntakeState::automatic){
		updateAutomatic(throttle);
	}
	else if(intake->getState() == IntakeState::manual) {
		updateManual(actuate, throttle);
	}
	else if(intake->getState() == IntakeState::autoscore){
		updateAutoscore();
	}
}

void PneumaticGripperCommand::finish(){
	CommandBase::finish();
}
