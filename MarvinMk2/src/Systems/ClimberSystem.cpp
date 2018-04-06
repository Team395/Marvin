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
	winchController.Set(1);
}

void ClimberSystem::stopClimbing() {
	winchController.Set(0);
}

void ClimberSystem::extendClimber() {
	telescopeController.Set(+0.4); // TODO:  tune speed
}

void ClimberSystem::retractClimber() {
	telescopeController.Set(-0.4); // TODO:  tune speed
}

void ClimberSystem::stopTelescopingClimber() {
	telescopeController.Set(0);
}

