/*
 * PneumaticGripperCommand.h
 *
 *  Created on: Jan 26, 2018
 *      Author: JARVIS
 */

#ifndef SRC_COMMANDS_PNEUMATICGRIPPERCOMMAND_H_
#define SRC_COMMANDS_PNEUMATICGRIPPERCOMMAND_H_

#include <Commands/CommandBase.h>
#include <Oi.h>
#include <Systems/Intake.h>

class PneumaticGripperCommand: public CommandBase {
	OI* oi;
	Intake* intake;
public:
	PneumaticGripperCommand(OI* oi, Intake* intake);
	virtual ~PneumaticGripperCommand();

	void init() override;
	void update() override;
	void finish() override;
};

#endif /* SRC_COMMANDS_PNEUMATICGRIPPERCOMMAND_H_ */
