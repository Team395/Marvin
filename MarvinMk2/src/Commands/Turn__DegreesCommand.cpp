/*
 * Turn90Command.cpp
 *
 *  Created on: Jan 18, 2018
 *      Author: JARVIS
 */
#include <SmartDashboard/SmartDashboard.h>

#include <OI.h>
#include <Commands/CommandBase.h>

#include "Turn__DegreesCommand.h"

Turn__DegreesCommand::Turn__DegreesCommand(Drivebase* drivebase, DrivebaseGyroSensor* gyroSensor, OI* oi)
: CommandBase("Turn_DegreesCommand"),
  pidController{gyroSensor->kP, gyroSensor->kI, gyroSensor->kD, gyroSensor, drivebase},
  gyroSensor{gyroSensor},
  oi{oi} {

}

Turn__DegreesCommand::~Turn__DegreesCommand() {

}

void Turn__DegreesCommand::init() {
	CommandBase::init();
}

void Turn__DegreesCommand::update() {
	gyroSensor->kP = gyroSensor->preferences->GetDouble("TurnDegreesKp", -.03);
	gyroSensor->kI = gyroSensor->preferences->GetDouble("TurnDegreesKi", 0);
	gyroSensor->kD = gyroSensor->preferences->GetDouble("TurnDegreesKd", 0);

	pidController.SetP(gyroSensor->kP);
	pidController.SetI(gyroSensor->kI);
	pidController.SetD(gyroSensor->kD);
	frc::SmartDashboard::PutData("PID Controller", &pidController);

	gyroSensor->setMinimumPidOutput(gyroSensor->preferences->GetDouble("TurnDegreesKMinimum", 0));

	if(!pidController.IsEnabled() && !turnFinished){
		pidController.SetSetpoint(gyroSensor->getAngleZ() + kTurnDegrees);
		pidController.SetAbsoluteTolerance(kAcceptableError);
		pidController.Enable();
	}

	if(pidController.OnTarget()){
		turnFinished = true;
		pidController.Disable();
	}

	frc::SmartDashboard::PutData("Turn Degrees PIDController", &pidController);
	frc::SmartDashboard::PutBoolean("Turn Degrees Finished", pidController.OnTarget());
	frc::SmartDashboard::PutNumber("Turn Degrees XAngle", gyroSensor->getAngleZ());
	frc::SmartDashboard::PutNumber("Turn Degrees PIDError", pidController.GetError());
	frc::SmartDashboard::PutNumber("Turn Degrees PIDSetpoint", pidController.GetSetpoint());
}

void Turn__DegreesCommand::finish() {
	CommandBase::finish();
}

void Turn__DegreesCommand::disable() {
	pidController.Disable();
	frc::SmartDashboard::PutData("Turn Degrees PIDController", &pidController);
}

void Turn__DegreesCommand::startNewturn() {
	turnFinished = false;
}

