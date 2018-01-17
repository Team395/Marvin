/*
 * ArcadeDrive.cpp
 *
 *  Created on: Jan 15, 2018
 *      Author: JARVIS
 */

#include <Commands/ArcadeDriveCommand.h>
#include "../Systems/Drivebase.h"
#include "../OI.h"

ArcadeDriveCommand::ArcadeDriveCommand(Drivebase* drivebase, OI* oi) : drivebase(drivebase), oi(oi) {
	// TODO Auto-generated constructor stub
}

ArcadeDriveCommand::~ArcadeDriveCommand() {
	// TODO Auto-generated destructor stub
}

void ArcadeDriveCommand::update(){
	double move = oi->GetDriveY();
	double turn = oi->GetDriveZ();

	drivebase->ArcadeDrive(move, turn);
}
