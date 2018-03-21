/*
 * CommandBase.cpp
 *
 *  Created on: Jan 19, 2018
 *      Author: JARVIS
 */
#include <string>
#include <iostream>

#include "CommandBase.h"

CommandBase::CommandBase(std::string name) : name{name} {
	commandState = CommandState::kNotStarted;
}

CommandBase::~CommandBase() {
}

void CommandBase::init(){
	commandState = CommandState::kInitialized;
}

void CommandBase::finish(){
	commandState = CommandState::kFinished;
}

void CommandBase::disable(){

}

std::string CommandBase::getName(){
	return name;
}

CommandState CommandBase::getCommandState(){
	return commandState;
}

void CommandBase::setCommandState(CommandState state){
	commandState = state;
}
