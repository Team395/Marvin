/*
 * TestCommand.cpp
 *
 *  Created on: Jan 19, 2018
 *      Author: JARVIS
 */
#include <iostream>

#include <Timer.h>

#include "TestCommand.h"

TestCommand::TestCommand(double seconds) : CommandBase("TestCommand"), seconds(seconds) {

}

TestCommand::~TestCommand(){

}

void TestCommand::init(){
	CommandBase::init();

	std::cout << getName() << " " << seconds << ": Started\n";
	startTime = frc::Timer::GetFPGATimestamp();
}

void TestCommand::update(){
	double currentDelta = Timer::GetFPGATimestamp() - startTime;
	std::cout << getName() << " " << seconds << ": " << currentDelta << '\n';

	if(currentDelta >= seconds){
		finish();
	}
}

void TestCommand::finish(){
	CommandBase::finish();

	std::cout << getName() << " " << seconds << ": Finished\n";
}

void TestCommand::disable(){

}

double TestCommand::getSeconds(){
	return seconds;
}
