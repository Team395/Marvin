/*
 * ArcadeDrive.cpp
 *
 *  Created on: Jan 15, 2018
 *      Author: JARVIS
 */
#include <Systems/Drivebase.h>
#include <OI.h>

#include "ArcadeDriveCommand.h"

ArcadeDriveCommand::ArcadeDriveCommand(Drivebase* drivebase, OI* oi) :
CommandBase("ArcadeDriveCommand"),
drivebase(drivebase),
oi(oi) {
	// TODO Auto-generated constructor stub
}

ArcadeDriveCommand::~ArcadeDriveCommand() {
	// TODO Auto-generated destructor stub
}

void ArcadeDriveCommand::init() {

}

void ArcadeDriveCommand::update() {
	double move = oi->GetDriveY();
	double turn = oi->GetDriveZ();

	drivebase->ArcadeDrive(move, turn);
}

void ArcadeDriveCommand::finish() {

}
