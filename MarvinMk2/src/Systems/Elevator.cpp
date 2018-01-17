/*
 * Elevator.cpp
 *
 *  Created on: Jan 15, 2018
 *      Author: JARVIS
 */

#include <Systems/Elevator.h>

Elevator::Elevator() {
	// TODO Auto-generated constructor stub

}

Elevator::~Elevator() {
	// TODO Auto-generated destructor stub
}

void Elevator::driveElevator(double speed){
	winchController.Set(speed);
}
