/*
 * CommandBase.cpp
 *
 *  Created on: Jan 19, 2018
 *      Author: JARVIS
 */

#include "Commands/CommandBase.h"
#include <string>
CommandBase::CommandBase(std::string name) : name{name} {
	commandState = CommandState::kNotStarted;
}

CommandBase::~CommandBase() {
	// TODO Auto-generated destructor stub
}

void CommandBase::init(){
	commandState = CommandState::kInitialized;
}

void CommandBase::finish(){
	commandState = CommandState::kFinished;
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
