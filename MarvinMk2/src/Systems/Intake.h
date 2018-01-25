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

class Intake {
	Talon leftIntake{IntakeMap::kIntakeLeft};
	Talon rightIntake{IntakeMap::kIntakeRight};

public : SystemBase:
	Intake();
	virtual ~Intake();

	void driveLeft(double);
	void driveRight(double);
};

#endif /* SRC_SYSTEMS_INTAKE_H_ */
