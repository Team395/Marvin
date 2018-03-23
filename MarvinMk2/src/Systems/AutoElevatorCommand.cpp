/*
 * AutoElevatorCommand.cpp
 *
 *  Created on: Mar 22, 2018
 *      Author: JARVIS
 */

#include <Systems/AutoElevatorCommand.h>

AutoElevatorCommand::AutoElevatorCommand(ElevatorPositionCommand* positionCommand, OI::ElevatorPreset height) :
CommandBase("Auto Elevator Command"),
positionCommand{positionCommand},
height{height} {
	// TODO Auto-generated constructor stub

}

AutoElevatorCommand::~AutoElevatorCommand() {
	// TODO Auto-generated destructor stub
}

void AutoElevatorCommand::init(){
	CommandBase::init();
}

void AutoElevatorCommand::update(){
	double setpoint;
	switch(height){
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
