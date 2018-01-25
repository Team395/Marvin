/*
 * ElevatorSetpointCommand.cpp
 *
 *  Created on: Jan 24, 2018
 *      Author: hlewi
 */

#include "ElevatorSetpointCommand.h"

ElevatorSetpointCommand::ElevatorSetpointCommand(Elevator* elevator) : CommandBase("ElevatorSetpointCommand"), elevator{elevator} {
	// TODO Auto-generated constructor stub

}

ElevatorSetpointCommand::~ElevatorSetpointCommand() {
	// TODO Auto-generated destructor stub
}

void ElevatorSetpointCommand::init(){
	CommandBase::init();
}

void ElevatorSetpointCommand::update(){

}

void ElevatorSetpointCommand::finish(){
	CommandBase::finish();
}
