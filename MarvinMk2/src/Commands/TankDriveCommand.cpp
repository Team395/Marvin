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

}

TankDriveCommand::~TankDriveCommand() {

}

void TankDriveCommand::init() {

}

void TankDriveCommand::update() {
	bool shift = oi->getShiftButton();
	//!= just happens to implement the truth table we want
	//High(true) x Shift(true) = Low(false)
	//High(true) x Don't Shift(false) = High(true)
	//Low(false) x Shift(true) = high(true)
	//Low(false) x Don't Shift(false) = Low(false)

	drivebase->shiftHighGear(shift != drivebase->isHighGear());

	double left = oi->getDriveLeft();
	double right = oi->getDriveRight();
	drivebase->tankDrive(left*left, right*right);
}

void TankDriveCommand::finish() {

}
