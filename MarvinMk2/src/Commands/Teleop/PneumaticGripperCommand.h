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
#include <Systems/Elevator.h>
#include <Timer.h>

enum class ElevatorAutomaticThreshold {
	kAbove,
	kBelow
};

class PneumaticGripperCommand: public CommandBase {
	Intake* intake;
	Elevator* elevator;
	OI* oi;
	const double intakeTime = 0.5;
	const double scoreTime = 0.5;
	double timerStartedTime = -1;
	bool cubeInIntake = false;
	bool bannerSensorTripped = false;
	bool scoreTimerStarted = false;
	double sensorDelay = 0.25;

	double retainTimerPeriod = 1;
	double retainTimerDuration = 0.25;
	bool retainPeriodTimerStarted = false;
	double retainPeriodTimerStartedTime = 0;
	bool retainTimerStarted = false;
	double retainTimerStartedTime = 0;
	IntakeState intakeStatePriorToRetain = IntakeState::automatic;

	//TODO: tune this
	int kElevatorAutomaticThreshold = 10;
	ElevatorAutomaticThreshold elevatorAutomaticThresholdState = ElevatorAutomaticThreshold::kBelow;


	void updateManual(OI::RequestedClawState, double);

public:
	bool updateAutomatic(double);
	bool updateAutoscore(double);
	bool updateAutoscore();
	void updateRetain();

	PneumaticGripperCommand(Intake* intake, Elevator* elevator, OI* oi);
	virtual ~PneumaticGripperCommand();

	void init() override;
	void update() override;
	void finish() override;
	void disable() override;
};

#endif /* SRC_COMMANDS_PNEUMATICGRIPPERCOMMAND_H_ */
