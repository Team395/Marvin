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
	leftSlave.Follow(leftMaster);
	rightSlave.Follow(rightMaster);
}

Drivebase::~Drivebase() {
	// TODO Auto-generated destructor stub
}

void Drivebase::tankDrive(double left, double right){
	leftMaster.Set(ControlMode::PercentOutput, left);
	rightMaster.Set(ControlMode::PercentOutput, right);
}

void Drivebase::PIDWrite(double output){
	if(output < 0 && output > -minimumPidOutput) { output = -minimumPidOutput; }
	else if (output > 0 && output < minimumPidOutput){ output = minimumPidOutput; }
	tankDrive(output, -output);
}

void Drivebase::setMinimumPidOutput(double minimum){
	minimumPidOutput = minimum;
}
