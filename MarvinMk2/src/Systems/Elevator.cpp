/*
 * Elevator.cpp
 *
 *  Created on: Jan 15, 2018
 *      Author: JARVIS
 */

#include <Systems/Elevator.h>

Elevator::Elevator() {
	winchController.SetInverted(ElevatorMap::kWinchInverted);
}

Elevator::~Elevator() {
	// TODO Auto-generated destructor stub
}

bool Elevator::topPressed(){
	return ElevatorMap::kTopInverted
			? !topLimit.Get()
			: topLimit.Get();
}

bool Elevator::bottomPressed(){
	return ElevatorMap::kBottomInverted
			? !bottomLimit.Get()
			: bottomLimit.Get();
}

void Elevator::driveWinch(double speed){
	winchController.Set(speed);
}
