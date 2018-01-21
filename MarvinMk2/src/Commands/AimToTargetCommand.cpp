/*
 * AimToTarget.cpp
 *
 *  Created on: Jan 20, 2018
 *      Author: JARVIS
 */

#include <Commands/AimToTargetCommand.h>
#include <SmartDashboard/SmartDashboard.h>

AimToTargetCommand::AimToTargetCommand(Drivebase* drivebase
		, Limelight* limelight
		, limelightMap::PipeLine pipeline)
	: CommandBase("AimToTarget")
		, drivebase{drivebase}
		, limelight{limelight}
		, pidController{limelight->kP, limelight->kI, limelight->kD, limelight, drivebase}
{
	limelight->setPipeline(pipeline);
}

AimToTargetCommand::~AimToTargetCommand(){

}

void AimToTargetCommand::init(){
	CommandBase::init();

	limelight->setCamMode(limelightMap::CamMode::kVisionProcessor);
	limelight->setLedMode(limelightMap::LedMode::kOn);
}

void AimToTargetCommand::update(){
	limelight->refreshNetworkTableValues();

	if(!pidController.IsEnabled() && !turnFinished){
		pidController.SetSetpoint(7.8);
		pidController.SetAbsoluteTolerance(1);

		pidController.SetP(limelight->kP);
		pidController.SetI(limelight->kI);
		pidController.SetD(limelight->kD);
		drivebase->setMinimumPidOutput(limelight->kMinRate);

		pidController.Enable();
	}

	/*double error = limelight->PIDGet();
	double turn = error * limelight->kP;

	if(error > 1.0){ turn = turn - limelight->kMinRate; }
	else if (error < 1.0){ turn = turn + limelight->kMinRate; }

	drivebase->ArcadeDrive(0, turn);*/

	frc::SmartDashboard::PutData("PIDController", &pidController);
	frc::SmartDashboard::PutBoolean("Finished", pidController.OnTarget());
}

void AimToTargetCommand::finish(){
	CommandBase::finish();

	pidController.Disable();
}

void AimToTargetCommand::disable() {
	pidController.Disable();
	turnFinished = true;
	frc::SmartDashboard::PutData("PIDController", &pidController);
}

void AimToTargetCommand::startNewTurn() {
	turnFinished = false;
}
