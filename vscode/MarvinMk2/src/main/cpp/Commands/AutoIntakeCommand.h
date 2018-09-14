/*
 * AutoIntakeCommand.h
 *
 *  Created on: Mar 20, 2018
 *      Author: JARVIS
 */

#ifndef SRC_COMMANDS_AUTOINTAKECOMMAND_H_
#define SRC_COMMANDS_AUTOINTAKECOMMAND_H_

#include <Commands/CommandBase.h>
#include <Commands/Teleop/PneumaticGripperCommand.h>

class AutoIntakeCommand: public CommandBase {
	PneumaticGripperCommand* gripperCommand;

public:
	AutoIntakeCommand(PneumaticGripperCommand*);
	virtual ~AutoIntakeCommand();

	void init() override;
	void update() override;
	void finish() override;
	void disable() override;
};

#endif /* SRC_COMMANDS_AUTOINTAKECOMMAND_H_ */
