/*
 * Drivebase.cpp
 *
 *  Created on: Jan 15, 2018
 *      Author: JARVIS
 */

#include <Talon.h>
#include <SpeedControllerGroup.h>
#include <Drive/DifferentialDrive.h>
#include <RobotMap.h>

#include "Drivebase.h"

Drivebase::Drivebase(NewTalonMap* newTalonMap)
    : SystemBase("drivebase"),
	  newTalonMap_(newTalonMap)
{
	// TODO:  Java backport cleanup
#if 0
	//leftMaster.SetInverted(true); //move inverted into RobotMap
	//leftSlave.SetInverted(true);
	rightMaster.SetInverted(true);
	rightSlave.SetInverted(true);
	leftSlave.Follow(leftMaster);
	rightSlave.Follow(rightMaster);
#else
	newTalonMap_->getTalonByID(DrivebaseMap::kRightMaster)->SetInverted(true);
	newTalonMap_->getTalonByID(DrivebaseMap::kRightSlave)->SetInverted(true);

	newTalonMap_->getTalonByID(DrivebaseMap::kLeftSlave)->Follow(*newTalonMap_->getTalonByID(DrivebaseMap::kLeftMaster));
	newTalonMap_->getTalonByID(DrivebaseMap::kRightSlave)->Follow(*newTalonMap_->getTalonByID(DrivebaseMap::kRightMaster));
#endif
}

Drivebase::~Drivebase() {

}

void Drivebase::tankDrive(double left, double right){
	// TODO:  Java backport cleanup
#if 0
	leftMaster.Set(ControlMode::PercentOutput, left);
	rightMaster.Set(ControlMode::PercentOutput, right);
#else
	// TODO: talon IDs from TalonMap?  existing encoder or new controller?
	newTalonMap_->getTalonByID(DrivebaseMap::kLeftMaster)->Set(ControlMode::PercentOutput, left);
	newTalonMap_->getTalonByID(DrivebaseMap::kRightMaster)->Set(ControlMode::PercentOutput, right);
#endif
}

void Drivebase::PIDWrite(double output){
	if(output < 0 && output > -minimumPidOutput) { output = -minimumPidOutput; }
	else if (output > 0 && output < minimumPidOutput){ output = minimumPidOutput; }
	tankDrive(output, -output); //TODO: fix motor inversion
}

void Drivebase::setMinimumPidOutput(double minimum){
	minimumPidOutput = minimum;
}

// TODO:  Java backport cleanup
#if 0
WPI_TalonSRX* Drivebase::getLeftMaster(){
	return &leftMaster;
}

WPI_TalonSRX* Drivebase::getRightMaster(){
	return &rightMaster;
}
#endif
