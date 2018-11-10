/*
 * ElevatorPositionCommand.cpp
 *
 *  Created on: Feb 19, 2018
 *      Author: JARVIS
 */

#include <Commands/ElevatorPositionCommand.h>
#include <SmartDashboard/SmartDashboard.h>

ElevatorPositionCommand::ElevatorPositionCommand(Elevator* elevatorSystem, double p, double i, double d)
: CommandBase("Elevator Position Command"),
  elevator(elevatorSystem),
  pidController(p, i, d, elevator, elevator),
  setpoint(0)
  {
	pidController.SetSetpoint(setpoint);
}

ElevatorPositionCommand::~ElevatorPositionCommand() {

}

void ElevatorPositionCommand::init(){
	pidController.Disable();
	pidController.SetAbsoluteTolerance(1);
}

void ElevatorPositionCommand::update(){
	frc::SmartDashboard::PutBoolean("bottomPressed", elevator->bottomPressed());

	if(elevator->bottomPressed()){
		elevator->homeEncoder();
	}
	if(elevator->topPressed()){
		setpoint = elevator->PIDGet() - 1; //TODO Verify this value
	}
	if(setpoint != pidController.GetSetpoint()){
		pidController.SetSetpoint(setpoint);
	}
//	if(setpoint == 0 && elevator->bottomPressed() && pidController.IsEnabled()){
	if(setpoint == 0 && elevator->PIDGet() < 1 && pidController.IsEnabled()){
		pidController.Disable();
		elevator->driveWinch(0);
	}
	else if(setpoint != 0 && !pidController.IsEnabled()){
		pidController.Enable();
	}

	SmartDashboard::PutData("Elevator PID Controller", &pidController);

	double p = preferences->GetDouble("elevatorP", pidController.GetP());
	double i = preferences->GetDouble("elevatorI", pidController.GetI());
	double d = preferences->GetDouble("elevatorD", pidController.GetD());
	double o = preferences->GetDouble("elevatorO", elevator->getOffset());

	pidController.SetP(p);
	pidController.SetI(i);
	pidController.SetD(d);
	elevator->setOffset(o);

//	SmartDashboard::PutNumber("PID P", pidController.GetP());
//	SmartDashboard::PutNumber("PID I", pidController.GetI());
//	SmartDashboard::PutNumber("PID D", pidController.GetD());
	SmartDashboard::PutNumber("PIDError", pidController.GetError());
}

void ElevatorPositionCommand::finish(){

}

void ElevatorPositionCommand::setSetpoint(double newSetpoint){
	if(newSetpoint > elevator->topPosition){
		setpoint = elevator->topPosition;
	}
	else if(newSetpoint < elevator->bottomPosition){
		setpoint = elevator->bottomPosition;
	}
	else{
		setpoint = newSetpoint;
	}
}

double ElevatorPositionCommand::getSetpoint(){
	return setpoint;
}

double ElevatorPositionCommand::getAbsError(){
	return std::abs(pidController.GetError());
}

void ElevatorPositionCommand::disable(){}

bool ElevatorPositionCommand::onTarget(){
	return pidController.OnTarget();
}
