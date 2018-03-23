/*
 * PneumaticGripperCommand.cpp
 *
 *  Created on: Jan 26, 2018
 *      Author: JARVIS
 */

#include <Commands/Teleop/PneumaticGripperCommand.h>
#include <SmartDashboard/Smartdashboard.h>
#include <iostream>

PneumaticGripperCommand::PneumaticGripperCommand(Intake* intake, Elevator* elevator, OI* oi) :
	CommandBase("PneumaticgripperCommand"),
	intake{intake},
	elevator{elevator},
	oi{oi}{

}

PneumaticGripperCommand::~PneumaticGripperCommand() {

}

bool PneumaticGripperCommand::updateAutomatic(double throttle){

	//Claw Position
	if(intake->getBackBanner() && Timer::GetFPGATimestamp() - timerStartedTime > 0.25){
		intake->setClawOpen(false);
	}
	else{
		intake->setClawOpen(true);
	}

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

			if(Timer::GetFPGATimestamp() - timerStartedTime > intakeTime + 0.25){
				cubeInIntake = true;
			}
			intake->driveLeft(-1);
			intake->driveRight(-1);
		}
		else{
			intake->driveLeft(throttle);
			intake->driveRight(throttle);
			return true;
		}
	}

	return false;
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

bool PneumaticGripperCommand::updateAutoscore(){
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
		return true;
	}
	return false;
}

void PneumaticGripperCommand::updateRetain(){
	if(!retainPeriodTimerStarted){
		retainPeriodTimerStartedTime = frc::Timer::GetFPGATimestamp();
		retainPeriodTimerStarted = true;
	}

	if(frc::Timer::GetFPGATimestamp() - retainPeriodTimerStartedTime > retainTimerPeriod) {
		if(!retainTimerStarted){
			retainTimerStarted = frc::Timer::GetFPGATimestamp();
			retainTimerStarted = true;
		}

		intake->driveLeft(-1);
		intake->driveRight(-1);

		if(frc::Timer::GetFPGATimestamp() - retainTimerStarted > retainTimerDuration){
			intake->driveLeft(0);
			intake->driveRight(0);

			retainTimerStarted = false;
			retainPeriodTimerStarted = false;

			intake->setState(intakeStatePriorToRetain);
		}
	}
}

void PneumaticGripperCommand::init(){
	CommandBase::init();
}

void PneumaticGripperCommand::update(){
	//TODO: remove
	if(oi->getShiftDownSeventyFive())
	{
		elevator->currentPosition = 20;
	}
	else if(oi->getShiftDownHalf()) {
		elevator->currentPosition = 1;
	}

	//Read in inputs
	OI::RequestedClawState actuate = oi->getRequestedIntakePosition();
	double throttle= oi->getIntakeThrottle();
	bool autoscore = oi->getIntakeAutoscore();

	if(oi->getToggleIntakeMode()){
		if(intake->getState() == IntakeState::automatic) intake->setState(IntakeState::manual);
		else if(intake->getState() == IntakeState::manual) intake->setState(IntakeState::automatic);
	}
	else if(elevatorAutomaticThresholdState == ElevatorAutomaticThreshold::kBelow && elevator->currentPosition > kElevatorAutomaticThreshold) {
		intake->setState(IntakeState::manual);
	}
	else if(elevatorAutomaticThresholdState == ElevatorAutomaticThreshold::kAbove && elevator->currentPosition < kElevatorAutomaticThreshold) {
		intake->setState(IntakeState::automatic);
	}
	else if(intake->getState() == IntakeState::automatic && actuate != OI::RequestedClawState::kDoNothing){
		intake->setState(IntakeState::manual);
	}
	else if(cubeInIntake && gripperState == GripperState::close){
		intakeStatePriorToRetain = intake->getState();
		intake->setState(IntakeState::retain);
	}

	if(intake->getState() != IntakeState::retain) {
		retainTimerStarted = false;
		retainPeriodTimerStarted = false;
	}

	elevatorAutomaticThresholdState = elevator->currentPosition > kElevatorAutomaticThreshold
			? ElevatorAutomaticThreshold::kAbove
			: ElevatorAutomaticThreshold::kBelow;

	//TODO: probably needs to be fixed to account for placing a cube by opening the claw
//	else if(intake->getState() == IntakeState::manual && actuate == OI::RequestedClawState::kOpen && intake->getClawOpen()){
//		intake->setState(IntakeState::automatic);
//	}

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
		case IntakeState::retain:
			updateRetain();
			break;
	}

	SmartDashboard::PutBoolean("Banner Sensor", intake->getBackBanner());
	SmartDashboard::PutNumber("IntakeState", (int)intake->getState());
	SmartDashboard::PutNumber("RequestedIntakeState", (int)actuate);
}

void PneumaticGripperCommand::finish(){
	CommandBase::finish();
}

void PneumaticGripperCommand::disable(){}
