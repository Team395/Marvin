/*
 * JoystickClimberCommand.cpp
 *
 *  Created on: Mar 11, 2018
 *      Author: JARVIS
 */

#include <Commands/Teleop/JoystickClimberCommand.h>

#include <SmartDashboard/Smartdashboard.h>
#include <iostream>

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
#if 1
	if (oi->getWinchClimber()) {
		climberSystem->startClimbing();
	} else {
		climberSystem->stopClimbing();
	}
#else
	SmartDashboard::PutBoolean("ExtendClimber", oi->getExtendClimber());
	SmartDashboard::PutBoolean("RetractClimber", oi->getRetractClimber());
	SmartDashboard::PutBoolean("WinchClimber", oi->getWinchClimber());
	SmartDashboard::PutBoolean("TiltClimber", oi->getTiltClimber());
	if (oi->getExtendClimber()) {
		climberSystem->extendClimber();
	} else if (oi->getRetractClimber()) {
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
#endif
}

void JoystickClimberCommand::finish() {
	CommandBase::finish();
}

void JoystickClimberCommand::disable(){}

