/*
 * AutoElevatorCommand.cpp
 *
 *  Created on: Mar 22, 2018
 *      Author: JARVIS
 */

#include <Commands/AutoElevatorCommand.h>
#include <Systems/Elevator.h>
#include <iostream>

AutoElevatorCommand::AutoElevatorCommand(ElevatorPositionCommand* positionCommand, OI::ElevatorPreset height) :
CommandBase("Auto Elevator Command"),
positionCommand{positionCommand},
height{height} {

}

AutoElevatorCommand::~AutoElevatorCommand() {

}

void AutoElevatorCommand::init(){
	CommandBase::init();
}

void AutoElevatorCommand::update(){
	std::cout << "setting height: " << (int)height << std::endl;
	double setpoint;
	switch(height){
		case(OI::ElevatorPreset::kHighScale):
				std::cout << "setting height high" << std::endl;
			setpoint = ElevatorPresets::kHighHeight;
			break;
		case(OI::ElevatorPreset::kNormalScale):
						std::cout << "setting normal high" << std::endl;
			setpoint = ElevatorPresets::kNormalHeight;
			break;
		case(OI::ElevatorPreset::kLowScale):
						std::cout << "setting height low" << std::endl;
			setpoint = ElevatorPresets::kLowHeight;
			break;
		case(OI::ElevatorPreset::kSwitch):
						std::cout << "setting height switch" << std::endl;
			setpoint = ElevatorPresets::kSwitchHeight;
			break;
		case(OI::ElevatorPreset::kBottom):
						std::cout << "setting height bottom" << std::endl;
			setpoint = ElevatorPresets::kBottomHeight;
			break;
		case(OI::ElevatorPreset::kDeploy):
				std::cout << "deploying" << std::endl;
			setpoint = ElevatorPresets::kDeployHeight;
			break;
		case(OI::ElevatorPreset::kNone):
		default:
			setpoint = 0;
	}

	positionCommand->setSetpoint(setpoint);
	if(positionCommand->onTarget()){
		finish();
	}
}
void AutoElevatorCommand::finish(){
	CommandBase::finish();
}

void AutoElevatorCommand::disable(){

}
