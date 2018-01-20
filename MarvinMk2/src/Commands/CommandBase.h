/*
 * CommandBase.h
 *
 *  Created on: Jan 19, 2018
 *      Author: JARVIS
 */

#ifndef SRC_COMMANDS_COMMANDBASE_H_
#define SRC_COMMANDS_COMMANDBASE_H_
#include <string>

class CommandBase {
	std::string name;

public:
	CommandBase(std::string);
	virtual ~CommandBase();

	virtual void init()=0;
	virtual void update()=0;
	virtual void finish()=0;
	virtual bool isFinished()=0;

	std::string getName();
};

#endif /* SRC_COMMANDS_COMMANDBASE_H_ */
