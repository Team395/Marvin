/*
 * DriveFeetCommand.h
 *
 *  Created on: Feb 17, 2018
 *      Author: JARVIS
 */

#ifndef SRC_COMMANDS_DRIVEFEETCOMMAND_H_
#define SRC_COMMANDS_DRIVEFEETCOMMAND_H_

#include <Commands/CommandBase.h>

class Drive__FeetCommand: public CommandBase {
public:
	Drive__FeetCommand(double);
	virtual ~Drive__FeetCommand();
};

#endif /* SRC_COMMANDS_DRIVEFEETCOMMAND_H_ */
