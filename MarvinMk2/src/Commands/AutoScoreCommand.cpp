/*
 * AutoScoreCommand.cpp
 *
 *  Created on: Mar 22, 2018
 *      Author: JARVIS
 */

#include <Commands/AutoScoreCommand.h>

AutoScoreCommand::AutoScoreCommand(PneumaticGripperCommand* gripperCommand) : CommandBase("Autoscore Command"), gripperCommand(gripperCommand){

}

AutoScoreCommand::~AutoScoreCommand() {
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
