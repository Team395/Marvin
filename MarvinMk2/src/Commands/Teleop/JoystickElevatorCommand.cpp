/*
 * JoystickElevatorCommand.cpp
 *
 *  Created on: Jan 15, 2018
 *      Author: JARVIS
 */
#include <OI.h>
#include <iostream>
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
	double setpoint = elevatorPositionCommand->getSetpoint();

	switch(oi->getElevatorPreset()){
		case(OI::ElevatorPreset::kHighScale):
			setpoint = highHeight;
			break;
		case(OI::ElevatorPreset::kNormalScale):
			setpoint = normalHeight;
			break;
		case(OI::ElevatorPreset::kLowScale):
			setpoint = lowHeight;
			break;
		case(OI::ElevatorPreset::kSwitch):
			setpoint = switchHeight;
			break;
		case(OI::ElevatorPreset::kBottom):
			setpoint = bottomHeight;
			break;
		case(OI::ElevatorPreset::kNone):
			break;
	}
	double setpointIncrement = 0;
	if(elevatorPositionCommand->getAbsError() < errorThreshold){
		setpointIncrement = oi->getElevatorThrottle();
	}
	elevatorPositionCommand->setSetpoint(setpoint + 0.15*setpointIncrement);
	std::cout<<setpoint<<std::endl;
}

void JoystickElevatorCommand::finish() {
	CommandBase::finish();
}

void JoystickElevatorCommand::disable(){}
