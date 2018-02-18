/*
 * JoystickElevatorCommand.h
 *
 *  Created on: Jan 15, 2018
 *      Author: JARVIS
 */

#ifndef SRC_COMMANDS_JOYSTICKELEVATORCOMMAND_H_
#define SRC_COMMANDS_JOYSTICKELEVATORCOMMAND_H_
#include <OI.h>
#include <Systems/Elevator.h>
#include <Commands/CommandBase.h>

class JoystickElevatorCommand : CommandBase {
	Elevator* elevator;
	OI* oi;

public:
	JoystickElevatorCommand(Elevator* elevator, OI* oi);
	virtual ~JoystickElevatorCommand();

	void init() override;
	void update() override;
	void finish() override;
};

#endif /* SRC_COMMANDS_JOYSTICKELEVATORCOMMAND_H_ */
