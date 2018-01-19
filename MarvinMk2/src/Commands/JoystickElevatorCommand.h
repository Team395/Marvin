/*
 * JoystickElevatorCommand.h
 *
 *  Created on: Jan 15, 2018
 *      Author: JARVIS
 */

#ifndef SRC_COMMANDS_JOYSTICKELEVATORCOMMAND_H_
#define SRC_COMMANDS_JOYSTICKELEVATORCOMMAND_H_
#include "../Systems/Elevator.h"
#include "../OI.h"
#include "CommandBase.h"

class JoystickElevatorCommand : CommandBase {
	Elevator* elevator;
	OI* oi;

public:
	JoystickElevatorCommand(Elevator* elevator, OI* oi);
	virtual ~JoystickElevatorCommand();

	void init();
	void update();
	void finished();
	bool isFinished();
};

#endif /* SRC_COMMANDS_JOYSTICKELEVATORCOMMAND_H_ */
