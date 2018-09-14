/*
 * TestCommand.h
 *
 *  Created on: Jan 19, 2018
 *      Author: JARVIS
 */

#ifndef SRC_COMMANDS_TESTCOMMAND_H_
#define SRC_COMMANDS_TESTCOMMAND_H_

#include <Commands/CommandBase.h>

class TestCommand: public CommandBase {
	double seconds;
	double startTime = -1;
public:
	TestCommand(double);
	virtual ~TestCommand();

	void init() override;
	void update() override;
	void finish() override;
	void disable() override;

	double getSeconds();
};

#endif /* SRC_COMMANDS_TESTCOMMAND_H_ */
