/*
 * Intake.h
 *
 *  Created on: Jan 24, 2018
 *      Author: hlewi
 */

#ifndef SRC_SYSTEMS_INTAKE_H_
#define SRC_SYSTEMS_INTAKE_H_
#include <Talon.h>

#include <RobotMap.h>
#include <Systems/SystemBase.h>
#include <Solenoid.h>

class Intake : SystemBase {
	Talon leftIntake{IntakeMap::kIntakeLeft};
	Talon rightIntake{IntakeMap::kIntakeRight};
	Solenoid clawOpen{IntakeMap::kSolenoidOpen};
	Solenoid clawClose{IntakeMap::kSolenoidClose};

public:
	Intake();
	virtual ~Intake();

	void actuateClaw(bool);
	void disable();
	void driveLeft(double);
	void driveRight(double);
};

#endif /* SRC_SYSTEMS_INTAKE_H_ */
