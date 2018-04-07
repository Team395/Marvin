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
#include <Timer.h>
#include <PIDOutput.h>
#include <PIDSource.h>
#include <Systems/DrivebaseEncoderSensors.h>

class DrivebaseSensors;

struct ElevatorPresets {
	//TODO tune all
	static constexpr double kHighHeight = 43;
	static constexpr double kNormalHeight = 36.7;
	static constexpr double kLowHeight = 30.7;
	static constexpr double kSwitchHeight = 15;
	static constexpr double kBottomHeight = 0;
	static constexpr double kDeployHeight = 3.145;
	static constexpr double kErrorThreshold = 3;
};

class Elevator : SystemBase, public PIDOutput, public PIDSource {
	WPI_TalonSRX winchOneController{ElevatorMap::kWinchOne};
	WPI_TalonSRX winchTwoController{ElevatorMap::kWinchTwo};
	frc::DigitalInput topLimit{ElevatorMap::kLimitTop};
	frc::DigitalInput bottomLimit{ElevatorMap::kLimitBottom};
	frc::Timer downTimer{};
	bool driveUpLastCommand;
	double percentOutputOffset = 0.1; //TODO tune
	double minimumAcceptableOutputBelowSwitchHeight = 0;
	double minimumAcceptableOutputAboveSwitchHeight = -0.1; //TODO tune

public:

//	const double inchesPerTick = 0.00182*4096/128; //TODO check by hand
	const double inchesPerTick = 0.00182;
	const double topPosition = 44; //TODO check before sending to top
	const double bottomPosition = 0;
	double currentPosition;

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
