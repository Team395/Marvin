/*
 * ArcadeDrive.h
 *
 *  Created on: Jan 15, 2018
 *      Author: JARVIS
 */

#ifndef SRC_COMMANDS_ARCADEDRIVECOMMAND_H_
#define SRC_COMMANDS_ARCADEDRIVECOMMAND_H_
#include "../Systems/Drivebase.h"
#include "../OI.h"

class ArcadeDriveCommand {
	Drivebase* drivebase;
	OI* oi;

public:
	ArcadeDriveCommand(Drivebase* drivebase, OI* oi);
	virtual ~ArcadeDriveCommand();

	void update();
};

#endif /* SRC_COMMANDS_ARCADEDRIVECOMMAND_H_ */
