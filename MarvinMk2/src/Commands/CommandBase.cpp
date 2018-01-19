/*
 * CommandBase.cpp
 *
 *  Created on: Jan 19, 2018
 *      Author: JARVIS
 */

#include "Commands/CommandBase.h"
#include <string>
CommandBase::CommandBase(std::string name) : name{name} {

}

CommandBase::~CommandBase() {
	// TODO Auto-generated destructor stub
}

std::string CommandBase::getName(){
	return name;
}
