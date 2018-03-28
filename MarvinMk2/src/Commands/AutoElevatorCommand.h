/*
 * AutoElevatorCommand.h
 *
 *  Created on: Mar 22, 2018
 *      Author: JARVIS
 */

#ifndef SRC_SYSTEMS_AUTOELEVATORCOMMAND_H_
#define SRC_SYSTEMS_AUTOELEVATORCOMMAND_H_
#include <Commands/ElevatorPositionCommand.h>
#include <OI.h>
#include <Commands/CommandBase.h>

class AutoElevatorCommand : public CommandBase{
	ElevatorPositionCommand* positionCommand;
	OI::ElevatorPreset height;

public:
	AutoElevatorCommand(ElevatorPositionCommand* positionCommand, OI::ElevatorPreset height);
	virtual ~AutoElevatorCommand();

	void init() override;
	void update() override;
	void finish() override;
	void disable() override;
};

#endif /* SRC_SYSTEMS_AUTOELEVATORCOMMAND_H_ */
