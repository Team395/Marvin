/*
 * ElevatorPositionCommand.cpp
 *
 *  Created on: Feb 19, 2018
 *      Author: JARVIS
 */

#include <Commands/ElevatorPositionCommand.h>

ElevatorPositionCommand::ElevatorPositionCommand(Elevator* elevatorSystem, double p, double i, double d)
: CommandBase("Elevator Position Command"),
  elevator(elevatorSystem),
  pidController(p, i, d, elevator, elevator),
  setpoint(0)
  {
	pidController.SetSetpoint(setpoint);
}

ElevatorPositionCommand::~ElevatorPositionCommand() {
	// TODO Auto-generated destructor stub
}

void ElevatorPositionCommand::init(){

}

void ElevatorPositionCommand::update(){
	if(elevator->bottomPressed()){
		elevator->homeEncoder();
	}
	if(!setpoint == pidController.GetSetpoint()){
		pidController.SetSetpoint(setpoint);
	}
	if(setpoint == 0 && elevator->bottomPressed() && pidController.IsEnabled()){
		pidController.Disable();
	}
	else if(setpoint != 0 && !pidController.IsEnabled()){
		pidController.Enable();
	}

	SmartDashboard::PutData("Elevator PID Controller", &pidController);
}

void ElevatorPositionCommand::finish(){

}

void ElevatorPositionCommand::setSetpoint(double newSetpoint){
	if(newSetpoint < elevator->bottomPosition || newSetpoint > elevator->topPosition){

	}
	else{
		setpoint = newSetpoint;
	}
}

double ElevatorPositionCommand::getSetpoint(){
	return setpoint;
}
