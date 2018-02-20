/*
 * JoystickElevatorCommand.cpp
 *
 *  Created on: Jan 15, 2018
 *      Author: JARVIS
 */
#include <OI.h>

#include <Systems/Elevator.h>

#include "JoystickElevatorCommand.h"

JoystickElevatorCommand::JoystickElevatorCommand(Elevator* elevator, OI* oi, ElevatorPositionCommand* elevatorPositionCommand) :
CommandBase("JoystickElevatorCommand"),
elevator(elevator),
oi(oi),
elevatorPositionCommand(elevatorPositionCommand){

}

JoystickElevatorCommand::~JoystickElevatorCommand() {

}

void JoystickElevatorCommand::init() {
	CommandBase::init();
}

void JoystickElevatorCommand::update() {
	double setpointIncrement = oi->getElevatorThrottle();
	double setpoint = elevatorPositionCommand->getSetpoint();
	elevatorPositionCommand->setSetpoint(setpoint += 0.3*setpointIncrement);
}

void JoystickElevatorCommand::finish() {
	CommandBase::finish();
}
