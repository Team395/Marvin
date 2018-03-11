/*
 * InstrumentCommand.h
 *
 *  Created on: Mar 11, 2018
 *      Author: JARVIS
 */

#ifndef SRC_COMMANDS_INSTRUMENTCOMMAND_H_
#define SRC_COMMANDS_INSTRUMENTCOMMAND_H_

#include <Commands/CommandBase.h>
#include <OI.h>

enum ElevatorStates{
	kSwitch = 0
	, kScaleLow
	, kScaleNormal
	, kScaleHigh
	, kDrivingUp
	, kDrivingDown
	, kHolding
	, kZero
};

enum IntakeStates{
	kAutomatic,
	kManual,
	kAutoscore
};

class InstrumentCommand: public CommandBase {
	bool intakeOpen = true;
	bool intakeOut = false;
	bool intakeIn = false;
	ElevatorStates elevatorState = kZero;
	IntakeStates intakeState = kAutomatic;
	IntakeStates lastIntakeState = kAutomatic;

	bool scoreTimerStarted = false;
	double scoreTimerStartedTime = 0;

	OI* oi;
public:
	InstrumentCommand(OI* oi);
	virtual ~InstrumentCommand();

	void init() override;
	void update() override;
	void finish() override;
};

#endif /* SRC_COMMANDS_INSTRUMENTCOMMAND_H_ */
