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
			std::cout << "Setting high: " << ElevatorPresets::kHighHeight << std::endl;
			setpoint = ElevatorPresets::kHighHeight;
			break;
		case(OI::ElevatorPreset::kNormalScale):
			std::cout << "Setting normal: " << ElevatorPresets::kNormalHeight << std::endl;
			setpoint = ElevatorPresets::kNormalHeight;
			break;
		case(OI::ElevatorPreset::kLowScale):
			std::cout << "Setting low scale: " << ElevatorPresets::kLowHeight << std::endl;
			setpoint = ElevatorPresets::kLowHeight;
			break;
		case(OI::ElevatorPreset::kSwitch):
			std::cout << "Setting switch: " << ElevatorPresets::kSwitchHeight << std::endl;
			setpoint = ElevatorPresets::kSwitchHeight;
			break;
		case(OI::ElevatorPreset::kBottom):
			std::cout << "Setting bottom: " << ElevatorPresets::kBottomHeight << std::endl;
			setpoint = ElevatorPresets::kBottomHeight;
			break;
		case(OI::ElevatorPreset::kNone):
		default:
			std::cout << "Setting none: " << setpoint << std::endl;
			break;
	}
	double setpointIncrement = 0;
#if 0
	if(elevatorPositionCommand->getAbsError() < ElevatorPresets::kErrorThreshold){
		setpointIncrement = oi->getElevatorThrottle();
	}
#else
	setpointIncrement = oi->getElevatorThrottle();
#endif
	elevatorPositionCommand->setSetpoint(setpoint + 0.15*setpointIncrement);
//	std::cout<<setpoint<<std::endl;
}

void JoystickElevatorCommand::finish() {
	CommandBase::finish();
}

void JoystickElevatorCommand::disable(){}
