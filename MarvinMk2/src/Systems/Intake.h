/*
 * Intake.h
 *
 *  Created on: Jan 24, 2018
 *      Author: hlewi
 */

#ifndef SRC_SYSTEMS_INTAKE_H_
#define SRC_SYSTEMS_INTAKE_H_
#include <Spark.h>

#include <RobotMap.h>
#include <Systems/SystemBase.h>
#include <Solenoid.h>
#include <DigitalInput.h>

enum class IntakeState{
	automatic,
	manual,
	autoscore,
	retain
};

enum class GripperState{
	open,
	close
};

class Intake : SystemBase {
	Spark leftIntake{IntakeMap::kIntakeLeft};
	Spark rightIntake{IntakeMap::kIntakeRight};
	Solenoid leftGripperOpen{IntakeMap::kLeftGripperOpen};
	Solenoid leftGripperClose{IntakeMap::kLeftGripperClose};
	Solenoid rightGripperOpen{IntakeMap::kRightGripperOpen};
	Solenoid rightGripperClose{IntakeMap::kRightGripperClose};
	DigitalInput backBannerSensor{IntakeMap::kBackBanner};
	IntakeState intakeState{IntakeState::automatic};
	GripperState gripperState{GripperState::open};

public:
	Intake();
	virtual ~Intake();

	void actuateClaw(bool);
	void setClawOpen(bool);
	void driveLeft(double);
	void driveRight(double);
	bool getBackBanner();
	bool getClawOpen();

	void setState(IntakeState);
	IntakeState getState();

	void setGripperState(GripperState);
	GripperState getGripperState();
};

#endif /* SRC_SYSTEMS_INTAKE_H_ */
