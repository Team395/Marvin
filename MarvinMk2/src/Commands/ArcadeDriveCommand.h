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
#include "CommandBase.h"

class ArcadeDriveCommand : CommandBase {
	Drivebase* drivebase;
	OI* oi;

public:
	ArcadeDriveCommand(Drivebase* drivebase, OI* oi);
	virtual ~ArcadeDriveCommand();

	void init();
	void update();
	void finished();
	bool isFinished();
};

#endif /* SRC_COMMANDS_ARCADEDRIVECOMMAND_H_ */
