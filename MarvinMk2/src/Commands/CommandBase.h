/*
 * CommandBase.h
 *
 *  Created on: Jan 19, 2018
 *      Author: JARVIS
 */

#ifndef SRC_COMMANDS_COMMANDBASE_H_
#define SRC_COMMANDS_COMMANDBASE_H_
#include <string>

#include <Commands/CommandState.h>

class CommandBase {
	std::string name;
	CommandState commandState;

public:
	CommandBase(std::string);
	virtual ~CommandBase();

	virtual void init();
	virtual void update()=0;
	virtual void finish();


	std::string getName();
	CommandState getCommandState();
	void setCommandState(CommandState);
};

#endif /* SRC_COMMANDS_COMMANDBASE_H_ */
