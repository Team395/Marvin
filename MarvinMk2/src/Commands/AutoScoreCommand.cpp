/*
 * AutoScoreCommand.cpp
 *
 *  Created on: Mar 22, 2018
 *      Author: JARVIS
 */

#include <Commands/AutoScoreCommand.h>

AutoScoreCommand::AutoScoreCommand(PneumaticGripperCommand* gripperCommand) : CommandBase("Autoscore Command"), gripperCommand(gripperCommand){
	// TODO Auto-generated constructor stub

}

AutoScoreCommand::~AutoScoreCommand() {
	// TODO Auto-generated destructor stub
}

void AutoScoreCommand::init(){
	CommandBase::init();
}

void AutoScoreCommand::update(){
	bool finished = gripperCommand->updateAutoscore();
	if(finished) finish();
}

void AutoScoreCommand::finish(){
	CommandBase::finish();
}

void AutoScoreCommand::disable(){

}
