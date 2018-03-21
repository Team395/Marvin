/*
 * ElevatorPositionCommand.h
 *
 *  Created on: Feb 19, 2018
 *      Author: JARVIS
 */

#ifndef SRC_COMMANDS_ELEVATORPOSITIONCOMMAND_H_
#define SRC_COMMANDS_ELEVATORPOSITIONCOMMAND_H_

#include <Commands/CommandBase.h>
#include <PIDController.h>
#include <Systems/Elevator.h>
#include <SmartDashboard/SmartDashboard.h>
#include <Preferences.h>
#include <cmath>

class ElevatorPositionCommand: public CommandBase {
	Elevator* elevator;
	PIDController pidController;
	double setpoint = 0;
	Preferences* preferences = Preferences::GetInstance();

public:
	ElevatorPositionCommand(Elevator*, double, double, double);
	virtual ~ElevatorPositionCommand();

	void init() override;
	void update() override;
	void finish() override;
	void disable() override;
	void setSetpoint(double);
	double getSetpoint();
	double getAbsError();
};

#endif /* SRC_COMMANDS_ELEVATORPOSITIONCOMMAND_H_ */
