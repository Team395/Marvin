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

Turn__DegreesCommand::Turn__DegreesCommand(Drivebase* drivebase, Gyroscope* gyroscope, OI* oi)
: CommandBase("Turn_DegreesCommand"),
  pidController{gyroscope->kP, gyroscope->kI, gyroscope->kD, gyroscope, drivebase},
  gyroscope{gyroscope},
  oi{oi} {

}

Turn__DegreesCommand::~Turn__DegreesCommand() {

}

void Turn__DegreesCommand::init() {

}

void Turn__DegreesCommand::update() {
	//gyroscope->kP = gyroscope->preferences->GetDouble("limelightKp", -.03);
	//gyroscope->kI = gyroscope->preferences->GetDouble("limelightKi", 0);
	//gyroscope->kD = gyroscope->preferences->GetDouble("limelightKd", 0);
	frc::SmartDashboard::PutData("PID Controller", &pidController);

	if(!pidController.IsEnabled() && !turnFinished){
		pidController.SetSetpoint(gyroscope->getAngleX() + kTurnDegrees);
		pidController.SetAbsoluteTolerance(kAcceptableError);
		pidController.Enable();
	}

	if(pidController.OnTarget()){
		turnFinished = true;
		pidController.Disable();
	}

	frc::SmartDashboard::PutData("PIDController", &pidController);
	frc::SmartDashboard::PutBoolean("Finished", pidController.OnTarget());
	frc::SmartDashboard::PutNumber("XAngle", gyroscope->getAngleX());
}

void Turn__DegreesCommand::finish() {

}

void Turn__DegreesCommand::disable() {
	pidController.Disable();
	frc::SmartDashboard::PutData("PIDController", &pidController);
}

void Turn__DegreesCommand::startNewturn() {
	turnFinished = false;
}

