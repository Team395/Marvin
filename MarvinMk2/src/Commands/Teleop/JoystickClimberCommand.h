/*
 * JoystickClimberCommand.h
 *
 *  Created on: Mar 11, 2018
 *      Author: JARVIS
 */

#ifndef SRC_COMMANDS_TELEOP_JOYSTICKCLIMBERCOMMAND_H_
#define SRC_COMMANDS_TELEOP_JOYSTICKCLIMBERCOMMAND_H_

#include <Commands/CommandBase.h>
#include <OI.h>
#include <Systems/CLimberSystem.h>

class JoystickClimberCommand: public CommandBase {
	OI* oi;
	ClimberSystem* climberSystem;
public:
	JoystickClimberCommand(OI* oi, ClimberSystem* climberSystem);
	virtual ~JoystickClimberCommand();

	void init() override;
	void update() override;
	void finish() override;
};

#endif /* SRC_COMMANDS_TELEOP_JOYSTICKCLIMBERCOMMAND_H_ */
