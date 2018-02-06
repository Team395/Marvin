/*
 * ArcadeDrive.cpp
 *
 *  Created on: Jan 15, 2018
 *      Author: JARVIS
 */
#include <Commands/TankDriveCommand.h>
#include <Systems/Drivebase.h>
#include <OI.h>


TankDriveCommand::TankDriveCommand(Drivebase* drivebase, OI* oi) :
CommandBase("ArcadeDriveCommand"),
drivebase(drivebase),
oi(oi) {
	// TODO Auto-generated constructor stub
}

TankDriveCommand::~TankDriveCommand() {
	// TODO Auto-generated destructor stub
}

void TankDriveCommand::init() {

}

void TankDriveCommand::update() {
	double left = oi->getDriveLeft();
	double right = oi->getDriveRight();

	drivebase->tankDrive(left*left, right*right);
}

void TankDriveCommand::finish() {

}
