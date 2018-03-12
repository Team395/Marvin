/*
 * DriveFeetCommand.cpp
 *
 *  Created on: Feb 17, 2018
 *      Author: JARVIS
 */

#include <Commands/DriveFeetCommand.h>
#include <SmartDashboard/SmartDashboard.h>


Drive__FeetCommand::Drive__FeetCommand(double feet, Drivebase* drivebase, DrivebaseEncoderSensors* encoderSensors, DrivebaseGyroSensor* gyroSensor) :
	CommandBase("Drive Feet Command"),
	linearPID{encoderSensors->kP, encoderSensors->kI,encoderSensors->kD, encoderSensors, linearGetter},
	rotationalPID{gyroSensor->kP, gyroSensor->kI, gyroSensor->kD, gyroSensor, rotationalGetter},
	requestedMovementFeet{feet},
	drivebase{drivebase},
	encoderSensors{encoderSensors},
	gyroSensor{gyroSensor}
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

	linearPID.SetP(encoderSensors->kP);
	linearPID.SetI(encoderSensors->kI);
	linearPID.SetD(encoderSensors->kD);
	encoderSensors->setMinimumPidOutput(encoderSensors->preferences->GetDouble("Drive Feet Minimum PID Output", 0));

	gyroSensor->kP = gyroSensor->preferences->GetDouble("RotationalKp", -.03);
	gyroSensor->kI = gyroSensor->preferences->GetDouble("RotationalKi", 0);
	gyroSensor->kD = gyroSensor->preferences->GetDouble("RotationalKd", 0);

	rotationalPID.SetP(gyroSensor->kP);
	rotationalPID.SetI(gyroSensor->kI);
	rotationalPID.SetD(gyroSensor->kD);
	gyroSensor->setMinimumPidOutput(gyroSensor->preferences->GetDouble("Drive Feet Minimum PID Output", 0));


	if(!linearPID.IsEnabled() && !movementFinished){
		encoderSensors->resetEncoderSensors();
		linearPID.SetSetpoint(encoderSensors->getAveragedEncoderPositions() + encoderSensors->convertToNativeUnits(requestedMovementFeet));
		linearPID.SetAbsoluteTolerance(kAcceptableError);
		linearPID.Enable();
		rotationalPID.SetSetpoint(gyroSensor->getAngleZ());
		rotationalPID.SetAbsoluteTolerance(0);
	}

	if(linearPID.OnTarget()){
		movementFinished = true;
		linearPID.Disable();
		rotationalPID.Disable();
	}

	if(linearPID.IsEnabled()){
		drivebase->tankDrive(linearGetter.getPIDValue() + rotationalGetter.getPIDValue(), linearGetter.getPIDValue() + rotationalGetter.getPIDValue());
	}

	frc::SmartDashboard::PutData("Drive Feet PID Controller", &linearPID);
	frc::SmartDashboard::PutBoolean("Drive Feet Finished", linearPID.OnTarget());
	frc::SmartDashboard::PutNumber("Drive Feet Average Encoder Positions", encoderSensors->getAveragedEncoderPositions());
	frc::SmartDashboard::PutNumber("Drive Feet PIDError", linearPID.GetError());
	frc::SmartDashboard::PutNumber("Drive Feet PIDSetpoint", linearPID.GetSetpoint());

}
void Drive__FeetCommand::finish(){
	CommandBase::finish();
}

void Drive__FeetCommand::disable(){
	linearPID.Disable();
	frc::SmartDashboard::PutData("Drive Feet PID Controller", &linearPID);
}
void Drive__FeetCommand::startNewMovement(){
	movementFinished = false;
}

Drive__FeetCommand::PIDGetter::PIDGetter(){
	pidValue = 0;
}

void Drive__FeetCommand::PIDGetter::PIDWrite(double value){
	pidValue = value;
}

double Drive__FeetCommand::PIDGetter::getValue(){
	return pidValue;
}
