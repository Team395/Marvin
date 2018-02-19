/*
 * Elevator.cpp
 *
 *  Created on: Jan 15, 2018
 *      Author: JARVIS
 */

#include "Elevator.h"

Elevator::Elevator() : SystemBase("elevator"), driveUpLastCommand(false) {
	winchController.SetInverted(ElevatorMap::kWinchInverted);
}

Elevator::~Elevator() {

}
/*
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
*/
void Elevator::driveWinch(double speed){
	if(speed > 0.1){
		driveUpLastCommand = true;
		winchController.Set(speed); //TODO: move inverted into RobotMap
	}
	else {
		if(driveUpLastCommand){
			downTimer.Start();
		}

		if(downTimer.Get() > 0)
		{
			if(downTimer.Get() <= 10){
				winchController.Set(0.10);
			}
			else {
				winchController.Set(0);
				driveUpLastCommand = false;
				downTimer.Stop();
				downTimer.Reset();
			}
		}
		else {
			winchController.Set(0);
		}
	}
}
