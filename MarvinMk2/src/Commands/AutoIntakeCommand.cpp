/*
 * AutoIntakeCommand.cpp
 *
 *  Created on: Mar 20, 2018
 *      Author: JARVIS
 */

#include <Commands/AutoIntakeCommand.h>

AutoIntakeCommand::AutoIntakeCommand(PneumaticGripperCommand* gripperCommand) : CommandBase("Auto Intake Command"), gripperCommand{gripperCommand}{
	// TODO Auto-generated constructor stub

}

AutoIntakeCommand::~AutoIntakeCommand() {
	// TODO Auto-generated destructor stub
}

void AutoIntakeCommand::init(){
	CommandBase::init();
}

void AutoIntakeCommand::update(){
	bool finished = gripperCommand->updateAutomatic(0);
	if(finished) finish();
}

void AutoIntakeCommand::finish(){
	CommandBase::finish();
}

void AutoIntakeCommand::disable(){}
