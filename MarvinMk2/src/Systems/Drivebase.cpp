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
	rightMaster.SetInverted(true);
	rightSlave.SetInverted(true);
	leftSlave.Follow(leftMaster);
	rightSlave.Follow(rightMaster);
	highGearSolenoid.Set(true);
	lowGearSolenoid.Set(false);
	highGear = true;
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
	tankDrive(output, -output);
}

void Drivebase::setMinimumPidOutput(double minimum){
	minimumPidOutput = minimum;
}

void Drivebase::shiftHighGear(bool gear){
	if(gear && !highGear){
		highGearSolenoid.Set(true);
		lowGearSolenoid.Set(false);
		highGear = true;
	}
	else if(!gear && highGear){
		highGearSolenoid.Set(false);
		lowGearSolenoid.Set(true);
		highGear = false;
	}
}

bool Drivebase::isHighGear(){
	return highGear;
}
