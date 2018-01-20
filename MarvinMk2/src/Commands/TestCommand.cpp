/*
 * TestCommand.cpp
 *
 *  Created on: Jan 19, 2018
 *      Author: JARVIS
 */

#include <Commands/TestCommand.h>
#include <Timer.h>
#include <iostream>

TestCommand::TestCommand(double seconds) : CommandBase("TestCommand"), seconds(seconds), startTime(frc::Timer::GetFPGATimestamp()) {
	// TODO Auto-generated constructor stub

}

TestCommand::~TestCommand(){
	// TODO Auto-generated destructor stub
}

void TestCommand::init(){

}

void TestCommand::update(){
	std::cout << Timer::GetFPGATimestamp() - startTime << '\n';
}

void TestCommand::finish(){

}

bool TestCommand::isFinished(){
	return (Timer::GetFPGATimestamp() - startTime > seconds);
}
