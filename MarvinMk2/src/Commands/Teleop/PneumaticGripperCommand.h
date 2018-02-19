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
#include <Timer.h>

class PneumaticGripperCommand: public CommandBase {
	Intake* intake;
	OI* oi;
	const double intakeTime = 1;
	double bannerSensorTrippedTime;
	bool cubeInIntake = false;
	bool bannerSensorTripped = false;

	void updateAutomatic(int, double);
	void updateManual(int, double);

public:
	PneumaticGripperCommand(Intake* intake, OI* oi);
	virtual ~PneumaticGripperCommand();

	void init() override;
	void update() override;
	void finish() override;
};

#endif /* SRC_COMMANDS_PNEUMATICGRIPPERCOMMAND_H_ */
