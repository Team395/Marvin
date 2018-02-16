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
#include <Systems/DrivebaseSensors.h>
#include <Systems/SystemBase.h>

class DrivebaseSensors;

class Elevator : SystemBase {
	WPI_TalonSRX winchController{ElevatorMap::kWinch};
	//bfrc::DigitalInput topLimit{ElevatorMap::kLimitTop};
	//frc::DigitalInput bottomLimit{ElevatorMap::kLimitBottom};

public:
	Elevator();
	virtual ~Elevator();

	void driveWinch(double);

	//bool topPressed();
	//bool bottomPressed();
};

#endif /* SRC_SYSTEMS_ELEVATOR_H_ */
