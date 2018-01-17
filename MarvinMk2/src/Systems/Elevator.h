/*
 * Elevator.h
 *
 *  Created on: Jan 15, 2018
 *      Author: JARVIS
 */

#ifndef SRC_SYSTEMS_ELEVATOR_H_
#define SRC_SYSTEMS_ELEVATOR_H_
#include "ctre/Phoenix.h"
#include "../RobotMap.h"

class Elevator {
	WPI_TalonSRX winchController{ElevatorMap::kWinch};

public:
	Elevator();
	virtual ~Elevator();

	void driveElevator(double);
};

#endif /* SRC_SYSTEMS_ELEVATOR_H_ */
