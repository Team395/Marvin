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
	// TODO Auto-generated constructor stub
}

JoystickElevatorCommand::~JoystickElevatorCommand() {
	// TODO Auto-generated destructor stub
}

void JoystickElevatorCommand::init() {
	CommandBase::init();
}

void JoystickElevatorCommand::update() {
	double speed = oi->getElevatorThrottle();

	if((speed > 0 && elevator->topPressed())){
		elevator->setWinchPercent(0);
	}
	else if((speed < 0 && elevator->bottomPressed())){
		elevator->setWinchPercent(0);
	}
	else{
		elevator->setWinchPercent(speed);
	}
}

void JoystickElevatorCommand::finish() {
	CommandBase::finish();
}
