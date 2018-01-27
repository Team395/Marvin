/*
 * PneumaticGripperCommand.cpp
 *
 *  Created on: Jan 26, 2018
 *      Author: JARVIS
 */

#include <Commands/PneumaticGripperCommand.h>

PneumaticGripperCommand::PneumaticGripperCommand(OI* oi, Intake* intake) : CommandBase("PneumaticgripperCommand"), oi{oi}, intake{intake}{
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
		intake->actuateClaw(oi->getIntakeThrottle());
	}
}

void PneumaticGripperCommand::finish(){
	CommandBase::finish();
}
