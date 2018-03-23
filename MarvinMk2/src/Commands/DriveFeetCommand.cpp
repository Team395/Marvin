/*
 * DriveFeetCommand.cpp
 *
 *  Created on: Feb 17, 2018
 *      Author: JARVIS
 */

#include <Commands/DriveFeetCommand.h>
#include <SmartDashboard/SmartDashboard.h>
#include <iostream>

Drive__FeetCommand::Drive__FeetCommand(double feet, Drivebase* drivebase, DrivebaseEncoderSensors* encoderSensors, DrivebaseGyroSensor* gyroSensor) :
	CommandBase("Drive Feet Command"),
	linearPID{encoderSensors->kP, encoderSensors->kI,encoderSensors->kD, encoderSensors, &linearGetter},
	rotationalPID{gyroSensor->kP, gyroSensor->kI, gyroSensor->kD, gyroSensor, &rotationalGetter},
	drivebase{drivebase},
	encoderSensors{encoderSensors},
	gyroSensor{gyroSensor},
	requestedMovementFeet{feet}
	{

}

Drive__FeetCommand::~Drive__FeetCommand() {

}

void Drive__FeetCommand::init(){
   CommandBase::init();
}

void Drive__FeetCommand::update(){
	encoderSensors->kP = encoderSensors->preferences->GetDouble("DriveFeetKp", 0.03);
	encoderSensors->kI = encoderSensors->preferences->GetDouble("DriveFeetKi", 0);
	encoderSensors->kD = encoderSensors->preferences->GetDouble("DriveFeetKd", 0.02);

	linearPID.SetP(encoderSensors->kP);
	linearPID.SetI(encoderSensors->kI);
	linearPID.SetD(encoderSensors->kD);
	encoderSensors->setMinimumPidOutput(encoderSensors->preferences->GetDouble("Drive Feet Minimum PID Output", 0));

	gyroSensor->kP = gyroSensor->preferences->GetDouble("RotationalKp", 0.02);
	gyroSensor->kI = gyroSensor->preferences->GetDouble("RotationalKi", 0);
	gyroSensor->kD = gyroSensor->preferences->GetDouble("RotationalKd", 0);

	rotationalPID.SetP(gyroSensor->kP);
	rotationalPID.SetI(gyroSensor->kI);
	rotationalPID.SetD(gyroSensor->kD);
	gyroSensor->setMinimumPidOutput(gyroSensor->preferences->GetDouble("Drive Feet Minimum PID Output", 0));


	if(!linearPID.IsEnabled() && !movementFinished){
		encoderSensors->resetEncoderSensors();
		if(encoderSensors->getAveragedEncoderPositions() == 0) {
			linearPID.SetSetpoint(encoderSensors->getAveragedEncoderPositions() + encoderSensors->convertToNativeUnits(requestedMovementFeet));
			linearPID.SetAbsoluteTolerance(kAcceptableError);
			linearPID.Enable();
			rotationalPID.SetSetpoint(gyroSensor->getAngleZ());
			rotationalPID.SetAbsoluteTolerance(0);
			rotationalPID.Enable();
		}
	}

	if(linearPID.OnTarget()){
		movementFinished = true;
		linearPID.Disable();
		rotationalPID.Disable();
		drivebase->tankDrive(0,0);
		finish();
	}

	if(linearPID.IsEnabled()){
		drivebase->tankDrive(linearGetter.getPIDValue() - rotationalGetter.getPIDValue()
				, linearGetter.getPIDValue() + rotationalGetter.getPIDValue());
	} else {
		rotationalPID.Disable();
	}

	frc::SmartDashboard::PutData("Drive Feet linear PID Controller", &linearPID);
	frc::SmartDashboard::PutData("Drive Feet rotational PID Controller", &rotationalPID);
	frc::SmartDashboard::PutBoolean("Drive Feet Finished", linearPID.OnTarget());
	frc::SmartDashboard::PutNumber("Drive Feet Average Encoder Positions", encoderSensors->getAveragedEncoderPositions());
	frc::SmartDashboard::PutNumber("Drive Feet PIDError", linearPID.GetError());
	frc::SmartDashboard::PutNumber("Drive Feet PIDSetpoint", linearPID.GetSetpoint());
	frc::SmartDashboard::PutNumber("Drive Feet PIDWrite", linearGetter.getPIDValue());
	frc::SmartDashboard::PutNumber("DF Right Output", drivebase->getRightMaster()->GetMotorOutputPercent());
	frc::SmartDashboard::PutNumber("DF Left Output", drivebase->getLeftMaster()->GetMotorOutputPercent());

}
void Drive__FeetCommand::finish(){
	disable();

	CommandBase::finish();
}

void Drive__FeetCommand::disable(){
	linearPID.Disable();
	rotationalPID.Disable();
	drivebase->tankDrive(0,0);

	frc::SmartDashboard::PutData("Drive Feet PID Controller", &linearPID);
}
void Drive__FeetCommand::startNewMovement(){
	movementFinished = false;
}

PIDGetter::PIDGetter() : pidValue{0}{

}

PIDGetter::~PIDGetter() {

}

void PIDGetter::PIDWrite(double value){
	pidValue = value;
}

double PIDGetter::getPIDValue(){
	return pidValue;
}
