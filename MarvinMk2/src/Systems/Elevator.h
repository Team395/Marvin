/*
 * Elevator.h
 *
 *  Created on: Jan 15, 2018
 *      Author: JARVIS
 */

#ifndef SRC_SYSTEMS_ELEVATOR_H_
#define SRC_SYSTEMS_ELEVATOR_H_
#include <ctre/Phoenix.h>
#include <DigitalInput.h>

#include <RobotMap.h>
#include <Systems/SystemBase.h>

using ControlMode = ctre::phoenix::motorcontrol::ControlMode;

class Elevator : SystemBase {
	WPI_TalonSRX winchController{CANMap::kWinch};
	frc::DigitalInput topLimit{ElevatorMap::kLimitTop};
	frc::DigitalInput bottomLimit{ElevatorMap::kLimitBottom};
public:
	Elevator();
	virtual ~Elevator();

	bool topPressed();
	bool bottomPressed();

	void setWinchPercent(double);
	void setWinchPosition(double);
};

#endif /* SRC_SYSTEMS_ELEVATOR_H_ */
