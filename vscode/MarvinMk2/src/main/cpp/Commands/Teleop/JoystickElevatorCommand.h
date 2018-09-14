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
#if 0
	const double highHeight = 40;
	const double normalHeight = 36.7;
	const double lowHeight = 30.7;
	const double switchHeight = 15;
	const double bottomHeight = 0;
	const double errorThreshold = 3;
#endif
public:
	JoystickElevatorCommand(Elevator*, OI*, ElevatorPositionCommand*);
	virtual ~JoystickElevatorCommand();

	void init() override;
	void update() override;
	void finish() override;
	void disable() override;
};

#endif /* SRC_COMMANDS_JOYSTICKELEVATORCOMMAND_H_ */
