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
#include <Systems/Intake.h>

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
	IntakeState intakeState = IntakeState::automatic;
	IntakeState lastIntakeState = IntakeState::automatic;

	bool scoreTimerStarted = false;
	double scoreTimerStartedTime = 0;

	OI* oi;
	Intake* intake;
public:
	InstrumentCommand(OI* oi, Intake* intake);
	virtual ~InstrumentCommand();

	void init() override;
	void update() override;
	void finish() override;
};

#endif /* SRC_COMMANDS_INSTRUMENTCOMMAND_H_ */
