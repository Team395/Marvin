/*
 * PneumaticGripperCommand.cpp
 *
 *  Created on: Jan 26, 2018
 *      Author: JARVIS
 */

#include <Commands/PneumaticGripperCommand.h>
#include <SmartDashboard/Smartdashboard.h>

PneumaticGripperCommand::PneumaticGripperCommand(Intake* intake, OI* oi) : CommandBase("PneumaticgripperCommand"), intake{intake}, oi{oi}{
	intake->disable();
}

PneumaticGripperCommand::~PneumaticGripperCommand() {
	// TODO Auto-generated destructor stub
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

	intake->driveLeft(oi->getIntakeThrottle()*IntakeMap::kIntakeLeftInverted);
	intake->driveRight(oi->getIntakeThrottle()*IntakeMap::kIntakeLeftInverted);
}

void PneumaticGripperCommand::finish(){
	CommandBase::finish();
}
