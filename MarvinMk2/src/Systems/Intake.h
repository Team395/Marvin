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
	automatic = 0,
	manual = 1
};

class Intake : SystemBase {
	Spark leftIntake{IntakeMap::kIntakeLeft};
	Spark rightIntake{IntakeMap::kIntakeRight};
	Solenoid gripperOpen{IntakeMap::kGripperOpen};
	Solenoid gripperClose{IntakeMap::kGripperClose};
	DigitalInput backBannerSensor{IntakeMap::kBackBanner};
	IntakeState intakeState{IntakeState::automatic};

public:
	Intake();
	virtual ~Intake();

	void actuateClaw(bool);
	bool getClawOpen();
	void driveLeft(double);
	void driveRight(double);
	bool getBackBanner();

	void setState(IntakeState);
	IntakeState getState();
};

#endif /* SRC_SYSTEMS_INTAKE_H_ */
