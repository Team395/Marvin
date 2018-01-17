/*
 * CommandBase.h
 *
 *  Created on: Jan 15, 2018
 *      Author: JARVIS
 */

#ifndef SRC_COMMANDBASE_H_
#define SRC_COMMANDBASE_H_

#include <Commands/Command.h>

class CommandBase: public frc::Command {
public:
	CommandBase();
	virtual ~CommandBase();
};

#endif /* SRC_COMMANDBASE_H_ */
