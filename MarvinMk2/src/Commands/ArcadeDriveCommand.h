/*
 * ArcadeDrive.h
 *
 *  Created on: Jan 15, 2018
 *      Author: JARVIS
 */

#ifndef SRC_COMMANDS_ARCADEDRIVECOMMAND_H_
#define SRC_COMMANDS_ARCADEDRIVECOMMAND_H_
#include <OI.h>
#include <Systems/Drivebase.h>
#include <Commands/CommandBase.h>

class ArcadeDriveCommand : CommandBase {
	Drivebase* drivebase;
	OI* oi;

public:
	ArcadeDriveCommand(Drivebase* drivebase, OI* oi);
	virtual ~ArcadeDriveCommand();

	void init() override;
	void update() override;
	void finish() override;
};

#endif /* SRC_COMMANDS_ARCADEDRIVECOMMAND_H_ */
