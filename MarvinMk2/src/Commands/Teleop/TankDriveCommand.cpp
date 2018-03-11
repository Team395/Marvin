/*
 * ArcadeDrive.cpp
 *
 *  Created on: Jan 15, 2018
 *      Author: JARVIS
 */
#include <Commands/Teleop/TankDriveCommand.h>
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

double sign(double x){
	return x >= 0.0 ? 1.0: -1.0;
}

void TankDriveCommand::update() {
	double left = oi->getDriveLeft();
	double right = oi->getDriveRight();
	bool shiftDown = oi->getShiftDown();

	if(shiftDown){
		left /= 2.0;
		right /= 2.0;
	}

	drivebase->tankDrive(sign(left) * left*left, sign(right) * right*right);
}

void TankDriveCommand::finish() {

}
