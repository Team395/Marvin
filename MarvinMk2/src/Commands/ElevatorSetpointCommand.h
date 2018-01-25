/*
 * ElevatorSetpointCommand.h
 *
 *  Created on: Jan 24, 2018
 *      Author: hlewi
 */

#ifndef SRC_COMMANDS_ELEVATORSETPOINTCOMMAND_H_
#define SRC_COMMANDS_ELEVATORSETPOINTCOMMAND_H_

#include <Commands/CommandBase.h>

class ElevatorSetpointCommand: public CommandBase {
public:
	ElevatorSetpointCommand();
	virtual ~ElevatorSetpointCommand();
};

#endif /* SRC_COMMANDS_ELEVATORSETPOINTCOMMAND_H_ */
