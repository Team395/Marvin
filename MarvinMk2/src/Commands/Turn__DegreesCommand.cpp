/*
 * Turn90Command.cpp
 *
 *  Created on: Jan 18, 2018
 *      Author: JARVIS
 */

#include "Turn__DegreesCommand.h"
#include <SmartDashboard/SmartDashboard.h>
#include "../OI.h"
#include "CommandBase.h"

Turn__DegreesCommand::Turn__DegreesCommand(Drivebase* drivebase, GyroSystem* gyroSystem, OI* oi)
: CommandBase("Turn_DegreesCommand"),
  pidController{gyroSystem->kP, gyroSystem->kI, gyroSystem->kD, gyroSystem, drivebase},
  gyroSystem{gyroSystem},
  oi{oi} {

}

Turn__DegreesCommand::~Turn__DegreesCommand() {

}

void init() {

}

void Turn__DegreesCommand::update() {
	if(!pidController.IsEnabled() && !turnFinished){
		pidController.SetSetpoint(kTurnRadians + gyroSystem->getAngleX());
		pidController.SetAbsoluteTolerance(kAcceptableError);
		pidController.Enable();
	}

	if(pidController.OnTarget()){
		turnFinished = true;
		pidController.Disable();
	}

	frc::SmartDashboard::PutData("PIDController", &pidController);
	frc::SmartDashboard::PutBoolean("Finished", pidController.OnTarget());
	frc::SmartDashboard::PutNumber("XAngle", gyroSystem->getAngleX());
}

void finished() {

}

bool isFinished() {
	return false;
}

/*
void Turn__DegreesCommand::disable() {
	pidController.Disable();
	frc::SmartDashboard::PutData("PIDController", &pidController);
}

void Turn__DegreesCommand::startNewturn() {
	turnFinished = false;
}
*/
