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

void PneumaticGripperCommand::updateAutomatic(int actuate, double throttle){
	//Claw Position
	if(!intake->getBackBanner()){
			intake->actuateClaw(false);
	}
	else{
		intake->actuateClaw(true);
	}

	//Wheel Speed
	if(!intake->getBackBanner()){
		intake->driveLeft(throttle);
		intake->driveRight(throttle);
		cubeInIntake = false;
		bannerSensorTripped = false;
	}
	else if(intake->getBackBanner() && !cubeInIntake){
		if(!bannerSensorTripped){
			bannerSensorTripped = true;
			bannerSensorTrippedTime = Timer::GetFPGATimestamp();
		}
		intake->driveLeft(-1);
		intake->driveRight(-1);
		if(Timer::GetFPGATimestamp() - intakeTime > bannerSensorTrippedTime){
			cubeInIntake = true;
		}
	}
	else if(intake->getBackBanner() && cubeInIntake){
		intake->driveLeft(0);
		intake->driveRight(0);
	}
}

void PneumaticGripperCommand::updateManual(int actuate, double throttle){
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

	intake->driveLeft(throttle);
	intake->driveRight(throttle);
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

	if(intake->getState() == IntakeState::automatic) {updateAutomatic(actuate, throttle);}
	else if(intake->getState() == IntakeState::manual) {updateManual(actuate, throttle);}

/*
	double throttle = oi->getIntakeThrottle();
	intake->driveLeft(throttle);
	intake->driveRight(throttle);

	int actuate = oi->getIntakePosition();
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
*/
}

void PneumaticGripperCommand::finish(){
	CommandBase::finish();
}
