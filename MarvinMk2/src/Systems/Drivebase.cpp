/*
 * Drivebase.cpp
 *
 *  Created on: Jan 15, 2018
 *      Author: JARVIS
 */

#include "Systems/Drivebase.h"
#include <Talon.h>
#include <SpeedControllerGroup.h>
#include <Drive/DifferentialDrive.h>
#include "../RobotMap.h"

Drivebase::Drivebase() : SystemBase("drivebase"){

}

Drivebase::~Drivebase() {
	// TODO Auto-generated destructor stub
}

void Drivebase::ArcadeDrive(double move, double turn){
	differentialDrive.ArcadeDrive(move, turn);
}

void Drivebase::PIDWrite(double output){
	if(output < 0 && output > -minimumPidOutput) { output = output - minimumPidOutput; }
	else if (output > 0 && output < minimumPidOutput){ output = output + minimumPidOutput; }
	ArcadeDrive(0, output);
}

void Drivebase::setMinimumPidOutput(double minimum){
	minimumPidOutput = minimum;
}
