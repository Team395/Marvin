/*
 * JoystickElevatorCommand.cpp
 *
 *  Created on: Jan 15, 2018
 *      Author: JARVIS
 */
#include <OI.h>

#include <Systems/Elevator.h>

#include "JoystickElevatorCommand.h"

JoystickElevatorCommand::JoystickElevatorCommand(Elevator* elevator, OI* oi) :
CommandBase("JoystickElevatorCommand"),
elevator(elevator),
oi(oi) {

}

JoystickElevatorCommand::~JoystickElevatorCommand() {

}

void JoystickElevatorCommand::init() {
	CommandBase::init();
}

void JoystickElevatorCommand::update() {
	double speed = oi->getElevatorThrottle();

	if((speed > 0 && elevator->topPressed())){
		elevator->driveWinch(0);
	}
	else if((speed < 0 && elevator->bottomPressed())){
		elevator->driveWinch(0);
	}
	else{
		elevator->driveWinch(speed);
	}
}

void JoystickElevatorCommand::finish() {
	CommandBase::finish();
}
