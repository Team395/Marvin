/*
 * JoystickClimberCommand.cpp
 *
 *  Created on: Mar 11, 2018
 *      Author: JARVIS
 */

#include <Commands/Teleop/JoystickClimberCommand.h>

JoystickClimberCommand::JoystickClimberCommand(OI* oi, ClimberSystem* climberSystem)
	: CommandBase("JoystickClimberCommand"),
	  oi{oi},
	  climberSystem{climberSystem}
{
}

JoystickClimberCommand::~JoystickClimberCommand() {
}

void JoystickClimberCommand::init() {
	CommandBase::init();
}

void JoystickClimberCommand::update() {
	if (oi->getExtendClimber()) {
		climberSystem->extendClimber();
	} else {
		climberSystem->stopTelescopingClimber();
	}

	if (oi->getRetractClimber()) {
		climberSystem->retractClimber();
	} else {
		climberSystem->stopTelescopingClimber();
	}

	if (oi->getWinchClimber()) {
		climberSystem->startClimbing();
	} else {
		climberSystem->stopClimbing();
	}

	if (oi->getTiltClimber()) {
		climberSystem->releaseClimber();
	}
}

void JoystickClimberCommand::finish() {
	CommandBase::finish();
}

