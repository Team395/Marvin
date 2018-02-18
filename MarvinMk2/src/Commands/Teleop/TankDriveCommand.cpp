/*
 * ArcadeDrive.cpp
 *
 *  Created on: Jan 15, 2018
 *      Author: JARVIS
 */
#include <Commands/TankDriveCommand.h>
#include <Systems/Drivebase.h>
#include <OI.h>
#include <SmartDashboard/SmartDashboard.h>

TankDriveCommand::TankDriveCommand(Drivebase* drivebase, OI* oi) :
CommandBase("ArcadeDriveCommand"),
drivebase(drivebase),
oi(oi) {

}

TankDriveCommand::~TankDriveCommand() {

}

void TankDriveCommand::init() {

}

double sgn(double x){
	return x >= 0.0 ? 1.0: -1.0;
}

void TankDriveCommand::update() {
	int shift = oi->getShiftButtons();
	//1 if high, -1 if low, 0 if nothing
	if(shift){
		drivebase->shiftHighGear(shift == 1 ? true : false);
	}

	double left = oi->getDriveLeft();
	double right = oi->getDriveRight();
	drivebase->tankDrive(sgn(left) * left*left, sgn(right) * right*right);
}

void TankDriveCommand::finish() {

}
