/*
 * DriveFeetCommand.cpp
 *
 *  Created on: Feb 17, 2018
 *      Author: JARVIS
 */

#include <Commands/DriveFeetCommand.h>
#include <SmartDashboard/SmartDashboard.h>


Drive__FeetCommand::Drive__FeetCommand(double feet, Drivebase* drivebase, DrivebaseEncoderSensors* encoderSensors) :
	CommandBase("Drive Feet Command"),
	pidController{encoderSensors->kP, encoderSensors->kI,encoderSensors->kD, encoderSensors, drivebase},
	encoderSensors{encoderSensors},
	requestedMovementFeet{feet}
	{
	// TODO Auto-generated constructor stub

}

Drive__FeetCommand::~Drive__FeetCommand() {
	// TODO Auto-generated destructor stub

}

void Drive__FeetCommand::init(){
   CommandBase::init();
}

void Drive__FeetCommand::update(){
	encoderSensors->kP = encoderSensors->preferences->GetDouble("DriveFeetKp", -.03);
	encoderSensors->kI = encoderSensors->preferences->GetDouble("DriveFeetKi", 0);
	encoderSensors->kD = encoderSensors->preferences->GetDouble("DriveFeetKd", 0);

	pidController.SetP(encoderSensors->kP);
	pidController.SetI(encoderSensors->kI);
	pidController.SetD(encoderSensors->kD);
	encoderSensors->setMinimumPidOutput(encoderSensors->preferences->GetDouble("Drive Feet Minimum PID Output", 0));

	if(!pidController.IsEnabled() && !movementFinished){
		encoderSensors->resetEncoderSensors();
		pidController.SetSetpoint(encoderSensors->getAveragedEncoderPositions() + encoderSensors->convertToNativeUnits(requestedMovementFeet));
		pidController.SetAbsoluteTolerance(kAcceptableError);
		pidController.Enable();
	}

	if(pidController.OnTarget()){
		movementFinished = true;
		pidController.Disable();
	}
	frc::SmartDashboard::PutData("Drive Feet PID Controller", &pidController);
	frc::SmartDashboard::PutBoolean("Drive Feet Finished", pidController.OnTarget());
	frc::SmartDashboard::PutNumber("Drive Feet Average Encoder Positions", encoderSensors->getAveragedEncoderPositions());
	frc::SmartDashboard::PutNumber("Drive Feet PIDError", pidController.GetError());
	frc::SmartDashboard::PutNumber("Drive Feet PIDSetpoint", pidController.GetSetpoint());

}
void Drive__FeetCommand::finish(){
	CommandBase::finish();
}

void Drive__FeetCommand::disable(){
	pidController.Disable();
	frc::SmartDashboard::PutData("Drive Feet PID Controller", &pidController);
}
void Drive__FeetCommand::startNewMovement(){
	movementFinished = false;
}
