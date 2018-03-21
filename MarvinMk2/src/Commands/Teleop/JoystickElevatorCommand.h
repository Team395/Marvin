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
#include <Commands/ElevatorPositionCommand.h>

class JoystickElevatorCommand : CommandBase {
	Elevator* elevator;
	OI* oi;
	ElevatorPositionCommand* elevatorPositionCommand;
	const double highHeight = 15;
	const double normalHeight = 12;
	const double lowHeight = 9;
	const double switchHeight = 6;
	const double bottomHeight = 0;
	const double errorThreshold = 3;
public:
	JoystickElevatorCommand(Elevator*, OI*, ElevatorPositionCommand*);
	virtual ~JoystickElevatorCommand();

	void init() override;
	void update() override;
	void finish() override;
	void disable() override;
};

#endif /* SRC_COMMANDS_JOYSTICKELEVATORCOMMAND_H_ */
