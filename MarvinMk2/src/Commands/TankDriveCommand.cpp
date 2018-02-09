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
	bool shift = oi->getShiftButton();
	frc::SmartDashboard::PutBoolean("shift", shift);
	frc::SmartDashboard::PutBoolean("High gear", drivebase->isHighGear());
frc::SmartDashboard::PutBoolean("Sent to drivebase", shift != drivebase->isHighGear());
	//!= just happens to implement the truth table we want
	//High(true) x Shift(true) = Low(false)
	//High(true) x Don't Shift(false) = High(true)
	//Low(false) x Shift(true) = high(true)
	//Low(false) x Don't Shift(false) = Low(false)

	drivebase->shiftHighGear(shift != drivebase->isHighGear());

	double left = oi->getDriveLeft();
	double right = oi->getDriveRight();
	drivebase->tankDrive(sgn(left) * left*left, sgn(right) * right*right);
}

void TankDriveCommand::finish() {

}
