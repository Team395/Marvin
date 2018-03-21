/*
 * ArcadeDrive.h
 *
 *  Created on: Jan 15, 2018
 *      Author: JARVIS
 */

#ifndef SRC_COMMANDS_TANKDRIVECOMMAND_H_
#define SRC_COMMANDS_TANKDRIVECOMMAND_H_
#include <OI.h>
#include <Systems/Drivebase.h>
#include <Commands/CommandBase.h>

class TankDriveCommand : CommandBase {
	Drivebase* drivebase;
	OI* oi;

public:
	TankDriveCommand(Drivebase* drivebase, OI* oi);
	virtual ~TankDriveCommand();

	void init() override;
	void update() override;
	void finish() override;
	void disable() override;
};

#endif /* SRC_COMMANDS_TANKDRIVECOMMAND_H_ */
