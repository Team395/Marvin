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

	void init() override;
	void update() override;
	void finish() override;
	bool isFinished() override;
};

#endif /* SRC_COMMANDS_JOYSTICKELEVATORCOMMAND_H_ */
