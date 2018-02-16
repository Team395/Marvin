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
	intake->disable();
}

PneumaticGripperCommand::~PneumaticGripperCommand() {

}

void PneumaticGripperCommand::init(){
	CommandBase::init();
}

void PneumaticGripperCommand::update(){
	if(oi->getClawDisable()){
		intake->disable();
	}
	else{
		double throttle = (oi->getIntakePosition());
		if(throttle == 1){
			intake->actuateClaw(true);
			SmartDashboard::PutBoolean("Claw Open", true);
		}
		else if(throttle == -1){
			intake->actuateClaw(false);
			SmartDashboard::PutBoolean("Claw Open", false);
		}
	}
	double throttle  = oi->getIntakeThrottle();
	std::cout << throttle << std::endl;
	intake->driveLeft(throttle*IntakeMap::kIntakeLeftInverted * 790/860);
	intake->driveRight(throttle*IntakeMap::kIntakeRightInverted);
}

void PneumaticGripperCommand::finish(){
	CommandBase::finish();
}
