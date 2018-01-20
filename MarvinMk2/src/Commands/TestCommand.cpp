/*
 * TestCommand.cpp
 *
 *  Created on: Jan 19, 2018
 *      Author: JARVIS
 */

#include <Commands/TestCommand.h>
#include <Timer.h>
#include <iostream>

TestCommand::TestCommand(double seconds) : CommandBase("TestCommand"), seconds(seconds) {
	// TODO Auto-generated constructor stub

}

TestCommand::~TestCommand(){
	// TODO Auto-generated destructor stub
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

double TestCommand::getSeconds(){
	return seconds;
}
