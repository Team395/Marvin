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

class JoystickElevatorCommand {
	Elevator* elevator;
	OI* oi;

public:
	JoystickElevatorCommand(Elevator* elevator, OI* oi);
	virtual ~JoystickElevatorCommand();

	void update();
};

#endif /* SRC_COMMANDS_JOYSTICKELEVATORCOMMAND_H_ */
