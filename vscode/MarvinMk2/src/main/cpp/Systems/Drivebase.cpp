/*
 * Drivebase.cpp
 *
 *  Created on: Jan 15, 2018
 *      Author: JARVIS
 */

#include <Talon.h>
#include <SpeedControllerGroup.h>
#include <Drive/DifferentialDrive.h>

#include "Drivebase.h"

Drivebase::Drivebase() : SystemBase("drivebase"){
	//leftMaster.SetInverted(true); //move inverted into RobotMap
	//leftSlave.SetInverted(true);
	rightMaster.SetInverted(true);
	rightSlave.SetInverted(true);
	leftSlave.Follow(leftMaster);
	rightSlave.Follow(rightMaster);
}

Drivebase::~Drivebase() {

}

void Drivebase::tankDrive(double left, double right){
	leftMaster.Set(ControlMode::PercentOutput, left);
	rightMaster.Set(ControlMode::PercentOutput, right);
}

void Drivebase::PIDWrite(double output){
	if(output < 0 && output > -minimumPidOutput) { output = -minimumPidOutput; }
	else if (output > 0 && output < minimumPidOutput){ output = minimumPidOutput; }
	tankDrive(output, -output); //TODO: fix motor inversion
}

void Drivebase::setMinimumPidOutput(double minimum){
	minimumPidOutput = minimum;
}

WPI_TalonSRX* Drivebase::getLeftMaster(){
	return &leftMaster;
}

WPI_TalonSRX* Drivebase::getRightMaster(){
	return &rightMaster;
}
