/*
 * ClimberSystem.cpp
 *
 *  Created on: Mar 11, 2018
 *      Author: JARVIS
 */

#include <Systems/ClimberSystem.h>

ClimberSystem::ClimberSystem()
	: SystemBase("ClimberSystem")
{

}

ClimberSystem::~ClimberSystem() {

}

void ClimberSystem::startClimbing() {
	winchController.Set(1); // TODO:  1, -1, smaller value; determine direction
}

void ClimberSystem::stopClimbing() {
	winchController.Set(0);
}

void ClimberSystem::extendClimber() {
	telescopeController.Set(-0.4); // TODO:  1, -1, smaller value; determine direction
}

void ClimberSystem::retractClimber() {
	telescopeController.Set(+0.4); // TODO:  1, -1, smaller value; determine direction
}

void ClimberSystem::stopTelescopingClimber() {
	telescopeController.Set(0);
}

void ClimberSystem::lockClimber() {
	tiltController.Set(0.45);
}

void ClimberSystem::releaseClimber() {
	tiltController.Set(1); // TODO:  1, -1, smaller value; determine direction
}

