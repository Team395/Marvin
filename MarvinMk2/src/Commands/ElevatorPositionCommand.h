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

class ElevatorPositionCommand: public CommandBase {
	Elevator* elevator;
	PIDController pidController;
	double setpoint = 0;
	Preferences* preferences = Preferences::GetInstance();

public:
	ElevatorPositionCommand(Elevator*, double, double, double);
	virtual ~ElevatorPositionCommand();

	void init();
	void update();
	void finish();
	void setSetpoint(double);
	double getSetpoint();
};

#endif /* SRC_COMMANDS_ELEVATORPOSITIONCOMMAND_H_ */
