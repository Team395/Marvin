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
			std::cout << "Setting high: " << highHeight << std::endl;
			setpoint = highHeight;
			break;
		case(OI::ElevatorPreset::kNormalScale):
			std::cout << "Setting normal: " << normalHeight << std::endl;
			setpoint = normalHeight;
			break;
		case(OI::ElevatorPreset::kLowScale):
			std::cout << "Setting low scale: " << lowHeight << std::endl;
			setpoint = lowHeight;
			break;
		case(OI::ElevatorPreset::kSwitch):
			std::cout << "Setting switch: " << switchHeight << std::endl;
			setpoint = switchHeight;
			break;
		case(OI::ElevatorPreset::kBottom):
			std::cout << "Setting bottom: " << bottomHeight << std::endl;
			setpoint = bottomHeight;
			break;
		case(OI::ElevatorPreset::kNone):
			std::cout << "Setting none: " << setpoint << std::endl;
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
