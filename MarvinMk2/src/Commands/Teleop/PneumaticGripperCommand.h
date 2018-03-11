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
	const double scoreTime = 1;
	double timerStartedTime = 0;
	bool cubeInIntake = false;
	bool bannerSensorTripped = false;
	bool scoreTimerStarted = false;

	void updateAutomatic(double);
	void updateManual(OI::RequestedClawState, double);
	void updateAutoscore();

public:
	PneumaticGripperCommand(Intake* intake, OI* oi);
	virtual ~PneumaticGripperCommand();

	void init() override;
	void update() override;
	void finish() override;
};

#endif /* SRC_COMMANDS_PNEUMATICGRIPPERCOMMAND_H_ */
