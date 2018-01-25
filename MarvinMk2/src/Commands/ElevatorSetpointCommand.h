/*
 * ElevatorSetpointCommand.h
 *
 *  Created on: Jan 24, 2018
 *      Author: hlewi
 */

#ifndef SRC_COMMANDS_ELEVATORSETPOINTCOMMAND_H_
#define SRC_COMMANDS_ELEVATORSETPOINTCOMMAND_H_

#include <string>

#include <Systems/Elevator.h>
#include <Commands/CommandBase.h>

class ElevatorSetpointCommand: public CommandBase {

	Elevator* elevator;

public:
	ElevatorSetpointCommand(Elevator*);
	virtual ~ElevatorSetpointCommand();

	void init() override;
	void update() override;
	void finish() override;
};

#endif /* SRC_COMMANDS_ELEVATORSETPOINTCOMMAND_H_ */
