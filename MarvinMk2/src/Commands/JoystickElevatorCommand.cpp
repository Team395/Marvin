/*
 * JoystickElevatorCommand.cpp
 *
 *  Created on: Jan 15, 2018
 *      Author: JARVIS
 */

#include <Commands/JoystickElevatorCommand.h>
#include "../Systems/Elevator.h"
#include "../OI.h"

JoystickElevatorCommand::JoystickElevatorCommand(Elevator* elevator, OI* oi) : elevator(elevator), oi(oi) {
	// TODO Auto-generated constructor stub
}

JoystickElevatorCommand::~JoystickElevatorCommand() {
	// TODO Auto-generated destructor stub
}

void JoystickElevatorCommand::update(){
	double speed = oi->GetManipulatorY();

	if((speed > 0 && elevator->topPressed())){
		elevator->driveElevator(0);
	}
	else if((speed < 0 && elevator->bottomPressed())){
		elevator->driveElevator(0);
	}
	else{
		elevator->driveElevator(speed);
	}
}
