/*
 * Elevator.cpp
 *
 *  Created on: Jan 15, 2018
 *      Author: JARVIS
 */

#include "Elevator.h"

Elevator::Elevator() : SystemBase("elevator") {
	winchController.SetInverted(ElevatorMap::kWinchInverted);
}

Elevator::~Elevator() {

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
