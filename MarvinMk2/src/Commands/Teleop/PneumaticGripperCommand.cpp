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
	if(intake->getBackBanner() && Timer::GetFPGATimestamp() - timerStartedTime > sensorDelay){
		intake->setClawOpen(false);
	}
//	else if(timerStartedTime != -1){
//		intake->setClawOpen(true);
//	}

	//Wheel Speed
	if(!intake->getBackBanner()){
		intake->driveLeft(throttle);
		intake->driveRight(throttle);
		intake->setClawOpen(true);
		cubeInIntake = false;
		bannerSensorTripped = false;
	}
	else{
		if(!cubeInIntake){
			if(!bannerSensorTripped){
				bannerSensorTripped = true;
				timerStartedTime = Timer::GetFPGATimestamp();
			}

			if(Timer::GetFPGATimestamp() - timerStartedTime > intakeTime + sensorDelay){
				cubeInIntake = true;
			}
			intake->driveLeft(-1);
			intake->driveRight(-1);
		}
		else{
			intake->driveLeft(throttle);
			intake->driveRight(throttle);
			intake->setState(IntakeState::manual);
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
	return updateAutoscore(0.4);
}

bool PneumaticGripperCommand::updateAutoscore(double throttle){
	if(!scoreTimerStarted){
		timerStartedTime = Timer::GetFPGATimestamp();
		scoreTimerStarted = true;
	}
	intake->driveLeft(throttle);
	intake->driveRight(throttle);
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
	if(!intake->getBackBanner()) {
		cubeInIntake = false;
		intake->setState(intakeStatePriorToRetain);
		intake->driveLeft(0);
		intake->driveRight(0);
		return;
	}
	if(!retainPeriodTimerStarted){
		retainPeriodTimerStartedTime = frc::Timer::GetFPGATimestamp();
		retainPeriodTimerStarted = true;
	}

	if(frc::Timer::GetFPGATimestamp() - retainPeriodTimerStartedTime > retainTimerPeriod) {
		if(!retainTimerStarted){
			retainTimerStartedTime = frc::Timer::GetFPGATimestamp();
			retainTimerStarted = true;
		}

		intake->driveLeft(-1);
		intake->driveRight(-1);

		if(frc::Timer::GetFPGATimestamp() - retainTimerStartedTime > retainTimerDuration){
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
	//Read in inputs
	GripperState gripperState = intake->getGripperState();
	OI::RequestedClawState actuate = oi->getRequestedIntakePosition();
	double throttle= oi->getIntakeThrottle();
	bool autoscore = oi->getIntakeAutoscore();

	if(oi->getToggleIntakeMode()){
		if(intake->getState() == IntakeState::automatic) intake->setState(IntakeState::manual);
		else if(intake->getState() == IntakeState::manual) intake->setState(IntakeState::automatic);
	}
	else if(elevatorAutomaticThresholdState == ElevatorAutomaticThreshold::kBelow && elevator->PIDGet() > kElevatorAutomaticThreshold) {
		intake->setState(IntakeState::manual);
	}
	else if(elevatorAutomaticThresholdState == ElevatorAutomaticThreshold::kAbove && elevator->PIDGet() < kElevatorAutomaticThreshold) {
		intake->setState(IntakeState::automatic);
	}
	else if(intake->getState() == IntakeState::automatic && actuate != OI::RequestedClawState::kDoNothing){
		intake->setState(IntakeState::manual);
	}
//	else if(cubeInIntake && gripperState == GripperState::close){
//		if(intake->getState() != IntakeState::retain) {
//			intakeStatePriorToRetain = IntakeState::manual;
//		}
//		intake->setState(IntakeState::retain);
//	}

	if(intake->getState() != IntakeState::retain) {
		retainTimerStarted = false;
		retainPeriodTimerStarted = false;
	}

	elevatorAutomaticThresholdState = elevator->PIDGet() > kElevatorAutomaticThreshold
			? ElevatorAutomaticThreshold::kAbove
			: ElevatorAutomaticThreshold::kBelow;

	frc::SmartDashboard::PutNumber("elevatorThresholdState", (int)elevatorAutomaticThresholdState);
	frc::SmartDashboard::PutNumber("intakeState", (int)intake->getState());
	frc::SmartDashboard::PutNumber("elevatorPosition", elevator->PIDGet());

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

//	SmartDashboard::PutBoolean("Banner Sensor", intake->getBackBanner());
//	SmartDashboard::PutNumber("IntakeState", (int)intake->getState());
//	SmartDashboard::PutNumber("RequestedIntakeState", (int)actuate);
}

void PneumaticGripperCommand::finish(){
	CommandBase::finish();
}

void PneumaticGripperCommand::disable(){

}
