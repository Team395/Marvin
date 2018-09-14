/*
 * AutoScoreCommand.h
 *
 *  Created on: Mar 22, 2018
 *      Author: JARVIS
 */

#ifndef SRC_COMMANDS_AUTOSCORECOMMAND_H_
#define SRC_COMMANDS_AUTOSCORECOMMAND_H_

#include <Commands/CommandBase.h>
#include <Commands/Teleop/PneumaticGripperCommand.h>

class AutoScoreCommand: public CommandBase {
	PneumaticGripperCommand* gripperCommand;

public:
	AutoScoreCommand(PneumaticGripperCommand* gripperCommand);
	virtual ~AutoScoreCommand();

	void init() override;
	void update() override;
	void finish() override;
	void disable() override;
};

#endif /* SRC_COMMANDS_AUTOSCORECOMMAND_H_ */
