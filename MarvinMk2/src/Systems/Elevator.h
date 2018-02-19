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
#include <Timer.h>
#include <PIDOutput.h>
#include <PIDSource.h>

class DrivebaseSensors;

class Elevator : SystemBase, PIDOutput, PIDSource {
	WPI_TalonSRX winchController{ElevatorMap::kWinch};
	frc::DigitalInput topLimit{ElevatorMap::kLimitTop};
	frc::DigitalInput bottomLimit{ElevatorMap::kLimitBottom};
	frc::Timer downTimer{};
	bool driveUpLastCommand;
	double percentOutputOffset = 0;

public:
	constexpr double inchesPerTick = 0;
	constexpr double topPosition = 40;
	constexpr double bottomPosition = 0;

	Elevator();
	virtual ~Elevator();

	void driveWinch(double);
	void getEncoder();

	double getOffset();
	void setOffset(double);

	double PIDGet();
	void PIDWrite(double);

	bool topPressed();
	bool bottomPressed();

	void homeEncoder();
};

#endif /* SRC_SYSTEMS_ELEVATOR_H_ */
