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

void PneumaticGripperCommand::updateManual(OI::RequestedClawState actuate, double throttle){
	switch(actuate){
		case OI::RequestedClawState::kClose:
			intake->setClawOpen(false);  // TODO:  check this is correct
			break;
		case OI::RequestedClawState::kOpen:
			intake->setClawOpen(true);  // TODO:  check this is correct
			break;
		default:
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
	OI::RequestedClawState actuate = oi->getRequestedIntakePosition();
	double throttle= oi->getIntakeThrottle();
	bool autoscore = oi->getIntakeAutoscore();

	if(oi->getToggleIntakeMode()){
		if(intake->getState() == IntakeState::automatic) intake->setState(IntakeState::manual);
		else if(intake->getState() == IntakeState::manual) intake->setState(IntakeState::automatic);
	}
	else if(intake->getState() == IntakeState::automatic && actuate != OI::RequestedClawState::kDoNothing){
		intake->setState(IntakeState::manual);
	}
	//TODO: probably needs to be fixed to account for placing a cube by opening the claw
//	else if(intake->getState() == IntakeState::manual && actuate == OI::RequestedClawState::kOpen && intake->getClawOpen()){
//		intake->setState(IntakeState::automatic);
//	}

	//TODO: remove
	//intake->setState(IntakeState::manual);

	if(autoscore){
		intake->setState(IntakeState::autoscore);
	}

	//Update based on mode
	switch (intake->getState()) {
		case IntakeState::automatic:
			updateAutomatic(throttle);
			break;
		case IntakeState::manual:
			updateManual(actuate, throttle);
			break;
		case IntakeState::autoscore:
			updateAutoscore();
			break;
	}

	SmartDashboard::PutBoolean("Banner Sensor", intake->getBackBanner());
	SmartDashboard::PutNumber("IntakeState", (int)intake->getState());
}

void PneumaticGripperCommand::finish(){
	CommandBase::finish();
}
